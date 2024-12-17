#ifndef SET_SERVER_ITEM_HPP
#define SET_SERVER_ITEM_HPP

/// <summary>
/// Index of the ID of the server item set, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#define SET_SERVER_ITEM_RES_ITEM_ID_OFFSET 2

/// <summary>
/// Index of the ID of the starting server item to be set, offset 
/// from the BAOS main service code in the baosTelegram array.
/// </summary>
#define SET_SERVER_ITEM_START_ITEM_ID_OFFSET BAOS_DATA_FIRST_INDEX

/// <summary>
/// Index of the number of server items to be set, offset 
/// from the BAOS main service code in the baosTelegram array.
/// </summary>
#define SET_SERVER_ITEM_NR_OF_ITEMS_OFFSET (BAOS_DATA_FIRST_INDEX + 2)

/// <summary>
/// Index of the ID of the first server item to be set, offset 
/// from the BAOS main service code in the baosTelegram array.
/// </summary>
#define SET_SERVER_ITEM_FIRST_ITEM_ID_OFFSET (BAOS_DATA_FIRST_INDEX + 4)

/// <summary>
/// Index of the length of the first server item to be set, offset 
/// from the BAOS main service code in the baosTelegram array.
/// </summary>
#define SET_SERVER_ITEM_FIRST_ITEM_LENGTH_OFFSET (BAOS_DATA_FIRST_INDEX + 6)

/// <summary>
/// Index of the value of the first server item to be set, offset 
/// from the BAOS main service code in the baosTelegram array.
/// </summary>
#define SET_SERVER_ITEM_FIRST_ITEM_DATA_OFFSET (BAOS_DATA_FIRST_INDEX + 7)

#include "BaosTelegram.hpp"
#include "../Enums/ServerItemEnum.hpp"
#include "../Utility/Macros.hpp"

/// <summary>
/// A BAOS service, allowing the setting of values of
/// certain server items of the connected BAOS device.
/// </summary>
class SetServerItem : public BaosTelegram
{
public:

	/// <summary>
	/// The constructor function calls the base class
	/// BaosTelegram constructor function, thus initializing
	/// the basic data members. The BAOS subservice code
	/// will be also initalized at this stage.
	/// </summary>
	SetServerItem(SerialConnection* serialConnection);

	/// <summary>
	/// The default destructor calls the parent function,
	/// which frees up the dynamically allocated
	/// memory of the baosTelegram and responseTelegram arrays.
	/// </summary>
	~SetServerItem();

	/// <summary>
	/// Sends telegram to the ObjectServer with the passed value,
	/// then retrieves and stores the answer. Returns false if the
	/// ObjectServer's answer indicates an error, true otherwise.
	/// Depending on the state of the decode flag, a message will be
	/// printed in the terminal, whether the execution was successful.
	/// </summary>
	bool setBaudrate(BAUDRATES baudrate, bool decode = false);
	
	/// <summary>
	/// Sends telegram to the ObjectServer with the passed value,
	/// then retrieves and stores the answer. Returns false if the
	/// ObjectServer's answer indicates an error, true otherwise.
	/// Depending on the state of the decode flag, a message will be
	/// printed in the terminal, whether the execution was successful.
	/// </summary>
	bool setCurrentBufferSize(unsigned short bufferSize, bool decode = false);

	/// <summary>
	/// Sends telegram to the ObjectServer with the passed value,
	/// then retrieves and stores the answer. Returns false if the
	/// ObjectServer's answer indicates an error, true otherwise.
	/// Depending on the state of the decode flag, a message will be
	/// printed in the terminal, whether the execution was successful.
	/// </summary>
	bool setProgrammingMode(bool enable, bool decode = false);

	/// <summary>
	/// Sends telegram to the ObjectServer with the passed value,
	/// then retrieves and stores the answer. Returns false if the
	/// ObjectServer's answer indicates an error, true otherwise.
	/// Depending on the state of the decode flag, a message will be
	/// printed in the terminal, whether the execution was successful.
	/// </summary>
	bool setIndicationSending(bool enable, bool decode = false);

private:

	/// <summary>
	/// A generic template function called by the public set functions with datatype 
	/// specifications. Builds the telegram based on the parameters, initiates communication
	/// with the ObjectServer, stores its answer, executes error check and returns its result.
	/// </summary>
	template <typename T> bool setValue(T itemValue, SERVER_ITEMS serverItem, unsigned char itemLength, bool decode);
	
	/// <summary>
	/// Checks if ObjectServer response is an error telegram. Returns false
	/// if an error code has been detected, which then will be decoded and
	/// a respective error message printed in the terminal.
	/// Returns true if the ObjectServer response contains no error code.
	/// </summary>
	bool checkForError();

	/// <summary>
	/// Decodes the ObjectServer's response, and
	/// prints a respective message in terminal.
	/// </summary>
	void decodeSetServerItemRes();
};

#endif // SET_SERVER_ITEM_HPP