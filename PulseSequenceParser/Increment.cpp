/*
 * Increment.cpp
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#include "Increment.h"

/**
 * @class Increment
 * @brief Represents an increment element in XML.
 *
 * This class represents an increment element parsed from an XML file.
 * It inherits from XMLElement class.
 */
Increment::Increment(QXmlStreamReader& reader) : XMLElement(XMLElement::Increments, reader)
{
	// TODO Auto-generated constructor stub

}
Increment::~Increment()
{
	// TODO Auto-generated destructor stub
}

/**
     * @brief Performs a sanity check on the Increment.
     *
     * This method performs a sanity check on the Increment to ensure it is nested directly inside a Param tag.
     *
     * @return True if the Increment is nested directly inside a Param tag, false otherwise.
     * @throw std::runtime_error if the Increment is not nested directly inside a Param tag.
     */
bool Increment::sanityCheck()
{
    XMLTag parentTag = getParent() -> getType();
    if(parentTag != XMLTag::Param)
        throw std::runtime_error("Increment is not nested directly inside of Param Tag");
    else
        return true;
}

/**
     * @brief Sets the value of the increment.
     *
     * @param newValueNgain The new value of the increment.
     */
void Increment::setValueNgain(const int &newValueNgain)
{
    ValueNgain = newValueNgain;
}
/**
     * @brief Sets the loop identifier for the increment.
     *
     * @param newLoopID The new loop identifier.
     */
void Increment::setLoopID(const QString &newLoopID)
{
    LoopID = newLoopID;
}

/**
     * @brief Gets the value of the increment.
     *
     * @return The value of the increment.
     */
int Increment::getValueNgain() const
{
    return ValueNgain;
}

/**
     * @brief Gets the loop identifier of the increment.
     *
     * @return The loop identifier of the increment.
     */
QString Increment::getLoopID() const
{
    return LoopID;
}

/**
     * @brief Parses the attributes of the Increment.
     *
     * This method parses the attributes of the Increment element, setting its value and loop identifier.
     */
void Increment::parseAttributes()
{
    QString valueNgain, LoopID, editField;

    valueNgain = reader.attributes().value("ValueNgain").toString();
    LoopID = reader.attributes().value("LoopId").toString();
    editField = reader.attributes().value("EditField").toString();

    setLoopID(LoopID);

    if(editField != "")
    {
        QStringList tokens =  valueNgain.split(":");

        QString initialKeyword = tokens.at(0);

        if(initialKeyword == "edit")
        {
            edit.setValue( tokens.at(1).toInt() );
            edit.setMinValue( tokens.at(2).toInt());
            edit.setMaxValue( tokens.at(3).toInt());

            edit.setEditField(editField);

            setValueNgain(edit.getValue());

        }

    }
    else
    {
        setValueNgain(valueNgain.toInt());
    }


}

/**
     * @brief Prints the Increment to an output stream.
     *
     * @param os The output stream.
     */
void Increment::print(std::ostream &os) const
{
    os << "Increment:";

    os << " ValueNGain: " << getValueNgain();
    os << " LoopID: " << getLoopID().toStdString();

    std::string editField = edit.getEditField().toStdString();

    if(edit.getValue() != 0)
    {
        os << " EditField: " << editField;
    }

    os << std::endl;
}
