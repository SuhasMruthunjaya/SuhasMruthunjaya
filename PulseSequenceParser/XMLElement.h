/*
 * XMLElement.h
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#ifndef XMLELEMENT_H_
#define XMLELEMENT_H_
#include "global.h"
#include <QXmlStreamReader>
#include <fstream>

#include <list>

class XmlPulseParser;

/**
 * @class XMLElement
 * @brief Represents a generic XML element.
 *
 * This class represents a generic XML element. It serves as the base class for specific XML element types.
 */
class XMLElement
{
public:

    /**
     * @brief Enumeration representing different types of XML elements.
     */
    typedef enum{
        Undefined,
        Sequence,
        Settings,
        Constants,
        Delay,
        Loop,
        Pulse,
        Action,
        Increments,
        Param,
        Channel
    }XMLTag;

protected:
    QXmlStreamReader& reader;               /**< Reference to the XML stream reader. */
    std::list <XMLElement*> childList;      /**< List of child elements. */
    XMLElement* parent;                     /**< Pointer to the parent element. */

private:
    const XMLTag _type{Undefined};      /**< Type of the XML element. */

public:

    //XMLElement();

    /**
     * @brief Constructs an XMLElement object.
     * @param type The type of the XML element.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs an XMLElement object with the specified type and XML stream reader.
     */
    XMLElement(XMLTag type,  QXmlStreamReader& reader) : _type(type), reader(reader) {}

    /**
     * @brief Virtual destructor for the XMLElement class.
     *
     * Virtual destructor for the XMLElement class. It performs cleanup tasks.
     */
    virtual ~XMLElement();

    /**
     * @brief Adds a child element to the current element.
     * @param child Pointer to the child element to be added.
     */
    void addtoParent(XMLElement* child);

    /**
     * @brief Performs a sanity check on the XML element.
     * @return True if the sanity check passes, false otherwise.
     *
     * This method performs a sanity check on the XML element.
     */
    virtual bool sanityCheck() = 0;

    /**
     * @brief Sets the parent element of the current element.
     * @param parent Pointer to the parent element.
     * @return RC_t indicating the success or failure of setting the parent.
     */
    RC_t setParent( XMLElement* parent) ;

    /**
     * @brief Gets the parent element of the current element.
     * @return Pointer to the parent element.
     */
    XMLElement* getParent() const;

    /**
     * @brief Gets the type of the XML element.
     * @return The type of the XML element.
     */
    XMLTag getType() const { return _type; }

    /**
     * @brief Parses the attributes of the XML element.
     *
     * This method parses the attributes of the XML element. It is meant to be overridden by derived classes.
     */
    virtual void parseAttributes(){ };

    // Declare a friend function to allow printing XMLElement objects to an output stream
    friend std::ostream& operator<< (std::ostream& os , const XMLElement& obj);

    /**
     * @brief Prints the XML element to an output stream.
     * @param os The output stream.
     */
    virtual void print(std::ostream& os) const {};

    /**
     * @brief Gets the list of child elements.
     * @return The list of child elements.
     */
    std::list<XMLElement *> getChildList() const;
};

#endif /* XMLELEMENT_H_ */
