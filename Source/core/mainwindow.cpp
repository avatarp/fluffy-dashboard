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
    std::vector<QBluetoothDeviceInfo> bluetoothDevices = bluetoothProvider.GetAvailableDevices();
    QString text("Total bluetooth devices found: ");
    text+=QString::number(bluetoothDevices.size());
    ui->textBrowser->append(text);
    for(auto& bluetoothDevice :bluetoothDevices)
    {
       ui->textBrowser->append(bluetoothDevice.name());
       ui->textBrowser->append(bluetoothDevice.address().toString());
       ui->textBrowser->append("\n");
    }
    std::vector<Obd::Device> usbDevices = usbProvider.GetAvailableDevices();
    text = "Total usb devices found: ";
    text+=QString::number(usbDevices.size());
    ui->textBrowser->append(text);
    for(auto& usbDevice :usbDevices)
    {
       ui->textBrowser->append(QString::fromStdString(usbDevice.GetDeviceFilePath()));
       ui->textBrowser->append(QString::fromStdString(usbDevice.GetDescription()));
       ui->textBrowser->append("\n");
    }
    //devices = bluetoothDevices;
    //devices.insert(devices.end(),usbDevices.begin(),usbDevices.end());


    Elm327Engine engine;
}



MainWindow::~MainWindow()
{
    delete ui;
}

