#include "obd.h"

obd2Interface::obd2Interface()
{
    connected=false;
}


bool obd2Interface::initConnection()
{
    std::cout<<"Opening connection..."<<std::endl;
    connectionHandle = open(port.c_str(), O_RDWR | O_NOCTTY );
    if (connectionHandle == -1)//error occured
    {
        connected=false;
        std::cout<<"INIT FAILURE\n"<<"Error:"<<strerror(errno)<<std::endl;
        return false;
    }
    std::cout<<"INIT OK\n"<<std::endl;
    connected=true;
    setupTermios();
    return findSupportedPIDs();
}


bool obd2Interface::findSupportedPIDs()
{
    supportedPIDs.clear();
    //for 1 try no data recived case
    getRawData("0100");
    std::string response=getRawData("0100");
    std::string encodedPIDs=utils::hexToBin(response);
    if(encodedPIDs.length()<1)
    {
        std::cout<<"Cannot receive supported PIDs"<<std::endl;
        connected=false;
        return false;
    }

    bool nextPids=false;

    for(unsigned i=0;i<encodedPIDs.length();i++)
    {
        std::string prefix;
        if(utils::decToHex(i+1).length()==1)
            prefix="010";
        else
            prefix="01";

        std::string pid=prefix+utils::decToHex(i+1);

        if(encodedPIDs[i]=='1')
        {

            supportedPIDs.insert(std::pair<std::string,bool>(pid,true));
        }
        else if(encodedPIDs[i]=='0')
        {
            supportedPIDs.insert(std::pair<std::string,bool>(pid,false));
        }

        if(i+1==32 && encodedPIDs[i]=='1')
        {
            nextPids=true;
        }
    }

    if(nextPids)
    {
        response=getRawData("0120");
        encodedPIDs=utils::hexToBin(response);
        if(encodedPIDs.length()<1)
        {
            std::cout<<"Cannot receive all PIDs"<<std::endl;
            return true;
        }

        for(unsigned i=0;i<encodedPIDs.length();i++)
        {
            std::string prefix="01";
            std::string pid=prefix+utils::decToHex(i+33);
            if(encodedPIDs[i]=='1')
            {
                supportedPIDs.insert(std::pair<std::string,bool>(pid,true));
            }
            else if(encodedPIDs[i]=='0')
            {
                supportedPIDs.insert(std::pair<std::string,bool>(pid,false));
            }
        }
    }

    getSupportedPIDs();
    return true;
}

void obd2Interface::setupTermios()
{
    //Clear rfcomm file
    bzero(&serialConnection, sizeof(serialConnection));
    serialConnection.c_cflag = baudRate | CS8 | CLOCAL | CREAD;
    serialConnection.c_iflag = IGNPAR;
    serialConnection.c_oflag = 0;
    serialConnection.c_lflag &= ~ICANON;     /* Set non-canonical mode */
    serialConnection.c_cc[VTIME]    = 5;    /* Set timeout of 5.0 seconds */
    serialConnection.c_cc[VMIN]     = 7;     /* blocking read for 1.0 second between characters */
    tcflush(connectionHandle, TCIOFLUSH);
    tcsetattr(connectionHandle,TCSANOW,&serialConnection);
}

obd2Interface::~obd2Interface()
{
    //only close device
    serialConnection.c_cflag = B0;
    if(connectionHandle>0)
    {
        close(connectionHandle);
    }
}

//################################################## commands start

bool obd2Interface::sendMessage(std::string msg)
{
    int writeResult = write(connectionHandle, msg.c_str(), msg.length());
    if(writeResult==-1)
    {
        std::cout<<"WRITE FAILURE\n"<<"Error:"<<strerror(errno)<<std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        //std::cout<<"Written "<<writeResult<<" bytes succesfully."<<std::endl;
        return true;
    }
}


