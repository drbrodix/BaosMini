#ifndef GET_SERVER_ITEM_RES_HPP
#define GET_SERVER_ITEM_RES_HPP

#ifndef SERVER_ITEM_OFFSET_FROM_ID
#define SERVER_ITEM_OFFSET_FROM_ID 3
#endif // !SERVER_ITEM_OFFSET_FROM_ID

#include "../Utility/GetErrorDescription.hpp"
#include "../../Enums/ServerItemEnum.hpp"
#include "../../Utility/Macros.hpp"

bool decodeGetServerItemRes(unsigned char* telegramCharArray, unsigned int telegramLength);
unsigned short decodeServerItem(unsigned char* telegramCharArray, unsigned short currentIndex, unsigned short itemId);
inline void formatServerItemHex(unsigned char* pDataStartAddress, unsigned char itemLength);
inline void formatServerItemVersion(unsigned char* pDataStartAddress);
inline void formatServerItemTime(unsigned char* pDataStartAddress, unsigned char itemLength);
inline void formatServerItemBaudrate(unsigned char* pDataStartAddress);
inline void formatServerItemSize(unsigned char* pDataStartAddress);
inline void formatServerItemIsEnabled(unsigned char* pDataStartAddress);
inline void formatServerItemKNXAddress(unsigned char* pDataStartAddress);

#endif // GET_SERVER_ITEM_RES_HPP