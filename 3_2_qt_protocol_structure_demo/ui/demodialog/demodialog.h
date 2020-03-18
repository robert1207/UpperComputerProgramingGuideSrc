#ifndef DEMODIALOG_H
#define DEMODIALOG_H

#include <QDialog>

#include "../../protocol/protocolmanager.h"
using namespace HYKT;

QT_BEGIN_NAMESPACE
namespace Ui { class DemoDialog; }
QT_END_NAMESPACE

class DemoDialog : public QDialog
{
    Q_OBJECT

public:
    DemoDialog(QWidget *parent = nullptr);
    ~DemoDialog();

private:
    void onConnectionError(QString msg);
    void onDisconnect();
    void onGetMachinetemperature(int value);
    void onReportValue(int value);

private slots:
    void on_pushButtonGettemperature_clicked();

    void on_pushButtonConnectDevice_clicked();

    void on_pushButtonSetValue_clicked();

private:
    Ui::DemoDialog *ui;

    ProtocolManager *protocol_manager_p;
};
#endif // DEMODIALOG_H
