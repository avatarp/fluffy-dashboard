#ifndef DATABUFFER_H
#define DATABUFFER_H


struct dataBuffer
{
    double engineLoad=-1;
    long engineRPM=-1;
    long coolantTemp=-1;
    long airIntakeTemp=-1;
    long speed=-1;
    double mafAirFlow=-1;
    long intakeManifoldPressure=-1;
    double throttlePosition=-1;
    double timingAdvance=-1;
    std::string timestamp;
};

#endif // DATABUFFER_H
