#ifndef GET_SERVER_ITEM_RES_HPP
#define GET_SERVER_ITEM_RES_HPP


/// <summary>
/// Index of the server item data in the response
/// array, offset from the ID of the server item.
/// </summary>
#define SERVER_ITEM_OFFSET_FROM_ID 3

/// <summary>
/// Index of the error code in the response array, in
/// case the ObjectServer responds with an error telegram.
/// </summary>
#define ERROR_CODE_OFFSET 6

#include "../Utility/GetErrorDescription.hpp"
#include "../Enums/ServerItemEnum.hpp"
#include "Macros.hpp"

/// <summary>
/// An entry point to a line of server item response decoding functions.
/// A GetServerItem response telegram passed as a parameter will be decoded,
/// and the content printed out in the standard output stream.
/// An error check will be executed, and a respective boolean value returned.
/// The function returns true if no indication of an error has been detected,
/// false otherwise.
/// </summary>
bool decodeServerItemRes(unsigned char* telegramCharArray, unsigned int telegramLength);

#endif // GET_SERVER_ITEM_RES_HPP