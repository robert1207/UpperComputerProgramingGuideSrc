
#include "deviceconnectdialog.h"
#include "ui_deviceconnectdialog.h"

#include <QMessageBox>

#include "my_log.h"

DeviceConnectDialog::DeviceConnectDialog(QWidget *parent)
    :QDialog(parent),
    ui(new Ui::DeviceConnectDialog)
{
    ui->setupUi(this);

    InitSearchedDeviceList();
    is_searching_device_ = false;

    finging_device_manager_p = new ProtocolFindingDeviceManager();

    connect(finging_device_manager_p, &ProtocolFindingDeviceManager::onFoundDevice,
            this, &DeviceConnectDialog::onFoundDevice);
    connect(finging_device_manager_p,  &ProtocolFindingDeviceManager::onFoundDeviceError,
            this, &DeviceConnectDialog::onFoundDeviceError);

}

DeviceConnectDialog::~DeviceConnectDialog()
{
    delete ui;
    delete finging_device_manager_p;
}

/*************************** searched device list *********************************/
void DeviceConnectDialog::InitSearchedDeviceList() {
    connect(ui->listWidgetSearchedDeviceList, &QListWidget::itemClicked,
            this, &DeviceConnectDialog::onSearchedDeviceItemClicked);

    ui->listWidgetSearchedDeviceList->setSelectionMode(QAbstractItemView:: SingleSelection);
}

void DeviceConnectDialog::AddSearchedDevices(QString ip, QString id) {

    QListWidgetItem *item = new QListWidgetItem(ui->listWidgetSearchedDeviceList,0);
    item->setSizeHint(QSize(100,50));

    QWidget *list_item_bg = new QWidget(ui->listWidgetSearchedDeviceList);


    QHBoxLayout *main_h_layout = new QHBoxLayout(list_item_bg);
    main_h_layout->setContentsMargins(8, 6, 8,6);


    //pushButton->cl
    QVBoxLayout *info_v_layout = new QVBoxLayout();
    info_v_layout->setSpacing(0);
    QLabel *label_id = new QLabel();
    label_id->setText("SN: "+id);

    QLabel *label_ip = new QLabel();
    label_ip->setText("IP: "+ip);

    info_v_layout->addWidget(label_id);
    info_v_layout->addWidget(label_ip);

   // main_h_layout->addWidget(img);
    main_h_layout->addLayout(info_v_layout);

    list_item_bg->setLayout(main_h_layout);
    ui->listWidgetSearchedDeviceList->setItemWidget(item, list_item_bg);
    ui->listWidgetSearchedDeviceList->setCurrentItem(item);
}

void DeviceConnectDialog::ClearSearchedDevices() {
    ui->listWidgetSearchedDeviceList->clear();
}

void DeviceConnectDialog::onSearchedDeviceItemClicked(QListWidgetItem *item) {
    Q_UNUSED(item)

     int current_row = ui->listWidgetSearchedDeviceList->currentRow();

}

/********************* presenter callback***********************/
void DeviceConnectDialog::UpdateSearchedDevices(QList<DeviceInfo> device_info_list) {
   // I << "UpdateSearchedDevices";
    device_info_list_ = device_info_list;
     ClearSearchedDevices();
     for(int a = 0; a < device_info_list.count(); a ++) {
         AddSearchedDevices(device_info_list[a].ip, device_info_list[a].sn);
     }
}

void DeviceConnectDialog::onFoundDevice(QList<DeviceInfo> device_list) {
    D << "finding device ";
    UpdateSearchedDevices(device_list);
}

void DeviceConnectDialog::onFoundDeviceError(QString msg) {
    Q_UNUSED(msg)

     E << "DeviceConnectDialog::onFoundDeviceError = " << msg;


    if(is_searching_device_) {
        on_pushButtonSearch_clicked();
    }

    QMessageBox::information(this,"Error", "Searching Device Error !");
}

void DeviceConnectDialog::on_pushButtonSearch_clicked()
{
    if(is_searching_device_ == false) {
        ui->pushButtonSearch->setText(QApplication::translate("DeviceConnectDialog", "Stop Search"));
        is_searching_device_ = true;
        finging_device_manager_p->StartFindingDevice();
    } else {
        ui->pushButtonSearch->setText(QApplication::translate("DeviceConnectDialog", "Start Search"));
        is_searching_device_ = false;
        finging_device_manager_p->StopFindingDevice();
    }
}

void DeviceConnectDialog::on_pushButtonConnect_clicked()
{
    QList<QListWidgetItem*> list = ui->listWidgetSearchedDeviceList->selectedItems();

    if(is_searching_device_) {
        QMessageBox::information(this, "Title", "Please stop searching first !");
        return;
    }

    if(list.count() <= 0) {
        QMessageBox::information(this, "Title", "Please select a device to connect !");
        return;
    } else if(list.count() > 1) {
        QMessageBox::information(this, "Title", "Up to one device can be selected !");
        return;
    }

    int current_row = ui->listWidgetSearchedDeviceList->currentRow();

    DeviceInfo selected_device_info = device_info_list_.at(current_row);

    QMessageBox::information(this, "Title", "Using ip is :"+ selected_device_info.ip);
}

void DeviceConnectDialog::on_pushButtonClean_clicked()
{
    ClearSearchedDevices();
}


