#include "../../include/utility/BaosTester.hpp"

BaosTester::BaosTester(SerialConnection* serialConnection)
	: serialConnection(serialConnection)
{
}

BaosTester::~BaosTester()
{
}

void BaosTester::startTestingProcess(
	bool runGetServerItemTest,
	bool runSetServerItemTest,
	bool runGetDatapointDescriptionTest,
	bool runGetDatapointValueTest,
	bool runSetDatapointValueTest,
	bool runGetParameterByteTest
)
{
	if (runGetServerItemTest) testGetServerItem();
	if (runSetServerItemTest) testSetServerItem();
	if (runGetDatapointDescriptionTest) testGetDatapointDescription();
	if (runGetDatapointValueTest) testGetDatapointValue();
	if (runSetDatapointValueTest) testSetDatapointValue();
	if (runGetParameterByteTest) testGetParameterByte();
}

void BaosTester::testGetServerItem()
{
	printf("TESTING GET SERVER ITEM STARTED\n\n");

	GetServerItem gsi(serialConnection);

	BaosHardwareType baosHardwareType = gsi.getHardwareType();
	printf("Hardware Type single request: %02X %02X %02X %02X %02X %02X\n",
	    baosHardwareType.byte1,
	    baosHardwareType.byte2,
	    baosHardwareType.byte3,
	    baosHardwareType.byte4,
	    baosHardwareType.byte5,
	    baosHardwareType.byte6);
	BaosVersion hardwareVersion = gsi.getHardwareVersion();
	printf("Hardware Version single request: %d.%d\n",
	    hardwareVersion.mainVersion,
	    hardwareVersion.minorVersion);
	BaosVersion firmwareVersion = gsi.getFirmwareVersion();
	printf("Firmware Version single request: %d.%d\n",
	    firmwareVersion.mainVersion,
	    firmwareVersion.minorVersion);
	printf("KNX Device Manufacturer Code single request: %04X\n",
	    gsi.getKnxDeviceManufacturerCode());
	printf("KNX App Manufacturer Code single request: %04X\n",
	    gsi.getKnxAppManufacturerCode());
	printf("Application ID single request: %04X\n",
	    gsi.getApplicationId());
	BaosVersion applicationVersion = gsi.getApplicationVersion();
	printf("Application Version single request: %d.%d\n",
	    applicationVersion.mainVersion,
	    applicationVersion.minorVersion);
	BaosSerialNumber baosSerialNumber = gsi.getSerialNumber();
	printf("Serial Number single request: %02X %02X %02X %02X %02X %02X\n",
	    baosSerialNumber.byte1,
	    baosSerialNumber.byte2,
	    baosSerialNumber.byte3,
	    baosSerialNumber.byte4,
	    baosSerialNumber.byte5,
	    baosSerialNumber.byte6);
	BaosTime timeSinceReset = gsi.getTimeSinceReset();
	printf("Time since reset single request: %02d:%02d:%02d\n",
	    timeSinceReset.hours,
	    timeSinceReset.minutes,
	    timeSinceReset.seconds);
	printf("Bus connection state single request: %s\n",
	    gsi.getBusConnectionState() ? "true" : "false");
	printf("Maximum buffer size single request: %hu\n",
	    gsi.getMaxBufferSize());
	printf("Length of description string single request: %hu\n",
	    gsi.getLengthOfDescString());
	switch (gsi.getBaudrate())
	{
		case BAUDRATE_115200:
			printf("Baudrate single request: 115200 Baud\n");
			break;
		case BAUDRATE_19200:
			printf("Baudrate single request: 19200 Baud\n");
			break;
		default:
			printf("Baudrate single request: unknown\n");
			break;
	}
	printf("Current buffer size single request: %hu\n",
	    gsi.getCurrentBufferSize());
	printf("Programming mode enabled single request: %s\n",
	    gsi.getProgrammingMode() ? "true" : "false");
	BaosVersion protocolVersionBinary = gsi.getProtocolVersionBinary();
	printf("Binary protocol version single request: %d.%d\n",
	    protocolVersionBinary.mainVersion,
	    protocolVersionBinary.minorVersion);
	printf("Indication sending enabled single request: %s\n",
	    gsi.getIndicationSending() ? "true" : "false");
	BaosVersion protocolVersionWeb = gsi.getProtocolVersionWeb();
	printf("WebService version single request: %d.%d\n",
	    protocolVersionWeb.mainVersion,
	    protocolVersionWeb.minorVersion);
	BaosVersion protocolVersionRest = gsi.getProtocolVersionRest();
	printf("RestService version single request: %d.%d\n",
	    protocolVersionRest.mainVersion,
	    protocolVersionRest.minorVersion);
	KnxDeviceAddress knxDeviceAddress = gsi.getKnxIndividualAddress();
	printf("Individual KNX Address single request: area: %hu line: %hu device: %hu\n",
	    knxDeviceAddress.area,
	    knxDeviceAddress.line,
	    knxDeviceAddress.device);

	printf("\nTESTING GET SERVER ITEM FINISHED\n\n");
}

