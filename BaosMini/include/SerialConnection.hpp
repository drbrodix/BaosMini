#ifndef SERIAL_CONNECTION_HPP
#define SERIAL_CONNECTION_HPP

#include <iostream>
#include <Windows.h>
#include <vector>
#include <sstream>
#include "utility/Headers.hpp"

class SerialConnection
{
public:
	SerialConnection(std::string connectionName);
	~SerialConnection();

	bool sendTelegram(std::vector<unsigned char>* telegramData);
	
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

	bool sendAck() const;
	bool sendResetRequest() const;

	// Returns control byte depending on the
	// current state of the isOddFrame data member
	unsigned char getControlByte();
	
	bool checkIsReadAnswerReq(unsigned char subServiceCode) const;
};

#endif // SERIAL_CONNECTION_HPP
