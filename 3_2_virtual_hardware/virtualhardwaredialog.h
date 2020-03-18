#ifndef VIRTUALHARDWAREDIALOG_H
#define VIRTUALHARDWAREDIALOG_H

#include <QDialog>
#include "./net/netmanager.h"
using namespace HYKT;

QT_BEGIN_NAMESPACE
namespace Ui { class VirtualHardwareDialog; }
QT_END_NAMESPACE

class VirtualHardwareDialog : public QDialog
{
    Q_OBJECT

public:
    VirtualHardwareDialog(QWidget *parent = nullptr);
    ~VirtualHardwareDialog();

private slots:
    void on_pushButtonStartService_clicked();

    void on_pushButtonReport_clicked();

private:
    void SearchingDeviceRecv(QByteArray *data, const QString ip, const quint16 port);
    void SearchingDeviceError(int error_code, QString extra_error_info);
    void CommunicationRecv(QByteArray *data, const QString ip, const quint16 port);
    void CommunicationError(int error_code, QString extra_error_info);


private:
    Ui::VirtualHardwareDialog *ui;

    NetManager *net_udp_communication_service_p;
    NetManager *net_udp_searching_device_service_p;


};
#endif // VIRTUALHARDWAREDIALOG_H
