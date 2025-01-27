#ifndef GET_PARAMETER_BYTE_HPP
#define GET_PARAMETER_BYTE_HPP

/// <summary>
/// Index of the ID of the parameter byte to be fetched, offset
/// from the BAOS main service code in the baosTelegram array.
/// </summary>
#define GET_PARAM_BYTE_PARAM_BYTE_ID_OFFSET BAOS_DATA_FIRST_INDEX

/// <summary>
/// Index of the number of parameter bytes to be fetched, offset
/// from the BAOS main service code in the baosTelegram array.
/// </summary>
#define GET_PARAM_BYTE_NR_OF_BYTES_OFFSET (BAOS_DATA_FIRST_INDEX + 2)

/// <summary>
/// Index of the number of parameter bytes requested, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#define GET_PARAM_BYTE_RES_NR_OF_BYTES_OFFSET 4

/// <summary>
/// Index of the first parameter byte requested, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#define GET_PARAM_BYTE_RES_FIRST_BYTE_OFFSET 6

#include "BaosTelegram.hpp"

/// <summary>
/// A BAOS service, allowing the retrieval of
/// parameter bytes configured in the ObjectServer.
/// </summary>
class GetParameterByte : public BaosTelegram
{
public:
    /// <summary>
    /// The constructor function executes the entire communication process between
    /// the client and the ObjectServer. It sets up and sends the telegram to the
    /// ObjectServer with the passed parameters, then retrieves and stores the answer.
    /// An error check will be done, and the result stored for further use.
    /// </summary>
    /// <param name="parameterByteId">The ID of the parameter byte,
    /// whose value should be fetched.</param>
    /// <param name="serialConnection">A pointer to the SerialConnection object.</param>
    GetParameterByte(
        unsigned short parameterByteId,
        SerialConnection* serialConnection);
	
    /// <summary>
    /// The default destructor calls the parent function,
    /// which frees up the dynamically allocated
    /// memory of the baosTelegram and responseTelegram arrays.
    /// </summary>
    ~GetParameterByte();

    /// <summary>
    /// Returns the retrieved parameter byte from the ObjectServer,
    /// or 0 if no valid value has been fetched from the ObjectServer.
    /// </summary>
    /// <returns>Returns the value of the parameter byte fetched from the ObjectServer.</returns>
    unsigned char getByte();

private:
    /// <summary>
    /// Checks if ObjectServer response is an error telegram.
    /// </summary>
    /// <returns>If an error is detected, false will be returned, and a
    /// respective error message printed out in the standard output stream.
    /// Returns true if no issues have been detected.</returns>
    bool checkForError();
};

#endif // GET_PARAMETER_BYTE_HPP