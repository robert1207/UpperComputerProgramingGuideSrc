

#ifndef PROTOCOLSETTINGMANAGER_H
#define PROTOCOLSETTINGMANAGER_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QThread>
#include <QDateTime>

#include "workmanager.h"
#include "../net/netmanager.h"
#include "command.h"

namespace HYKT {


class ProtocolManager : public QThread
{
    Q_OBJECT
private:
    ProtocolManager();
    ~ProtocolManager();
public:
    static ProtocolManager* GetInstance();

    int Connect(QString ip, quint16 port);
    void Disconnect();
    bool IsConnected();

    void AddWork(QByteArray &pkg);

signals:
    void onConnectionError(QString msg);
    void onDisconnect();

   //user defined command
    void onGetMachinetemperature(int value);
    void onReportValue(int value);

private:
    static ProtocolManager *instance_p;
    //connection
    int Send(const QByteArray &data);
    void onRecv(QByteArray *data, QString ip, quint16 port);
    void onError(int error_code, QString extra_error_info);
    void doDisconnect();

    //process
    void Process(quint8 b);
    void ProcessMetaPkg(quint8 *pkg, int len);
    void CleanWorkList();
    void DispatchPackage(quint8 *pkg, int len);
    void ReSendPkg();

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
      NetManager* udp_manager_p;
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
      const qint64 TIME_OUT_SECONDS = 4;

      QThread *helper_thread_p;

};

} //namespace HYKT

#endif // PROTOCOLSETTINGMANAGER_H
