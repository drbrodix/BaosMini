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
/// Index of the datapoint value, offset from the BAOS main
/// service code in the ObjectsServer's response telegram array.
/// </summary>
#define GET_DP_VALUE_RES_DP_VALUE_OFFSET 10

#include "BaosTelegram.hpp"
#include "../Utility/FloatConverter.hpp"
#include "../Utility/DatapointTypes.hpp"
#include "../Utility/Macros.hpp"

/// <summary>
/// Enumration of filter codes, allowing further configuration
/// of the way, which datapoint values should be fetched.
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
	/// <param name="datapointId">The ID of the datapoint,
    /// whose value should be fetched.</param>
	/// <param name="dpt">The datapoint type of the datapoint,
    /// whose value should be fetched.</param>
    /// <param name="serialConnection">A pointer to the SerialConnection object.</param>
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
    /// Gets the boolean value of the datapoint specified in the constructor.
    /// </summary>
    /// <returns>Returns the boolean value of the datapoint specified
    /// in the constructor, or 0 if fetched telegram values are invalid.</returns>
    bool getBooleanValue();

    /// <summary>
    /// Gets the 1byte unsigned value of the datapoint specified in the constructor.
    /// </summary>
    /// <returns>Returns the 1byte unsigned value of the datapoint specified
    /// in the constructor, or 0 if fetched telegram values are invalid.</returns>
    unsigned char getUnsignedValue1Byte();
    
    /// <summary>
    /// Gets the 1byte signed value of the datapoint specified in the constructor.
    /// </summary>
    /// <returns>Returns the 1byte signed value of the datapoint specified
    /// in the constructor, or 0 if fetched telegram values are invalid.</returns>
    signed char getSignedValue1Byte();
    
    /// <summary>
    /// Gets the 2byte unsigned value of the datapoint specified in the constructor.
    /// </summary>
    /// <returns>Returns the 2byte unsigned value of the datapoint specified
    /// in the constructor, or 0 if fetched telegram values are invalid.</returns>
    unsigned short getUnsignedValue2Byte();
    
    /// <summary>
    /// Gets the 2byte signed value of the datapoint specified in the constructor.
    /// </summary>
    /// <returns>Returns the 2byte signed value of the datapoint specified
    /// in the constructor, or 0 if fetched telegram values are invalid.</returns>
    signed short getSignedValue2Byte();

    /// <summary>
    /// Gets the 2byte float value of the datapoint specified in the constructor.
    /// </summary>
    /// <returns>Returns the 2byte float value of the datapoint specified
    /// in the constructor, or 0 if fetched telegram values are invalid.</returns>
    float getFloatValue2Byte();
    
    /// <summary>
    /// Gets the 4byte unsigned value of the datapoint specified in the constructor.
    /// </summary>
    /// <returns>Returns the 4byte unsigned value of the datapoint specified
    /// in the constructor, or 0 if fetched telegram values are invalid.</returns>
    unsigned int getUnsignedValue4Byte();
    
    /// <summary>
    /// Gets the 4byte signed value of the datapoint specified in the constructor.
    /// </summary>
    /// <returns>Returns the 4byte signed value of the datapoint specified
    /// in the constructor, or 0 if fetched telegram values are invalid.</returns>
    signed int getSignedValue4Byte();

    /// <summary>
    /// Gets the 4byte float value of the datapoint specified in the constructor.
    /// </summary>
    /// <returns>Returns the 4byte float value of the datapoint specified
    /// in the constructor, or 0 if fetched telegram values are invalid.</returns>
    float getFloatValue4Byte();

private:
    /// <summary>
    /// Type of the datapoint, whose value should be fetched from the ObjectServer.
    /// </summary>
    DatapointTypes::DATAPOINT_TYPES dpt;

    /// <summary>
    /// Checks if ObjectServer response is an error telegram.
    /// Also checks if the length of the retrieved datapoint value doesn't
    /// match the length of the datapoint type specified in the constructor.
    /// </summary>
    /// <param name="datapointId">The ID of the datapoint,
    /// whose value should be fetched.</param>
    /// <returns>If an error is detected, false will be returned, and a
    /// respective error message printed out in the standard output stream.
    /// Returns true if no issues have been detected.</returns>
    bool checkForError(unsigned short datapointId);
    
    /// <summary>
    /// A generic template function called by the public get functions with datatype specifications.
    /// </summary>
    /// <typeparam name="T">Datatype of the datapoint value, which is returned.</typeparam>
    /// <param name="expectedDpt">Expected datapoint type of the datapoint,
    /// whose value will be returned.</param>
    /// <param name="dptString">Datapoint type of the datapoint, whose value
    /// will be returned, as a string.</param>
    /// <returns>Returns the datapoint value fetched from 
    /// the ObjectServer, in the specified datatype.</returns>
    template <typename T> T getValue(DatapointTypes::DATAPOINT_TYPES expectedDpt, const char* dptString);
};

#endif // GET_DATAPOINT_VALUE_HPP
