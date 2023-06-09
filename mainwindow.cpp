#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cpimageutil.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initTab();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::encodeClicked() {
    QString input = ui->inputTextEdit->toPlainText();
    qDebug() << "input: " << input;
    QImage barcode = cpBarcode.encode(input);
    barcode.save("/Users/paipeng/Downloads/barcode.bmp", "bmp");
    ui->barcodeLabel->setPixmap(QPixmap::fromImage(CPImageUtil::resizeQImage(barcode, ui->barcodeLabel->size())));
}

void MainWindow::initTab() {
    initQRCodeTab();

}
void MainWindow::initQRCodeTab() {
    // version
    ui->qrcodeVersionComboBox->clear(); //清除列表
    for (int i=0;i<=40;i++) {
        if (i == 0) {
            ui->qrcodeVersionComboBox->addItem("自动");
        } else {
            ui->qrcodeVersionComboBox->addItem(QString::asprintf("Version %d",i));
        }
    }
    ui->qrcodeEccComboBox->clear();
    ui->qrcodeEccComboBox->addItem("Low (7%)");
    ui->qrcodeEccComboBox->addItem("Medium (15%)");
    ui->qrcodeEccComboBox->addItem("Quality (25%)");
    ui->qrcodeEccComboBox->addItem("High (30%)");

    ui->qrcodeEccComboBox->setCurrentIndex(3);
    //ui->qrcodeVersionComboBox->addItem(icon,QString::asprintf("Item %d",i)); //带图标

    ui->qrcodeMaskPatternComboBox->clear();
    for (int i=0;i<=8;i++) {
        if (i == 8) {
            ui->qrcodeMaskPatternComboBox->addItem("自动");
        } else {
            ui->qrcodeMaskPatternComboBox->addItem(QString::asprintf("Pattern %d",i));
        }
    }
    ui->qrcodeMaskPatternComboBox->setCurrentIndex(8);

    ui->qrcodeMarginLineEdit->setValidator(new QIntValidator(ui->qrcodeMarginLineEdit));
    ui->qrcodeMarginLineEdit->setText("0");


    ui->qrcodeCharacterSetComboBox->clear();


    QStringList characterSets = cpBarcode.getCharacterSets();

    for ( const auto& i : characterSets  ) {
        ui->qrcodeCharacterSetComboBox->addItem(i);
    }

    ui->qrcodeEccComboBox->addItem("Low (7%)");
    ui->qrcodeEccComboBox->addItem("Medium (15%)");
    ui->qrcodeEccComboBox->addItem("Quality (25%)");
    ui->qrcodeEccComboBox->addItem("High (30%)");

}
