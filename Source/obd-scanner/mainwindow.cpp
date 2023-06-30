#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    Obd::BluetoothProvider bluetoothProvider;
    Obd::UsbSerialProvider usbProvider;
    bluetoothProvider.StartScan();
    sleep(1);
    bluetoothProvider.StopScan();
    std::vector<QBluetoothDeviceInfo> bluetoothDevices = bluetoothProvider.GetAvailableDevicesInfo();

    QString text("Total bluetooth devices found: ");
    text+=QString::number(bluetoothDevices.size());
    ui->logsTextBrowser->append(text);

    for(auto& bluetoothDevice :bluetoothDevices)
    {
        ui->logsTextBrowser->append(bluetoothDevice.name());
        ui->logsTextBrowser->append(bluetoothDevice.address().toString());
        ui->logsTextBrowser->append("\n");
    }

    std::vector<Obd::Device> usbDevices = usbProvider.GetAvailableDevices();

    text = "Total usb devices found: ";
    text+=QString::number(usbDevices.size());
    ui->logsTextBrowser->append(text);
    for(auto& usbDevice :usbDevices)
    {
        ui->logsTextBrowser->append(QString::fromStdString(usbDevice.GetDeviceFilePath()));
        ui->logsTextBrowser->append(QString::fromStdString(usbDevice.GetDescription()));
        ui->logsTextBrowser->append("\n");
    }

    //devices = bluetoothDevices;
    //devices.insert(devices.end(),usbDevices.begin(),usbDevices.end());


    //Elm327Engine engine;

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LiveDataButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(pages::liveData);
}

void MainWindow::on_FreezeFrameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(pages::freezeFrame);
}

void MainWindow::on_DtcButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(pages::dtc);
}

void MainWindow::on_TestResultButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(pages::testResults);
}

void MainWindow::on_VehicleInfoButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(pages::vehicleInfo);
}

void MainWindow::on_carDataBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(pages::mainPage);
}

void MainWindow::on_freezeFrameBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(pages::mainPage);
}

void MainWindow::on_dtcBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(pages::mainPage);
}

void MainWindow::on_testResultsBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(pages::mainPage);
}

void MainWindow::on_vInfoBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(pages::mainPage);
}
