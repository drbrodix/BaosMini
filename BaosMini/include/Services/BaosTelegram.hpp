#ifndef BAOS_TELEGRAM_HPP
#define BAOS_TELEGRAM_HPP

// Byte swapper macros for endianess
#ifndef swap2
#define swap2(x) (((x << 8) & 0xFF00) | ((x >> 8) & 0x00FF))
#endif // !swap2

#ifndef swap4
#define swap4(x) (((x << 24) & 0xFF000000) | ((x << 8) & 0x00FF0000) | ((x >> 8) & 0x0000FF00) | ((x >> 24) & 0x000000FF))
#endif // !swap4

#include <cstring>
#include <cstdio>
#include <exception>
#include "../SerialConnection.hpp"

enum BaosSubServices
{
    GetServerItemReq            = 0x01,
    SetServerItemReq            = 0x02,
    GetDatapointDescriptionReq  = 0x03,
    GetDescriptionStringReq     = 0x04,
    GetDatapointValueReq        = 0x05,
    SetDatapointValueReq        = 0x06,
    GetParameterByteReq         = 0x07,
    SetParameterByteReq         = 0x08,
    GetServerItemRes            = 0x81,
    SetServerItemRes            = 0x82,
    GetDatapointDescriptionRes  = 0x83,
    GetDescriptionStringRes     = 0x84,
    GetDatapointValueRes        = 0x85,
    SetDatapointValueRes        = 0x86,
    GetParameterByteRes         = 0x87,
    SetParameterByteRes         = 0x88,
    DatapointValueind           = 0xC1,
    ServerItemInd               = 0xC2
};

class BaosTelegram
{
protected:
    BaosTelegram();
    BaosTelegram(SerialConnection *serialConnection);
    ~BaosTelegram();

    // BAOS telegram data members
    static const unsigned char BAOS_MAIN_SERVICE = 0xF0;
    const unsigned char TELEGRAM_ARR_SIZE = 30;
    unsigned char telegramLength;
    unsigned char *baosTelegram;
    SerialConnection *serialConnection;
};

#endif // BAOS_TELEGRAM_HPP
