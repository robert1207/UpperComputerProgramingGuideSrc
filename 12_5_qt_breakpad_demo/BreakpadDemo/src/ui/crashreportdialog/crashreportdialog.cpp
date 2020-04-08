#include "crashreportdialog.h"
#include "ui_crashreportdialog.h"

#include <QtDebug>

CrashReportDialog::CrashReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CrashReportDialog)
{
    ui->setupUi(this);
    //remove question mark
    Qt::WindowFlags flags= this->windowFlags();
    setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);

}

CrashReportDialog::~CrashReportDialog()
{
    delete ui;
}


void CrashReportDialog::on_pushButtonOk_clicked()
{
    this->accept();
}
