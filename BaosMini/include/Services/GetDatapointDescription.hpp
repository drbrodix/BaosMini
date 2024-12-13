#ifndef GET_DATAPOINT_DESCRIPTION_HPP
#define GET_DATAPOINT_DESCRIPTION_HPP

/// <summary>
/// Index of the datapoint value type, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#ifndef DP_VALUE_TYPE_OFFSET_FROM_MAINSERVICE
#define DP_VALUE_TYPE_OFFSET_FROM_MAINSERVICE 8
#endif // !DP_VALUE_TYPE_OFFSET_FROM_MAINSERVICE

/// <summary>
/// Index of the datapoint configuration flags, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#ifndef DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE
#define DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE 9
#endif // !DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE

/// <summary>
/// Index of the datapoint type, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#ifndef DP_DPT_OFFSET_FROM_MAINSERVICE
#define DP_DPT_OFFSET_FROM_MAINSERVICE 10
#endif // !DP_DPT_OFFSET_FROM_MAINSERVICE

/// <summary>
/// Index of the number of datapoints requested, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#ifndef NR_OF_DPS_OFFSET_FROM_MAINSERVICE
#define NR_OF_DPS_OFFSET_FROM_MAINSERVICE 4
#endif // !NR_OF_DPS_OFFSET_FROM_MAINSERVICE

/// <summary>
/// Index of the datapoint ID, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#ifndef DP_ID_OFFSET_FROM_MAINSERVICE
#define DP_ID_OFFSET_FROM_MAINSERVICE 6
#endif // !DP_ID_OFFSET_FROM_MAINSERVICE

#include "BaosTelegram.hpp"

/// <summary>
/// A bitfield structure to store the datapoint
/// configuration flags in a clear and efficient way.
/// </summary>
typedef struct {
    unsigned char transmitPriority          : 2;
    unsigned char datapointCommunication    : 1;
    unsigned char readFromBus               : 1;
    unsigned char writeFromBus              : 1;
    unsigned char readOnInit                : 1;
    unsigned char transmitToBus             : 1;
    unsigned char updateOnResponse          : 1;
} ConfigFlags;

/// <summary>
/// A BAOS service, allowing the retrieval of various data
/// about configured datapoints in the ObjectServer.
/// </summary>
class GetDatapointDescription : public BaosTelegram
{
public:
    /// <summary>
    /// The constructor function executes the entire communication process between
    /// the client and the ObjectServer. It sets up and sends the telegram to the
    /// ObjectServer with the passed parameters, then retrieves and stores the answer.
    /// An error check will be done, and the result stored for further use.
    /// </summary>
    GetDatapointDescription(
        unsigned short datapointId,
        SerialConnection* serialConnection);
    
    /// <summary>
    /// The default destructor calls the parent function,
    /// which frees up the dynamically allocated
    /// memory of the baosTelegram and responseTelegram arrays.
    /// </summary>
	~GetDatapointDescription();
    
    /// <summary>
    /// Prints data, specified in the parameters, about the datapoint in terminal.
    /// Returns true if fetched telegram values are valid, false if invalid.
    /// </summary>
    bool printDpDescription(
        bool datapointDpt,
        bool datapointValueType,
        bool datapointConfigFlag);

    /// <summary>
    /// Returns the datapoint type of the datapoint specified
    /// in the constructor, or 0 if fetched telegram values are invalid.
    /// For types explanation refer to BAOS Protocol Documentation, Appendix D.
    /// </summary>
    DatapointTypes::DATAPOINT_TYPES getDpDpt();

    /// <summary>
    /// Returns the datapoint value type of the datapoint specified
    /// in the constructor, or 0x0F if fetched telegram values are invalid.
    /// For value types explanation refer to BAOS Protocol Documentation, Appendix C.
    /// </summary>
    DatapointTypes::DATAPOINT_VALUE_TYPES getDpValueType();

    /// <summary>
    /// Returns ConfigFlags structure, either with configuration flags of the
    /// datapoint specified in the constructor, or filled with zeros if
    /// fetched telegram values are invalid. For information about existing
    /// configuration flags refer to BAOS Protocol Documentation, chapter 3.7.
    /// </summary>
    ConfigFlags getDpConfigFlags();

private:
    /// <summary>
    /// Checks if ObjectServer response is an error telegram. Returns false
    /// if an error code has been detected, which then will be decoded and
    /// a respective error message printed in the terminal.
    /// Returns true if the ObjectServer response contains no error code.
    /// </summary>
    bool checkForError();

    /// <summary>
    /// Decodes the datapoint type of the datapoint specified in the constructor.
    /// Prints the result in the terminal.
    /// </summary>
    void decodeDpDpt(DatapointTypes::DATAPOINT_TYPES dpt);

    /// <summary>
    /// Decodes the configuration flags of the datapoint specified in the constructor.
    /// Prints the result in the terminal.
    /// </summary>
    void decodeDpConfigFlags(ConfigFlags configFlagByte);

    /// <summary>
    /// Decodes the datapoint value type of the datapoint specified in the constructor.
    /// Prints the result in the terminal.
    /// </summary>
    void decodeDpValueType(DatapointTypes::DATAPOINT_VALUE_TYPES dpValueType);
};

#endif // GET_DATAPOINT_DESCRIPTION_HPP
