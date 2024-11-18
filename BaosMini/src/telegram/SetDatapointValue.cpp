#include "telegram/SetDatapointValue.hpp"

SetDatapointValue::SetDatapointValue(Datapoint *datapoint)
    : nrOfDps(0)
{
    baosTelegram.push_back(BaosTelegram::BAOS_MAIN_SERVICE);
    baosTelegram.push_back(BaosSubServices::SetDatapointValueReq);
    //baosTelegram.push_back(0x00);
    //baosTelegram.push_back(unsigned char(datapointId)); // ID of first datapoint to set
    //baosTelegram.push_back(0x00);
    //baosTelegram.push_back(0x01); // Number of datapoints to set
    //baosTelegram.push_back(0x00);
    //baosTelegram.push_back(unsigned char(datapointId)); // ID of first datapoint
    //baosTelegram.push_back(0x03); // Command byte of first datapoint - 0b0011 == Set value and send on bus
    //baosTelegram.push_back(0x01); // Length byte of first datapoint
    //baosTelegram.push_back(datapointValue); // Value of first datapoint
}

SetDatapointValue::SetDatapointValue()
    : nrOfDps(0)
{
}

SetDatapointValue::~SetDatapointValue()
{
}

bool SetDatapointValue::addDatapoint(Datapoint *datapoint)
{
    const std::vector<unsigned char>* const dpData = datapoint->getDpData();

    try
    {
        if (!nrOfDps)
        {
            baosTelegram.push_back(dpData->at(0));
            baosTelegram.push_back(dpData->at(1));
        }

        unsigned char nrOfDpsByteOne = 0;
        unsigned char nrOfDpsByteTwo = 0;

        FormatterFunctions::formatValueInTwoBytes(nrOfDps + 1, &nrOfDpsByteOne, &nrOfDpsByteTwo);

        baosTelegram.push_back(nrOfDpsByteOne);
        baosTelegram.push_back(nrOfDpsByteTwo);


        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}