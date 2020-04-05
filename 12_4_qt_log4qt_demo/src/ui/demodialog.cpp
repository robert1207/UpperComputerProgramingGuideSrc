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

