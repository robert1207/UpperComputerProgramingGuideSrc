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


private slots:
    void on_crashButton_clicked();

private:
    void MakeACrash();


private:
    Ui::DemoDialog *ui;
};
#endif // DEMODIALOG_H
