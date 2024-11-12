#ifndef SERIAL_CONNECTION_HPP
#define SERIAL_CONNECTION_HPP

#include <iostream>
#include <windows.h>

class SerialConnection
{
public:
	SerialConnection(std::string connectionName);
	~SerialConnection();

	HANDLE getHandle();
private:
	// Value to keep track of control byte state
	bool isOddFrame;

	// Const to avoid magic numbers
	const unsigned char CONTROL_BYTE[2] =
	{
	0x73,	// ODD	<- ARRAY INDEX 0
	0x53	// EVEN <- ARRAY INDEX 1
	};

	// Data members for connection
	std::string connectionName;
	HANDLE serialHandle;
	DCB dcbSerialParam;
	COMMTIMEOUTS timeout;

	HANDLE createSerialHandle() const;
	bool configureConnect();
	bool configureTimeout();
};

#endif // SERIAL_CONNECTION_HPP
