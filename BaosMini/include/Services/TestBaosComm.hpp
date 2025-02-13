//#ifndef TEST_BAOS_COMM_HPP
//#define TEST_BAOS_COMM_HPP
//
///// <summary>
///// Index of the ID of the datapoint set, offset from the BAOS
///// main service code in the ObjectsServer's response telegram array.
///// </summary>
//#define SET_DP_VALUE_RES_DP_ID_OFFSET 2
//
///// <summary>
///// Index of the ID of the starting datapoint to be set, offset
///// from the BAOS main service code in the baosTelegram array.
///// </summary>
//#define SET_DP_VALUE_START_DP_ID_OFFSET BAOS_DATA_FIRST_INDEX
//
///// <summary>
///// Index of the number of datapoints to be set, offset from
///// the BAOS main service code in the baosTelegram array.
///// </summary>
//#define SET_DP_VALUE_NR_OF_DPS_OFFSET (BAOS_DATA_FIRST_INDEX + 2)
//
///// <summary>
///// Index of the ID of the first datapoint to be set, offset
///// from the BAOS main service code in the baosTelegram array.
///// </summary>
//#define SET_DP_VALUE_FIRST_DP_ID_OFFSET (BAOS_DATA_FIRST_INDEX + 4)
//
///// <summary>
///// Index of the command byte, offset from the
///// BAOS main service code in the baosTelegram array.
///// </summary>
//#define SET_DP_VALUE_COMMAND_BYTE_OFFSET (BAOS_DATA_FIRST_INDEX + 6)
//
///// <summary>
///// Index of the datapoint value size, offset from the
///// BAOS main service code in the baosTelegram array.
///// </summary>
//#define SET_DP_VALUE_DP_VALUE_SIZE_OFFSET (BAOS_DATA_FIRST_INDEX + 7)
//
///// <summary>
///// Index of the actual value to set the datapoint to, offset
///// from the BAOS main service code in the baosTelegram array.
///// </summary>
//#define SET_DP_VALUE_DP_VALUE_OFFSET (BAOS_DATA_FIRST_INDEX + 8)
//
//#include <cstring>
//#include <cstdio>
//#include "BaosTelegram.hpp"
//#include "../Utility/FloatConverter.hpp"
//#include "../Utility/DatapointTypes.hpp"
//
///// <summary>
///// Enumration of command bytes, allowing further configuration,
///// what the telegram will be used for. Under normal circumstances,
///// SetNewValueAndSendOnBus will be used to set the value of a datapoint.
///// </summary>
//enum CommandByte
//{
//	NoCommand                       = 0x00, // No Command
//	SetNewValue                     = 0x01, // Set new value
//	SendValueOnBus                  = 0x02, // Send value on bus
//	SetNewValueAndSendOnBus         = 0x03, // Set new value and send on bus
//	ReadNewValueViaBus              = 0x04, // Read new value via bus
//	ClearDatapointTransmissionState = 0x05  // Clear datapoint transmission state
//};
//
///// <summary>
///// A BAOS service, allowing the setting of value
///// of datapoints configured in the ObjectServer.
///// </summary>
//class TestBaosComm : BaosTelegram
//{
//public:
//
//	/// <summary>
//	/// The constructor function calls the base class
//	/// BaosTelegram constructor function, thus initializing
//	/// the basic data members. Parts of the telegram used in
//	/// all cases will be also initalized at this stage.
//	/// </summary>
//	TestBaosComm(
//		unsigned short dpId,
//		SerialConnection* serialConnection
//	);
//
//	/// <summary>
//	/// The default destructor calls the parent function,
//	/// which frees up the dynamically allocated
//	/// memory of the baosTelegram and responseTelegram arrays.
//	/// </summary>
//	~TestBaosComm();
//
//	//						Generic structure of BAOS Datapoint
//	// 
//	//	ID of DP          Command byte of DP    Length byte of DP         Value of DP
//	// 
//	//	0x00 0x00        |        0x00        |        0x00        |         0x00 ...
//	
//	/// <summary>
//	/// Sends telegram to the ObjectServer with the passed parameters,
//	/// then retrieves and stores the answer. Returns false if the
//	/// ObjectServer's answer indicates an error, true otherwise.
//	/// Depending on the state of the decode flag, a message will be
//	/// printed in the terminal, whether the execution was successful.
//	/// </summary>
//	bool setBoolean(bool dpValue, CommandByte commandByte, bool decode = false);
//	
//	/// <summary>
//	/// Sends telegram to the ObjectServer with the passed parameters,
//	/// then retrieves and stores the answer. Returns false if the
//	/// ObjectServer's answer indicates an error, true otherwise.
//	/// Depending on the state of the decode flag, a message will be
//	/// printed in the terminal, whether the execution was successful.
//	/// </summary>
//	bool setUnsignedValue1Byte(unsigned char dpValue, CommandByte commandByte, bool decode = false);
//	
//	/// <summary>
//	/// Sends telegram to the ObjectServer with the passed parameters,
//	/// then retrieves and stores the answer. Returns false if the
//	/// ObjectServer's answer indicates an error, true otherwise.
//	/// Depending on the state of the decode flag, a message will be
//	/// printed in the terminal, whether the execution was successful.
//	/// </summary>
//	bool setSignedValue1Byte(signed char dpValue, CommandByte commandByte, bool decode = false);
//	
//	/// <summary>
//	/// Sends telegram to the ObjectServer with the passed parameters,
//	/// then retrieves and stores the answer. Returns false if the
//	/// ObjectServer's answer indicates an error, true otherwise.
//	/// Depending on the state of the decode flag, a message will be
//	/// printed in the terminal, whether the execution was successful.
//	/// </summary>
//	bool setUnsignedValue2Byte(unsigned short dpValue, CommandByte commandByte, bool decode = false);
//	
//	/// <summary>
//	/// Sends telegram to the ObjectServer with the passed parameters,
//	/// then retrieves and stores the answer. Returns false if the
//	/// ObjectServer's answer indicates an error, true otherwise.
//	/// Depending on the state of the decode flag, a message will be
//	/// printed in the terminal, whether the execution was successful.
//	/// </summary>
//	bool setSignedValue2Byte(signed short dpValue, CommandByte commandByte, bool decode = false);
//	
//	/// <summary>
//	/// Sends telegram to the ObjectServer with the passed parameters,
//	/// then retrieves and stores the answer. Returns false if the
//	/// ObjectServer's answer indicates an error, true otherwise.
//	/// Depending on the state of the decode flag, a message will be
//	/// printed in the terminal, whether the execution was successful.
//	/// </summary>
//	bool setFloatValue2Byte(float dpValue, CommandByte commandByte, bool decode = false);
//	
//	/// <summary>
//	/// Sends telegram to the ObjectServer with the passed parameters,
//	/// then retrieves and stores the answer. Returns false if the
//	/// ObjectServer's answer indicates an error, true otherwise.
//	/// Depending on the state of the decode flag, a message will be
//	/// printed in the terminal, whether the execution was successful.
//	/// </summary>
//	bool setUnsignedValue4Byte(unsigned int dpValue, CommandByte commandByte, bool decode = false);
//	
//	/// <summary>
//	/// Sends telegram to the ObjectServer with the passed parameters,
//	/// then retrieves and stores the answer. Returns false if the
//	/// ObjectServer's answer indicates an error, true otherwise.
//	/// Depending on the state of the decode flag, a message will be
//	/// printed in the terminal, whether the execution was successful.
//	/// </summary>
//	bool setSignedValue4Byte(signed int dpValue, CommandByte commandByte, bool decode = false);
//	
//	/// <summary>
//	/// Sends telegram to the ObjectServer with the passed parameters,
//	/// then retrieves and stores the answer. Returns false if the
//	/// ObjectServer's answer indicates an error, true otherwise.
//	/// Depending on the state of the decode flag, a message will be
//	/// printed in the terminal, whether the execution was successful.
//	/// </summary>
//	bool setFloatValue4Byte(float dpValue, CommandByte commandByte, bool decode = false);
//
//private:
//	/// <summary>
//	/// ID of the datapoint, whose value should be set.
//	/// </summary>
//	unsigned short dpId;
//	
//	/// <summary>
//	/// Initializes parts of the telegram used in all cases.
//	/// </summary>
//	inline void initTelegram();
//
//	/// <summary>
//	/// Checks if ObjectServer response is an error telegram. Returns false
//	/// if an error code has been detected, which then will be decoded and
//	/// a respective error message printed in the terminal.
//	/// Returns true if the ObjectServer response contains no error code.
//	/// </summary>
//	bool checkForError();
//
//	/// <summary>
//	/// A generic template function called by the public set functions with
//	/// datatype specifications. Builds the telegram based on the parameters,
//	/// initiates communication with the ObjectServer, stores its answer,
//	/// executes error check and returns its result.
//	/// </summary>
//	template <typename T> bool setValue(T dpValue, DatapointTypes::DATAPOINT_TYPES dpt, CommandByte commandByte, bool decode);
//};
//
//#endif // TEST_BAOS_COMM_HPP
