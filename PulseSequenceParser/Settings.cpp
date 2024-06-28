/*
 * Settings.cpp
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#include "Settings.h"
#include <QDebug>

/**
     * @brief Constructs a Settings object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Settings object by initializing it with the XML stream reader.
     */
Settings::Settings(QXmlStreamReader& reader) : XMLElement(XMLElement::Settings,reader)
{
	// TODO Auto-generated constructor stub


}

/**
     * @brief Destructor for the Settings object.
     *
     * Destructor for the Settings object. It performs cleanup tasks.
     */
Settings::~Settings()
{
	// TODO Auto-generated destructor stub
}

/**
     * @brief Performs a sanity check on the Settings.
     *
     * This method performs a sanity check on the Settings to ensure it is nested directly inside a Sequence tag.
     *
     * @return True if the Settings is nested directly inside a Sequence tag, false otherwise.
     * @throw std::runtime_error if the Settings is not nested directly inside a Sequence tag.
     */
bool Settings::sanityCheck()
{
    XMLTag parentTag = getParent() -> getType();
    if ( parentTag != XMLTag::Sequence )
        throw std::runtime_error("Settings is not nested directly inside of Sequence Tage.");

    return parentTag == XMLTag::Sequence;
}

/**
     * @brief Parses the attributes of the Settings.
     *
     * This method parses the attributes of the Settings element. Currently, no attributes are parsed.
     */
void Settings::parseAttributes()
{
    // No attributes as of now
}

/**
     * @brief Prints the Settings to an output stream.
     * @param os The output stream.
     */
void Settings::print(std::ostream &os) const
{
    os << "Settings:" << std::endl;

    for(auto const& entry : childList)
    {
        os << "-->" << *entry << std::endl;
    }
}
