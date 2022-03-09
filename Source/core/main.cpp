#include <QApplication>
#include <iostream>
#include "parameters-engine/ELM327/elm327-engine.h"
#include "parameters-engine/bluetooth-provider.h"
#include "parameters-engine/usb-serial-provider.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
#if __cplusplus >= 202002L
    // C++20 (and later) code
    std::cout << "C++20 (and later)" << std::endl;
#endif
    std::cout<<__cplusplus<<std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    std::vector<Obd::Device> devices;

    Obd::BluetoothProvider bluetoothProvider;
    Obd::UsbSerialProvider usbProvider;
    //std::vector<Obd::Device> bluetoothDevices = bluetoothProvider.GetAvailableDevices();
    std::vector<Obd::Device> usbDevices = usbProvider.GetAvailableDevices();
    //devices = bluetoothDevices;
    devices.insert(devices.end(),usbDevices.begin(),usbDevices.end());


    Elm327Engine engine;
    return a.exec();
}
