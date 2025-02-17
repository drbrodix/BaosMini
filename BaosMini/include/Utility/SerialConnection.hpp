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

#define READ_TIMEOUT        500
#define INPUT_ARRAY_LENGTH  250
#define FT12_ARRAY_LENGTH   250
#define BAOS_ACK_BYTE		0xE5
#define FT12_START_BYTE     0x68
#define FT12_END_BYTE       0x16
#define FIND_FT12_END_BYTE(START_BYTE_INDEX, PAYLOAD_LENGTH) (START_BYTE_INDEX + 5 + PAYLOAD_LENGTH)
#define GET_FT12_LENGTH(START_BYTE_INDEX, END_BYTE_INDEX) ((END_BYTE_INDEX - START_BYTE_INDEX) + 1)
#define GET_PAYLOAD_END_INDEX(PAYLOAD_LENGTH) (PAYLOAD_LENGTH + 3)

typedef enum {
	SEARCHING_START_BYTE = 0,
	CHECKING_FIRST_LENGTH = 1,
	CHECKING_SECOND_LENGTH = 2,
	CHECKING_SECOND_START_BYTE = 3,
	CHECKING_CONTROL_BYTE = 4,
	CHECKING_BAOS_PAYLOAD = 5,
	CHECKING_CHECKSUM = 6,
	CHECKING_END_BYTE = 7,
	RECEPTION_COMPLETE = 8,
} STATES;

typedef struct {
	STATES currentState;
	DWORD currentInputIndex;
	DWORD currentOutputIndex;
	DWORD payloadLength;
	int checksumSum;
	bool doStartBytesMatch;
	bool doLengthBytesMatch;
	bool doesChecksumMatch;
	bool isEndByteFound;
} ReaderInfo;

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
	SerialConnection(LPCWSTR connectionName);

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
	bool sendTelegram(unsigned char* baosTelegram, DWORD telegramLength, DatapointTypes::DATAPOINT_TYPES dpt = DatapointTypes::NO_DATAPOINT_TYPE);
	
	/// <summary>
	/// Reads data sent by the ObjectServer, and stores the received
	/// telegram in the passed unsigned char array. The checksum of
	/// the received telegram will be checked. The length of the
	/// received telegram will be returned, or 0 if any error is detected.
	/// </summary>
	unsigned int receiveTelegram(unsigned char* telegramCharArray, HANDLE inputThreadHandle = nullptr);

	/// <summary>
	/// A getter function for the serial connection handle object.
	/// </summary>
	HANDLE getHandle() const
	{
		return serialHandle;
	}

	/// <summary>
	/// Returns control byte depending on the
	/// current state of the isOddFrame data member.
	/// </summary>
	unsigned char getControlByte();

	bool switchControlByteState();

	bool sendAck() const;

	bool readAck() const;
	
private:
	DWORD readBuffer(unsigned char* pBuff, const DWORD bytesRead, unsigned char* destBuff, ReaderInfo* ri);
	STATES readFrame(unsigned char* pBuff, const DWORD bytesRead, unsigned char* destBuff, ReaderInfo* ri);
	void parseTelegram(unsigned char* ft12Buff, DWORD telegramLength, unsigned char* telegramCharArray);

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
	LPCWSTR connectionName;
	
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
	/// Sends a reset request to the connected BAOS device. Returns
	/// true if the sending process was successful, false otherwise.
	/// </summary>
	bool sendResetRequest() const;

	bool writeToSerial(LPCVOID buffToWrite, DWORD bytesToWrite) const;
};

#endif // SERIAL_CONNECTION_HPP
