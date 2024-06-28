/*
 * Delay.cpp
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#include "Delay.h"

/**
     * @brief Constructs a Delay object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Delay object by initializing it with the XML stream reader.
     */
Delay::Delay(QXmlStreamReader& reader) : XMLElement(XMLElement::Delay, reader)
{
	// TODO Auto-generated constructor stub

}

Delay::~Delay()
{
	// TODO Auto-generated destructor stub
}

/**
     * @brief Performs a sanity check on the Delay.
     *
     * This method performs a sanity check on the Delay to ensure it is nested directly inside a Channel tag.
     *
     * @return True if the Delay is nested directly inside a Channel tag, false otherwise.
     * @throw std::runtime_error if the Delay is not nested directly inside a Channel tag.
     */
bool Delay::sanityCheck()
{
    if(getParent()->getType() != XMLTag::Channel)
        throw std::runtime_error("Delay is not nested directly inside of Channel Tag");
    else
        return true;
}

/**
     * @brief Prints the Delay and its child elements to an output stream.
     *
     * @param os The output stream.
     */
void Delay::print(std::ostream &os) const
{
    os << "Delay: " << std::endl;

    for(auto const& entry : childList)
    {
        os << "--->" << *entry << std::endl;
    }
}
