#include "../include/BaosMini.hpp"

int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;
    SerialConnection serialConnection("COM3");
    
    IndicationListener il(&serialConnection);

    //GetParameterByte gpb(9, &serialConnection);
    //printf("Param #9: %hhu", gpb.getByte());

    //SetServerItem ssi(&serialConnection);
    //ssi.setProgrammingMode(true, true);

    //GetServerItem gsi(HARDWARE_TYPE, 20, &serialConnection);

    //GetDatapointDescription gdd1(1, &serialConnection);
    //gdd.printDpDescription(true, false, false);
    //GetDatapointDescription gdd2(19, &serialConnection);
    //gdd.printDpDescription(true, true, true);
    //GetDatapointDescription gdd3(3, &serialConnection);
    //gdd.printDpDescription(true, true, true);
    //GetDatapointDescription gdd4(4, &serialConnection);
    //gdd.printDpDescription(true, true, true);
    //GetDatapointDescription gdd5(5, &serialConnection);
    //gdd.printDpDescription(true, true, true);
    //GetDatapointDescription gdd6(9, &serialConnection);
    //gdd.printDpDescription(true, true, true);

    //SetServerItem ssi(&serialConnection);
    //ssi.setProgrammingMode(true, true);

    //SetDatapointValue dp9(9, &serialConnection);
    //dp9.setFloatValue2Byte(-37.78, SetNewValueAndSendOnBus, true);

    //GetDatapointValue dpv1(1, DatapointTypes::BOOLEAN, &serialConnection);
    //printf("Datapoint 1: %hhu\n", dpv.getBooleanValue());
    //GetDatapointValue dpv2(1300, DatapointTypes::BOOLEAN, &serialConnection);
    //printf("Datapoint 1300: %hhu\n", dpv.getBooleanValue());
    //GetDatapointValue dpv3(3, DatapointTypes::BOOLEAN, &serialConnection);
    //printf("Datapoint 3: %hhu\n", dpv.getBooleanValue());
    //GetDatapointValue dpv4(4, DatapointTypes::BOOLEAN, &serialConnection);
    //printf("Datapoint 4: %hhu\n", dpv.getBooleanValue());
    //GetDatapointValue dpv5(9, DatapointTypes::FLOAT_VALUE_2BYTE, &serialConnection);
    //printf("Datapoint 9: %.2f\n", dpv.getFloatValue2Byte());

    //SetDatapointValue dp1(1, &serialConnection);
    //dp1.setBoolean(true, SetNewValueAndSendOnBus, true);
    //SetDatapointValue dp2(2, &serialConnection);
    //dp2.setBoolean(true, SetNewValueAndSendOnBus, true);
    //SetDatapointValue dp3(3, &serialConnection);
    //dp3.setBoolean(true, SetNewValueAndSendOnBus, true);
    //SetDatapointValue dp4(4, &serialConnection);
    //dp4.setBoolean(true, SetNewValueAndSendOnBus, true);

    //const auto RUN_SPEED = 200ms;
    //
    //SetDatapointValue dp1(1, &serialConnection);
    //SetDatapointValue dp2(2, &serialConnection);
    //SetDatapointValue dp3(3, &serialConnection);
    //SetDatapointValue dp4(4, &serialConnection);
    //
    //dp1.setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp1.setBoolean(false, CommandByte::SetNewValueAndSendOnBus);
    //dp2.setBoolean(true, CommandByte::SetNewValueAndSendOnBus);  
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp2.setBoolean(false, CommandByte::SetNewValueAndSendOnBus);
    //dp3.setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp3.setBoolean(false, CommandByte::SetNewValueAndSendOnBus);
    //dp4.setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp4.setBoolean(false, CommandByte::SetNewValueAndSendOnBus);

    return EXIT_SUCCESS;
}