std::string obd2Interface::readMessage()
{
    char readBuffer[constants::bufferSize]{};
    memset(&readBuffer, '\0', sizeof(readBuffer));
    int dataReadCount = read(connectionHandle, &readBuffer, constants::bufferSize);
    if(dataReadCount <= 0)
    {
        std::cout<<"READ FAILURE\n"<<"Error:"<<strerror(errno)<<std::endl;

        connected=false;
    }
    std::string receivedMessage=readBuffer;
//    std::string temp = receivedMessage;
//    utils::removeControlCharacters(temp);
//    std::cout<<"Message recived: "<<temp<<std::endl;
    return receivedMessage;
}

std::string obd2Interface::getDataBytes(std::string command,std::string text)
{

    std::string patternString={command[1],' ',command[2],command[3]};
    patternString+=" (.+) \r";
    std::regex pattern(patternString);
    std::smatch match;
    std::regex_search(text,match,pattern);
    if(command=="0902\r")
    {
        utils::removeControlCharacters(text);
    }
    return match[1];

}

std::string obd2Interface::getRawData(std::string command)
{
    if(command.length()<4 || connected==false)
        return std::string();
    if(command.back()!='\r')
        command.push_back('\r');
    //Send message
    sendMessage(command);
    sleep(1);
    //Read message
    std::string response=readMessage();
    if(response.length()==0)
    {
        std::cout<<"NO DATA FOUND"<<std::endl;

        if(command!="0100")
            connected=false;

    }
    //Match data bytes
    std::cout<<"connected="<<connected<<std::endl;
    return getDataBytes(command, response);

}


//////////////////////////////////////////data commands


long obd2Interface::getEngineRPM() //
{
    std::string PID="010C";
    if(!isCommandSupported(PID))
        return -1;

    std::string data=getRawData(PID);
    //std::cout<<"data: "<<data<<std::endl;
    long result=-1;
    //(256*A+B)/4
    if(data.length()<5)
        return result;

    std::string byteA{data[0],data[1]};
    std::string byteB{data[3],data[4]};
    int valA=utils::hexToDec(byteA.c_str());
    int valB=utils::hexToDec(byteB);
    result = (256*valA+valB)/4;
    return result;
}

double obd2Interface::getEngineLoadPercentage()//
{
    std::string PID="0104";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    //std::cout<<"data: "<<data<<std::endl;
    double result=-1;
    //(100/255)*A
    std::string byte={data[0],data[1]};
    result= (100.0/255.0)*utils::hexToDec(byte);

    return result;
}

long obd2Interface::getCoolantTemp()//
{
    std::string PID="0105";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    //std::cout<<"data: "<<data<<std::endl;
    long result=-1;
    //A-40
    char byteA[2]={data[0],data[1]};
    result= utils::hexToDec(byteA)-40;

    return result;
}

long obd2Interface::getAirIntakeTemp()//
{
    std::string PID="010F";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    //std::cout<<"data: "<<data<<std::endl;
    long result=-1;
    //A-40
    char byteA[2]={data[0],data[1]};
    result= utils::hexToDec(byteA)-40;

    return result;
}

long obd2Interface::getSpeed()//
{
    std::string PID="010D";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    //std::cout<<"data: "<<data<<std::endl;
    long result=-1;
    //A
    char byteA[2]={data[0],data[1]};
    result = utils::hexToDec(byteA);

    return result;
}

float obd2Interface::getMafAirFlow()//
{
    std::string PID="0110";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    //std::cout<<"data: "<<data<<std::endl;
    float result=-1;
    //A
    char byteA[2]={data[0],data[1]};
    char byteB[2]={data[3],data[4]};

    result = (256*utils::hexToDec(byteA) +utils::hexToDec(byteB))/100;

    return result;
}

long obd2Interface::getIntakeManifoldPressure()//
{
    std::string PID="010B";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    ////std::cout<<"data: "<<data<<std::endl;
    long result=-1;
    //A
    char byteA[2]={data[0],data[1]};
    result = utils::hexToDec(byteA);

    return result;
}


double obd2Interface::getThrottlePosition()//
{
    std::string PID="0111";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    ////std::cout<<"data: "<<data<<std::endl;
    double result=-1;
    //A
    char byteA[2]={data[0],data[1]};
    result = 2.55*utils::hexToDec(byteA);

    return result;
}


