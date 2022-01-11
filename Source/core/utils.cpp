#include "utils.h"
#include <iostream>

namespace  utils
{

long hexToDec(std::string hex)
{
    char *p;
    return strtol( hex.c_str(), & p, 16 );
}

std::string decToHex(int dec)
{
    std::stringstream sstream;
    sstream << std::hex << dec;
    return sstream.str();
}

std::string hexToBin(std::string hex)
{
    std::string sReturn = "";
    for (unsigned i = 0; i < hex.length(); ++i)
    {
        switch (tolower(hex[i]))
        {
        case '0': sReturn.append ("0000"); break;
        case '1': sReturn.append ("0001"); break;
        case '2': sReturn.append ("0010"); break;
        case '3': sReturn.append ("0011"); break;
        case '4': sReturn.append ("0100"); break;
        case '5': sReturn.append ("0101"); break;
        case '6': sReturn.append ("0110"); break;
        case '7': sReturn.append ("0111"); break;
        case '8': sReturn.append ("1000"); break;
        case '9': sReturn.append ("1001"); break;
        case 'a': sReturn.append ("1010"); break;
        case 'b': sReturn.append ("1011"); break;
        case 'c': sReturn.append ("1100"); break;
        case 'd': sReturn.append ("1101"); break;
        case 'e': sReturn.append ("1110"); break;
        case 'f': sReturn.append ("1111"); break;
        default: break;
        }
    }
    return sReturn;
}


void removeControlCharacters(std::string &text)
{
    for(unsigned i =0;i<text.length();i++)
    {
        //std::cout<<(int)text[i]<<" ";
        if(text[i]=='\0')
            break;

        if(text[i]=='\r')
        {
            text[i]='R';
        }
        if(iscntrl(text[i]))
        {
            text[i]='#';
        }

    }
    std::cout<<"RAW: "<<text<<std::endl;
}

std::string getTimestamp()
{
    std::stringstream transTime;
    time_t const now_c = time(NULL);
    transTime << std::put_time(localtime(&now_c), "%a %d %b %Y - %I:%M:%S%p");
    return  transTime.str();
}

void removeControlCharacters(char* text,int size)
{
    for(int i =0;i<size;i++)
    {
        std::cout<<(int)text[i]<<" ";
        if(text[i]=='\0')
            break;

        if(text[i]=='\r')
        {
            text[i]='c';
        }
        if(iscntrl(text[i]))
        {
            text[i]='#';
        }

    }
}

}
