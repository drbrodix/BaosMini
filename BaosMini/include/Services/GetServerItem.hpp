#ifndef GET_SERVER_ITEM_HPP
#define GET_SERVER_ITEM_HPP

#include "BaosTelegram.hpp"
#include "../Utility/DecodeServerItemRes.hpp"
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
	// Returns true if no errors have been encountered
	// while fetching datapoint value, false otherwise
	bool checkForError();
};

#endif // GET_SERVER_ITEM_HPP
