#include "telegram/SetDatapointValue.hpp"

SetDatapointValue::SetDatapointValue(
    int datapointId,
    bool datapointValue)
{
    baosTelegram.push_back(BaosTelegram::BAOS_MAIN_SERVICE);
    baosTelegram.push_back(BaosSubServices::SetDatapointValueReq);
    baosTelegram.push_back(0x00);
    baosTelegram.push_back(unsigned char(datapointId)); // ID of first datapoint to set
    baosTelegram.push_back(0x00);
    baosTelegram.push_back(0x01); // Number of datapoints to set
    baosTelegram.push_back(0x00);
    baosTelegram.push_back(unsigned char(datapointId)); // ID of first datapoint
    baosTelegram.push_back(0x03); // Command byte of first datapoint - 0b0011 == Set value and send on bus
    baosTelegram.push_back(0x01); // Length byte of first datapoint
    baosTelegram.push_back(datapointValue); // Value of first datapoint
}

SetDatapointValue::~SetDatapointValue()
{
}