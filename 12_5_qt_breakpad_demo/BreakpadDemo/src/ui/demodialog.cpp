#include "demodialog.h"
#include "ui_demodialog.h"

DemoDialog::DemoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DemoDialog)
{
    ui->setupUi(this);
}

DemoDialog::~DemoDialog()
{
    delete ui;
}

void crash() { volatile int* a = (int*)(NULL); *a = 1; }

void DemoDialog::on_crashButton_clicked()
{
     crash();
}


