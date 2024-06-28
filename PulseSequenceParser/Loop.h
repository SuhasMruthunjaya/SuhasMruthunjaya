/*
 * Loop.h
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#ifndef LOOP_H_
#define LOOP_H_

#include "XMLElement.h"

/**
 * @class Loop
 * @brief Represents a loop element in XML.
 *
 * This class represents a loop element parsed from an XML file.
 * It inherits from XMLElement class.
 */
class Loop : public XMLElement
{
private:
    QString ID;         /**< Identifier of the loop. */
    int Duration;       /**< Duration of the loop. */
    QString unit;       /**< Unit of the loop duration. */

public:
    /**
     * @brief Constructs a Loop object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Loop object by initializing it with the XML stream reader.
     */
    Loop(QXmlStreamReader& reader);

    /**
     * @brief Destructor for the Loop object.
     *
     * Destructor for the Loop object. It performs cleanup tasks.
     */
    virtual ~Loop();

    /**
     * @brief Performs a sanity check on the Loop.
     *
     * This method performs a sanity check on the Loop to ensure it is nested directly inside another Loop or Sequence tag.
     *
     * @return True if the Loop is nested directly inside another Loop or Sequence tag, false otherwise.
     * @throw std::runtime_error if the Loop is not nested directly inside another Loop or Sequence tag.
     */
    bool sanityCheck();

    /**
     * @brief Parses the attributes of the Loop.
     *
     * This method parses the attributes of the Loop element, setting its ID, duration, and unit.
     */
    void parseAttributes();

    /**
     * @brief Sets the identifier of the loop.
     *
     * @param newID The new identifier of the loop.
     */
    void setID(const QString &newID);

    /**
     * @brief Sets the duration of the loop.
     *
     * @param newDuration The new duration of the loop.
     */
    void setDuration(const int &newDuration);

    /**
     * @brief Sets the unit of the loop duration.
     *
     * @param newUnit The new unit of the loop duration.
     */
    void setUnit(const QString &newUnit);

    /**
     * @brief Prints the Loop to an output stream.
     *
     * @param os The output stream.
     */
    void print(std::ostream& os) const;

    /**
     * @brief Gets the identifier of the loop.
     *
     * @return The identifier of the loop.
     */
    QString getID() const;

    /**
     * @brief Gets the duration of the loop.
     *
     * @return The duration of the loop.
     */
    int getDuration() const;

    /**
     * @brief Gets the unit of the loop duration.
     *
     * @return The unit of the loop duration.
     */
    QString getUnit() const;
};

#endif /* LOOP_H_ */
