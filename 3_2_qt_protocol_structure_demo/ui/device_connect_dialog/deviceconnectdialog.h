

#ifndef DEVICECONNECTDIALOG_H
#define DEVICECONNECTDIALOG_H


#include <QDialog>
#include <QListWidgetItem>


#include <QStandardItemModel>
#include <QStandardItem>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>

//#include "my_log.h"
#include "../../device_finding/deviceinfo.h"
#include "../../device_finding/findingdevicemanager.h"

#include "../../protocol/protocolmanager.h"

using namespace HYKT;

namespace Ui {
class DeviceConnectDialog;
}

class DeviceConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceConnectDialog(QWidget *parent = nullptr);
    ~DeviceConnectDialog() override;

private slots:
    void on_pushButtonSearch_clicked();
    void on_pushButtonClean_clicked();
    void on_pushButtonConnect_clicked();


private:
    //searched device
    void AddSearchedDevices(QString ip, QString id);
    void ClearSearchedDevices();
    void InitSearchedDeviceList();
    void onSearchedDeviceListItemCloseBtnClicked(int index);
    void onSearchedDeviceItemClicked(QListWidgetItem *item);

    void UpdateSearchedDevices(QList<DeviceInfo> device_list);

    void onConnectionError(QString msg);

private slots:
    void onFoundDevice(QList<DeviceInfo> device_list);//refresh and emit this signal every 10s
    void onFoundDeviceError(QString msg);

private:
    Ui::DeviceConnectDialog *ui;

    FindingDeviceManager *finging_device_manager_p;

    bool is_searching_device_;
  //  int selected_searched_device_index_;
    QList<DeviceInfo> device_info_list_;

    ProtocolManager *protocol_manager_p;
};

#endif // DEVICECONNECTDIALOG_H
