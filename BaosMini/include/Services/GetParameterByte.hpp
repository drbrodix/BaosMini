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
    // Returns true if no errors have been encountered
    // while fetching datapoint value, false otherwise
    bool checkForError();
};

#endif // GET_PARAMETER_BYTE_HPP