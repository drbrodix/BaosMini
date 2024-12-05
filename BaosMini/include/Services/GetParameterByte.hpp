#ifndef GET_PARAMETER_BYTE_HPP
#define GET_PARAMETER_BYTE_HPP

#include "BaosTelegram.hpp"

class GetParameterByte : public BaosTelegram
{
public:
    GetParameterByte(
        unsigned short indexOfFirstByte,
        SerialConnection* serialConnection);
	~GetParameterByte();
    unsigned char getByte();

private:
    bool checkForError();
};

#endif // GET_PARAMETER_BYTE_HPP