/*
 * Constants.h
 *
 *  Created on: 8 Jan 2024
 *      Author: suhas
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "XMLElement.h"
#include <stack>

/**
 * @brief Represents a constants element in XML.
 *
 * This class represents a constants element parsed from an XML file.
 * It inherits from XMLElement class.
 */
class Constants : public XMLElement
{
private:
    QString Type;       /**< Type of the constant. */
    QString ConstId;    /**< Identifier of the constant. */
    int value;     /**< Value of the constant. */
    std::vector<float> lutValues;   /**< Vector to store LUT values. */


    /**
     * @brief Gets the referenced value of a constant.
     *
     * This method retrieves the value of a constant referenced by the provided variable name.
     * It searches for the constant within the parent element and returns its value.
     *
     * @param variable The name of the constant to retrieve the value for.
     * @return The value of the referenced constant.
     */
    int getReferenceValue(std::string& variable);

public:
    /**
     * @brief Constructs a Constants object.
     * @param reader Reference to the XML stream reader.
     *
     * Constructs a Constants object by initializing it with the XML stream reader.
     */
    Constants(QXmlStreamReader& reader);

    /**
     * @brief Destructor for the Constants object.
     *
     * Destructor for the Constants object. It performs cleanup tasks.
     */
    virtual ~Constants();

    /**
     * @brief Performs a sanity check on the Constants.
     *
     * This method performs a sanity check on the Constants to ensure it is nested directly inside a Settings tag.
     *
     * @return True if the Constants is nested directly inside a Settings tag, false otherwise.
     * @throw std::runtime_error if the Constants is not nested directly inside a Settings tag.
     */
    bool sanityCheck();

    /**
     * @brief Parses the attributes of the Constants.
     *
     * This method parses the attributes of the Constants element, setting its type, identifier, and value.
     */
    void parseAttributes();

    /**
     * @brief Gets the type of the constant.
     *
     * @return Type of the constant.
     */
    QString getType() const;

    /**
     * @brief Sets the type of the constant.
     *
     * @param newType New type of the constant.
     */
    void setType(const QString &newType);

    /**
     * @brief Gets the identifier of the constant.
     *
     * @return Identifier of the constant.
     */
    QString getConstId() const;

    /**
     * @brief Sets the identifier of the constant.
     *
     * @param newConstId New identifier of the constant.
     */
    void setConstId(const QString &newConstId);

    /**
     * @brief Gets the value of the constant.
     *
     * @return Value of the constant.
     */
    int getValue() const;

    /**
     * @brief Sets the value of the constant.
     *
     * @param newValue New value of the constant.
     */
    void setValue(int newValue);

    /**
     * @brief Gets the LUT values.
     *
     * @return Vector containing LUT values.
     */
    std::vector<float> getLutValues() const;

    /**
     * @brief Prints the Constants to an output stream.
     *
     * @param os The output stream.
     */
    void print(std::ostream& os) const;

    /**
     * @brief Evaluates and sets the value of the constant from an expression.
     *
     * This method evaluates the given expression containing arithmetic operations and sets the value of the constant.
     *
     * @param valueStr Expression representing the value of the constant.
     */
    void evaluateOpSetValue(std::string expression);

    /**
     * @brief Performs a binary operation on operands.
     *
     * This template function performs a binary operation on operands using the provided operation functor.
     *
     * @tparam T Type of operands.
     * @tparam BinaryOperation Type of the binary operation functor.
     * @param operands Stack containing operands.
     * @param op Binary operation functor.
     */
    template<typename T, typename BinaryOperation>
    void performBinaryOperation(std::stack<T>& operands, BinaryOperation op) {
        T operandOne = operands.top();
        operands.pop();

        T operandTwo = operands.top();
        operands.pop();

        T result = op(operandTwo, operandOne);

        operands.push(result);
    }


};

#endif /* CONSTANTS_H_ */
