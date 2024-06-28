/*
 * Sequence.h
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "XMLElement.h"
#include <QString>

/**
 * @class Sequence
 * @brief Represents a sequence element in an XML file.
 *
 * This class represents a sequence element parsed from an XML file.
 * It inherits from the XMLElement class.
 */
class Sequence : public XMLElement
{
private:
    QString experimentName;             /**< Experiment name associated with the sequence. */

public:
    /**
     * @brief Constructs a Sequence object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Sequence object by initializing it with the XML stream reader.
     */
    Sequence(QXmlStreamReader& reader);

    /**
     * @brief Destructor for the Sequence object.
     *
     * Destructor for the Sequence object. It performs cleanup tasks.
     */
    virtual ~Sequence();

    /**
     * @brief Performs a sanity check on the Sequence.
     *
     * This method performs a sanity check on the Sequence.
     * Since Sequences are always considered valid, it always returns true.
     *
     * @return Always returns true.
     */
    bool sanityCheck(){return true;}

    /**
     * @brief Gets the experiment name associated with the sequence.
     * @return The experiment name.
     */
    const QString getexpName() const;

    /**
     * @brief Sets the experiment name associated with the sequence.
     * @param experimentName The new experiment name to set.
     */
    void setExperimentName(QString experimentName);

    /**
     * @brief Parses the attributes of the Sequence.
     *
     * This method parses the attributes of the Sequence element, setting its experiment name.
     */
    void parseAttributes();

    /**
     * @brief Prints the Sequence to an output stream.
     * @param os The output stream.
     */
    void print(std::ostream& os) const;


};

#endif /* SEQUENCE_H_ */