double obd2Interface::getTimingAdvance()//
{
    std::string PID="010E";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    ////std::cout<<"data: "<<data<<std::endl;
    double result=-1;
    //A
    char byteA[2]={data[0],data[1]};
    result = utils::hexToDec(byteA)/2-64;

    return result;
}


double obd2Interface::getShortTermFuelTrim1()
{
    std::string PID="0106";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    ////std::cout<<"data: "<<data<<std::endl;
    double result=-1;
    //A
    char byteA[2]={data[0],data[1]};
    result = 1.28*utils::hexToDec(byteA)-100;

    return result;
}


double obd2Interface::getLongTermFuelTrim1()
{
    std::string PID="0107";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    ////std::cout<<"data: "<<data<<std::endl;
    double result=-1;
    //A
    char byteA[2]={data[0],data[1]};
    result = 1.28*utils::hexToDec(byteA)-100;

    return result;
}

double obd2Interface::getO2Bank1Sensor1Voltage()
{
    std::string PID="0114";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    ////std::cout<<"data: "<<data<<std::endl;
    double result=-1;
    //A
    char byteA[2]={data[0],data[1]};
    result = utils::hexToDec(byteA)/200;

    return result;
}

double obd2Interface::getO2Bank1Sensor1ShortTermFuelTrim()
{
    std::string PID="0114";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    ////std::cout<<"data: "<<data<<std::endl;
    double result=-1;
    //A
    char byteB[2]={data[3],data[4]};
    result = 1.28*utils::hexToDec(byteB)-100;

    return result;
}


double obd2Interface::getO2Bank1Sensor2Voltage()
{
    std::string PID="0115";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    ////std::cout<<"data: "<<data<<std::endl;
    double result=-1;
    //A
    char byteA[2]={data[0],data[1]};
    result = utils::hexToDec(byteA)/200;

    return result;
}

double obd2Interface::getO2Bank1Sensor2ShortTermFuelTrim()
{
    std::string PID="0115";
    if(!isCommandSupported(PID))
        return -1;
    std::string data=getRawData(PID);
    ////std::cout<<"data: "<<data<<std::endl;
    double result=-1;
    //A
    char byteB[2]={data[3],data[4]};
    result = 1.28*utils::hexToDec(byteB)-100;

    return result;
}

std::string obd2Interface::getFuelSystemStatus()
{
    std::string PID="0103";
    if(!isCommandSupported(PID))
        return "NO DATA";
    std::string data=getRawData(PID);
    ////std::cout<<"data: "<<data<<std::endl;
    return data;
}

std::string obd2Interface::getCarPIDs()
{
    std::string data=getRawData(("0100"));
    data+="\n";
    data+=getRawData("0120");
    data+="\n";
    data+=getRawData("0900");
    data+="\n";
    data+="standard -";
    data+=getRawData("011C");
    return data;
}


std::string obd2Interface::getVIN()
{
    std::string PID="0902";
    std::string data=getRawData(PID);
    utils::removeControlCharacters(data);
    return data;
}

//################################################## commands end

bool obd2Interface::isCommandSupported(std::string PID)
{
    for(unsigned i=0;i<PID.length();i++)
    {
        PID[i]=tolower(PID[i]);
    }
    std::map<std::string,bool>::iterator it = supportedPIDs.find(PID);
    bool isSupported=false;
    if(it != supportedPIDs.end())
    {
        //element found;
       isSupported = it->second;
    }

    if(!isSupported)
    {
        std::cout<<"Command "<<PID<<" NOT supported"<<std::endl;
    }
    return isSupported;
}

std::vector<std::string> obd2Interface::getSupportedPIDs()
{
    std::vector<std::string> list;
    for(auto i=supportedPIDs.begin();i!=supportedPIDs.end();++i)
    {
        std::cout<<i->first<<" is supported "<<i->second<<std::endl;
        if(i->second==true)
            list.push_back(i->first);
    }
    return list;
}
