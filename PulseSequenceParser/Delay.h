/*
 * Delay.h
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "XMLElement.h"

/**
 * @class Delay
 * @brief Represents a delay element in XML.
 *
 * This class represents a delay element parsed from an XML file.
 * It inherits from XMLElement class.
 */
class Delay : public XMLElement
{
private:
public:
    /**
     * @brief Constructs a Delay object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Delay object by initializing it with the XML stream reader.
     */
    Delay(QXmlStreamReader& reader);

    /**
     * @brief Destructor for the Delay object.
     *
     * Destructor for the Delay object. It performs cleanup tasks.
     */
    virtual ~Delay();

    /**
     * @brief Performs a sanity check on the Delay.
     *
     * This method performs a sanity check on the Delay to ensure it is nested directly inside a Channel tag.
     *
     * @return True if the Delay is nested directly inside a Channel tag, false otherwise.
     * @throw std::runtime_error if the Delay is not nested directly inside a Channel tag.
     */
    bool sanityCheck();

    /**
     * @brief Prints the Delay and its child elements to an output stream.
     *
     * @param os The output stream.
     */
    void print(std::ostream& os) const;
};

#endif /* DELAY_H_ */
