

#ifndef PROTOCOLSETTINGMANAGER_H
#define PROTOCOLSETTINGMANAGER_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QThread>
#include <QDateTime>
#include <QMutex>

#include "workmanager.h"
#include "command.h"
#include "comm_interface.h"


class ProtocolManager : public QThread
{
    Q_OBJECT
private:
    ProtocolManager();
    ~ProtocolManager();
public:

    enum ProtocolError {
        CrcCheckError,
        ReTry3TimesError
    };
    static ProtocolManager* GetInstance();

    void SetProtocolComm(CommInterface* comm);
    void AddWork(QByteArray &pkg);
    int GetCachedWorkCount();

    //comm
    void CommInit();
    bool CommOpen();
    void CommClose();
    bool CommIsOpen();

signals:
    //std signals
    void onCommInitCallback();
    void onProtocolError(int error_type, QString error_string);
    void onDispatchPackage(quint8 *pkg, int len);


private:
    static ProtocolManager *instance_p;

    //connection
    qint64 Send(const QByteArray &data);
    void onRecv(QByteArray &data, void *extra_data);

    //process
    void Process(quint8 b);
    void ProcessMetaPkg(quint8 *pkg, int len);
    void CleanWorkList();
    void ReSendPkg();
    void ProcessTimeOutError();

    //thread
    void run();
    void StartThread();
    void StopThread();
    bool IsThreadWorking();

    //thread-switch-functions
    void doSend();
signals:
    void callSend();

private:
      CommInterface *comm_p;
      bool is_sending_;

      WorkManager wm_;
      bool wait_response_;
      Work *current_work_p;

      //package param
      bool package_on_;
      const static int CACHE_LENGTH = 1024 * 5;
      quint8 cache[CACHE_LENGTH];
      int pos;

      QMutex mutex_;
      qint64 start_work_secs_;
      const qint64 TIME_OUT_SECONDS = 16;

};

#endif // PROTOCOLSETTINGMANAGER_H
