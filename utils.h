#pragma once
#include <string>
#include <sstream>
//#include <QtDebug>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "constants.h"
namespace utils {
long hexToDec(std::string hex);
std::string hexToBin(std::string hex);
std::string decToHex(int dec);
void removeControlCharacters(std::string &text);
void removeControlCharacters(char *text, int size);
std::string getTimestamp();
}