void BaosTester::testSetServerItem()
{
	printf("TESTING SET SERVER ITEM STARTED\n\n");

	SetServerItem ssi(serialConnection);
	ssi.setBaudrate(BAUDRATE_19200, true);
	ssi.setCurrentBufferSize(125, true);
	ssi.setCurrentBufferSize(250, true);
	ssi.setIndicationSending(false, true);
	ssi.setIndicationSending(true, true);
	ssi.setProgrammingMode(true, true);
	ssi.setProgrammingMode(false, true);

	printf("\nTESTING SET SERVER ITEM FINISHED\n\n");
}

void BaosTester::testGetDatapointDescription()
{
	printf("TESTING GET DATAPOINT DESCRIPTION STARTED\n\n");

	GetDatapointDescription(1,	serialConnection)
		.printDpDescription(true, true, true);
	GetDatapointDescription(2,	serialConnection)
		.printDpDescription(true, true, true);
	GetDatapointDescription(3,	serialConnection)
		.printDpDescription(true, true, true);
	GetDatapointDescription(4,	serialConnection)
		.printDpDescription(true, true, true);
	GetDatapointDescription(5,	serialConnection)
		.printDpDescription(true, true, true);
	GetDatapointDescription(9,	serialConnection)
		.printDpDescription(true, true, true);
	GetDatapointDescription(13, serialConnection)
		.printDpDescription(true, true, true);
	GetDatapointDescription(17, serialConnection)
		.printDpDescription(true, true, true);
	GetDatapointDescription(25, serialConnection)
		.printDpDescription(true, true, true);
	GetDatapointDescription(69, serialConnection)
		.printDpDescription(true, true, true);

	printf("\nTESTING GET DATAPOINT DESCRIPTION FINISHED\n\n");
}

void BaosTester::testGetDatapointValue()
{
	printf("TESTING GET DATAPOINT VALUE STARTED\n\n");

	printf(
			"Datapoint 1: %d\n",
			GetDatapointValue(
								1,
								DatapointTypes::BOOLEAN,
								serialConnection
							 ).getBooleanValue()
		  );

	printf(
			"Datapoint 2: %d\n",
			GetDatapointValue(
								2,
								DatapointTypes::BOOLEAN,
								serialConnection
							 ).getBooleanValue()
		  );

	printf(
			"Datapoint 3: %d\n",
			GetDatapointValue(
								3,
								DatapointTypes::BOOLEAN,
								serialConnection
							 ).getBooleanValue()
		  );

	printf(
			"Datapoint 4: %d\n",
			GetDatapointValue(
								4,
								DatapointTypes::BOOLEAN,
								serialConnection
							 ).getBooleanValue()
		  );

	printf(
			"Datapoint 5: %d\n",
			GetDatapointValue(
								5,
								DatapointTypes::FLOAT_VALUE_2BYTE,
								serialConnection
							 ).getBooleanValue()
		  );

	printf(
			"Datapoint 9: %d\n",
			GetDatapointValue(
								9,
								DatapointTypes::SIGNED_VALUE_2BYTE,
								serialConnection
							 ).getFloatValue2Byte()
		  );

	printf(
			"Datapoint 13: %d\n",
			GetDatapointValue(
								13,
								DatapointTypes::UNSIGNED_VALUE_2BYTE,
								serialConnection
							 ).getFloatValue2Byte()
		  );

	printf(
			"Datapoint 17: %d\n",
			GetDatapointValue(
								17,
								DatapointTypes::FLOAT_VALUE_4BYTE,
								serialConnection
							 ).getFloatValue2Byte()
		  );

	printf(
			"Datapoint 25: %d\n",
			GetDatapointValue(
								25,
								DatapointTypes::SIGNED_VALUE_4BYTE,
								serialConnection
							 ).getFloatValue2Byte()
		  );

	printf(
			"Datapoint 69: %d\n",
			GetDatapointValue(
								69,
								DatapointTypes::UNSIGNED_VALUE_4BYTE,
								serialConnection
							 ).getFloatValue2Byte()
		  );

	printf("\nTESTING GET DATAPOINT VALUE FINISHED\n\n");
}

