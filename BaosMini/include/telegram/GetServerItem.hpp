#ifndef GET_SERVER_ITEM_HPP
#define GET_SERVER_ITEM_HPP

#include "telegram/BaosTelegram.hpp"
#include "Utility/FormatterFunctions.hpp"

class GetServerItem : public BaosTelegram
{
public:
	GetServerItem(
		unsigned short firstItemId,
		unsigned short nrOfItems);
	~GetServerItem();

private:

};

#endif // GET_SERVER_ITEM_HPP
