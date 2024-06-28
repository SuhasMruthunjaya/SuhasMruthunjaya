#include "PulseSequenceParser.h"

/**
     * @brief Constructs a PulseSequenceParser object.
     * @param filePath The file path of the pulse sequence file to parse.
     */
PulseSequenceParser::PulseSequenceParser(QString const& filePath) {

    this->filePath = filePath;
}
