#include "telegram/SetDatapointValueReq.hpp"

SetDatapointValue::SetDatapointValue(int datapointId, bool datapointValue)
{
	baosTelegram[0] = BAOS_MAIN_SERVICE; // Main service code
	baosTelegram[1] = BaosSubServices::SetDatapointValueReq; // Subservice code
	baosTelegram[2] = 0x00; // ID of first datapoint to set - Byte 1
	baosTelegram[3] = datapointId; // ID of first datapoint to set - Byte 2
	baosTelegram[4] = 0x00; // Number of datapoints to set - Byte 1
	baosTelegram[5] = 0x01; // Number of datapoints to set - Byte 2
	baosTelegram[6] = 0x00; // ID of first datapoint - Byte 1
	baosTelegram[7] = datapointId; // ID of first datapoint - Byte 2
	baosTelegram[8] = 0x03; // Command byte of first datapoint - 0b0011 == Set value and send on bus
	baosTelegram[9] = 0x01; // Length byte of first datapoint
	baosTelegram[10] = datapointValue; // Value of first datapoint
}

SetDatapointValue::~SetDatapointValue()
{
}

unsigned char* SetDatapointValue::getTelegram()
{
	return baosTelegram;
}