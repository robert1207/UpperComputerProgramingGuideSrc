#ifndef CRASHREPORTDIALOG_H
#define CRASHREPORTDIALOG_H

#include <QDialog>

namespace Ui {
class CrashReportDialog;
}

class CrashReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CrashReportDialog(QWidget *parent = nullptr);
    ~CrashReportDialog();

private slots:
    void on_pushButtonOk_clicked();

private:
    Ui::CrashReportDialog *ui;
};

#endif // CRASHREPORTDIALOG_H
