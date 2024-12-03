#ifndef BAOS_TELEGRAM_HPP
#define BAOS_TELEGRAM_HPP

#include <cstring>
#include <cstdio>
#include <exception>
#include "../Utility/SerialConnection.hpp"
#include "../Utility/DatapointTypes.hpp"
#include "../Enums/SubservicesEnum.hpp"
#include "../Utility/Macros.hpp"

class BaosTelegram
{
protected:
    BaosTelegram();
    BaosTelegram(SerialConnection *serialConnection);
    ~BaosTelegram();
    unsigned int getAnswer();

    // BAOS telegram data members
    static const unsigned char BAOS_MAIN_SERVICE = 0xF0;
    const unsigned char TELEGRAM_ARR_SIZE = 30;
    const unsigned char RESPONSE_ARR_SIZE = 250;
    unsigned int responseLength;
    unsigned char telegramLength;
    unsigned char *baosTelegram;
    unsigned char *responseTelegram;
    SerialConnection *serialConnection;
};

#endif // BAOS_TELEGRAM_HPP
