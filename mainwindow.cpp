#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cpimageutil.h"
#include <QDebug>
#include <QFileDialog>

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

void MainWindow::importClicked() {
    QString file = QFileDialog::getOpenFileName(this,
                tr("select_csv_file"), QDir::home().path(), "文件格式 (*.txt *.csv)");
        qDebug() << "selected file: " << file;

    if (file.length() > 0) {
        QFile inputFile(file);
        if (inputFile.open(QIODevice::ReadOnly)) {
           QTextStream in(&inputFile);
           while (!in.atEnd()) {
              QString line = in.readLine();
              qDebug() << line;
              ui->inputTextEdit->append(line);
           }
           inputFile.close();
        }
    }
}
void MainWindow::encodeClicked() {
    QString input = ui->inputTextEdit->toPlainText();
    qDebug() << "input: " << input;

    int encoding= ui->qrcodeCharacterSetComboBox->currentIndex();
    int margin = ui->qrcodeMarginLineEdit->text().toInt();
    int ecc = ui->qrcodeEccComboBox->currentIndex();
    int version = ui->qrcodeVersionComboBox->currentIndex();
    int maskPattern = ui->qrcodeMaskPatternComboBox->currentIndex();
    int sizeFactor = ui->qrcodeSizeFactorLineEdit->text().toInt();


    // QString.split(QRegExp("\n|\r\n|\r"));
    QStringList inputLines = input.split(QRegExp("\n|\r\n|\r"));

    int i = 0;
    for ( const auto& line : inputLines) {
        QImage barcode = cpBarcode.encodeQrcode(line, encoding, margin, ecc, version, maskPattern);

        barcode = CPImageUtil::resizeQImage(barcode, QSize(barcode.width()*sizeFactor, barcode.height()*sizeFactor));
        ui->resultLabel->setText(QString::asprintf("size: %d-%d", barcode.width(), barcode.height()));
        barcode.save(QString::asprintf("/Users/paipeng/Downloads/barcode_%05d.bmp", i), "bmp");

        if (inputLines.last() == line) {
            ui->barcodeLabel->setPixmap(QPixmap::fromImage(CPImageUtil::resizeQImage(barcode, ui->barcodeLabel->size())));
        }
        i++;
    }


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

    ui->qrcodeSizeFactorLineEdit->setValidator(new QIntValidator(ui->qrcodeSizeFactorLineEdit));
    ui->qrcodeSizeFactorLineEdit->setText("1");
}
