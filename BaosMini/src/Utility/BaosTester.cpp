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
	printf("TESTING GET SERVER ITEM STARTED\n");

	GetServerItem gsi(serialConnection);
	gsi.getApplicationId();
	gsi.getApplicationVersion();
	gsi.getBaudrate();
	gsi.getBusConnectionState();
	gsi.getCurrentBufferSize();
	gsi.getFirmwareVersion();
	gsi.getHardwareType();
	gsi.getHardwareVersion();
	gsi.getIndicationSending();
	gsi.getKnxAppManufacturerCode();
	gsi.getKnxDeviceManufacturerCode();
	gsi.getKnxIndividualAddress();
	gsi.getLengthOfDescString();
	gsi.getMaxBufferSize();
	gsi.getProgrammingMode();
	gsi.getProtocolVersionBinary();
	gsi.getProtocolVersionRest();
	gsi.getProtocolVersionWeb();
	gsi.getSerialNumber();
	gsi.getTimeSinceReset();

	printf("TESTING GET SERVER ITEM FINISHED\n\n");
}

void BaosTester::testSetServerItem()
{
	printf("TESTING SET SERVER ITEM STARTED\n");

	SetServerItem ssi(serialConnection);
	ssi.setBaudrate(BAUDRATE_19200);
	ssi.setCurrentBufferSize(125);
	ssi.setCurrentBufferSize(250);
	ssi.setIndicationSending(false);
	ssi.setIndicationSending(true);
	ssi.setProgrammingMode(true);
	ssi.setProgrammingMode(false);

	printf("TESTING SET SERVER ITEM FINISHED\n\n");
}

void BaosTester::testGetDatapointDescription()
{
	printf("TESTING GET DATAPOINT DESCRIPTION STARTED\n");

	GetDatapointDescription(1,	serialConnection);
	GetDatapointDescription(2,	serialConnection);
	GetDatapointDescription(3,	serialConnection);
	GetDatapointDescription(4,	serialConnection);
	GetDatapointDescription(5,	serialConnection);
	GetDatapointDescription(9,	serialConnection);
	GetDatapointDescription(13, serialConnection);
	GetDatapointDescription(17, serialConnection);
	GetDatapointDescription(25, serialConnection);
	GetDatapointDescription(69, serialConnection);

	printf("TESTING GET DATAPOINT DESCRIPTION FINISHED\n\n");
}

void BaosTester::testGetDatapointValue()
{
	printf("TESTING GET DATAPOINT VALUE STARTED\n");

	GetDatapointValue(1, DatapointTypes::BOOLEAN, serialConnection);
	GetDatapointValue(2, DatapointTypes::BOOLEAN, serialConnection);
	GetDatapointValue(3, DatapointTypes::BOOLEAN, serialConnection);
	GetDatapointValue(4, DatapointTypes::BOOLEAN, serialConnection);
	GetDatapointValue(5, DatapointTypes::FLOAT_VALUE_2BYTE, serialConnection);
	GetDatapointValue(9, DatapointTypes::SIGNED_VALUE_2BYTE, serialConnection);
	GetDatapointValue(13, DatapointTypes::UNSIGNED_VALUE_2BYTE, serialConnection);
	GetDatapointValue(17, DatapointTypes::FLOAT_VALUE_4BYTE, serialConnection);
	GetDatapointValue(25, DatapointTypes::SIGNED_VALUE_4BYTE, serialConnection);
	GetDatapointValue(69, DatapointTypes::UNSIGNED_VALUE_4BYTE, serialConnection);

	printf("TESTING GET DATAPOINT VALUE FINISHED\n\n");
}

void BaosTester::testSetDatapointValue()
{
	printf("TESTING SET DATAPOINT VALUE STARTED\n");

	SetDatapointValue sdv1(1, serialConnection);
	sdv1.setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
	sdv1.setBoolean(false, CommandByte::SetNewValueAndSendOnBus);

	SetDatapointValue sdv2(2, serialConnection);
	sdv2.setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
	sdv2.setBoolean(false, CommandByte::SetNewValueAndSendOnBus);

	SetDatapointValue sdv3(3, serialConnection);
	sdv3.setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
	sdv3.setBoolean(false, CommandByte::SetNewValueAndSendOnBus);

	SetDatapointValue sdv4(4, serialConnection);
	sdv4.setBoolean(true, CommandByte::SetNewValueAndSendOnBus);
	sdv4.setBoolean(false, CommandByte::SetNewValueAndSendOnBus);

	SetDatapointValue sdv5(5, serialConnection);
	sdv5.setFloatValue2Byte(3.14, CommandByte::SetNewValueAndSendOnBus);

	SetDatapointValue sdv6(9, serialConnection);
	sdv6.setSignedValue2Byte(-7, CommandByte::SetNewValueAndSendOnBus);

	SetDatapointValue sdv7(13, serialConnection);
	sdv7.setUnsignedValue2Byte(13975, CommandByte::SetNewValueAndSendOnBus);

	SetDatapointValue sdv8(17, serialConnection);
	sdv8.setFloatValue4Byte(17.97528, CommandByte::SetNewValueAndSendOnBus);

	SetDatapointValue sdv9(25, serialConnection);
	sdv9.setSignedValue4Byte(-12759, CommandByte::SetNewValueAndSendOnBus);

	SetDatapointValue sdv10(69, serialConnection);
	sdv10.setUnsignedValue4Byte(179635, CommandByte::SetNewValueAndSendOnBus);

	printf("TESTING SET DATAPOINT VALUE FINISHED\n\n");
}

void BaosTester::testGetParameterByte()
{
	printf("TESTING GET PARAMETER BYTE STARTED\n");

	GetParameterByte(1, serialConnection);
	GetParameterByte(2, serialConnection);
	GetParameterByte(3, serialConnection);
	GetParameterByte(4, serialConnection);
	GetParameterByte(5, serialConnection);
	GetParameterByte(9,	serialConnection);
	GetParameterByte(13,serialConnection);
	GetParameterByte(17,serialConnection);
	GetParameterByte(25,serialConnection);
	GetParameterByte(69,serialConnection);

	printf("TESTING GET PARAMETER BYTE FINISHED\n\n");
}