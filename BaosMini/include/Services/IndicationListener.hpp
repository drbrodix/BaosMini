#ifndef INDICATION_LISTENER_HPP
#define INDICATION_LISTENER_HPP

#include "BaosTelegram.hpp"
#include "../Utility/DatapointTypes.hpp"
#include <thread>

class IndicationListener : public BaosTelegram
{
public:
	IndicationListener(
        SerialConnection* serialConnection);
	~IndicationListener();

private:
};

#endif // INDICATION_LISTENER_HPP
