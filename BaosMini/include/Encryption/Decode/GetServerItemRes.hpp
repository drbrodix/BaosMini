#ifndef GET_SERVER_ITEM_RES_HPP
#define GET_SERVER_ITEM_RES_HPP

#include "../Utility/GetErrorDescription.hpp"

bool decodeGetServerItemRes(unsigned char* telegramCharArray, unsigned int telegramLength);

#endif // GET_SERVER_ITEM_RES_HPP