#ifndef BAOS_TELEGRAM_HPP
#define BAOS_TELEGRAM_HPP

#ifndef START_BYTE_INDEX_OFFSET_FROM_MAIN_SERVICE
#define START_BYTE_INDEX_OFFSET_FROM_MAIN_SERVICE 2
#endif // !START_BYTE_INDEX_OFFSET_FROM_MAIN_SERVICE

#ifndef NR_OF_BYTES_OFFSET_FROM_MAIN_SERVICE
#define NR_OF_BYTES_OFFSET_FROM_MAIN_SERVICE 4
#endif // !NR_OF_BYTES_OFFSET_FROM_MAIN_SERVICE

#ifndef FIRST_BYTE_OFFSET_FROM_MAIN_SERVICE
#define FIRST_BYTE_OFFSET_FROM_MAIN_SERVICE 6
#endif // !FIRST_BYTE_OFFSET_FROM_MAIN_SERVICE

#ifndef NR_OF_DPS_OFFSET_FROM_MAINSERVICE
#define NR_OF_DPS_OFFSET_FROM_MAINSERVICE 4
#endif // !NR_OF_DPS_OFFSET_FROM_MAINSERVICE

#ifndef DP_ID_OFFSET_FROM_MAINSERVICE
#define DP_ID_OFFSET_FROM_MAINSERVICE 6
#endif // !DP_ID_OFFSET_FROM_MAINSERVICE

#ifndef DP_VALUE_OFFSET_FROM_MAINSERVICE
#define DP_VALUE_OFFSET_FROM_MAINSERVICE 10
#endif // !DP_VALUE_OFFSET_FROM_MAINSERVICE

#ifndef DP_VALUE_TYPE_OFFSET_FROM_MAINSERVICE
#define DP_VALUE_TYPE_OFFSET_FROM_MAINSERVICE 8
#endif // !DP_VALUE_TYPE_OFFSET_FROM_MAINSERVICE

#ifndef DP_LENGTH_OFFSET_FROM_MAINSERVICE
#define DP_LENGTH_OFFSET_FROM_MAINSERVICE 9
#endif // !DP_LENGTH_OFFSET_FROM_MAINSERVICE

#ifndef DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE
#define DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE 9
#endif // !DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE

#ifndef DP_DPT_OFFSET_FROM_MAINSERVICE
#define DP_DPT_OFFSET_FROM_MAINSERVICE 10
#endif // !DP_DPT_OFFSET_FROM_MAINSERVICE

#ifndef ERROR_CODE_OFFSET_FROM_MAINSERVICE
#define ERROR_CODE_OFFSET_FROM_MAINSERVICE 6
#endif // !ERROR_CODE_OFFSET_FROM_MAINSERVICE

#include <cstring>
#include <cstdio>
#include <exception>
#include "../Utility/GetErrorDescription.hpp"
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
