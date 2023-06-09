#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage barcode = cpBarcode.encode("test");
    barcode.save("/Users/paipeng/Downloads/barcode.bmp", "bmp");
}

MainWindow::~MainWindow()
{
    delete ui;
}

