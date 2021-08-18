#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::Run()
{
    obd.initConnection();
    if(obd.isConnected())
    {
        onConnectionEstablished();
    }
    else
    {
        onConnectionLost();
    }
}

void MainWindow::updateUI()
{

    if(engineLoadCheckbox->isChecked())
    {
        engineLoadLabel->setText(QString::number(obdBuffer.engineLoad)+"%");
    }

    if(rpmCheckbox->isChecked())
    {
        rpmLabel->setText(QString::number(obdBuffer.engineRPM)+"rpm");
    }

    if(coolantCheckbox->isChecked())
    {
        coolantLabel->setText(QString::number(obdBuffer.coolantTemp)+"°C");
    }

    if(airIntakeTempCheckbox->isChecked())
    {
        airIntakeTempLabel->setText(QString::number(obdBuffer.airIntakeTemp)+"°C");
    }

    if(speedCheckbox->isChecked())
    {
        speedLabel->setText(QString::number(obdBuffer.speed)+"km/h");
    }

    if(mafCheckbox->isChecked())
    {
        mafLabel->setText(QString::number(obdBuffer.mafAirFlow)+"g/sec");
    }

    if(intakeManifoldPressureCheckbox->isChecked())
    {
        intakeManifoldPressureLabel->setText(QString::number(obdBuffer.intakeManifoldPressure)+"kPa");
    }

    if(throttleCheckbox->isChecked())
    {
        throttleLabel->setText(QString::number(obdBuffer.throttlePosition)+"%");
    }

    if(timingAdvanceCheckbox->isChecked())
    {
        timingAdvanceLabel->setText(QString::number(obdBuffer.timingAdvance)+"°");
    }

}

void MainWindow::setLabelText(QString text)
{
    statusLabel->setText(text);
}

void MainWindow::setProgress(int percent)
{
    progresBar->setValue(percent);
}

void MainWindow::GetDataJob()
{

    if(!getDataLock.try_lock())
    {
        do
        {
            isGettingData=true;
            emit setProgressSignal(0);
            if(engineLoadCheckbox->isChecked())
            {
                obdBuffer.engineLoad=obd.getEngineLoadPercentage();
            }
            emit updateUiSignal();
            emit setProgressSignal(10);

            if(rpmCheckbox->isChecked())
            {
                obdBuffer.engineRPM=obd.getEngineRPM();
            }
            emit updateUiSignal();
            emit setProgressSignal(20);

            if(coolantCheckbox->isChecked())
            {
                obdBuffer.coolantTemp=obd.getCoolantTemp();
            }
            emit updateUiSignal();
            emit setProgressSignal(30);

            if(airIntakeTempCheckbox->isChecked())
            {
                obdBuffer.airIntakeTemp=obd.getAirIntakeTemp();
            }
            emit updateUiSignal();
            emit setProgressSignal(40);

            if(speedCheckbox->isChecked())
            {
                obdBuffer.speed=obd.getSpeed();
            }
            emit updateUiSignal();
            emit setProgressSignal(50);

            if(mafCheckbox->isChecked())
            {
                obdBuffer.mafAirFlow=obd.getMafAirFlow();
            }
            emit updateUiSignal();
            emit setProgressSignal(60);

            if(intakeManifoldPressureCheckbox->isChecked())
            {
                obdBuffer.intakeManifoldPressure=obd.getIntakeManifoldPressure();
            }
            emit updateUiSignal();
            emit setProgressSignal(70);

            if(throttleCheckbox->isChecked())
            {
                obdBuffer.throttlePosition=obd.getThrottlePosition();
            }
            emit updateUiSignal();
            emit setProgressSignal(80);

            if(timingAdvanceCheckbox->isChecked())
            {
                obdBuffer.timingAdvance=obd.getTimingAdvance();
            }
            emit updateUiSignal();
            emit setProgressSignal(100);

            obdBuffer.timestamp=utils::getTimestamp();

            if(isRecording)
            {
                dataBufferList.push_back(obdBuffer);
                emit setLabelSignal("Recorded "+QString::number(dataBufferList.size())+" frames.");
            }

        }while(isRecording || continousReadCheckbox->isChecked() );
        getDataLock.unlock();
        isGettingData=false;

    }
}

void MainWindow::GetData()
{
    if(obd.isConnected())
    {
        if(!isGettingData)
        {
            obdThread=std::thread(&MainWindow::GetDataJob,this);
            obdThread.detach();
        }
    }
    else
    {
        onConnectionLost();
    }
}

