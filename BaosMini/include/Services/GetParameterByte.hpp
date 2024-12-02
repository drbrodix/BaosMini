#ifndef GET_PARAMETER_BYTE_HPP
#define GET_PARAMETER_BYTE_HPP

#include "BaosTelegram.hpp"

class GetParameterByte : public BaosTelegram
{
public:
    GetParameterByte(
        unsigned short indexOfFirstByte,
        unsigned short numberOfBytes,
        SerialConnection* serialConnection);
	~GetParameterByte();

private:

};

#endif // GET_PARAMETER_BYTE_HPP