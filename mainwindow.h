#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <list>
#include <thread>
#include <mutex>
#include <iomanip>
#include <ctime>
#include <fstream>
#include "obd.h"
#include "databuffer.h"
#include "ui_mainwindow.h"

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
    void GetData();
    void tryConnect();
    void startRecording();
    void stopRecording();
    void updateUI();
    void setLabelText(QString text);
    void setProgress(int percent);
signals:
    void updateUiSignal();
    void setLabelSignal(QString text);
    void setProgressSignal(int percent);
private:
    dataBuffer obdBuffer;
    std::thread obdThread;
    bool isGettingData=false;
    bool isRecording=false;
    std::mutex getDataLock;
    std::thread::id mainThreadId;

    std::list<dataBuffer> dataBufferList;
    Ui::MainWindow *ui;
    obd2Interface obd;
    void Run();
    void onConnectionLost();
    void onConnectionEstablished();

    void GetDataJob();
    void setControlsEnabled(bool state);
    void showSupportedParameters();
    void setParametersVisibility(bool visible);

    //GUI
    QPushButton *getDataButton;
    QPushButton *connectButton;
    QPushButton *startRecordButton;
    QPushButton *stopRecordButton;
    QProgressBar *progresBar;
    QCheckBox *continousReadCheckbox;

    QLabel *statusLabel;
    QRadioButton *connectionStatus;

    //Data Checkboxes
    QCheckBox *rpmCheckbox;
    QCheckBox *speedCheckbox;
    QCheckBox *coolantCheckbox;
    QCheckBox *airIntakeTempCheckbox;
    QCheckBox *engineLoadCheckbox;
    QCheckBox *throttleCheckbox;
    QCheckBox *timingAdvanceCheckbox;
    QCheckBox *intakeManifoldPressureCheckbox;
    QCheckBox *mafCheckbox;

    //Data Labels
    QLabel *rpmLabel;
    QLabel *speedLabel;
    QLabel *coolantLabel;
    QLabel *airIntakeTempLabel;
    QLabel *engineLoadLabel;
    QLabel *throttleLabel;
    QLabel *timingAdvanceLabel;
    QLabel *intakeManifoldPressureLabel;
    QLabel *mafLabel;
};
#endif // MAINWINDOW_H
