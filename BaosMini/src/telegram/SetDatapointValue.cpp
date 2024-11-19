#include "telegram/SetDatapointValue.hpp"

SetDatapointValue::SetDatapointValue()
    : nrOfDps(0)
{
    baosTelegram.push_back(BaosTelegram::BAOS_MAIN_SERVICE);
    baosTelegram.push_back(BaosSubServices::SetDatapointValueReq);
}

SetDatapointValue::SetDatapointValue(Datapoint *datapoint)
    : SetDatapointValue()
{
    addDatapoint(datapoint);
}

SetDatapointValue::~SetDatapointValue()
{
}

bool SetDatapointValue::addDatapoint(Datapoint *datapoint)
{
    // Get and save in var actual datapoint data as vector from datapoint object
    const std::vector<unsigned char>* const dpData = datapoint->getDpData();

    try
    {
        if (!nrOfDps)
        {
            // ID of first DP is what we're currently working with,
            // if number of datapoints is currently at 0.
            // In this case add it to the telegram as
            // ID of first datapoint to set.
            baosTelegram.push_back(dpData->at(0));
            baosTelegram.push_back(dpData->at(1));
        }

        // Format number of DPs into a 2 bytes format.
        // We add +1 to nrOfDps because the var has not been
        // incremented yet, in case an exception happens
        // before reaching the end of the function.
        unsigned char nrOfDpsByteOne = 0;
        unsigned char nrOfDpsByteTwo = 0;
        FormatterFunctions::formatValueInTwoBytes(nrOfDps + 1, &nrOfDpsByteOne, &nrOfDpsByteTwo);

        baosTelegram.push_back(nrOfDpsByteOne);
        baosTelegram.push_back(nrOfDpsByteTwo);

        // Incorporate datapoint into telegram
        for (unsigned char uc : *dpData)
        {
            baosTelegram.push_back(uc);
        }

        ++nrOfDps;

        return true;
    }
    catch (const std::exception& e)
    {
        printf("Exception while building Set Datapoint Value Request telegram:\n %s", e.what());
        return false;
    }
}