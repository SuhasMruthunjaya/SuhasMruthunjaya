/*
 * Increment.h
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#ifndef INCREMENT_H_
#define INCREMENT_H_

#include "XMLElement.h"
#include "Editable.h"


/**
 * @class Increment
 * @brief Represents an increment element in XML.
 *
 * This class represents an increment element parsed from an XML file.
 * It inherits from XMLElement class.
 */
class Increment : public XMLElement
{
private:
    int ValueNgain;     /**< Value of the increment. */
    QString LoopID;     /**< Identifier for the loop. */

    Editable edit;      /**< Editable object associated with the increment. */
public:

    /**
     * @brief Constructs an Increment object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs an Increment object by initializing it with the XML stream reader.
     */
    Increment(QXmlStreamReader& reader);

    /**
     * @brief Destructor for the Increment object.
     *
     * Destructor for the Increment object. It performs cleanup tasks.
     */
	virtual ~Increment();

    /**
     * @brief Performs a sanity check on the Increment.
     *
     * This method performs a sanity check on the Increment to ensure it is nested directly inside a Param tag.
     *
     * @return True if the Increment is nested directly inside a Param tag, false otherwise.
     * @throw std::runtime_error if the Increment is not nested directly inside a Param tag.
     */
    bool sanityCheck();

    /**
     * @brief Sets the value of the increment.
     *
     * @param newValueNgain The new value of the increment.
     */
    void setValueNgain(const int &newValueNgain);

    /**
     * @brief Sets the loop identifier for the increment.
     *
     * @param newLoopID The new loop identifier.
     */
    void setLoopID(const QString &newLoopID);

    /**
     * @brief Parses the attributes of the Increment.
     *
     * This method parses the attributes of the Increment element, setting its value and loop identifier.
     */
    void parseAttributes();

    /**
     * @brief Prints the Increment to an output stream.
     *
     * @param os The output stream.
     */
    void print(std::ostream& os) const;


    /**
     * @brief Gets the value of the increment.
     *
     * @return The value of the increment.
     */
    int getValueNgain() const;

    /**
     * @brief Gets the loop identifier of the increment.
     *
     * @return The loop identifier of the increment.
     */
    QString getLoopID() const;
};

#endif /* INCREMENT_H_ */
