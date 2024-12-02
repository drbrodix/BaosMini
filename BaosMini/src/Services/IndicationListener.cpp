#include "../../include/Services/IndicationListener.hpp"

static unsigned int lookForIndication(SerialConnection *serialConnection, unsigned char* telegramCharArray)
{
    HANDLE serialHandle = serialConnection->getHandle();
    const unsigned short MAX_TRIES_COUNT = 30;       // Caps number of tries looking for FT1.2 start byte
    const unsigned short HEADER_SIZE = 5;        // Fixed size of FT1.2 header; unless the protocol changes, this constant shouldn't be touched
    unsigned int readTries = 0;        // Keeps count of number of tries looking for FT1.2 start byte
    unsigned int telegramLength = 0;        // Variable to save BAOS telegram length after reading FT1.2 header
    unsigned char ft12Header[HEADER_SIZE] = { 0 };    // { (0) 0x68 , (1) Length, (2) Length, (3) 0x68, (4) ControlByte }
    unsigned char checksum = 0;
    unsigned char endByte = 0;
    unsigned char c = 0;

    while (true)
    {
        // Looking for starter byte of FT1.2 frame
        DWORD drBytesRead = 0;
        if (!ReadFile(
            serialHandle,
            &c,
            sizeof(c),
            &drBytesRead,
            nullptr
        )) {

        }
        ++readTries;
        if (c == 0xC1)  // If reader recognizes FT1.2 Start Byte,
            // it should read the rest of the fixed sized header
        {
            serialConnection->sendAck();
            printf("HAPPY DAY");
        }
    }
    return 0;
}

IndicationListener::IndicationListener(
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
    unsigned char buff[300];

    std::thread listener(lookForIndication, serialConnection, buff);

    listener.join();

}

IndicationListener::~IndicationListener()
{
}