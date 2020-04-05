#ifndef DEMODIALOG_H
#define DEMODIALOG_H

#include <QDialog>

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
    Ui::DemoDialog *ui;
};
#endif // DEMODIALOG_H
