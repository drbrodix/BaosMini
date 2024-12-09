#ifndef GET_SERVER_ITEM_RES_HPP
#define GET_SERVER_ITEM_RES_HPP

#ifndef SERVER_ITEM_OFFSET_FROM_ID
#define SERVER_ITEM_OFFSET_FROM_ID 3
#endif // !SERVER_ITEM_OFFSET_FROM_ID

#include "../Utility/GetErrorDescription.hpp"
#include "../Enums/ServerItemEnum.hpp"
#include "Macros.hpp"

bool decodeServerItemRes(unsigned char* telegramCharArray, unsigned int telegramLength);

#endif // GET_SERVER_ITEM_RES_HPP