void MainWindow::setControlsEnabled(bool state)
{
    connectionStatus->setChecked(state);
    getDataButton->setEnabled(state);
    continousReadCheckbox->setEnabled(state);

    rpmCheckbox->setEnabled(state);
    speedCheckbox->setEnabled(state);
    coolantCheckbox->setEnabled(state);
    airIntakeTempCheckbox->setEnabled(state);
    engineLoadCheckbox->setEnabled(state);
    throttleCheckbox->setEnabled(state);
    timingAdvanceCheckbox->setEnabled(state);
    intakeManifoldPressureCheckbox->setEnabled(state);
    mafCheckbox->setEnabled(state);

    startRecordButton->setEnabled(state);
    stopRecordButton->setEnabled(state);
}

void MainWindow::showSupportedParameters()
{
    std::vector<std::string> pids = obd.getSupportedPIDs();

    for(unsigned i=0;i<pids.size();i++)
    {
        if(pids[i] =="010c")
        {
            rpmCheckbox->setVisible(true);
            rpmCheckbox->setEnabled(true);
            rpmLabel->setVisible(true);
        }
        if(pids[i] =="010d")
        {
            speedCheckbox->setVisible(true);
            speedCheckbox->setEnabled(true);
            speedLabel->setVisible(true);
        }
        if(pids[i] =="0105")
        {
            coolantCheckbox->setVisible(true);
            coolantCheckbox->setEnabled(true);
            coolantLabel->setVisible(true);
        }
        if(pids[i] =="010f")
        {
            airIntakeTempCheckbox->setVisible(true);
            airIntakeTempCheckbox->setEnabled(true);
            airIntakeTempLabel->setVisible(true);
        }
        if(pids[i] =="0104")
        {
            engineLoadCheckbox->setVisible(true);
            engineLoadCheckbox->setEnabled(true);
            engineLoadLabel->setVisible(true);
        }
        if(pids[i] =="0111")
        {
            throttleCheckbox->setVisible(true);
            throttleCheckbox->setEnabled(true);
            throttleLabel->setVisible(true);
        }
        if(pids[i] =="010e")
        {
            timingAdvanceCheckbox->setVisible(true);
            timingAdvanceCheckbox->setEnabled(true);
            timingAdvanceLabel->setVisible(true);
        }
        if(pids[i] =="010b")
        {
            intakeManifoldPressureCheckbox->setVisible(true);
            intakeManifoldPressureCheckbox->setEnabled(true);
            intakeManifoldPressureLabel->setVisible(true);
        }
        if(pids[i] =="0110")
        {
            mafCheckbox->setVisible(true);
            mafCheckbox->setEnabled(true);
            mafLabel->setVisible(true);
        }

    }

}

void MainWindow::setParametersVisibility(bool visible)
{
    rpmCheckbox->setVisible(visible);
    rpmLabel->setVisible(visible);

    speedCheckbox->setVisible(visible);
    speedLabel->setVisible(visible);

    coolantCheckbox->setVisible(visible);
    coolantLabel->setVisible(visible);

    airIntakeTempCheckbox->setVisible(visible);
    airIntakeTempLabel->setVisible(visible);

    engineLoadCheckbox->setVisible(visible);
    engineLoadLabel->setVisible(visible);

    throttleCheckbox->setVisible(visible);
    throttleLabel->setVisible(visible);

    timingAdvanceCheckbox->setVisible(visible);
    timingAdvanceLabel->setVisible(visible);

    intakeManifoldPressureCheckbox->setVisible(visible);
    intakeManifoldPressureLabel->setVisible(visible);

    mafCheckbox->setVisible(visible);
    mafLabel->setVisible(visible);
}


void MainWindow::onConnectionLost()
{
    setControlsEnabled(false);
    setParametersVisibility(true);
    statusLabel->setText("Disconnected");
    connectButton->setEnabled(true);
    QApplication::processEvents();
}

void MainWindow::onConnectionEstablished()
{
   setControlsEnabled(true);
   setParametersVisibility(false);
   showSupportedParameters();
   statusLabel->setText("Connection established");
   connectButton->setEnabled(false);
   QApplication::processEvents();
}

void MainWindow::tryConnect()
{
    if(!obd.isConnected())
    {
        connectButton->setEnabled(false);
        progresBar->setValue(0);
        obd.initConnection();
        progresBar->setValue(50);

        connectionStatus->setDown(obd.isConnected());
        if(!obd.isConnected())
        {
            connectButton->setEnabled(true);
            onConnectionLost();
        }
        else
        {
            onConnectionEstablished();
        }
        progresBar->setValue(100);
    }
}

