#ifndef GET_SERVER_ITEM_HPP
#define GET_SERVER_ITEM_HPP

#include "BaosTelegram.hpp"

class GetServerItem : public BaosTelegram
{
public:
	GetServerItem(
		unsigned short firstItemId,
		unsigned short nrOfItems,
		SerialConnection* serialConnection);
	~GetServerItem();

private:

};

#endif // GET_SERVER_ITEM_HPP
