/*
 * Constants.cpp
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#include "Constants.h"
#include <sstream>
#include <iostream>
#include <stack>


/**
     * @brief Constructs a Constants object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Constants object by initializing it with the XML stream reader.
     */
Constants::Constants(QXmlStreamReader& reader) : XMLElement(XMLElement::Constants, reader)
{
    // TODO Auto-generated constructor stub

}

Constants::~Constants()
{
    // TODO Auto-generated destructor stub
}


/**
     * @brief Performs a sanity check on the Constants.
     *
     * This method performs a sanity check on the Constants to ensure it is nested directly inside a Settings tag.
     *
     * @return True if the Constants is nested directly inside a Settings tag, false otherwise.
     * @throw std::runtime_error if the Constants is not nested directly inside a Settings tag.
     */
bool Constants::sanityCheck()
{
    if(getParent()->getType() != XMLTag::Settings)
        throw std::runtime_error("Constants is not nested directly inside of Settings Tag");
    else
        return true;
}

/**
     * @brief Parses the attributes of the Constants.
     *
     * This method parses the attributes of the Constants element, setting its type, identifier, and value.
     */
void Constants::parseAttributes()
{
    QString type = reader.attributes().value("Type").toString();

    QString constID = reader.attributes().value("ConstId").toString();

    QString value = reader.attributes().value("Value").toString();

    setType(type);

    setConstId(constID);

    std::string typeStr = type.toStdString();

    for(char& ch : typeStr)
    {
        ch = std::tolower(ch);
    }

    std::string valueStr = value.toStdString();

    if(typeStr == "lut")
    {

        std::istringstream stream(valueStr);
        std::string lut_val;

        while(std::getline(stream, lut_val, ','))
        {
            float lut_val_float = std::stof(lut_val);

            lutValues.push_back(lut_val_float);
        }
    }

    auto it = valueStr.find('$');

    if(it != valueStr.npos)
    {
        evaluateOpSetValue(valueStr);
    }
    else
    {
        setValue(std::stoi(value.toStdString()));
    }
}


/**
     * @brief Gets the referenced value of a constant.
     *
     * This method retrieves the value of a constant referenced by the provided variable name.
     * It searches for the constant within the parent element and returns its value.
     *
     * @param variable The name of the constant to retrieve the value for.
     * @return The value of the referenced constant.
     */
int Constants::getReferenceValue(std::string& variable)
{
    int result = 0;

    XMLElement* parent = this->getParent();

    for(auto& element : parent->getChildList())
    {
        Constants* constPtr = dynamic_cast<Constants*>(element);

        if(constPtr != nullptr)
        {
            if(constPtr->getConstId().toStdString() == variable)
            {
                result = constPtr->getValue();
            }
        }
    }

    return result;
}


/**
     * @brief Gets the type of the constant.
     *
     * @return Type of the constant.
     */
QString Constants::getType() const
{
    return Type;
}

/**
     * @brief Sets the type of the constant.
     *
     * @param newType New type of the constant.
     */
void Constants::setType(const QString &newType)
{
    Type = newType;
}

/**
     * @brief Gets the identifier of the constant.
     *
     * @return Identifier of the constant.
     */
QString Constants::getConstId() const
{
    return ConstId;
}

/**
     * @brief Sets the identifier of the constant.
     *
     * @param newConstId New identifier of the constant.
     */
void Constants::setConstId(const QString &newConstId)
{
    ConstId = newConstId;
}

/**
     * @brief Gets the value of the constant.
     *
     * @return Value of the constant.
     */

int Constants::getValue() const
{
    return value;
}

/**
     * @brief Sets the value of the constant.
     *
     * @param newValue New value of the constant.
     */
void Constants::setValue(int newValue)
{
    value = newValue;
}

/**
     * @brief Gets the LUT values.
     *
     * @return Vector containing LUT values.
     */
std::vector<float> Constants::getLutValues() const
{
    return lutValues;
}

/**
     * @brief Prints the Constants to an output stream.
     *
     * @param os The output stream.
     */
void Constants::print(std::ostream &os) const
{
    os << "Constants: ";

    os << " Type: " << this->getType().toStdString();

    os << " ConstId: " << this->getConstId().toStdString();


    auto vect = this->getLutValues();

    if(this->getType().toStdString() == "LUT")
    {
        os << " Value: ";
        for(auto it = vect.begin(); it != vect.end(); ++it)
        {
            os << *it;

            if(std::next(it) != vect.end())
            {
                os << ",";
            }
        }
    }
    else
    {
        os << " Value: " << this->getValue() << std::endl;
    }

}

/**
     * @brief Evaluates and sets the value of the constant from an expression.
     *
     * This method evaluates the given expression containing arithmetic operations and sets the value of the constant.
     *
     * @param valueStr Expression representing the value of the constant.
     */
void Constants::evaluateOpSetValue(std::string valueStr)
{
    std::stack<char> operators;
    std::stack<int> operands;

    if(*valueStr.begin() == '$')
    {
        valueStr.erase(valueStr.begin());
    }

    if(*std::prev(valueStr.end()) == '$')
    {
        valueStr.erase(std::prev(valueStr.end()));
    }

    for (size_t i = 0; i < valueStr.size(); ++i)

    {
        char c = valueStr[i];

        if (c == '(')
        {
            // Ignore opening bracket
            continue;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            // Push operator onto operator stack
            operators.push(c);
        }
        else if (isalpha(c))
        {
            // Assuming predefined strings are alphanumeric
            std::string variable;

            while (isalpha(valueStr[i]))
            {
                variable += valueStr[i++];
            }

            int referencedValue = getReferenceValue(variable);

            operands.push(referencedValue);

            --i;
        }

        if (operands.size() == 2)
        {
            char ch = operators.top();
            operators.pop();

            if (ch == '+') {
                performBinaryOperation(operands, std::plus<int>());
            } else if (ch == '-') {
                performBinaryOperation(operands, std::minus<int>());
            } else if (ch == '*') {
                performBinaryOperation(operands, std::multiplies<int>());
            } else if (ch == '/') {
                performBinaryOperation(operands, std::divides<int>());
            }
        }
    }

    setValue(operands.top());
}
