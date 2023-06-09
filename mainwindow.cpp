#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cpimageutil.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::encodeClicked() {
    QImage barcode = cpBarcode.encode("test");
    barcode.save("/Users/paipeng/Downloads/barcode.bmp", "bmp");
    ui->barcodeLabel->setPixmap(QPixmap::fromImage(CPImageUtil::resizeQImage(barcode, ui->barcodeLabel->size())));
}

