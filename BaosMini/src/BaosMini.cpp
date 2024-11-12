#include "Headers.hpp"

int main(int argc, char* argv[])
{
    SerialConnection *pSerialConnection = new SerialConnection("COM3");

    SetDatapointValue myTelegram(1, true, pSerialConnection->getHandle());
    myTelegram.sendTelegram();

    delete(pSerialConnection);
    return EXIT_SUCCESS;
}
