#include "../../include/Services/IndicationListener.hpp"

IndicationListener::IndicationListener(
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
}

IndicationListener::~IndicationListener()
{
}

void IndicationListener::startListening()
{
    printf("Listening for incoming telegram...\n");

    while (true)
    {
        getAnswer();

        // Check if caught telegram is a datapoint indication
        if (*(responseTelegram + 1) == SUBSERVICES::DatapointValueind)
        {
            // Extract ID of indication datapoint
            unsigned short dpId = swap2(*(unsigned short*)(responseTelegram + 2));

            //// Fetch info about the datapoint
            GetDatapointDescription* gdd = new GetDatapointDescription(dpId, serialConnection);

            if (!Encryption::decodeTelegram(responseTelegram, responseLength, (DatapointTypes::DATAPOINT_TYPES)gdd->getDpDpt()))
            {
                std::cerr << "Error while decoding ObjectServer response." << '\n';
            }
        }

        // Check if caught telegram is a datapoint indication
        if (*(responseTelegram + 1) == SUBSERVICES::ServerItemInd)
        {
            if (!Encryption::decodeTelegram(responseTelegram, responseLength))
            {
                std::cerr << "Error while decoding ObjectServer response." << '\n';
            }
        }
    }
}