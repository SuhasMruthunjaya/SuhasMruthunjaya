/*
 * XMLElement.cpp
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#include "XMLElement.h"


XMLElement::~XMLElement()
{
	// TODO Auto-generated destructor stub
}

RC_t XMLElement::setParent( XMLElement* parent)
{
    this->parent = parent;
    return RC_SUCCESS;
}

/**
     * @brief Gets the parent element of the current element.
     * @return Pointer to the parent element.
     */
XMLElement* XMLElement::getParent() const
{
    return parent;
}

// Declare a friend function to allow printing XMLElement objects to an output stream
std::ostream& operator<<(std::ostream &os, const XMLElement &obj)
{
    obj.print(os);

    return os;
}

/**
     * @brief Adds a child element to the current element.
     * @param child Pointer to the child element to be added.
     */
void XMLElement::addtoParent(XMLElement* child)
{
    childList.push_back(child);
}

/**
     * @brief Gets the list of child elements.
     * @return The list of child elements.
     */
std::list<XMLElement *> XMLElement::getChildList() const
{
    return childList;
}
