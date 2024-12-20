#ifndef INDICATION_LISTENER_HPP
#define INDICATION_LISTENER_HPP

#define IND_LISTEN_DP_LENGTH_OFFSET 9

#define IND_LISTEN_DP_VALUE_OFFSET 10

#include "BaosTelegram.hpp"
#include "../Utility/FloatConverter.hpp"
#include "../Utility/DatapointTypes.hpp"
#include "../Utility/DecodeServerItemRes.hpp"
#include "../Services/GetDatapointDescription.hpp"
#include <thread>

/// <summary>
/// A service, which allows the monitoring of the connection with the
/// BAOS device. The ObjectServer sends an indication if values of
/// configured datapoints and / or server items are changed, to which the
/// IndicationListener reacts by alerting the user in the standard output stream.
/// </summary>
class IndicationListener : public BaosTelegram
{
public:
	/// <summary>
	/// The constructor function calls the base class BaosTelegram 
	/// constructor function, thus initializing the basic data members.
	/// A new thread will be started, in which the IndicationListener
	/// will be constantly reading the data sent by the ObjectServer.
	/// </summary>
	/// <param name="serialConnection">A pointer to the SerialConnection object.</param>
	IndicationListener(
        SerialConnection* serialConnection);

	/// <summary>
	/// The default destructor calls the parent function,
	/// which frees up the dynamically allocated
	/// memory of the baosTelegram and responseTelegram arrays.
	/// </summary>
	~IndicationListener();

private:
	/// <summary>
	/// The function passed to the listener thread. It is constantly
	/// reading data recieved through the serial connection. If a
	/// datapoint or server item indication is recieved from the
	/// ObjectServer, the content of the telegram will be decoded,
	/// and a respective message printed out in the standard output stream.
	/// </summary>
	/// 
	/// <param name="responseTelegram">A pointer to the buffer, in which the
	/// recieved indication telegram will be stored.</param>
	/// 
	/// <param name="responseLength">A pointer to the intiger, in which the
	/// length of the indication telegram buffer will be stored.</param>
	/// 
	/// <param name="serialConnection">A pointer to the SerialConnection object.</param>
	static void startListening(unsigned char* responseTelegram, unsigned int* responseLength, SerialConnection* serialConnection);
	
	/// <summary>
	/// It is responsible for reversing the byte order of
	/// a 4byte float value, effectively converting it
	/// between little-endian and big-endian formatting.
	/// </summary>
	/// 
	/// <param name="pValueStartAddress">Address of the float
	/// value in the recieved telegram.</param>
	/// 
	/// <returns>Returns the float value in reversed byte order.</returns>
	static float decode4ByteFloat(unsigned char* pValueStartAddress);
	
	/// <summary>
	/// Called if the IndicationListener recieves a datapoint
	/// indication. It decodes the recieved telegram, and prints
	/// out the content in the standard output stream.
	/// </summary>
	/// 
	/// <param name="responseTelegram">An array containing the indication
	/// telegram recieved from the ObjectServer.</param>
	/// 
	/// <param name="dpt">The datapoint type of the datapoint,
	/// to which the indication was sent.</param>
	/// 
	/// <returns>Returns true if the decoding process
	/// was successful, false otherwise.</returns>
	static bool decodeDatapointIndication(unsigned char* responseTelegram, DatapointTypes::DATAPOINT_TYPES dpt);
};

#endif // INDICATION_LISTENER_HPP
