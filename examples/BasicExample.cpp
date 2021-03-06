///
/// \file 				BasicExample.cpp
/// \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
/// \edited             n/a
/// \created			2017-06-20
/// \last-modified		2017-08-23
/// \brief 				Contains a simple SerialFiller example.
/// \details
///		See README.md in root dir for more info.

// User includes
#include "SerialFiller/SerialFiller.hpp"

using namespace mn::SerialFiller;

int main() {

    SerialFiller serialFiller;

    // Connect the I/O together, to make
    // a software "loop-back"
    serialFiller.txDataReady_ = ([&](ByteQueue txData) -> void {
        serialFiller.GiveRxData(txData);
    });

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