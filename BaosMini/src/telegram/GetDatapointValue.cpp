#include "telegram/GetDatapointValue.hpp"

GetDatapointValue::GetDatapointValue(
   int datapointId,
   int nrOfDatapoints)
{
   baosTelegram.push_back(BaosTelegram::BAOS_MAIN_SERVICE);
   baosTelegram.push_back(BaosSubServices::GetDatapointValueReq);
   baosTelegram.push_back(0x00);
   baosTelegram.push_back(unsigned char(datapointId)); // ID of first datapoint to set
   baosTelegram.push_back(0x00);
   baosTelegram.push_back(unsigned char(nrOfDatapoints)); // Maximum number of datapoints to get
   baosTelegram.push_back(FILTER_CODES::GetAllDatapointValues); // Filter, which datapoints should be retrieved
}

GetDatapointValue::~GetDatapointValue()
{
}