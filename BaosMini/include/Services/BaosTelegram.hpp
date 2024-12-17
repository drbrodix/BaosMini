#ifndef BAOS_TELEGRAM_HPP
#define BAOS_TELEGRAM_HPP

/// <summary>
/// BAOS main service code constant
/// </summary>
#define BAOS_MAIN_SERVICE 0xF0

/// <summary>
/// Constant for allocation of memory for
/// telegram to be sent to ObjectServer
/// </summary>
#define TELEGRAM_ARR_SIZE 30

/// <summary>
/// Constant for allocation of memory for
/// ObjectServer response telegram buffer
/// </summary>
#define RESPONSE_ARR_SIZE 250

/// <summary>
/// Number of bytes reserved for the
/// BAOS telegram in the FT1.2 array
/// </summary>
#define BAOS_BYTES_IN_ARR (TELEGRAM_ARR_SIZE - BAOS_DATA_FIRST_INDEX)

/// <summary>
/// Index of the first byte in the baosTelegram array
/// reserved for the BAOS telegram header part.
/// This stands after the 5 bytes of the FT1.2 header.
/// </summary>
#define BAOS_HEADER_FIRST_INDEX 5

/// <summary>
/// Index of the BAOS subservice code in the BAOS header
/// </summary>
#define BAOS_SUBSERVICE_CODE_INDEX (BAOS_HEADER_FIRST_INDEX + 1)

/// <summary>
/// Index of the first byte in the baosTelegram array
/// reserved for the BAOS telegram data part.
/// This stands after the 2 bytes of the BAOS header.
/// </summary>
#define BAOS_DATA_FIRST_INDEX (BAOS_HEADER_FIRST_INDEX + 2)

/// <summary>
/// Index of the error code in the baosTelegram array,
/// in case the ObjectServer responds with an error telegram.
/// </summary>
#define ERROR_CODE_OFFSET 6

#include <cstring>
#include <cstdio>
#include <exception>
#include "../Utility/GetErrorDescription.hpp"
#include "../Utility/SerialConnection.hpp"
#include "../Utility/DatapointTypes.hpp"
#include "../Enums/SubservicesEnum.hpp"
#include "../Utility/Macros.hpp"

/// <summary>
/// A base class for all the BAOS service telegrams.
/// It provides basic data members, member functions
/// and various definitions to its children classes.
/// Cannot be instantiated on its own.
/// </summary>
class BaosTelegram
{
protected:
    /// <summary>
    /// The default constructor initiates all data
    /// members to NULL and nullptr accordingly.
    /// </summary>
    BaosTelegram();
    /// <summary>
    /// The constructor function allocates TELEGRAM_ARR_SIZE (30 bytes)
    /// to the BAOS telegram, initializes all the elements to 0,
    /// and sets the first element to the BAOS main service code (0xF0).
    /// The constructor function allocates RESPONSE_ARR_SIZE (250 bytes)
    /// to the response telegram, and initializes all the elements to 0.
    /// </summary>
    BaosTelegram(SerialConnection *serialConnection);
    /// <summary>
    /// The default destructor frees up the dynamically allocated
    /// memory of the baosTelegram and responseTelegram arrays.
    /// </summary>
    ~BaosTelegram();

    /// <summary>
    /// Initiates reading the ObjectServer's response.
    /// Returns response telegram length, or 0 if error has occured.
    /// </summary>
    unsigned int getAnswer();

    /// <summary>
    /// Clear the data part of the telegram, that is the bytes
    /// after the BAOS mainservice and subservice codes, so that
    /// no conflict occurs in case of differring telegram lengths.
    /// </summary>
    void clearTelegram();
    
    /// <summary>
    /// Length of telegram recieved from ObjectServer.
    /// </summary>
    unsigned int responseLength;

    /// <summary>
    /// Length of telegram to be sent to ObjectServer.
    /// </summary>
    unsigned char telegramLength;

    /// <summary>
    /// Unsigned char array of telegram to be sent to ObjectServer.
    /// </summary>
    unsigned char *baosTelegram;

    /// <summary>
    /// Unsigned char array of ObjectServer response telegram .
    /// </summary>
    unsigned char *responseTelegram;

    /// <summary>
    /// Keeps track if ObjectServer response telegram is valid.
    /// </summary>
    bool hasValidResponse;

    /// <summary>
    /// The passed pointer to the serial connection object will be
    /// stored to allow communication with the connected BAOS device.
    /// </summary>
    SerialConnection *serialConnection;
};

#endif // BAOS_TELEGRAM_HPP
