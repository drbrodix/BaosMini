#ifndef GET_SERVER_ITEM_RES_HPP
#define GET_SERVER_ITEM_RES_HPP

#ifndef OFFSET_FROM_ID
#define OFFSET_FROM_ID 3
#endif // !OFFSET_FROM_ID

// Byte swapper macros for endianess
#ifndef swap2
#define swap2(x) (((x << 8) & 0xFF00) | ((x >> 8) & 0x00FF))
#endif // !swap2

#ifndef swap4
#define swap4(x) (((x << 24) & 0xFF000000) | ((x << 8) & 0x00FF0000) | ((x >> 8) & 0x0000FF00) | ((x >> 24) & 0x000000FF))
#endif // !swap4

#include "../Utility/GetErrorDescription.hpp"
#include "../../Enums/ServerItemEnum.hpp"

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