/*
 * Sequence.cpp
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#include "Sequence.h"
#include <QDebug>
#include <fstream>

/**
     * @brief Constructs a Sequence object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Sequence object by initializing it with the XML stream reader.
     */
Sequence::Sequence(QXmlStreamReader& reader) : XMLElement(XMLTag::Sequence,reader)
{
    this->experimentName = " ";
}

/**
     * @brief Destructor for the Sequence object.
     *
     * Destructor for the Sequence object. It performs cleanup tasks.
     */
Sequence::~Sequence()
{
	// TODO Auto-generated destructor stub
}

/**
     * @brief Gets the experiment name associated with the sequence.
     * @return The experiment name.
     */
const QString Sequence::getexpName() const
{
    return experimentName;

}

/**
     * @brief Sets the experiment name associated with the sequence.
     * @param experimentName The new experiment name to set.
     */
void Sequence::setExperimentName(QString experimentName)
{
    this->experimentName = experimentName;
}

/**
     * @brief Parses the attributes of the Sequence.
     *
     * This method parses the attributes of the Sequence element, setting its experiment name.
     */
void Sequence::parseAttributes()
{
    QString name = reader.attributes().value("name").toString();
    setExperimentName(name);
}

/**
     * @brief Prints the Sequence to an output stream.
     * @param os The output stream.
     */
void Sequence::print(std::ostream &os) const
{
    os << "Sequence:" << std::endl;

    for( auto const& element : childList)
    {
        os << "->" << *element << std::endl;
    }


}
