///
/// \file 				ExceptionCheckingExample.cpp
/// \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
/// \edited             n/a
/// \created			2017-06-20
/// \last-modified		2015-06-20
/// \brief 				Contains an example which checks for all types of exceptions thrown.
/// \details
///		See README.md in root dir for more info.

#include "SerialFiller/SerialFiller.hpp"

int main() {

    mn::SerialFiller serialFiller;

    // Connect the I/O together, to make
    // a software "loop-back"
    serialFiller.txDataReady_ = [&](mn::ByteQueue txData) -> void {

        try {
            serialFiller.GiveRxData(txData);
        } catch (mn::CrcCheckFailed e) {
            std::cout << e.what() << std::endl;
        }
    };

    // Subscribe to topic "mytopic"
    serialFiller.Subscribe("mytopic", [](std::vector<uint8_t> rxData) -> void {
        std::cout << "Received packet on mytopic!" << std::endl;

        std::cout << " Data = ";
        for(auto dataByte : rxData) {
            std::cout << std::to_string(dataByte);
        }
        std::cout << std::endl;
    });

    serialFiller.Publish("mytopic", {0x01, 0x02, 0x03});

    return 0;

}