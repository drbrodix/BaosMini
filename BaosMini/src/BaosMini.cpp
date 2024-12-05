#include "../include/BaosMini.hpp"

int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;
    SerialConnection *serialConnection = new SerialConnection("COM3");
    
    //IndicationListener* il = new IndicationListener(serialConnection);
    //il->startListening();
    //delete il;

    //GetParameterByte* gpb = new GetParameterByte(330, serialConnection);
    //printf("Param #9: %hhu", gpb->getByte());
    //delete gpb;

    //SetServerItem* ssi = new SetServerItem(serialConnection);
    //ssi->setProgrammingMode(false);
    //delete ssi;

    //GetServerItem* gsi = new GetServerItem(HARDWARE_TYPE, 20, serialConnection);
    //delete gsi;


    //GetDatapointDescription* gdd = new GetDatapointDescription(1, serialConnection);
    //gdd->printDpDescription(true, false, false);

    //gdd = new GetDatapointDescription(19, serialConnection);
    //gdd->printDpDescription(true, true, true);

    //gdd = new GetDatapointDescription(3, serialConnection);
    //gdd->printDpDescription(true, true, true);

    //gdd = new GetDatapointDescription(4, serialConnection);
    //gdd->printDpDescription(true, true, true);

    //gdd = new GetDatapointDescription(5, serialConnection);
    //gdd->printDpDescription(true, true, true);

    //gdd = new GetDatapointDescription(9, serialConnection);
    //gdd->printDpDescription(true, true, true);

    //delete gdd;

    //SetServerItem* ssi = new SetServerItem(serialConnection);
    //ssi->setProgrammingMode(false, true);
    //delete ssi;

    //SetDatapointValue* dp9 = new SetDatapointValue(9, serialConnection);
    //dp9->setFloatValue2Byte(-37.78, SetNewValueAndSendOnBus);
    //delete dp9;

    //GetDatapointValue* dpv = new GetDatapointValue(9, DatapointTypes::FLOAT_VALUE_2BYTE, serialConnection);

    GetDatapointValue* dpv = new GetDatapointValue(1, DatapointTypes::BOOLEAN, serialConnection);
    printf("Datapoint 1: %hhu\n", dpv->getBooleanValue());
    dpv = new GetDatapointValue(1300, DatapointTypes::BOOLEAN, serialConnection);
    printf("Datapoint 1300: %hhu\n", dpv->getBooleanValue());
    dpv = new GetDatapointValue(3, DatapointTypes::BOOLEAN, serialConnection);
    printf("Datapoint 3: %hhu\n", dpv->getBooleanValue());
    dpv = new GetDatapointValue(4, DatapointTypes::BOOLEAN, serialConnection);
    printf("Datapoint 4: %hhu\n", dpv->getBooleanValue());
    dpv = new GetDatapointValue(9, DatapointTypes::FLOAT_VALUE_2BYTE, serialConnection);
    printf("Datapoint 9: %.2f\n", dpv->getFloatValue2Byte());
    delete dpv;

    //SetDatapointValue* dp1 = new SetDatapointValue(1, serialConnection);
    //dp1->setBoolean(false, SetNewValueAndSendOnBus, true);
    //delete dp1;
    //SetDatapointValue* dp2 = new SetDatapointValue(2, serialConnection);
    //dp2->setBoolean(false, SetNewValueAndSendOnBus, true);
    //delete dp2;
    //SetDatapointValue* dp3 = new SetDatapointValue(3, serialConnection);
    //dp3->setBoolean(false, SetNewValueAndSendOnBus, true);
    //delete dp3;
    //SetDatapointValue* dp4 = new SetDatapointValue(4, serialConnection);
    //dp4->setBoolean(false, SetNewValueAndSendOnBus, true);
    //delete dp4;

    //GetDatapointValue* dpv2 = new GetDatapointValue(1, DatapointTypes::BOOLEAN, serialConnection);
    //dpv2->printDpValue();
    //dpv2 = new GetDatapointValue(2, DatapointTypes::BOOLEAN, serialConnection);
    //dpv2->printDpValue();
    //dpv2 = new GetDatapointValue(3, DatapointTypes::BOOLEAN, serialConnection);
    //dpv2->printDpValue();
    //dpv2 = new GetDatapointValue(4, DatapointTypes::BOOLEAN, serialConnection);
    //dpv2->printDpValue();
    //delete dpv2;

    //const auto RUN_SPEED = 200ms;
    //
    //SetDatapointValue* dp1 = new SetDatapointValue(1, serialConnection);
    //SetDatapointValue* dp2 = new SetDatapointValue(2, serialConnection);
    //SetDatapointValue* dp3 = new SetDatapointValue(3, serialConnection);
    //SetDatapointValue* dp4 = new SetDatapointValue(4, serialConnection);

    //dp1->setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp1->setBoolean(false, CommandByte::SetNewValueAndSendOnBus);
    //dp2->setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
    //delete dp1;
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp2->setBoolean(false, CommandByte::SetNewValueAndSendOnBus);
    //dp3->setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
    //delete dp2;
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp3->setBoolean(false, CommandByte::SetNewValueAndSendOnBus);
    //dp4->setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
    //delete dp3;
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp4->setBoolean(false, CommandByte::SetNewValueAndSendOnBus);
    //delete dp4;

    delete serialConnection;
    return EXIT_SUCCESS;
}
