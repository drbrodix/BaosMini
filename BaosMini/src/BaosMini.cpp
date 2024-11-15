#include "BaosMini.hpp"


int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;
    SerialConnection *serialConnection = new SerialConnection("COM3");

    BaosTelegram *myTelegram1 = new GetServerItem(1, 5);
    serialConnection->sendTelegram(myTelegram1->getTelegramData());

    //BaosTelegram *myTelegram1 = new GetDatapointValue(3, 1);
    //serialConnection->sendTelegram(myTelegram1->getTelegramData());
    
    //BaosTelegram *myTelegram2 = new GetDatapointValue(1, 1);
    //serialConnection->sendTelegram(myTelegram2->getTelegramData());
    //
    //BaosTelegram* myTelegram3 = new GetDatapointValue(3, true);
    //serialConnection->sendTelegram(myTelegram3->getTelegramData());
    //
    //BaosTelegram* myTelegram4 = new GetDatapointValue(4, true);
    //serialConnection->sendTelegram(myTelegram4->getTelegramData());

    //BaosTelegram *myTelegram1 = new SetDatapointValue(1, true);
    //serialConnection->sendTelegram(myTelegram1->getTelegramData());
    //std::this_thread::sleep_for(500ms);
    //BaosTelegram *myTelegram2 = new GetDatapointValue(1, 1);
    //serialConnection->sendTelegram(myTelegram2->getTelegramData());
    //std::this_thread::sleep_for(500ms);
    //BaosTelegram* myTelegram3 = new SetDatapointValue(3, true);
    //serialConnection->sendTelegram(myTelegram3->getTelegramData());
    //std::this_thread::sleep_for(500ms);
    //BaosTelegram* myTelegram4 = new SetDatapointValue(4, true);
    //serialConnection->sendTelegram(myTelegram4->getTelegramData());
    //std::this_thread::sleep_for(500ms);
    //BaosTelegram* myTelegram5 = new SetDatapointValue(1, false);
    //serialConnection->sendTelegram(myTelegram5->getTelegramData());
    //std::this_thread::sleep_for(500ms);
    //BaosTelegram* myTelegram6 = new GetDatapointValue(1, 1);
    //serialConnection->sendTelegram(myTelegram6->getTelegramData());
    //std::this_thread::sleep_for(500ms);
    //BaosTelegram* myTelegram7 = new SetDatapointValue(3, false);
    //serialConnection->sendTelegram(myTelegram7->getTelegramData());
    //std::this_thread::sleep_for(500ms);
    //BaosTelegram* myTelegram8 = new SetDatapointValue(4, false);
    //serialConnection->sendTelegram(myTelegram8->getTelegramData());
    //std::this_thread::sleep_for(500ms);

    /*for (int i = 0; i < 4; i++)
    {*/
        //SetDatapointValue myTelegram1(1, true, pSerialConnection);
        //myTelegram1.sendTelegram();
        
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
    //delete myTelegram2;
    //delete myTelegram3;
    //delete myTelegram4;

    delete serialConnection;
    return EXIT_SUCCESS;
}
