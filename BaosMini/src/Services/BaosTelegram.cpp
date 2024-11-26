#include "../../include/Services/BaosTelegram.hpp"

BaosTelegram::BaosTelegram(SerialConnection* serialConnection)
	: serialConnection(serialConnection)
    , baosTelegram(nullptr)
    , telegramLength(0)
{
    // Allocate TELEGRAM_ARR_SIZE (30 bytes) for the BAOS telegram,
    // set the value of all the elements to 0,
    // and set the first element to the BAOS main service.
    baosTelegram = new unsigned char[TELEGRAM_ARR_SIZE];
    if (baosTelegram != nullptr)
    {
        try {
            memset(baosTelegram, 0, TELEGRAM_ARR_SIZE);
            baosTelegram[BAOS_HEADER_FIRST_INDEX] = BaosTelegram::BAOS_MAIN_SERVICE;
        }
        catch (const std::exception& e) {
            printf("Exception while initializing BAOS telegram array:\n %s", e.what());
        }
    }
    else
    {
        printf("Error: BAOS telegram array is null.");
    }
}

BaosTelegram::BaosTelegram()
    : serialConnection(nullptr)
    , baosTelegram(nullptr)
    , telegramLength(0)
{
}

BaosTelegram::~BaosTelegram()
{
	delete[] baosTelegram;
}