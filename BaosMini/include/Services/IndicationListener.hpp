#ifndef INDICATION_LISTENER_HPP
#define INDICATION_LISTENER_HPP

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
	void startListening();

private:
	float decode4ByteFloat(unsigned char* pValueStartAddress);
	bool decodeDatapointIndication(DatapointTypes::DATAPOINT_TYPES dpt);
};

#endif // INDICATION_LISTENER_HPP
