/*
 * Channel.cpp
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#include "Channel.h"

/**
     * @brief Constructs a Channel object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Channel object by initializing it with the XML stream reader.
     */
Channel::Channel(QXmlStreamReader& reader) : XMLElement(XMLElement::Channel, reader)
{
	// TODO Auto-generated constructor stub

}

Channel::~Channel()
{
	// TODO Auto-generated destructor stub
}


/**
     * @brief Performs a sanity check on the Channel.
     *
     * This method performs a sanity check on the Channel to ensure it is nested
     * directly inside a Sequence or Loop tag.
     *
     * @return True if the channel is nested directly inside a Sequence or Loop tag, false otherwise.
     * @throw std::runtime_error if the channel is not nested directly inside a Sequence or Loop tag.
     */
bool Channel::sanityCheck()
{
    XMLTag parentTag = getParent() -> getType();
    if(parentTag == XMLTag::Loop ||
        parentTag == XMLTag::Sequence)
    {
        return true;
    }
    else
    {
        throw std::runtime_error("Channel is not nested directly inside of "
                                 "Sequence / Loop Tag");

    }
}

/**
     * @brief Parses the attributes of the Channel.
     *
     * This method parses the attributes of the Channel element, setting its name.
     */
void Channel::parseAttributes()
{
    QString name = reader.attributes().value("Name").toString();

    if(name != "")
        setName(name);
}

/**
     * @brief Gets the name of the channel.
     *
     * @return Name of the channel.
     */
QString Channel::getName() const
{
    return name;
}

/**
     * @brief Sets the name of the channel.
     *
     * @param newName New name of the channel.
     */
void Channel::setName(const QString &newName)
{
    name = newName;
}

/**
     * @brief Prints the Channel to an output stream.
     *
     * @param os The output stream to print to.
     */
void Channel::print(std::ostream &os) const
{
    os << "Channel: ";

    os << "Name:" << getName().toStdString() << std::endl;

    for(auto const& entry : childList)
    {
        os << "-->" << *entry << std::endl;
    }
}
