#include "telegram/GetDatapointValue.hpp"

GetDatapointValue::GetDatapointValue(
	unsigned short datapointId,
	unsigned short nrOfDatapoints)
	: BaosTelegram()
{
	unsigned char DP_ID_BYTEONE = 0;
	unsigned char DP_ID_BYTETWO = 0;

	unsigned char DP_NR_BYTEONE = 0;
	unsigned char DP_NR_BYTETWO = 0;

	FormatterFunctions::formatValueInTwoBytes(datapointId, &DP_ID_BYTEONE, &DP_ID_BYTETWO);
	FormatterFunctions::formatValueInTwoBytes(nrOfDatapoints, &DP_NR_BYTEONE, &DP_NR_BYTETWO);

	baosTelegram[1] = BaosSubServices::GetDatapointValueReq;
	baosTelegram[2] = DP_ID_BYTEONE;
	baosTelegram[3] = DP_ID_BYTETWO; // ID of first datapoint to set
	baosTelegram[4] = DP_NR_BYTEONE;
	baosTelegram[5] = DP_NR_BYTETWO; // Maximum number of datapoints to get
	baosTelegram[6] = FILTER_CODES::GetAllDatapointValues; // Filter, which datapoints should be retrieved

	telegramLength = 7;
}

GetDatapointValue::~GetDatapointValue()
{
}