#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "parameters-engine/ELM327/elm327-engine.h"
#include "obd-access/bluetooth-provider.h"
#include "obd-access/usb-serial-provider.h"

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
    void on_vInfoBackButton_clicked();

    void on_DtcButton_clicked();

    void on_VehicleInfoButton_clicked();

    void on_dtcBackButton_clicked();

    void on_carDataBackButton_clicked();

    void on_freezeFrameBackButton_clicked();

    void on_FreezeFrameButton_clicked();

    void on_LiveDataButton_clicked();

    void on_TestResultButton_clicked();

    void on_testResultsBackButton_clicked();

private:
    Ui::MainWindow *ui;

};

enum pages
{
    mainPage = 0,
    liveData = 1,
    freezeFrame = 2,
    dtc = 3,
    testResults = 4,
    vehicleInfo = 5
};

#endif // MAINWINDOW_H
