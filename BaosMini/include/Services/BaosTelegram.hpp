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
#include "../Utility/SerialConnection.hpp"
#include "../Enums/SubservicesEnum.hpp"

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
