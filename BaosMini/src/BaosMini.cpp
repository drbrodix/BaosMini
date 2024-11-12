#include "Headers.hpp"

int main(int argc, char* argv[])
{
    SerialConnection *pSerialConnection = new SerialConnection("COM3");

    SetDatapointValue myTelegram1(1, false, pSerialConnection);
    myTelegram1.sendTelegram();

    SetDatapointValue myTelegram2(2, false, pSerialConnection);
    myTelegram2.sendTelegram();

    SetDatapointValue myTelegram3(3, false, pSerialConnection);
    myTelegram3.sendTelegram();

    SetDatapointValue myTelegram4(4, false, pSerialConnection);
    myTelegram4.sendTelegram();

    delete(pSerialConnection);
    return EXIT_SUCCESS;
}
