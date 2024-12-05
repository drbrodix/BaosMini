#ifndef GET_DATAPOINT_DESCRIPTION_HPP
#define GET_DATAPOINT_DESCRIPTION_HPP

#include "BaosTelegram.hpp"

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
    unsigned char getDpDpt();
    // Refer to BAOS Protocol Documentation, Appendix C
    // Returns 0 if fetched telegram values are invalid
    unsigned char getDpValueType();
    // Refer to BAOS Protocol Documentation, Chapter 3.7
    // Returns 0 if fetched telegram values are invalid
    unsigned char getDpConfigFlagsByte();

private:
    // Returns true if errors have been encountered while fetching datapoint value
    bool checkForError();
    void decodeDpDpt(unsigned char dpt);
    void decodeDpConfigFlags(unsigned char configFlagByte);
    void decodeDpValueType(unsigned char dpValueType);
};

#endif // GET_DATAPOINT_DESCRIPTION_HPP
