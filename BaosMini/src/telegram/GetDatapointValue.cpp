#include "telegram/GetDatapointValue.hpp"

GetDatapointValue::GetDatapointValue(
	int datapointId,
	int nrOfDatapoints)
{
	const unsigned char DP_ID_BYTEONE = datapointId / 256;
	const unsigned char DP_ID_BYTETWO = datapointId % 256;

	const unsigned char DP_NR_BYTEONE = nrOfDatapoints / 256;
	const unsigned char DP_NR_BYTETWO = nrOfDatapoints % 256;

	baosTelegram.push_back(BaosTelegram::BAOS_MAIN_SERVICE);
	baosTelegram.push_back(BaosSubServices::GetDatapointValueReq);
	baosTelegram.push_back(DP_ID_BYTEONE);
	baosTelegram.push_back(DP_ID_BYTETWO); // ID of first datapoint to set
	baosTelegram.push_back(DP_NR_BYTEONE);
	baosTelegram.push_back(DP_NR_BYTETWO); // Maximum number of datapoints to get
	baosTelegram.push_back(FILTER_CODES::GetAllDatapointValues); // Filter, which datapoints should be retrieved
}

GetDatapointValue::~GetDatapointValue()
{
}