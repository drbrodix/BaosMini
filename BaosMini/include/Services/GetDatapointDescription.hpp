#ifndef GET_DATAPOINT_DESCRIPTION_HPP
#define GET_DATAPOINT_DESCRIPTION_HPP

#include "BaosTelegram.hpp"

typedef struct {
    unsigned char transmitPriority          : 2;
    unsigned char datapointCommunication    : 1;
    unsigned char readFromBus               : 1;
    unsigned char writeFromBus              : 1;
    unsigned char readOnInit                : 1;
    unsigned char transmitToBus             : 1;
    unsigned char updateOnResponse          : 1;
} ConfigFlags;

class GetDatapointDescription : public BaosTelegram
{
public:
    GetDatapointDescription(
        unsigned short datapointId,
        SerialConnection* serialConnection);
	~GetDatapointDescription();
    
    // Print all available data about the datapoint in terminal
    // Returns true if fetched telegram values are valid, false if invalid
    bool printDpDescription(
        bool datapointDpt,
        bool datapointValueType,
        bool datapointConfigFlag);
    // Refer to BAOS Protocol Documentation, Appendix D
    // Returns 0 if fetched telegram values are invalid
    DatapointTypes::DATAPOINT_TYPES getDpDpt();
    // Refer to BAOS Protocol Documentation, Appendix C
    // Returns 0x0F if fetched telegram values are invalid
    DatapointTypes::DATAPOINT_VALUE_TYPES getDpValueType();
    // Refer to BAOS Protocol Documentation, Chapter 3.7
    // Returns ConfigFlags object filled with 0,
    // if fetched telegram values are invalid
    ConfigFlags getDpConfigFlags();

private:
    // Returns true if no errors have been encountered
    // while fetching datapoint value, false otherwise
    bool checkForError();
    void decodeDpDpt(DatapointTypes::DATAPOINT_TYPES dpt);
    void decodeDpConfigFlags(ConfigFlags configFlagByte);
    void decodeDpValueType(DatapointTypes::DATAPOINT_VALUE_TYPES dpValueType);
};

#endif // GET_DATAPOINT_DESCRIPTION_HPP
