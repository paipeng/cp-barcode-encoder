#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cpbarcode.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void encodeClicked();

private:
    void initTab();
    void initQRCodeTab();

private:
    Ui::MainWindow *ui;
    CPBarcode cpBarcode;
};
#endif // MAINWINDOW_H
