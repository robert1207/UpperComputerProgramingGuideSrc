#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    I << "MainWindow";
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    I << "~MainWindow";
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    I << "test button click";
}
