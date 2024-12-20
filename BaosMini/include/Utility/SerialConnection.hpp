#ifndef SERIAL_CONNECTION_HPP
#define SERIAL_CONNECTION_HPP

/// <summary>
/// A constant representing the size of the FT1.2 header in bytes.
/// </summary>
#define FT12_HEADER_SIZE 5

#include <iostream>
#include <Windows.h>
#include "../Utility/ChecksumCalculator.hpp"
#include "../Utility/FrameFormatter.hpp"
#include "../Utility/DatapointTypes.hpp"

/// <summary>
/// This class takes care of the serial connection between the client and the BAOS device.
/// </summary>
class SerialConnection
{
public:
	/// <summary>
	/// The construction of the serial connection will be
	/// taken care of in the constructor function by calling
	/// the responsible functions. The user gets warned
	/// if the opening of the connection is unsuccessful.
	/// </summary>
	SerialConnection(std::string connectionName);

	/// <summary>
	/// The serial connection handle will be closed when the
	/// SerialConnection object is destroyed. The user gets
	/// warned if the closing of the handle is unsuccessful.
	/// </summary>
	~SerialConnection();

	/// <summary>
	/// Takes a raw BAOS telegram, wraps it in an FT1.2 frame,
	/// and sends it to the connected BAOS device. Returns true 
	/// if the sending process was successful, false otherwise.
	/// </summary>
	bool sendTelegram(unsigned char* baosTelegram, unsigned char telegramLength, DatapointTypes::DATAPOINT_TYPES dpt = DatapointTypes::NO_DATAPOINT_TYPE);
	
	/// <summary>
	/// Reads data sent by the ObjectServer, and stores the recieved
	/// telegram in the passed unsigned char array. The checksum of
	/// the recieved telegram will be checked. The length of the
	/// recieved telegram will be returned, or 0 if any error is detected.
	/// </summary>
	unsigned int recieveTelegram(unsigned char* telegramCharArray);

	/// <summary>
	/// A getter function for the serial connection handle object.
	/// </summary>
	HANDLE getHandle() const
	{
		return serialHandle;
	}
	bool sendAck() const;
	
private:
	/// <summary>
	/// Value to keep track of the control byte state,
	/// which gets switched after every telegram sent.
	/// </summary>
	bool isOddFrame;

	/// <summary>
	/// Array containing the two varying control byte values.
	/// </summary>
	const unsigned char CONTROL_BYTE[2] =
	{
	/// <summary>
	/// Control byte for even telegrams.
	/// </summary>
	0x53,

	/// <summary>
	/// Control byte for odd telegrams.
	/// </summary>
	0x73
	};

	/// <summary>
	/// String containing the name of the client serial interface.
	/// </summary>
	std::string connectionName;
	
	/// <summary>
	/// Handle object of the serial connection.
	/// </summary>
	HANDLE serialHandle;

	/// <summary>
	/// DCB object containing the configurations of the serial connection.
	/// </summary>
	DCB dcbSerialParam;
	
	/// <summary>
	/// Object containing the timeout configurations of the serial connection.
	/// </summary>
	COMMTIMEOUTS timeout;

	/// <summary>
	/// Constructs and returns a handle for the serial connection with
	/// interface name passed to the SerialConnection constructor function.
	/// </summary>
	HANDLE createSerialHandle() const;

	/// <summary>
	/// Sets the properties of the DCB configuration object,
	/// and configures the serial connection with it. Returns true 
	/// if the configuration process was successful, false otherwise.
	/// </summary>
	bool configureConnect();
	
	/// <summary>
	/// Sets the properties of the COMMTIMEOUTS configuration object,
	/// and configures the serial connection with it. Returns true 
	/// if the configuration process was successful, false otherwise.
	/// </summary>
	bool configureTimeout();

	/// <summary>
	/// Reads incoming data and looks for the character passed as
	/// parameter. After reading a byte, it returns true if the read
	/// byte and passed value match, false otherwise. Will be used
	/// to detect the start byte of FT1.2 frames sent by the ObjectServer.
	/// </summary>
	bool isCharFound(unsigned char charToFind) const;
	
	/// <summary>
	/// Reads the header of the detected FT1.2 frame. Returns the
	/// length of the payload telegram, or 0 if an error occurs.
	/// </summary>
	unsigned int readHeader(unsigned char* ft12Header) const;

	/// <summary>
	/// Reads one byte sent from the ObjectServer and
	/// stores it in the passed buffer. Returns true if
	/// the reading process was successful, false otherwise.
	/// </summary>
	bool readData(unsigned char* buffer) const;

	/// <summary>
	/// Sends a reset request to the connected BAOS device. Returns
	/// true if the sending process was successful, false otherwise.
	/// </summary>
	bool sendResetRequest() const;

	/// <summary>
	/// Returns control byte depending on the
	/// current state of the isOddFrame data member.
	/// </summary>
	unsigned char getControlByte();
};

#endif // SERIAL_CONNECTION_HPP
