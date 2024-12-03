#ifndef INDICATION_LISTENER_HPP
#define INDICATION_LISTENER_HPP

#include "BaosTelegram.hpp"
#include "../Utility/DatapointTypes.hpp"
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
};

#endif // INDICATION_LISTENER_HPP
