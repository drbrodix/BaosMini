#ifndef SET_SERVER_ITEM_RES_HPP
#define SET_SERVER_ITEM_RES_HPP

#include "../../Enums/ServerItemEnum.hpp"
#include "../Utility/GetErrorDescription.hpp"
#include "../../Utility/Macros.hpp"

bool decodeSetServerItemRes(unsigned char* telegramCharArray, unsigned int telegramLength);

#endif // SET_SERVER_ITEM_RES_HPP