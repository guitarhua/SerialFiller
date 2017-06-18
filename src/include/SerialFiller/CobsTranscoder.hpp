
#ifndef SERIAL_FILLER_COBS_TRANSCODER_H_
#define SERIAL_FILLER_COBS_TRANSCODER_H_

// System includes
#include <string>

// User includes
#include "SerialFiller/SerialFiller.hpp"

namespace mn {

    class CobsTranscoder {

    public:

        enum class DecodeStatus {
            SUCCESS,
            ERROR_ZERO_BYTE_NOT_EXPECTED
        };

        /// \details    The encoding process cannot fail.
        static void Encode(
                const mn::ByteArray &rawData,
                ByteArray &encodedData);

        /// \brief      Decode data using "Consistent Overhead Byte Stuffing" (COBS).
        /// \details    Provided encodedData is expected to be a single, valid COBS encoded packet. If not, method
        ///             will return #DecodeStatus::ERROR_ZERO_BYTE_NOT_EXPECTED.
        ///             #decodedData is emptied of any pre-existing data. If the decode fails, decodedData is left empty.
        static DecodeStatus Decode(const ByteArray &encodedData, ByteArray &decodedData);

    };
}

#endif // #ifndef SERIAL_FILLER_COBS_TRANSCODER_H_