void MainWindow::startRecording()
{
    isRecording=true;

    if(!isGettingData)
    {
        obdThread=std::thread(&MainWindow::GetDataJob,this);
        obdThread.detach();
    }

}

void MainWindow::stopRecording()
{
    emit updateUiSignal();
    isRecording=false;

    while(isGettingData)
        usleep(100);
    std::string timestamp=utils::getTimestamp();
    std::ofstream record(timestamp+".csv");

    unsigned listSize=dataBufferList.size();
    unsigned i=0;
    while(!dataBufferList.empty())
    {
        progresBar->setValue((float)i/(float)listSize*100);

        record<<dataBufferList.front().timestamp<<", ";
        record<<dataBufferList.front().airIntakeTemp<<", ";
        record<<dataBufferList.front().coolantTemp<<", ";
        record<<dataBufferList.front().engineLoad<<", ";
        record<<dataBufferList.front().engineRPM<<", ";
        record<<dataBufferList.front().intakeManifoldPressure<<", ";
        record<<dataBufferList.front().mafAirFlow<<", ";
        record<<dataBufferList.front().speed<<", ";
        record<<dataBufferList.front().throttlePosition<<", ";
        record<<dataBufferList.front().timingAdvance<<", ";
        record<<std::endl;
        dataBufferList.pop_front();
        i++;
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //GUI setup
    getDataButton=MainWindow::findChild<QPushButton*>("getDataButton");
    connectButton=MainWindow::findChild<QPushButton*>("connectButton");
    startRecordButton=MainWindow::findChild<QPushButton*>("startRecordButton");
    stopRecordButton=MainWindow::findChild<QPushButton*>("stopRecordButton");
    progresBar= MainWindow::findChild<QProgressBar*>("progressBar");
    continousReadCheckbox=MainWindow::findChild<QCheckBox*>("continousReadCheckbox");
    statusLabel = MainWindow::findChild<QLabel*>("statusLabel");
    connectionStatus = MainWindow::findChild<QRadioButton*>("statusRadio");

    //Checkbox
    rpmCheckbox = MainWindow::findChild<QCheckBox*>("rpmCheckbox");
    speedCheckbox = MainWindow::findChild<QCheckBox*>("speedCheckbox");
    coolantCheckbox = MainWindow::findChild<QCheckBox*>("coolantCheckbox");
    airIntakeTempCheckbox = MainWindow::findChild<QCheckBox*>("airIntakeTempCheckbox");
    engineLoadCheckbox = MainWindow::findChild<QCheckBox*>("engineLoadCheckbox");
    throttleCheckbox = MainWindow::findChild<QCheckBox*>("throttleCheckbox");
    timingAdvanceCheckbox = MainWindow::findChild<QCheckBox*>("timingAdvanceCheckbox");
    intakeManifoldPressureCheckbox = MainWindow::findChild<QCheckBox*>("intakeManifoldPressureCheckbox");
    mafCheckbox = MainWindow::findChild<QCheckBox*>("mafCheckbox");

    rpmLabel=MainWindow::findChild<QLabel*>("rpmLabel");
    speedLabel=MainWindow::findChild<QLabel*>("speedLabel");
    coolantLabel=MainWindow::findChild<QLabel*>("coolantLabel");
    airIntakeTempLabel=MainWindow::findChild<QLabel*>("airIntakeTempLabel");
    engineLoadLabel=MainWindow::findChild<QLabel*>("engineLoadLabel");
    throttleLabel=MainWindow::findChild<QLabel*>("throttleLabel");
    timingAdvanceLabel=MainWindow::findChild<QLabel*>("timingAdvanceLabel");
    intakeManifoldPressureLabel=MainWindow::findChild<QLabel*>("intakeManifoldPressureLabel");
    mafLabel=MainWindow::findChild<QLabel*>("mafLabel");

    connect(getDataButton,SIGNAL(pressed()),this,SLOT(GetData()));
    connect(connectButton,SIGNAL(pressed()),this,SLOT(tryConnect()));
    connect(startRecordButton,SIGNAL(pressed()),this,SLOT(startRecording()));
    connect(stopRecordButton,SIGNAL(pressed()),this,SLOT(stopRecording()));
    connect(this,SIGNAL(updateUiSignal()),this,SLOT(updateUI()));
    connect(this,SIGNAL(setProgressSignal(int)),this,SLOT(setProgress(int)));
    connect(this,SIGNAL(setLabelSignal(QString)),this,SLOT(setLabelText(QString)));

    onConnectionLost();
}



MainWindow::~MainWindow()
{
    delete ui;
}

