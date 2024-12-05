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
    // Returns response telegram length,
    // or 0 if error has occured
    unsigned int getAnswer();

    // BAOS telegram data members
    static const unsigned char BAOS_MAIN_SERVICE = 0xF0;
    // Constant for allocation of memory for
    // telegram to be sent to ObjectServer
    const unsigned char TELEGRAM_ARR_SIZE = 30;
    // Constant for allocation of memory for
    // ObjectServer response telegram buffer
    const unsigned char RESPONSE_ARR_SIZE = 250;
    
    // Length of telegram recieved from ObjectServer
    unsigned int responseLength;
    // Length of telegram to be sent to ObjectServer
    unsigned char telegramLength;
    // Unsigned char array of telegram to be sent to ObjectServer
    unsigned char *baosTelegram;
    // Unsigned char array of ObjectServer response telegram 
    unsigned char *responseTelegram;
    // Keeps track if ObjectServer response telegram is valid
    bool hasValidResponse;
    SerialConnection *serialConnection;
};

#endif // BAOS_TELEGRAM_HPP
