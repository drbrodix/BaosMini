#ifndef SERIAL_CONNECTION_HPP
#define SERIAL_CONNECTION_HPP

#define FT12_HEADER_SIZE 5	// Fixed size of FT1.2 header; unless the protocol changes, this constant shouldn't be touched
#define FT12_START_BYTE 0x68

#include <iostream>
#include <Windows.h>
#include "../Utility/ChecksumCalculator.hpp"
#include "../Encryption/Decode/TelegramDecoder.hpp"
#include "../Utility/FrameFormatter.hpp"
#include "../Utility/DatapointTypes.hpp"

class SerialConnection
{
public:
	SerialConnection(std::string connectionName);
	~SerialConnection();

	bool sendTelegram(unsigned char* baosTelegram, unsigned char telegramLength, DatapointTypes::DATAPOINT_TYPES dpt = DatapointTypes::NO_DATAPOINT_TYPE);
	unsigned int recieveTelegram(unsigned char* telegramCharArray);
	HANDLE getHandle() const
	{
		return serialHandle;
	}
	bool sendAck() const;
	
private:
	// Value to keep track of control byte state
	bool isOddFrame;
	bool isFirstTelegram;

	// Const to avoid magic numbers
	const unsigned char CONTROL_BYTE[2] =
	{
	0x53,	// EVEN <- ARRAY INDEX 0
	0x73	// ODD	<- ARRAY INDEX 1
	};

	// Data members for connection
	std::string connectionName;
	HANDLE serialHandle;
	DCB dcbSerialParam;
	COMMTIMEOUTS timeout;

	HANDLE createSerialHandle() const;
	bool configureConnect();
	bool configureTimeout();

	bool charFound(unsigned char charToFind);
	unsigned int readHeader(unsigned char* ft12Header);
	bool readData(unsigned char* buffer);

	bool sendResetRequest() const;

	// Returns control byte depending on the
	// current state of the isOddFrame data member
	unsigned char getControlByte();
};

#endif // SERIAL_CONNECTION_HPP
