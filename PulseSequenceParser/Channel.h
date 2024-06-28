/*
 * Channel.h
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "XMLElement.h"

/**
 * @brief Represents a channel element in XML.
 *
 * This class represents a channel element parsed from an XML file.
 * It inherits from XMLElement class.
 */
class Channel : public XMLElement
{
private:
    QString name;   /**< Name of the channel. */

public:
    /**
     * @brief Constructs a Channel object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Channel object by initializing it with the XML stream reader.
     */
    Channel(QXmlStreamReader& reader);
	virtual ~Channel();

    /**
     * @brief Performs a sanity check on the Channel.
     *
     * This method performs a sanity check on the Channel to ensure it is nested
     * directly inside a Sequence or Loop tag.
     *
     * @return True if the channel is nested directly inside a Sequence or Loop tag, false otherwise.
     * @throw std::runtime_error if the channel is not nested directly inside a Sequence or Loop tag.
     */
    bool sanityCheck();

    /**
     * @brief Parses the attributes of the Channel.
     *
     * This method parses the attributes of the Channel element, setting its name.
     */
    void parseAttributes();

    /**
     * @brief Sets the name of the channel.
     *
     * @param newName New name of the channel.
     */
    void setName(const QString &newName);

    /**
     * @brief Prints the Channel to an output stream.
     *
     * @param os The output stream to print to.
     */
    void print(std::ostream& os) const;

    /**
     * @brief Gets the name of the channel.
     *
     * @return Name of the channel.
     */
    QString getName() const;
};

#endif /* CHANNEL_H_ */
