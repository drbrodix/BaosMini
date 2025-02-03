#ifndef BAOS_TESTER_HPP
#define BAOS_TESTER_HPP

#include "../Services/SetDatapointValue.hpp"
#include "../Services/GetDatapointValue.hpp"
#include "../Services/GetServerItem.hpp"
#include "../Services/SetServerItem.hpp"
#include "../Services/GetDatapointDescription.hpp"
#include "../Services/GetParameterByte.hpp"
#include "../Services/IndicationListener.hpp"

class BaosTester
{
public:
	BaosTester(SerialConnection* serialConnection);
	~BaosTester();

	void startTestingProcess(
		bool runGetServerItemTest = true,
		bool runSetServerItemTest = true,
		bool runGetDatapointDescriptionTest = true,
		bool runGetDatapointValueTest = true,
		bool runSetDatapointValueTest = true,
		bool runGetParameterByteTest = true
	);

private:
	SerialConnection* serialConnection;

	void testGetServerItem();
	void testSetServerItem();
	void testGetDatapointDescription();
	void testGetDatapointValue();
	void testSetDatapointValue();
	void testGetParameterByte();
};

#endif // BAOS_TESTER_HPP