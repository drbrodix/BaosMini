#include "../include/BaosMini.hpp"


int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;
    SerialConnection *serialConnection = new SerialConnection("COM3");

    GetServerItem* gsi = new GetServerItem(1, 5, serialConnection);
    delete gsi;

    Datapoint* dp1 = new Datapoint(1, serialConnection);
    Datapoint* dp2 = new Datapoint(2, serialConnection);
    Datapoint* dp3 = new Datapoint(3, serialConnection);
    Datapoint* dp4 = new Datapoint(4, serialConnection);
    dp1->setSignedValue1Byte(true, CommandByte::SetNewValueAndSendOnBus);
    std::this_thread::sleep_for(1000ms);
    dp1->setSignedValue1Byte(false, CommandByte::SetNewValueAndSendOnBus);
    dp2->setSignedValue1Byte(true, CommandByte::SetNewValueAndSendOnBus);
    delete dp1;
    std::this_thread::sleep_for(1000ms);
    dp2->setSignedValue1Byte(false, CommandByte::SetNewValueAndSendOnBus);
    dp3->setSignedValue1Byte(true, CommandByte::SetNewValueAndSendOnBus);
    delete dp2;
    std::this_thread::sleep_for(1000ms);
    dp3->setSignedValue1Byte(false, CommandByte::SetNewValueAndSendOnBus);
    dp4->setSignedValue1Byte(true, CommandByte::SetNewValueAndSendOnBus);
    delete dp3;
    std::this_thread::sleep_for(1000ms);
    dp4->setSignedValue1Byte(false, CommandByte::SetNewValueAndSendOnBus);
    delete dp4;

    delete serialConnection;
    return EXIT_SUCCESS;
}
