#ifndef GET_SERVER_ITEM_HPP
#define GET_SERVER_ITEM_HPP

#include "BaosTelegram.hpp"
#include "../Enums/ServerItemEnum.hpp"

class GetServerItem : public BaosTelegram
{
public:
	GetServerItem(
		SERVER_ITEMS firstItemId,
		unsigned short nrOfItems,
		SerialConnection* serialConnection);
	~GetServerItem();

private:
	// Returns true if errors have been encountered while fetching datapoint value
	bool checkForError();
};

#endif // GET_SERVER_ITEM_HPP
