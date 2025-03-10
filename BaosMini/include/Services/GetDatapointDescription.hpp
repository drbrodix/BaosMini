#ifndef GET_DATAPOINT_DESCRIPTION_HPP
#define GET_DATAPOINT_DESCRIPTION_HPP

/// <summary>
/// Index of the ID of the datapoint, whose description
/// should be fetched, offset from the BAOS 
/// main service code in the baosTelegram array.
/// </summary>
#define GET_DP_DESC_DP_ID_OFFSET BAOS_DATA_FIRST_INDEX

/// <summary>
/// Index of the datapoint configuration flags, offset from
/// the BAOS main service code in the baosTelegram array.
/// </summary>
#define GET_DP_DESC_NR_OF_DPS_OFFSET (BAOS_DATA_FIRST_INDEX + 2)

/// <summary>
/// Index of the datapoint value type, offset from the
/// BAOS main service code in the baosTelegram array.
/// </summary>
#define GET_DP_DESC_DP_VALUE_TYPE_OFFSET 8

/// <summary>
/// Index of the datapoint configuration flags, offset from
/// the BAOS main service code in the baosTelegram array.
/// </summary>
#define GET_DP_DESC_DP_CONFIG_FLAGS_OFFSET 9

/// <summary>
/// Index of the number of datapoints requested, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#define GET_DP_DESC_RES_NR_OF_DPS_OFFSET 4

/// <summary>
/// Index of the datapoint ID, offset from the BAOS main service
/// code in the ObjectsServer's response telegram array.
/// </summary>
#define GET_DP_DESC_RES_DP_ID_OFFSET 6

/// <summary>
/// Index of the datapoint type, offset from the BAOS main service 
/// code in the ObjectsServer's response telegram array.
/// </summary>
#define GET_DP_DESC_RES_DP_DPT_OFFSET 10

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
    /// An error check will be executed, and the result stored for further use.
    /// </summary>
    /// <param name="datapointId">The ID of the datapoint, whose description should be fetched.</param>
    /// <param name="serialConnection">A pointer to the SerialConnection object.</param>
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
    /// Prints out data, specified in the parameters,
    /// about the datapoint in the standard output stream.
    /// </summary>
    /// 
    /// <param name="datapointDpt">Set to true to print out datapoint type
    /// of the datapoint in the standard output stream.</param>
    /// 
    /// <param name="datapointValueType">Set to true to print out datapoint
    /// value type of the datapoint in the standard output stream.</param>
    /// 
    /// <param name="datapointConfigFlag">Set to true to print out information about
    /// the configuration flags of the datapoint in the standard output stream.</param>
    /// 
    /// <returns>Returns true if fetched telegram values are valid, false if invalid.</returns>
    bool printDpDescription(
        bool datapointDpt,
        bool datapointValueType,
        bool datapointConfigFlag);

    /// <summary>
    /// For datapoint types explanation refer
    /// to BAOS Protocol Documentation, Appendix D.
    /// </summary>
    /// <returns>Returns the datapoint type of the datapoint specified
    /// in the constructor, or 0 if fetched telegram values are invalid.</returns>
    DatapointTypes::DATAPOINT_TYPES getDpDpt();

    /// <summary>
    /// For value types explanation refer to BAOS Protocol Documentation, Appendix C.
    /// </summary>
    /// <returns>Returns the datapoint value type of the datapoint specified
    /// in the constructor, or 0x0F if fetched telegram values are invalid.</returns>
    DatapointTypes::DATAPOINT_VALUE_TYPES getDpValueType();

    /// <summary>
    /// For information about existing configuration flags
    /// refer to BAOS Protocol Documentation, chapter 3.7.
    /// </summary>
    /// <returns>Returns ConfigFlags structure, either with configuration
    /// flags of the datapoint specified in the constructor, or filled
    /// with zeros if fetched telegram values are invalid.</returns>
    ConfigFlags getDpConfigFlags();

private:
    /// <summary>
    /// Checks if ObjectServer response is an error telegram.
    /// </summary>
    /// <returns>Returns false if an error code has been detected,
    /// which then will be decoded and a respective error message
    /// printed out in the standard output stream. Returns true,
    /// if the ObjectServer response contains no error code.</returns>
    bool checkForError();

    /// <summary>
    /// Decodes the datapoint type of the datapoint specified in the
    /// constructor. Prints the result in the standard output stream.
    /// </summary>
    /// <param name="dpt">The datapoint type to be decoded</param>
    void decodeDpDpt(DatapointTypes::DATAPOINT_TYPES dpt);

    /// <summary>
    /// Decodes the configuration flags of the datapoint specified in
    /// the constructor. Prints the result in the standard output stream.
    /// </summary>
    /// <param name="configFlagByte">The datapoint configuration
    /// flag byte to be decoded.</param>
    void decodeDpConfigFlags(ConfigFlags configFlagByte);

    /// <summary>
    /// Decodes the datapoint value type of the datapoint specified in
    /// the constructor. Prints the result in the standard output stream.
    /// </summary>
    /// <param name="configFlagByte">The datapoint configuration
    /// flag byte to be decoded.</param>
    void decodeDpValueType(DatapointTypes::DATAPOINT_VALUE_TYPES dpValueType);
};

#endif // GET_DATAPOINT_DESCRIPTION_HPP
