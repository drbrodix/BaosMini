#include "../include/BaosMini.hpp"

static void printConfigFlags(unsigned short dpId, ConfigFlags configFlagByte)
{
    printf("Datapoint %hu:\n", dpId);
    printf("\tTransmit priority: ");
    switch (configFlagByte.transmitPriority)
    {
    case 0b00:
        printf("System priority\n");
        break;
    case 0b01:
        printf("High priority\n");
        break;
    case 0b10:
        printf("Alarm priority\n");
        break;
    case 0b11:
        printf("Low priority\n");
        break;
    default:
        printf("unknown\n");
        break;
    }

    printf("\tDatapoint communication: %s\n",
        configFlagByte.datapointCommunication ? "Enabled" : "Disabled");

    printf("\tRead from bus: %s\n",
        configFlagByte.readFromBus ? "Enabled" : "Disabled");

    printf("\tWrite from bus: %s\n",
        configFlagByte.writeFromBus ? "Enabled" : "Disabled");

    printf("\tRead on init: %s\n",
        configFlagByte.readOnInit ? "Enabled" : "Disabled");

    printf("\tTransmit to bus: %s\n",
        configFlagByte.transmitToBus ? "Enabled" : "Disabled");

    printf("\tUpdate on response: %s\n",
        configFlagByte.updateOnResponse ? "Enabled" : "Disabled");
}

