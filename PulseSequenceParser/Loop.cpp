/*
 * Loop.cpp
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#include "Loop.h"

/**
     * @brief Constructs a Loop object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Loop object by initializing it with the XML stream reader.
     */
Loop::Loop(QXmlStreamReader& reader): XMLElement(XMLElement::Loop, reader)
{
    // TODO Auto-generated constructor stub

}

/**
     * @brief Destructor for the Loop object.
     *
     * Destructor for the Loop object. It performs cleanup tasks.
     */
Loop::~Loop()
{
    // TODO Auto-generated destructor stub
}

/**
     * @brief Performs a sanity check on the Loop.
     *
     * This method performs a sanity check on the Loop to ensure it is nested directly inside another Loop or Sequence tag.
     *
     * @return True if the Loop is nested directly inside another Loop or Sequence tag, false otherwise.
     * @throw std::runtime_error if the Loop is not nested directly inside another Loop or Sequence tag.
     */
bool Loop::sanityCheck()
{
    XMLTag parentTag = getParent() -> getType();
    if((parentTag == XMLTag::Sequence) ||
        (parentTag == XMLTag::Loop))
        return true;

    else
        throw std::runtime_error(" Loop is not nested directly inside of another Loop / Sequence Tag");
}

/**
     * @brief Parses the attributes of the Loop.
     *
     * This method parses the attributes of the Loop element, setting its ID, duration, and unit.
     */
void Loop::parseAttributes()
{
    QString ID, unit;
    int duration;

    ID = reader.attributes().value("ID").toString();
    duration = reader.attributes().value("Duration").toInt();
    unit = reader.attributes().value("Unit").toString();

        setID(ID);
        setDuration(duration);
        setUnit(unit);
}

/**
     * @brief Sets the identifier of the loop.
     *
     * @param newID The new identifier of the loop.
     */
void Loop::setID(const QString &newID)
{
    ID = newID;
}

/**
     * @brief Sets the duration of the loop.
     *
     * @param newDuration The new duration of the loop.
     */
void Loop::setDuration(const int &newDuration)
{
    Duration = newDuration;
}

/**
     * @brief Sets the unit of the loop duration.
     *
     * @param newUnit The new unit of the loop duration.
     */
void Loop::setUnit(const QString &newUnit)
{
    unit = newUnit;
}

/**
     * @brief Gets the identifier of the loop.
     *
     * @return The identifier of the loop.
     */
QString Loop::getID() const
{
    return ID;
}

/**
     * @brief Gets the duration of the loop.
     *
     * @return The duration of the loop.
     */
int Loop::getDuration() const
{
    return Duration;
}

/**
     * @brief Gets the unit of the loop duration.
     *
     * @return The unit of the loop duration.
     */
QString Loop::getUnit() const
{
    return unit;
}

/**
     * @brief Prints the Loop to an output stream.
     *
     * @param os The output stream.
     */
void Loop::print(std::ostream &os) const
{
    os <<"Loop: ";
    os << "ID: "  << getID().toStdString();
    os << " Duration: " << getDuration();

    if(getUnit().toStdString() != "")
    {
        os << " Unit: " << getUnit().toStdString() << std::endl;
    }
    else
    {
        os << std::endl;
    }

    if(this->getParent()->getType() == XMLTag::Loop)
    {
        for(auto const& entry : childList)
        {
            os << "--->" << *entry << std::endl;
        }
    }
    else
    {
        for(auto const& entry : childList)
        {
            os << "-->" << *entry << std::endl;
        }
    }

}
