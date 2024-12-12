#include "../../include/Services/BaosTelegram.hpp"

BaosTelegram::BaosTelegram(SerialConnection* serialConnection)
    : BaosTelegram()
{
    BaosTelegram::serialConnection  = serialConnection;
    // Allocate TELEGRAM_ARR_SIZE (30 bytes) to the BAOS telegram,
    // set the value of all the elements to 0,
    // and set the first element to the BAOS main service code (0xF0).
    baosTelegram                    = new unsigned char[TELEGRAM_ARR_SIZE];
    // Allocate RESPONSE_ARR_SIZE (250 bytes) to the response telegram,
    // and set the value of all the elements to 0.
    responseTelegram                = new unsigned char[RESPONSE_ARR_SIZE];
    if (baosTelegram != nullptr)
    {
        memset(baosTelegram, 0, TELEGRAM_ARR_SIZE);
        baosTelegram[BAOS_HEADER_FIRST_INDEX] = BAOS_MAIN_SERVICE;
    }
    else
    {
        printf("Error: BAOS telegram array is null.");
    }

    if (responseTelegram != nullptr)
    {
        memset(responseTelegram, 0, RESPONSE_ARR_SIZE);
    }
    else
    {
        printf("Error: response array is null.");
    }
}

BaosTelegram::BaosTelegram()
    : serialConnection(nullptr)
    , baosTelegram(nullptr)
    , responseTelegram(nullptr)
    , telegramLength(0)
    , responseLength(0)
    , hasValidResponse(false)
{
}

BaosTelegram::~BaosTelegram()
{
	delete[] baosTelegram;
    delete[] responseTelegram;
}

unsigned int BaosTelegram::getAnswer()
{
    if (responseTelegram != nullptr)
    {
        memset(responseTelegram, 0, RESPONSE_ARR_SIZE);

        responseLength = serialConnection->recieveTelegram(responseTelegram);

        if (responseLength > 0)
        {
            serialConnection->sendAck();
            return responseLength;
        }
        else
        {
            printf("Error while reading from COM port.\n");
            return 0;
        }
    }
    else
    {
        printf("Response telegram buffer has not been initialized\n");
        return 0;
    }
}