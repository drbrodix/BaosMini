#ifndef GET_DATAPOINT_VALUE_HPP
#define GET_DATAPOINT_VALUE_HPP

/// <summary>
/// Index of the ID of the datapoint, whose value should be fetched,
/// offset from the BAOS main service code in the baosTelegram array.
/// </summary>
#define GET_DP_VALUE_DP_ID_OFFSET BAOS_DATA_FIRST_INDEX

/// <summary>
/// Index of the number of datapoints, whose values should be fetched,
/// offset from the BAOS main service code in the baosTelegram array.
/// </summary>
#define GET_DP_VALUE_NR_OF_DPS_OFFSET (BAOS_DATA_FIRST_INDEX + 2)

/// <summary>
/// Index of the filter code, offset from the BAOS
/// main service code in the baosTelegram array.
/// </summary>
#define GET_DP_VALUE_FILTER_CODE_OFFSET (BAOS_DATA_FIRST_INDEX + 4)

/// <summary>
/// Index of the number of datapoints requested, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#define GET_DP_VALUE_RES_NR_OF_DPS_OFFSET 4

/// <summary>
/// Index of the length of the datapoint value, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#define GET_DP_VALUE_RES_DP_LENGTH_OFFSET 9

/// <summary>
/// Index of the datapoint value, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#define GET_DP_VALUE_RES_DP_VALUE_OFFSET 10

#include "BaosTelegram.hpp"
#include "../Utility/FloatConverter.hpp"
#include "../Utility/DatapointTypes.hpp"
#include "../Utility/Macros.hpp"

/// <summary>
/// Enumration of filter codes, allowing further configuration
/// of the way, what datapoint values should be retrieved.
/// </summary>
enum FILTER_CODES
{
        GetAllDatapointValues = 0x00,
        GetOnlyValidDatapointValues = 0x01,
        GetOnlyUpdatedDatapointValues = 0x02
};

/// <summary>
/// A BAOS service, allowing the retrieval of values
/// of datapoints configured in the ObjectServer.
/// </summary>
class GetDatapointValue : public BaosTelegram
{
public:
    /// <summary>
    /// The constructor function executes the entire communication process between
    /// the client and the ObjectServer. It sets up and sends the telegram to the
    /// ObjectServer with the passed parameters, then retrieves and stores the answer.
    /// The specification of the datapoint type is needed for error avoidance
    /// when decoding the retrieved datapoint values.
    /// An error check will be done, and the result stored for further use.
    /// </summary>
	GetDatapointValue(
        unsigned short datapointId,
        DatapointTypes::DATAPOINT_TYPES dpt,
        SerialConnection* serialConnection);

    /// <summary>
    /// The default destructor calls the parent function,
    /// which frees up the dynamically allocated
    /// memory of the baosTelegram and responseTelegram arrays.
    /// </summary>
	~GetDatapointValue();

    /// <summary>
    /// Returns the retrieved boolean value from the ObjectServer,
    /// or 0 if no valid value has been fetched from ObjectServer.
    /// </summary>
    bool getBooleanValue();

    /// <summary>
    /// Returns the retrieved 1byte unsigned value from the ObjectServer,
    /// or 0 if no valid value has been fetched from ObjectServer.
    /// </summary>
    unsigned char getUnsignedValue1Byte();
    
    /// <summary>
    /// Returns the retrieved 1byte signed value from the ObjectServer,
    /// or 0 if no valid value has been fetched from ObjectServer.
    /// </summary>
    signed char getSignedValue1Byte();
    
    /// <summary>
    /// Returns the retrieved 2byte unsigned value from the ObjectServer,
    /// or 0 if no valid value has been fetched from ObjectServer.
    /// </summary>
    unsigned short getUnsignedValue2Byte();
    
    /// <summary>
    /// Returns the retrieved 2byte signed value from the ObjectServer,
    /// or 0 if no valid value has been fetched from ObjectServer.
    /// </summary>
    signed short getSignedValue2Byte();

    /// <summary>
    /// Returns the retrieved 2byte float value from the ObjectServer,
    /// or 0 if no valid value has been fetched from ObjectServer.
    /// </summary>
    float getFloatValue2Byte();
    
    /// <summary>
    /// Returns the retrieved 4byte unsigned value from the ObjectServer,
    /// or 0 if no valid value has been fetched from ObjectServer.
    /// </summary>
    unsigned int getUnsignedValue4Byte();
    
    /// <summary>
    /// Returns the retrieved 4byte signed value from the ObjectServer,
    /// or 0 if no valid value has been fetched from ObjectServer.
    /// </summary>
    signed int getSignedValue4Byte();

    /// <summary>
    /// Returns the retrieved 4byte float value from the ObjectServer,
    /// or 0 if no valid value has been fetched from ObjectServer.
    /// </summary>
    float getFloatValue4Byte();

private:
    /// <summary>
    /// Type of the datapoint, whose value should be fetched from the ObjectServer.
    /// </summary>
    DatapointTypes::DATAPOINT_TYPES dpt;

    /// <summary>
    /// Checks if ObjectServer response is an error telegram. Returns false
    /// if an error code has been detected, which then will be decoded and
    /// a respective error message printed in the terminal.
    /// Also checks if the length of the retrieved datapoint value doesn't
    /// match the length of the datapoint type specified in the constructor.
    /// In this case false will be returned, and an error message
    /// printed in terminal. Returns true if no issues have been detected.
    /// </summary>
    bool checkForError(unsigned short datapointId);

    /// <summary>
    /// A generic template function called by the public get functions
    /// with datatype specifications. Returns the datapoint value retrieved
    /// from the ObjectServer in the specified datapoint type.
    /// </summary>
    template <typename T> T getValue(DatapointTypes::DATAPOINT_TYPES expectedDpt, const char* dptString);
};

#endif // GET_DATAPOINT_VALUE_HPP
