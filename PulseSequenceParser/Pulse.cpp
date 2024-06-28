/*
 * Pulse.cpp
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#include "Pulse.h"

/**
     * @brief Constructs a Pulse object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Pulse object by initializing it with the XML stream reader.
     */
Pulse::Pulse(QXmlStreamReader& reader) : XMLElement(XMLElement::Pulse, reader)
{
	// TODO Auto-generated constructor stub

}

/**
     * @brief Destructor for the Pulse object.
     *
     * Destructor for the Pulse object. It performs cleanup tasks.
     */
Pulse::~Pulse()
{
	// TODO Auto-generated destructor stub
}

/**
     * @brief Performs a sanity check on the Pulse.
     *
     * This method performs a sanity check on the Pulse to ensure it is nested directly inside a Channel tag.
     *
     * @return True if the Pulse is nested directly inside a Channel tag, false otherwise.
     * @throw std::runtime_error if the Pulse is not nested directly inside a Channel tag.
     */
bool Pulse::sanityCheck()
{
    XMLTag parentTag = getParent() -> getType();
    if(parentTag != XMLTag::Channel)
        throw std::runtime_error("Pulse is not nested directly inside of Channel Tag");
    else
        return true;
}

/**
     * @brief Parses the attributes of the Pulse.
     *
     * This method parses the attributes of the Pulse element.
     * As of now, it does nothing.
     */
void Pulse::parseAttributes()
{
    // nothing as of now
}

/**
     * @brief Prints the Pulse to an output stream.
     *
     * @param os The output stream.
     */
void Pulse::print(std::ostream &os) const
{
    os << "Pulse: " << std::endl;

    for(auto const& entry : childList)
    {
        os << "--->" << *entry << std::endl;
    }
}
