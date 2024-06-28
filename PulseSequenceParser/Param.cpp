#include "Param.h"
#include <stdexcept>
#include <QDebug>
#include <iostream>
#include "XmlPulseParser.h"
#include "Settings.h"

/**
 * @class Param
 * @brief Represents a parameter element in XML.
 *
 * This class represents a parameter element parsed from an XML file.
 * It inherits from XMLElement class.
 */
Param::Param(QXmlStreamReader& reader) : XMLElement(XMLElement::Param, reader)
{

}

/**
     * @brief Performs a sanity check on the Param.
     *
     * This method performs a sanity check on the Param to ensure it is nested directly inside Settings, Pulse, Loop, Delay,
     * or Action tags.
     *
     * @return True if the Param is nested directly inside one of the specified tags, false otherwise.
     * @throw std::runtime_error if the Param is not nested directly inside one of the specified tags.
     */
bool Param::sanityCheck()
{
    XMLTag parentTag = getParent() -> getType();
    if(parentTag == XMLTag::Settings)
        return true;
    else if(parentTag == XMLTag::Pulse)
        return true;
    else if(parentTag == XMLTag::Delay)
        return true;
    else if(parentTag == XMLTag::Action)
        return true;
    else if(parentTag == XMLTag::Loop)
        return true;
    else
        throw std::runtime_error("Param is not nested directly inside of Settengs Tag/ Pulse Tag/"
                                 "Loop Tag/ Delay Tag/ Action Tag");

}

/**
     * @brief Parses the attributes of the Param.
     *
     * This method parses the attributes of the Param element, setting its type, unit, and value.
     */
void Param::parseAttributes()
{
    QString value, type, unit, editField;
    value = reader.attributes().value("Value").toString();
    type =  reader.attributes().value("Type").toString();
    unit =  reader.attributes().value("Unit").toString();
    editField = reader.attributes().value("EditField").toString();

    setType(type);

    if(unit == "" && ((type == "Duration") || (type == "Frequency") || (type == "Power")))
    {
        unitUpdate();
    }
    else
    {
        setUnit(unit);
    }

    if(editField != "")
    {
        QStringList tokens =  value.split(":");

        QString initialKeyword = tokens.at(0);

        if(initialKeyword == "edit")
        {
            edit.setValue( tokens.at(1).toInt() );
            edit.setMinValue( tokens.at(2).toInt());
            edit.setMaxValue( tokens.at(3).toInt());

            edit.setEditField(editField);

            setValue(edit.getValue());

        }
    }
    else
    {
        setValue(value.toInt());
    }

}

/**
     * @brief Updates the unit based on surrounding elements.
     */
void Param::unitUpdate()
{
    bool isSettingsFound = false;

    XMLElement* parent = getParent();

    while(!isSettingsFound && parent != nullptr)
    {
        std::list<XMLElement*> childList = parent->getChildList();

        for(auto& element: childList)
        {
            setEmptyUnit(element, isSettingsFound);
        }

        parent = parent->getParent();
    }


}

/**
     * @brief Sets an empty unit based on surrounding elements.
     * @param element The XML element to check for unit.
     * @param isSettingsFound Flag indicating if settings were found.
     */
void Param::setEmptyUnit(XMLElement* element, bool& isSettingsFound)
{

    class Settings* pSequence = dynamic_cast<class Settings*>(element);

    if(pSequence != nullptr)
    {
        auto const& settingsChildList = pSequence->getChildList();

        for(auto const& entry : settingsChildList)
        {
            Param* pParam  = dynamic_cast<Param*>(entry);

            if(pParam != nullptr)
            {
                if(type == pParam->getType())
                {
                    setUnit(pParam->getUnit());
                }
            }

        }

        isSettingsFound = true;
    }

}

/**
     * @brief Sets the value of the parameter.
     *
     * @param newValue The new value of the parameter.
     */
void Param::setValue(const int &newValue)
{
    value = newValue;
}

/**
     * @brief Sets the type of the parameter.
     *
     * @param newType The new type of the parameter.
     */
void Param::setType(const QString &newType)
{
    type = newType;
}

/**
     * @brief Sets the unit of the parameter.
     *
     * @param newUnit The new unit of the parameter.
     */
void Param::setUnit(const QString &newUnit)
{
    unit = newUnit;
}

/**
     * @brief Gets the type of the parameter.
     *
     * @return The type of the parameter.
     */
QString Param::getType() const
{
    return type;
}

/**
     * @brief Gets the unit of the parameter.
     *
     * @return The unit of the parameter.
     */
QString Param::getUnit() const
{
    return unit;
}

/**
     * @brief Gets the value of the parameter.
     *
     * @return The value of the parameter.
     */
int Param::getValue() const
{
    return value;
}

/**
     * @brief Gets the edit field of the parameter.
     *
     * @return The edit field of the parameter.
     */
std::string Param::getEditField() const
{
    return edit.getEditField().toStdString();
}

/**
     * @brief Prints the Param to an output stream.
     *
     * @param os The output stream.
     */
void Param::print(std::ostream &os) const
{
    os << "Param: ";
    os << " Type: " << getType().toStdString();

    if((type == "Duration") || (type == "Frequency") || (type == "Power"))
        os << " Unit: " << getUnit().toStdString();

    os << " Value: " << getValue();

    std::string editField = getEditField();

    if(edit.getValue() != 0)
    {
        os << " EditField: " << editField;
    }

    os << std::endl;

    for(auto const& entry : childList)
    {
        os << "---->" << *entry << std::endl;
    }
}
