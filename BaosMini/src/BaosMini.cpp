#include "BaosMini.hpp"


int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;
    SerialConnection *serialConnection = new SerialConnection("COM3");

    BaosTelegram *myTelegram1 = new SetDatapointValue(1, true);
    serialConnection->sendTelegram(myTelegram1->getTelegramData());

    /*for (int i = 0; i < 4; i++)
    {*/
        //SetDatapointValue myTelegram1(1, true, pSerialConnection);
        //myTelegram1.sendTelegram();
        //std::this_thread::sleep_for(500ms);
        //SetDatapointValue myTelegram2(2, true, pSerialConnection);
        //myTelegram2.sendTelegram();
        //SetDatapointValue myTelegram3(1, false, pSerialConnection);
        //myTelegram3.sendTelegram();
        //std::this_thread::sleep_for(500ms);
        //SetDatapointValue myTelegram4(3, true, pSerialConnection);
        //myTelegram4.sendTelegram();
        //SetDatapointValue myTelegram5(2, false, pSerialConnection);
        //myTelegram5.sendTelegram();
        //std::this_thread::sleep_for(500ms);
        //SetDatapointValue myTelegram6(4, true, pSerialConnection);
        //myTelegram6.sendTelegram();
        //SetDatapointValue myTelegram7(3, false, pSerialConnection);
        //myTelegram7.sendTelegram();
        //std::this_thread::sleep_for(500ms);
        //SetDatapointValue myTelegram8(4, false, pSerialConnection);
        //myTelegram8.sendTelegram();
    //}

    delete myTelegram1;
    delete serialConnection;
    return EXIT_SUCCESS;
}
