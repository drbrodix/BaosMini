#include "BaosMini.hpp"


int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;
    SerialConnection *serialConnection = new SerialConnection("COM3");

    Datapoint* dp = new Datapoint(1);
    dp->setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
    
    BaosTelegram *baosTelegram = new SetDatapointValue(dp);

    serialConnection->sendTelegram(baosTelegram);

    std::this_thread::sleep_for(1000ms);

    dp->setBoolean(false, CommandByte::SetNewValueAndSendOnBus);
    baosTelegram = new SetDatapointValue(dp);


    serialConnection->sendTelegram(baosTelegram);

    delete dp;
    delete baosTelegram;

    delete serialConnection;
    return EXIT_SUCCESS;
}
