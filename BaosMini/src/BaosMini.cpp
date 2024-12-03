#include "../include/BaosMini.hpp"

int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;
    SerialConnection *serialConnection = new SerialConnection("COM3");
    
    IndicationListener* il = new IndicationListener(serialConnection);
    il->startListening();
    delete il;
    
    //GetDescriptionString* gds = new GetDescriptionString(1, serialConnection);
    //delete gds;

    //GetParameterByte* gpb = new GetParameterByte(1, 10, serialConnection);
    //delete gpb;

    //GetServerItem* gsi = new GetServerItem(HARDWARE_TYPE, 20, serialConnection);
    //delete gsi;

    //GetDatapointDescription* gdd = new GetDatapointDescription(1, serialConnection);
    //gdd = new GetDatapointDescription(2, serialConnection);
    //printf("%hhu\n", gdd->getDpDpt());
    //gdd = new GetDatapointDescription(3, serialConnection);
    //printf("%hhu\n", gdd->getDpDpt());
    //gdd = new GetDatapointDescription(4, serialConnection);
    //printf("%hhu\n", gdd->getDpDpt());
    //gdd = new GetDatapointDescription(5, serialConnection);
    //printf("%hhu\n", gdd->getDpDpt());
    //gdd = new GetDatapointDescription(9, serialConnection);
    //printf("%hhu\n", gdd->getDpDpt());
    //delete gdd;

    //SetServerItem* ssi = new SetServerItem(serialConnection);
    //ssi->SetProgrammingMode(true);
    //delete ssi;

    //Datapoint* dp9 = new Datapoint(9, serialConnection);
    //dp9->setFloatValue2Byte(27.9, SetNewValueAndSendOnBus);
    //delete dp9;

    //GetDatapointValue* dpv = new GetDatapointValue(9, DatapointTypes::FLOAT_VALUE_2BYTE, serialConnection);

    /*GetDatapointValue* dpv = new GetDatapointValue(1, DatapointTypes::BOOLEAN, serialConnection);
    dpv = new GetDatapointValue(1300, DatapointTypes::BOOLEAN, serialConnection);
    dpv = new GetDatapointValue(3, DatapointTypes::BOOLEAN, serialConnection);
    dpv = new GetDatapointValue(4, DatapointTypes::BOOLEAN, serialConnection);
    delete dpv;*/

    //Datapoint* dp = new Datapoint(1, serialConnection);
    //dp->setBoolean(false, SetNewValueAndSendOnBus);
    //dp = new Datapoint(2, serialConnection);
    //dp->setBoolean(false, SetNewValueAndSendOnBus);
    //dp = new Datapoint(3, serialConnection);
    //dp->setBoolean(false, SetNewValueAndSendOnBus);
    //dp = new Datapoint(4, serialConnection);
    //dp->setBoolean(false, SetNewValueAndSendOnBus);
    //delete dp;

    //GetDatapointValue* dpv2 = new GetDatapointValue(1, DatapointTypes::BOOLEAN, serialConnection);
    //dpv2 = new GetDatapointValue(2, DatapointTypes::BOOLEAN, serialConnection);
    //dpv2 = new GetDatapointValue(3, DatapointTypes::BOOLEAN, serialConnection);
    //dpv2 = new GetDatapointValue(4, DatapointTypes::BOOLEAN, serialConnection);
    //delete dpv2;

    //Datapoint* dp1 = new Datapoint(1, serialConnection);
    //Datapoint* dp2 = new Datapoint(2, serialConnection);
    //Datapoint* dp3 = new Datapoint(3, serialConnection);
    //Datapoint* dp4 = new Datapoint(4, serialConnection);

    //dp1->setSignedValue1Byte(true, CommandByte::SetNewValueAndSendOnBus);
    //std::this_thread::sleep_for(1000ms);
    //dp1->setSignedValue1Byte(false, CommandByte::SetNewValueAndSendOnBus);
    //dp2->setSignedValue1Byte(true, CommandByte::SetNewValueAndSendOnBus);
    //delete dp1;
    //std::this_thread::sleep_for(1000ms);
    //dp2->setSignedValue1Byte(false, CommandByte::SetNewValueAndSendOnBus);
    //dp3->setSignedValue1Byte(true, CommandByte::SetNewValueAndSendOnBus);
    //delete dp2;
    //std::this_thread::sleep_for(1000ms);
    //dp3->setSignedValue1Byte(false, CommandByte::SetNewValueAndSendOnBus);
    //dp4->setSignedValue1Byte(true, CommandByte::SetNewValueAndSendOnBus);
    //delete dp3;
    //std::this_thread::sleep_for(1000ms);
    //dp4->setSignedValue1Byte(false, CommandByte::SetNewValueAndSendOnBus);
    //delete dp4;

    delete serialConnection;
    return EXIT_SUCCESS;
}
