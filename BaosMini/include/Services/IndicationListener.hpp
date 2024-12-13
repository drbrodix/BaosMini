#ifndef INDICATION_LISTENER_HPP
#define INDICATION_LISTENER_HPP

#ifndef DP_LENGTH_OFFSET_FROM_MAINSERVICE
#define DP_LENGTH_OFFSET_FROM_MAINSERVICE 9
#endif // !DP_LENGTH_OFFSET_FROM_MAINSERVICE

#ifndef DP_VALUE_OFFSET_FROM_MAINSERVICE
#define DP_VALUE_OFFSET_FROM_MAINSERVICE 10
#endif // !DP_VALUE_OFFSET_FROM_MAINSERVICE

#include "BaosTelegram.hpp"
#include "../Utility/FloatConverter.hpp"
#include "../Utility/DatapointTypes.hpp"
#include "../Utility/DecodeServerItemRes.hpp"
#include "../Services/GetDatapointDescription.hpp"
#include <functional>
#include <thread>

class IndicationListener : public BaosTelegram
{
public:
	IndicationListener(
        SerialConnection* serialConnection);
	~IndicationListener();

private:
	static void startListening(unsigned char* responseTelegram, unsigned int* responseLength, SerialConnection* serialConnection);
	static float decode4ByteFloat(unsigned char* pValueStartAddress);
	static bool decodeDatapointIndication(unsigned char* responseTelegram, DatapointTypes::DATAPOINT_TYPES dpt);
};

#endif // INDICATION_LISTENER_HPP
