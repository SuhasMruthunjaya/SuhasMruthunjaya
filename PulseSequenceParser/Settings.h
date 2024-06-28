/*
 * Settings.h
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "XMLElement.h"

/**
 * @class Settings
 * @brief Represents a settings element in an XML file.
 *
 * This class represents a settings element parsed from an XML file.
 * It inherits from the XMLElement class.
 */
class Settings : public XMLElement
{
private:


public:
    /**
     * @brief Constructs a Settings object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Settings object by initializing it with the XML stream reader.
     */
    Settings(QXmlStreamReader& reader);

    /**
     * @brief Destructor for the Settings object.
     *
     * Destructor for the Settings object. It performs cleanup tasks.
     */
    virtual ~Settings();

    /**
     * @brief Performs a sanity check on the Settings.
     *
     * This method performs a sanity check on the Settings to ensure it is nested directly inside a Sequence tag.
     *
     * @return True if the Settings is nested directly inside a Sequence tag, false otherwise.
     * @throw std::runtime_error if the Settings is not nested directly inside a Sequence tag.
     */
    bool sanityCheck();

    /**
     * @brief Parses the attributes of the Settings.
     *
     * This method parses the attributes of the Settings element. Currently, no attributes are parsed.
     */
    void parseAttributes();

    /**
     * @brief Prints the Settings to an output stream.
     * @param os The output stream.
     */
    void print(std::ostream& os) const;
};

#endif /* SETTINGS_H_ */