void BaosTester::testSetDatapointValue()
{
	printf("TESTING SET DATAPOINT VALUE STARTED\n\n");

	SetDatapointValue sdv1(1, serialConnection);
	sdv1.setBoolean(true, CommandByte::SetNewValueAndSendOnBus, true);
	sdv1.setBoolean(false, CommandByte::SetNewValueAndSendOnBus, true);

	SetDatapointValue sdv2(2, serialConnection);
	sdv2.setBoolean(true, CommandByte::SetNewValueAndSendOnBus, true);
	sdv2.setBoolean(false, CommandByte::SetNewValueAndSendOnBus, true);

	SetDatapointValue sdv3(3, serialConnection);
	sdv3.setBoolean(true, CommandByte::SetNewValueAndSendOnBus, true);
	sdv3.setBoolean(false, CommandByte::SetNewValueAndSendOnBus, true);

	SetDatapointValue sdv4(4, serialConnection);
	sdv4.setBoolean(true, CommandByte::SetNewValueAndSendOnBus, true);
	sdv4.setBoolean(false, CommandByte::SetNewValueAndSendOnBus, true);

	SetDatapointValue sdv5(9, serialConnection);
	sdv5.setFloatValue2Byte(3.14, CommandByte::SetNewValueAndSendOnBus, true);

	SetDatapointValue sdv6(11, serialConnection);
	sdv6.setSignedValue2Byte(25, CommandByte::SetNewValueAndSendOnBus, true);

	SetDatapointValue sdv7(13, serialConnection);
	sdv7.setUnsignedValue2Byte(13975, CommandByte::SetNewValueAndSendOnBus, true);

	SetDatapointValue sdv8(17, serialConnection);
	sdv8.setFloatValue4Byte(17.97528, CommandByte::SetNewValueAndSendOnBus, true);

	SetDatapointValue sdv9(25, serialConnection);
	sdv9.setSignedValue4Byte(-12759, CommandByte::SetNewValueAndSendOnBus, true);

	SetDatapointValue sdv10(69, serialConnection);
	sdv10.setUnsignedValue4Byte(179635, CommandByte::SetNewValueAndSendOnBus, true);

	printf("\nTESTING SET DATAPOINT VALUE FINISHED\n\n");
}

void BaosTester::testGetParameterByte()
{
	printf("TESTING GET PARAMETER BYTE STARTED\n\n");

	printf(
			"Parameter 1: %hhu\n",
			GetParameterByte(
							1,
							serialConnection
							).getByte()
		  );

	printf(
			"Parameter 2: %hhu\n",
			GetParameterByte(
							2,
							serialConnection
							).getByte()
		  );

	printf(
			"Parameter 3: %hhu\n",
			GetParameterByte(
							3,
							serialConnection
							).getByte()
		  );

	printf(
			"Parameter 4: %hhu\n",
			GetParameterByte(
							4,
							serialConnection
							).getByte()
		  );

	printf(
			"Parameter 5: %hhu\n",
			GetParameterByte(
							5,
							serialConnection
							).getByte()
		  );

	printf(
			"Parameter 9: %hhu\n",
			GetParameterByte(
							9,
							serialConnection
							).getByte()
		  );

	printf(
			"Parameter 13: %hhu\n",
			GetParameterByte(
							13,
							serialConnection
							).getByte()
		  );

	printf(
			"Parameter 17: %hhu\n",
			GetParameterByte(
							17,
							serialConnection
							).getByte()
		  );

	printf(
			"Parameter 25: %hhu\n",
			GetParameterByte(
							25,
							serialConnection
							).getByte()
		  );

	printf(
			"Parameter 69: %hhu\n",
			GetParameterByte(
							69,
							serialConnection
							).getByte()
		  );

	printf("\nTESTING GET PARAMETER BYTE FINISHED\n\n");
}