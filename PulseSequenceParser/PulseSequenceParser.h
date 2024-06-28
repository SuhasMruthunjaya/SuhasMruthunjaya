#ifndef PULSESEQUENCEPARSER_H
#define PULSESEQUENCEPARSER_H

#include "global.h"
#include <QString.h>

/**
 * @class PulseSequenceParser
 * @brief Base class for parsing pulse sequence files.
 *
 * This class provides a base interface for parsing pulse sequence files.
 * Subclasses should implement the parseDoc() method to define specific parsing behavior.
 */
class PulseSequenceParser
{
protected:
    QString filePath;    /**< File path of the pulse sequence file. */
public:
    /**
     * @brief Constructs a PulseSequenceParser object.
     * @param filePath The file path of the pulse sequence file to parse.
     */
    PulseSequenceParser(QString const& filePath = " ");

    /**
     * @brief Parses the pulse sequence document.
     *
     * This method should be implemented by subclasses to define specific parsing behavior.
     *
     * @return RC_t Return code indicating the success or failure of the parsing operation.
     */
    virtual RC_t parseDoc() = 0;



};

#endif // PULSESEQUENCEPARSER_H
