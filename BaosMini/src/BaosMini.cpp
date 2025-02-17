#include "../include/BaosMini.hpp"

int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;
    SerialConnection serialConnection(L"COM3");
    
    //IndicationListener il(&serialConnection);
    //il.startListening();

    BaosTester baosTester(&serialConnection);
    baosTester.startTestingProcess(
        true,   // GetServerItem
        true,   // SetServerItem
        true,   // GetDatapointDescription
        true,   // GetDatapointValue
        true,   // SetDatapointValue
        true    // GetParameterByte
    );

    return EXIT_SUCCESS;
}
