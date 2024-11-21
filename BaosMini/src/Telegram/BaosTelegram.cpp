#include "Telegram/BaosTelegram.hpp"

BaosTelegram::BaosTelegram()
    : baosTelegram(nullptr)
    , telegramObjectSize(0)
{
    // Set size of BAOS telegram array to TELEGRAM_SIZE (20)
    // and set the value of all the elements to 0
    baosTelegram = new unsigned char[TELEGRAM_SIZE];
    if (baosTelegram != nullptr)
    {
        try {
            memset(baosTelegram, 0, TELEGRAM_SIZE);
            baosTelegram[0] = BaosTelegram::BAOS_MAIN_SERVICE;
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

BaosTelegram::~BaosTelegram()
{
	delete[] baosTelegram;
}