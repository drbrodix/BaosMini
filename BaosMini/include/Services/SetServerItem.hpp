#ifndef SET_SERVER_ITEM_HPP
#define SET_SERVER_ITEM_HPP

#ifndef START_ITEM_OFFSET_FROM_MAINSERVICE
#define START_ITEM_OFFSET_FROM_MAINSERVICE BAOS_HEADER_FIRST_INDEX + 2
#endif // !START_ITEM_OFFSET_FROM_MAINSERVICE

#ifndef NR_OF_ITEMS_OFFSET_FROM_MAINSERVICE
#define NR_OF_ITEMS_OFFSET_FROM_MAINSERVICE BAOS_HEADER_FIRST_INDEX + 4
#endif // !NR_OF_ITEMS_OFFSET_FROM_MAINSERVICE

#ifndef FIRST_ITEM_ID_OFFSET_FROM_MAINSERVICE
#define FIRST_ITEM_ID_OFFSET_FROM_MAINSERVICE BAOS_HEADER_FIRST_INDEX + 6
#endif // !FIRST_ITEM_ID_OFFSET_FROM_MAINSERVICE

#ifndef FIRST_ITEM_LENGTH_OFFSET_FROM_MAINSERVICE
#define FIRST_ITEM_LENGTH_OFFSET_FROM_MAINSERVICE BAOS_HEADER_FIRST_INDEX + 8
#endif // !FIRST_ITEM_LENGTH_OFFSET_FROM_MAINSERVICE

#ifndef FIRST_ITEM_DATA_OFFSET_FROM_MAINSERVICE
#define FIRST_ITEM_DATA_OFFSET_FROM_MAINSERVICE BAOS_HEADER_FIRST_INDEX + 9
#endif // !FIRST_ITEM_DATA_OFFSET_FROM_MAINSERVICE

#include "BaosTelegram.hpp"
#include "../Enums/ServerItemEnum.hpp"
#include "../Utility/Macros.hpp"

class SetServerItem : public BaosTelegram
{
public:
	SetServerItem(
		SerialConnection* serialConnection);
	~SetServerItem();

	bool setBaudrate(BAUDRATES baudrate, bool decode = false);
	bool setCurrentBufferSize(unsigned short bufferSize, bool decode = false);
	bool setProgrammingMode(bool enable, bool decode = false);
	bool setIndicationSending(bool enable, bool decode = false);

private:
	template <typename T> bool setValue(T itemValue, SERVER_ITEMS serverItem, unsigned char itemLength, bool decode);
	bool decodeSetServerItemRes();
};

#endif // SET_SERVER_ITEM_HPP