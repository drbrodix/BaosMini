#ifndef GET_DESCRIPTION_STRING_HPP
#define GET_DESCRIPTION_STRING_HPP

#include "BaosTelegram.hpp"

class GetDescriptionString : public BaosTelegram
{
public:
    GetDescriptionString(
        unsigned short datapointId,
        SerialConnection* serialConnection);
	~GetDescriptionString();

private:

};

#endif // GET_DESCRIPTION_STRING_HPP
