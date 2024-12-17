# BaosMini Overview

## Introduction
  
### Generally about the project
  
This is a minimalistic implementation of the BAOS Protocol, aiming to serve as a stripped down
tool allowing easy access for embedded building automation controller devices to a KNX bus.
This can be done by the use of a BAOS device, which serves as a middle man between our controller and the
target KNX bus, and by the use of this SDK, which provides a communication means with the BAOS device.

### Focus points and the minimalistic approach of the project

Given the minimalistic nature of the project, while other connection types are possible,
this SDK provides a solution exclusively for the intended FT1.2 serial connection, using Windows APIs.
This project has been built entirely in pure C++. During the development, it was an important focus 
of the project to avoid any kind of significant dependency, and promote portability.
To achieve this objective, it was attempted to minimize the use of both external and internal
libraries, and stick to standard features.
This means features available in C++ standards not more recent than C++11,
and those available in most common C++ compilers.
To further improve portability and reduce dependency on anything, be it libraries
or developer environments, the linking of source files and headers to each other
has been done using relative paths. Avoiding the use of a build system, such as Makefile
or CMake, was also a deliberate choice. While these tools provide an excellent way to develop
multiplatform projects, they are also prone to become the source of headaches when the project
is imported into an environment, which is not meant to be used which such build systems.
Instead, using the SDK should be as easy as cloning the project, and including
the header files of the services, which we wish to use in our new project.

## Examples
Below can be found some basic examples, presenting how the communication can be built with
a BAOS device, how telegrams can be created
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

First, create a GetServerItem object, with a pointer to the SerialConnection
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

A quick and easy way to print out certain information about the
BAOS device in the standard output stream is also provided.
For this, use the printServerItems() member function.
When calling the function, pass the first server item
to be retrieved, and then the number of server items requested.

    getServerItem.printServerItems(SERVER_ITEMS::SERIAL_NUMBER, 7);

### SetServerItem
SetServerItem is a BAOS subservice, which allows the setting of values of certain server items
of the connected BAOS device. Refer to Appendix A in the BAOS documentation to find out 
more about the available server items. Not all server items are accessible in this implementation.

First, create a SetServerItem object, with a pointer to the SerialConnection
object passed to the constructor function as a parameter.

    SetServerItem setServerItem(&serialConnection);

Then, use the available member functions of the created SetServerItem
object to communicate with the ObjectServer in the desired way. The function
returns a boolean value, indicating whether the communication was successful.

    bool objectServerResponse   = false;
    objectServerResponse        = setServerItem.setProgrammingMode(true);

The member functions also accept an optional decode parameter, which allows the ObjectServer's 
response to be printed out in the standard output stream. It is set to false by default.

    setServerItem.setBaudrate(BAUDRATES::BAUDRATE_19200, true);

### GetDatapointDescription
SetServerItem is a BAOS subservice, which allows the retrieval of
various data about configured datapoints in the ObjectServer.

First, create a GetDatapointDescription object, with the ID of the datapoint,
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