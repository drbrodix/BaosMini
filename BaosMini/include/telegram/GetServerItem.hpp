#ifndef GET_SERVER_ITEM_HPP
#define GET_SERVER_ITEM_HPP

#include "telegram/BaosTelegram.hpp"

class GetServerItem : public BaosTelegram
{
public:
    GetServerItem(
       int firstItemId,
       int nrOfItems);
	~GetServerItem();

private:

};

#endif // GET_SERVER_ITEM_HPP
