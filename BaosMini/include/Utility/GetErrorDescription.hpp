#ifndef GET_ERROR_DESCRIPTION_HPP
#define GET_ERROR_DESCRIPTION_HPP

/// <summary>
/// A constant representing the size of the error string.
/// </summary>
#define ERROR_STRING_SIZE 30

#include <string>

/// <summary>
/// Takes an error code defined in the BAOS protocol,
/// and decodes it. A respective string will be formatted,
/// and printed out in the standard output stream.
/// </summary>
bool getErrorDescription(unsigned char errorCode);

#endif // !GET_ERROR_DESCRIPTION_HPP