

#include "protocolmanager.h"
#include <QString>
#include <QDebug>

ProtocolManager *ProtocolManager::instance_p = nullptr;

ProtocolManager::ProtocolManager()
{
    is_sending_ = false;
    wait_response_ = false;
    pos = 0;
    package_on_ = false;
    comm_p = nullptr;

    //be note that caller-thread and creater-thread must be one thread for object of this class


    //for thread switch
    //qDebug() << "ProtocolManager::ProtocolManager connect ";
    connect(this, &ProtocolManager::callSend, this, &ProtocolManager::doSend);
}

ProtocolManager::~ProtocolManager()
{
    //qDebug() << "ProtocolManager::~ProtocolManager dis connect ";
    disconnect(this, &ProtocolManager::callSend, this, &ProtocolManager::doSend);
}

ProtocolManager* ProtocolManager::GetInstance() {
    if (instance_p == nullptr) {
        instance_p = new ProtocolManager();
    }
    return instance_p;
}



/******************************* connection *****************************/


qint64 ProtocolManager::Send(const QByteArray &data) {
   // qDebug() << "**************    ProtocolManager::Send";
    return comm_p->Send(data);
}

void ProtocolManager::onRecv(QByteArray &data, void *extra_data) {
    Q_UNUSED(extra_data)

  //  qDebug() << "ProtocolManager::onRecv = " << data;

    for(int a = 0; a < data.length(); a ++) {
        Process(static_cast<quint8>(data.at(a)));
    }
}

/******************************* thread *****************************/

void ProtocolManager::StartThread() {
    is_sending_ = true;
    start();
}

void ProtocolManager::StopThread() {
    is_sending_ = false;
}

bool ProtocolManager::IsThreadWorking() {
    return is_sending_;
}

void ProtocolManager::run() {
    while(is_sending_) {
        current_work_p = wm_.GetCurrentWork();
        if (current_work_p != nullptr) {
            wait_response_ = true;
            //qDebug() << "emit callSend();";
            emit callSend();


            start_work_secs_ = QDateTime::currentSecsSinceEpoch();

        } else { //end of all work
            StopThread();
            wait_response_ = false;
        }

        while (wait_response_) {
             msleep(10);
             //call re-send when timeout
            qint64 current_secs = QDateTime::currentSecsSinceEpoch();
            if(current_secs - start_work_secs_ > TIME_OUT_SECONDS) {
                ReSendPkg();
            }

        }
    }
}

void ProtocolManager::doSend() {
    //qDebug() << "ProtocolManager::doSend";
    Send(current_work_p->data);
}

/********************** work process **************************/

void ProtocolManager::AddWork(QByteArray &pkg) {
   // qDebug() << "ProtocolManager::AddWork";
    wm_.AddWork(pkg);
     if (IsThreadWorking() == false) {
         StartThread();
     }
}

int ProtocolManager::GetCachedWorkCount() {
    return wm_.GetWorkCount();
}

void ProtocolManager::CleanWorkList() {
    wm_.CleanWorkList();
}

void ProtocolManager::Process(quint8 b) {
    if (package_on_ == true)
    {
        if (pos > CACHE_LENGTH) {
            package_on_ = false;
            pos = 0;
            return;
        }

        cache[pos++] = b;

        if (pos > 4 &&
            cache[pos - 4] == tail[0] &&    //a pkg is finished
            cache[pos - 3] == tail[1] &&
            cache[pos - 2] == tail[2] &&
            cache[pos - 1] == tail[3] &&
            cache[sizeof (head)] + sizeof (head) + sizeof (tail)  == pos //check pkg len
                ) {
            package_on_ = false;

            int skip_head_and_pkg_len = 2;
            int skip_tail = 4;
            quint8* pkg = &cache[skip_head_and_pkg_len]; //remove head and pkg-len
            int pkg_len = pos - skip_head_and_pkg_len - skip_tail;//skip index of tail byte

            if (Crc::CheckCRC(pkg, pkg_len) == true) {
                ProcessMetaPkg(pkg, pkg_len-2);//-2 : remove crc byte
            } else {
                CleanWorkList();
                emit onProtocolError(CrcCheckError, "crc check error");
            }
        }
    } else if (package_on_ == false && b == head[0]) { //start a pkg
        package_on_ = true;
        pos = 0;
        cache[pos++] = b;
    }
}

//for timer send a false pkg
void ProtocolManager::ReSendPkg() {
    //qDebug() << "ProtocolManager::ReSendPkg";
     ProcessMetaPkg(nullptr, 0);
}

//thread and recv-callback are will call this functinn ,so this function need a lock
void ProtocolManager::ProcessMetaPkg(quint8 *pkg, int len) {
    mutex_.lock();

    //根据指令类型码判断，如果是下位机主动反馈指令，在这里拦截判断
    if(pkg != nullptr && Command::IsCommandIsReportingType(pkg)) {
        emit onDispatchPackage(pkg, len);
        mutex_.unlock();
        return;
    }

    if (wait_response_ == false) {
        mutex_.unlock();
        return;
    }

   // qDebug() << "recv a package";

    //检验下位机对上位机命令的反馈指令是否正确
    if (pkg != nullptr && current_work_p->CheckResponse(pkg) == true) {
      //  qDebug() << "finished a package";
        wm_.FinishAWork();
        emit onDispatchPackage(pkg, len);//without head, pack_len, crc, and tail
    } else {
        ProcessTimeOutError();
    }
    wait_response_ = false;

    mutex_.unlock();
}

void ProtocolManager::ProcessTimeOutError() {
    if (current_work_p != nullptr)
    {
        current_work_p->failed_times++;
        if (current_work_p->failed_times >= 3)
        {
            CleanWorkList();
            StopThread();
            wait_response_ = false;
           // Disconnect();
            emit onProtocolError(ReTry3TimesError, "retry 3 times error");
        }
    }
}

/*
//对于接收下位反馈给上位机数据的指令，在此函数中获取数据
void ProtocolManager::DispatchPackage(quint8 *pkg, int len) {
    if (len < 2) return;

    if(Command::IsCommandReportValue(pkg))  {
        Send(*Command::ResponseForReportValue()); //give response immediately
        emit onReportValue(Command::GetReportValue(pkg, len));
        //wm_.InsertWorkAtHead(*Command::ResponseForReportValue());
    }

    //根据不同指令，调用对应的处理函数，并调用其回调函数，如果有必要的时候
    if(Command::IsCommandGetMachinetemperature(pkg)) {
        emit onGetMachinetemperature(Command::GetValueOfGetMachinetemperature(pkg, len));
    }
}*/

/********************** comm **************************/
//为了避免以下报错，因此为了实现 通信设备实例 和此 协议处理模块能 相互解耦。因此这里
//设计了这个 设备初始化回调函数
//QObject: Cannot create children for a parent that is in a different thread.

void ProtocolManager::SetProtocolComm(CommInterface* comm) {
    comm_p = comm;
    disconnect(comm_p, &CommInterface::onRecv, this, &ProtocolManager::onRecv);
    connect(comm_p, &CommInterface::onRecv, this, &ProtocolManager::onRecv);
}

void ProtocolManager::CommInit() {
    emit onCommInitCallback();
}

bool ProtocolManager::CommOpen() {
    return comm_p->Open();
}

void ProtocolManager::CommClose() {
    if(comm_p == nullptr) return;
    comm_p->Close();
}

bool ProtocolManager::CommIsOpen() {
    return comm_p->IsOpen();
}