int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;
    SerialConnection serialConnection("COM3");
    
    IndicationListener il(&serialConnection);

    //GetParameterByte gpb(9, &serialConnection);
    //printf("Param #9: %hhu", gpb.getByte());

    SetServerItem ssi(&serialConnection);
    ssi.setProgrammingMode(true);
    ssi.setBaudrate(BAUDRATES::BAUDRATE_19200, true);

    //GetServerItem gsi(&serialConnection);
    //BaosHardwareType baosHardwareType = gsi.getHardwareType();
    //printf("Hardware Type single request: %02X %02X %02X %02X %02X %02X\n",
    //    baosHardwareType.byte1,
    //    baosHardwareType.byte2,
    //    baosHardwareType.byte3,
    //    baosHardwareType.byte4,
    //    baosHardwareType.byte5,
    //    baosHardwareType.byte6);
    //BaosVersion hardwareVersion = gsi.getHardwareVersion();
    //printf("Hardware Version single request: %d.%d\n",
    //    hardwareVersion.mainVersion,
    //    hardwareVersion.minorVersion);
    //BaosVersion firmwareVersion = gsi.getFirmwareVersion();
    //printf("Firmware Version single request: %d.%d\n",
    //    firmwareVersion.mainVersion,
    //    firmwareVersion.minorVersion);
    //printf("KNX Device Manufacturer Code single request: %04X\n",
    //    gsi.getKnxDeviceManufacturerCode());
    //printf("KNX App Manufacturer Code single request: %04X\n",
    //    gsi.getKnxAppManufacturerCode());
    //printf("Application ID single request: %04X\n",
    //    gsi.getApplicationId());
    //BaosVersion applicationVersion = gsi.getApplicationVersion();
    //printf("Application Version single request: %d.%d\n",
    //    applicationVersion.mainVersion,
    //    applicationVersion.minorVersion);
    //BaosSerialNumber baosSerialNumber = gsi.getSerialNumber();
    //printf("Serial Number single request: %02X %02X %02X %02X %02X %02X\n",
    //    baosSerialNumber.byte1,
    //    baosSerialNumber.byte2,
    //    baosSerialNumber.byte3,
    //    baosSerialNumber.byte4,
    //    baosSerialNumber.byte5,
    //    baosSerialNumber.byte6);
    //BaosTime timeSinceReset = gsi.getTimeSinceReset();
    //printf("Time since reset single request: %02d:%02d:%02d\n",
    //    timeSinceReset.hours,
    //    timeSinceReset.minutes,
    //    timeSinceReset.seconds);
    //printf("Bus connection state single request: %s\n",
    //    gsi.getBusConnectionState() ? "true" : "false");
    //printf("Maximum buffer size single request: %hu\n",
    //    gsi.getMaxBufferSize());
    //printf("Length of description string single request: %hu\n",
    //    gsi.getLengthOfDescString());
    //switch (gsi.getBaudrate())
    //{
    //case BAUDRATE_115200:
    //    printf("Baudrate single request: 115200 Baud\n");
    //    break;
    //case BAUDRATE_19200:
    //    printf("Baudrate single request: 19200 Baud\n");
    //    break;
    //default:
    //    printf("Baudrate single request: unknown\n");
    //    break;
    //}
    //printf("Current buffer size single request: %hu\n",
    //    gsi.getCurrentBufferSize());
    //printf("Programming mode enabled single request: %s\n",
    //    gsi.getProgrammingMode() ? "true" : "false");
    //BaosVersion protocolVersionBinary = gsi.getProtocolVersionBinary();
    //printf("Binary protocol version single request: %d.%d\n",
    //    protocolVersionBinary.mainVersion,
    //    protocolVersionBinary.minorVersion);
    //printf("Indication sending enabled single request: %s\n",
    //    gsi.getIndicationSending() ? "true" : "false");
    //BaosVersion protocolVersionWeb = gsi.getProtocolVersionWeb();
    //printf("WebService version single request: %d.%d\n",
    //    protocolVersionWeb.mainVersion,
    //    protocolVersionWeb.minorVersion);
    //BaosVersion protocolVersionRest = gsi.getProtocolVersionRest();
    //printf("RestService version single request: %d.%d\n",
    //    protocolVersionRest.mainVersion,
    //    protocolVersionRest.minorVersion);
    //KnxDeviceAddress knxDeviceAddress = gsi.getKnxIndividualAddress();
    //printf("Individual KNX Address single request: area: %hu line: %hu device: %hu\n",
    //    knxDeviceAddress.area,
    //    knxDeviceAddress.line,
    //    knxDeviceAddress.device);
    //printf("\n");
    
    // gsi.printServerItems(SERVER_ITEMS::SERIAL_NUMBER, 20);

    //GetDatapointDescription gdd1(1, &serialConnection);
    //GetDatapointDescription gdd2(2, &serialConnection);
    //GetDatapointDescription gdd3(3, &serialConnection);
    //GetDatapointDescription gdd4(4, &serialConnection);
    //GetDatapointDescription gdd5(5, &serialConnection);
    //GetDatapointDescription gdd9(9, &serialConnection);
    //
    //printConfigFlags(1, gdd1.getDpConfigFlags());
    //printConfigFlags(2, gdd2.getDpConfigFlags());
    //printConfigFlags(3, gdd3.getDpConfigFlags());
    //printConfigFlags(4, gdd4.getDpConfigFlags());
    //printConfigFlags(5, gdd5.getDpConfigFlags());
    //printConfigFlags(9, gdd9.getDpConfigFlags());

    /*GetDatapointDescription gdd1(1, &serialConnection);
    gdd1.printDpDescription(true, false, true);
    GetDatapointDescription gdd2(19, &serialConnection);
    gdd2.printDpDescription(true, true, true);
    GetDatapointDescription gdd3(3, &serialConnection);
    gdd3.printDpDescription(true, true, true);
    GetDatapointDescription gdd4(4, &serialConnection);
    gdd4.printDpDescription(true, true, true);
    GetDatapointDescription gdd5(5, &serialConnection);
    gdd5.printDpDescription(true, true, true);
    GetDatapointDescription gdd9(9, &serialConnection);
    gdd9.printDpDescription(true, true, true);*/

    //SetServerItem ssi(&serialConnection);
    //ssi.setProgrammingMode(true, true);

    //SetDatapointValue dp9(9, &serialConnection);
    //dp9.setFloatValue2Byte(-49.17f, SetNewValueAndSendOnBus, true);
    //
    //GetDatapointValue dpv1(1, DatapointTypes::BOOLEAN, &serialConnection);
    //printf("Datapoint 1: %hhu\n", dpv1.getBooleanValue());
    //GetDatapointValue dpv2(1300, DatapointTypes::BOOLEAN, &serialConnection);
    //printf("Datapoint 1300: %hhu\n", dpv2.getBooleanValue());
    //GetDatapointValue dpv3(3, DatapointTypes::BOOLEAN, &serialConnection);
    //printf("Datapoint 3: %hhu\n", dpv3.getBooleanValue());
    //GetDatapointValue dpv4(4, DatapointTypes::BOOLEAN, &serialConnection);
    //printf("Datapoint 4: %hhu\n", dpv4.getBooleanValue());
    //GetDatapointValue dpv5(9, DatapointTypes::FLOAT_VALUE_2BYTE, &serialConnection);
    //printf("Datapoint 9: %.2f\n", dpv5.getFloatValue2Byte());

    //SetDatapointValue dp1(1, &serialConnection);
    //dp1.setBoolean(true, SetNewValueAndSendOnBus, true);
    //SetDatapointValue dp2(2, &serialConnection);
    //dp2.setBoolean(true, SetNewValueAndSendOnBus, true);
    //SetDatapointValue dp3(3, &serialConnection);
    //dp3.setBoolean(true, SetNewValueAndSendOnBus, true);
    //SetDatapointValue dp4(4, &serialConnection);
    //dp4.setBoolean(true, SetNewValueAndSendOnBus, true);

    //const auto RUN_SPEED = 500ms;
    //
    //SetDatapointValue dp1(1, &serialConnection);
    //SetDatapointValue dp2(2, &serialConnection);
    //SetDatapointValue dp3(3, &serialConnection);
    //SetDatapointValue dp4(4, &serialConnection);
    //
    //dp1.setBoolean(true, CommandByte::SetNewValueAndSendOnBus, true);
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp1.setBoolean(false, CommandByte::SetNewValueAndSendOnBus, true);
    //dp2.setBoolean(true, CommandByte::SetNewValueAndSendOnBus, true);  
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp2.setBoolean(false, CommandByte::SetNewValueAndSendOnBus, true);
    //dp3.setBoolean(true, CommandByte::SetNewValueAndSendOnBus, true);
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp3.setBoolean(false, CommandByte::SetNewValueAndSendOnBus, true);
    //dp4.setBoolean(true, CommandByte::SetNewValueAndSendOnBus, true);
    //std::this_thread::sleep_for(RUN_SPEED);
    //dp4.setBoolean(false, CommandByte::SetNewValueAndSendOnBus, true);

    return EXIT_SUCCESS;
}
