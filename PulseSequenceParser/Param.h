#ifndef PARAM_H
#define PARAM_H

#include "XMLElement.h"
#include <QXmlStreamReader>
#include "Editable.h"

/**
 * @class Param
 * @brief Represents a parameter element in XML.
 *
 * This class represents a parameter element parsed from an XML file.
 * It inherits from XMLElement class.
 */
class Param : public XMLElement
{
private:

    QString type;        /**< Type of the parameter. */
    QString unit;        /**< Unit of the parameter. */
    int value;           /**< Value of the parameter. */

    Editable edit;      /**< Editable object associated with the parameter. */

    /**
     * @brief Updates the unit based on surrounding elements.
     */
    void unitUpdate();

    /**
     * @brief Sets an empty unit based on surrounding elements.
     * @param element The XML element to check for unit.
     * @param isSettingsFound Flag indicating if settings were found.
     */
    void setEmptyUnit(XMLElement* element, bool& isSettingsFound);

public:

    /**
     * @brief Constructs a Param object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Param object by initializing it with the XML stream reader.
     */
    Param(QXmlStreamReader& reader);

    /**
     * @brief Performs a sanity check on the Param.
     *
     * This method performs a sanity check on the Param to ensure it is nested directly inside Settings, Pulse, Loop, Delay,
     * or Action tags.
     *
     * @return True if the Param is nested directly inside one of the specified tags, false otherwise.
     * @throw std::runtime_error if the Param is not nested directly inside one of the specified tags.
     */
    bool sanityCheck();

    /**
     * @brief Parses the attributes of the Param.
     *
     * This method parses the attributes of the Param element, setting its type, unit, and value.
     */
    void parseAttributes();

    /**
     * @brief Sets the value of the parameter.
     *
     * @param newValue The new value of the parameter.
     */
    void setValue(const int &newValue);

    /**
     * @brief Sets the type of the parameter.
     *
     * @param newType The new type of the parameter.
     */
    void setType(const QString &newType);

    /**
     * @brief Sets the unit of the parameter.
     *
     * @param newUnit The new unit of the parameter.
     */
    void setUnit(const QString &newUnit);

    /**
     * @brief Prints the Param to an output stream.
     *
     * @param os The output stream.
     */
    void print(std::ostream& os) const;

    /**
     * @brief Gets the type of the parameter.
     *
     * @return The type of the parameter.
     */
    QString getType() const;

    /**
     * @brief Gets the unit of the parameter.
     *
     * @return The unit of the parameter.
     */
    QString getUnit() const;

    /**
     * @brief Gets the value of the parameter.
     *
     * @return The value of the parameter.
     */
    int getValue() const;

    /**
     * @brief Gets the edit field of the parameter.
     *
     * @return The edit field of the parameter.
     */
    std::string getEditField() const;
};

#endif // PARAM_H
