#include "Telegram/SetDatapointValue.hpp"

SetDatapointValue::SetDatapointValue()
	: BaosTelegram()
{
	// BAOS telegram always starts with
    // the main service and the sub service
    baosTelegram[1] = BaosSubServices::SetDatapointValueReq;
}

SetDatapointValue::SetDatapointValue(Datapoint *datapoint)
    : SetDatapointValue()
{
    addDatapoint(datapoint);
}

SetDatapointValue::~SetDatapointValue()
{
    delete[] baosTelegram;
}

bool SetDatapointValue::addDatapoint(Datapoint *datapoint)
{
    // Get and save actual datapoint data and its size from datapoint object
    const unsigned char dpObjectSize = datapoint->getDpObjectSize();
    const unsigned char *dpData = datapoint->getDpData();

    try
    {
        // ID of first DP is what we're currently working with,
        // if number of datapoints is currently at 0.
        // In this case add it to the telegram as
        // ID of first datapoint to set.
        baosTelegram[2] = dpData[0];
        baosTelegram[3] = dpData[1];

        // Format number of DPs into a 2 bytes format.
        // We add +1 to nrOfDps because the var has not been
        // incremented yet, in case an exception happens
        // before reaching the end of the function.
        unsigned char nrOfDpsByteOne = 0;
        unsigned char nrOfDpsByteTwo = 0;
        FormatterFunctions::formatValueInTwoBytes(1, &nrOfDpsByteOne, &nrOfDpsByteTwo);

		// Add number of DPs to the telegram
		baosTelegram[4] = nrOfDpsByteOne;
		baosTelegram[5] = nrOfDpsByteTwo;

        // Incorporate datapoint into telegram
        for (int i = 0; i < dpObjectSize; ++i)
		{
			baosTelegram[6 + i] = dpData[i];
		}

        telegramObjectSize = 6 + dpObjectSize;

        return true;
    }
    catch (const std::exception& e)
    {
        printf("Exception while building Set Datapoint Value Request telegram:\n %s", e.what());
        return false;
    }
}