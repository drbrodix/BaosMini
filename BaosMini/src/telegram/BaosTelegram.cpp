#include "telegram/BaosTelegram.hpp"

BaosTelegram::BaosTelegram()
{
}
BaosTelegram::BaosTelegram(
    unsigned char subServiceCode,
    unsigned char dataLength,
    unsigned char controlByte,
    unsigned char checksum)
    : subServiceCode(subServiceCode)
    , dataLength(dataLength)
    , controlByte(controlByte)
    , checksum(checksum)
{
}
BaosTelegram::~BaosTelegram()
{
}