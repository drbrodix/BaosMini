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

	void setBaudrate(BAUDRATES baudrate, bool decode = false);
	void setCurrentBufferSize(unsigned short bufferSize, bool decode = false);
	void setProgrammingMode(bool enable, bool decode = false);
	void setIndicationSending(bool enable, bool decode = false);

private:
	void setBool(bool enable, bool decode, SERVER_ITEMS serverItem);
	bool decodeSetServerItemRes();
};

#endif // SET_SERVER_ITEM_HPP