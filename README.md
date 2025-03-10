## Introduction
  
### Generally about the project
  
This is a minimalistic implementation of the BAOS Protocol, which was created by
[Weinzierl Engineering GmbH](http://weinzierl.de/). This project aims to serve as a
stripped down tool for embedded building automation controller devices, allowing
easy and quick access to a KNX bus. This can be done by the use of a BAOS device,
which serves as a middleman between our controller and the target KNX bus, and
by the use of this SDK, which provides a communication means with the BAOS device.

### Focus points and the minimalistic approach of the project

Given the minimalistic nature of the project, while other connection types are possible,
this SDK provides a solution exclusively for the intended FT1.2 serial connection,
using Windows APIs. This project has been built entirely in pure C++. During the development,
it was an important focus of the project to avoid any kind of significant dependency, and
promote portability. To achieve this objective, it was attempted to minimize the use of both
external and internal libraries, and stick to standard features. This means features available
in C++ standards not more recent than C++11, and those available in most common C++ compilers.
To further improve portability and reduce dependency on anything, be it libraries
or developer environments, the linking of source files and headers to each other
has been done using relative paths. Avoiding the use of a build system, such as Makefile
or CMake, was a deliberate choice as well.

## Examples
Below can be found some basic examples, presenting how the communication with a BAOS device
can be built, how telegrams can be created
to use certain supported BAOS subservices, and how these telegrams can be eventually sent
to the ObjectServer via serial connection.

### Serial Connection
Before everything else, a SerialConnection object should be created, which serves as a means
to send data to, and recieve data from the connected BAOS device.

    // Simply create a SerialConnection object, with a string
    // of the name of the serial interface passed as a parameter

    SerialConnection serialConnection("COM3");

### GetServerItem
GetServerItem is a BAOS subservice, which allows the retrieval of various data about the 
connected BAOS device. Refer to Appendix A in the BAOS documentation to find out more
about the available server items. Not all server items are accessible in this implementation.

First, create a GetServerItem object with a pointer to the SerialConnection
object passed to the constructor function as a parameter.

    GetServerItem getServerItem(&serialConnection);

Then, use the available member functions of the created GetServerItem
object to communicate with the ObjectServer in the desired way.

    BaosVersion hardwareVersion = { 0 };
    hardwareVersion             = getServerItem.getHardwareVersion();

    BaosSerialNumber baosSerialNumber   = { 0 };
    baosSerialNumber                    = getServerItem.getSerialNumber();

    bool isProgrammingModeEnabled   = false;
    isProgrammingModeEnabled        = getServerItem.getProgrammingMode();

A quick and easy way to print out certain information about the BAOS device
in the standard output stream is also provided. For this, use the printServerItems()
member function. When calling the function, pass the first server item to be
retrieved, and then the number of server items requested as parameters.

    getServerItem.printServerItems(SERVER_ITEMS::SERIAL_NUMBER, 7);

### SetServerItem
SetServerItem is a BAOS subservice, which allows the setting of values of certain server items
of the connected BAOS device. Refer to Appendix A in the BAOS documentation to find out 
more about the available server items. Not all server items are accessible in this implementation.

First, create a SetServerItem object with a pointer to the SerialConnection
object passed to the constructor function as a parameter.

    SetServerItem setServerItem(&serialConnection);

Then, use the available member functions of the created SetServerItem
object to communicate with the ObjectServer in the desired way. The function
returns a boolean value, indicating whether the communication was successful.

    bool objectServerResponse   = false;
    objectServerResponse        = setServerItem.setProgrammingMode(true);

The member functions also accept an optional decode boolean parameter, which allows the
ObjectServer's response to be printed out in the standard output stream. It is set to false by default.

    // Will print out ObjectServer response

    setServerItem.setBaudrate(BAUDRATES::BAUDRATE_19200, true);

### GetDatapointDescription
GetDatapointDescription is a BAOS subservice, which allows the retrieval of
various data about configured datapoints in the ObjectServer.

First, create a GetDatapointDescription object with the ID of the datapoint,
whose description we want to fetch from the ObjectServer, and with a pointer to
the SerialConnection object, passed to the constructor function as parameters.

    GetDatapointDescription getDatapointDescription(5, &serialConnection);

Then, use the available member functions of the created 
GetDatapointDescription object to get the desired data.

    DatapointTypes::DATAPOINT_VALUE_TYPES dpValueType = getDatapointDescription.getDpValueType();

    ConfigFlags configFlags     = getDatapointDescription.getDpConfigFlags();
    bool updateOnResponseFlag   = configFlags.updateOnResponse;
    bool readOnInitFlag         = configFlags.readOnInit;

A quick and easy way to print out certain information about the datapoint in the standard output
stream is also provided. For this, use the printDpDescription() member function.
To print out the datapoint type, the datapoint value type, and the datapoint configuration flags,
the respective flags need to be set by passing the function boolean parameters accordingly.

    // The datapoint type and the datapoint configuration flags
    // will be output, the datapoint value type not.

    getDatapointDescription.printDpDescription(true, false, true);

### GetDatapointValue
GetDatapointValue is a BAOS subservice, which allows the retrieval of datapoint values of configured
datapoints in the ObjectServer. Refer to Appendix D in the BAOS documentation to find out more
about the available datapoint types. Not all datapoint types are accessible in this implementation.

First, create a GetDatapointValue object with the ID of the datapoint,
whose value we want to fetch from the ObjectServer, with the datatype of
the datapoint, and with a pointer to the SerialConnection object,
passed to the constructor function as parameters.

    GetDatapointValue getBoolValue(7, DatapointTypes::BOOLEAN, &serialConnection);

    GetDatapointValue getSigned2ByteValue(9, DatapointTypes::SIGNED_VALUE_2BYTE, &serialConnection);

Then, use the available member functions of the created 
GetDatapointValue object to get the desired data.

    bool boolValue  = false;
    boolValue       = getBoolValue.getBooleanValue();

    short shortValue    = 0;
    shortValue          = getSigned2ByteValue.getSignedValue2Byte();

### SetDatapointValue
SetDatapointValue is a BAOS subservice, which allows the setting of datapoint values of
configured datapoints in the ObjectServer. Refer to Appendix D in the BAOS documentation to find out 
more about the available datapoint types. Not all datapoint types are accessible in this implementation.

First, create a SetDatapointValue object with the ID of the datapoint,
whose value we want to set, and with a pointer to the SerialConnection
object, passed to the constructor function as parameters.

    SetDatapointValue setDatapointValue17(17, &serialConnection);

    SetDatapointValue setDatapointValue39(39, &serialConnection);

Then, use the available member functions of the created SetDatapointValue object
to communicate with the ObjectServer in the desired way. When calling the function,
pass the value, which the datapoint should be set to, and a command byte, which
allows further configuration, what the telegram will be used for, as parameters.

    setDatapointValue17.setBoolean(true, CommandByte::SetNewValueAndSendOnBus);

The member functions also accept an optional decode boolean parameter, which allows the
ObjectServer's response to be printed out in the standard output stream. It is set to false by default.

    // Will print out ObjectServer response

    setDatapointValue39.setFloatValue2Byte(-49.17f, CommandByte::SetNewValueAndSendOnBus, true);

### GetParameterByte
GetParameterByte is a BAOS subservice, which allows the
retrieval of parameter bytes configured in the ObjectServer.

First, create a GetParameterByte object with the ID of the parameter byte,
whose value we want to fetch from the ObjectServer, and with a pointer to
the SerialConnection object, passed to the constructor function as parameters.

    GetParameterByte getParameterByte(24, &serialConnection);

Then, simply call the member function getByte(), which returns the fetched value.

    getParameterByte.getByte();

### IndicationListener
Finally, an IndicationListener is also available in this SDK, which
is constantly listening to any data sent from the connected BAOS device
on the serial connection. In case a datapoint or a server item indication
is sent to the client, the IndicationListener prints the content of the
indication in the standard output stream.
To start the listening subservice, just create an IndicationListener object with a
pointer to the SerialConnection object passed to the constructor function as parameter.

    IndicationListener indicationListener(&serialConnection);

While this subservice is listening, other parts of the program will be waiting!

### BaosTester
One more handy tool is the BaosTester. It is a class, which allows the quick testing
of all the available BAOS subservices. By default, the functions in this class
are filled with some basic requests in order to test the system. These functions
are quite easy and straightforward to edit in the source code.
To start testing the connection and the subservices, just create a BaosTester object with a
pointer to the SerialConnection object passed to the constructor function as parameter.

    BaosTester baosTester(&serialConnection);

Then call the startTestingProcess member function of this new object.

    baosTester.startTestingProcess();

It is possible to configure the testing process and use only certain BAOS subservices
by setting the corresponding boolean parameters. By default, all these parameters
are set to true.

    baosTester.startTestingProcess(
            true,   // GetServerItem
            true,   // SetServerItem
            true,   // GetDatapointDescription
            true,   // GetDatapointValue
            true,   // SetDatapointValue
            true    // GetParameterByte
        );

## Further documentation
Further documentation of the project is available as a Doxygen documentation.
Use the GitHub Pages link to check it out.
