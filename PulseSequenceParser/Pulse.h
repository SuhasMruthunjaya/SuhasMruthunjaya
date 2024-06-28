/*
 * Pulse.h
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#ifndef PULSE_H_
#define PULSE_H_

#include "XMLElement.h"

/**
 * @class Pulse
 * @brief Represents a pulse element in XML.
 *
 * This class represents a pulse element parsed from an XML file.
 * It inherits from XMLElement class.
 */
class Pulse : public XMLElement
{
private:

public:

    /**
     * @brief Constructs a Pulse object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Pulse object by initializing it with the XML stream reader.
     */
    Pulse(QXmlStreamReader& reader);

    /**
     * @brief Destructor for the Pulse object.
     *
     * Destructor for the Pulse object. It performs cleanup tasks.
     */
    virtual ~Pulse();

    /**
     * @brief Performs a sanity check on the Pulse.
     *
     * This method performs a sanity check on the Pulse to ensure it is nested directly inside a Channel tag.
     *
     * @return True if the Pulse is nested directly inside a Channel tag, false otherwise.
     * @throw std::runtime_error if the Pulse is not nested directly inside a Channel tag.
     */
    bool sanityCheck();

    /**
     * @brief Parses the attributes of the Pulse.
     *
     * This method parses the attributes of the Pulse element.
     * As of now, it does nothing.
     */
    void parseAttributes();

    /**
     * @brief Prints the Pulse to an output stream.
     *
     * @param os The output stream.
     */
    void print(std::ostream& os) const;
};

#endif /* PULSE_H_ */
