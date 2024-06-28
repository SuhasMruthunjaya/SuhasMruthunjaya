#include "Editable.h"

/**
     * @brief Constructs an Editable object.
     */
Editable::Editable() {}

/**
     * @brief Gets the current value of the editable object.
     *
     * @return The current value.
     */
int Editable::getValue() const
{
    return value;
}

/**
     * @brief Sets the value of the editable object.
     *
     * @param newValue The new value to set.
     */
void Editable::setValue(int newValue)
{
    value = newValue;
}

/**
     * @brief Gets the maximum allowed value.
     *
     * @return The maximum allowed value.
     */
int Editable::getMaxValue() const
{
    return maxValue;
}

/**
     * @brief Sets the maximum allowed value.
     *
     * @param newMaxValue The new maximum value to set.
     */
void Editable::setMaxValue(int newMaxValue)
{
    maxValue = newMaxValue;
}

/**
     * @brief Gets the minimum allowed value.
     *
     * @return The minimum allowed value.
     */
int Editable::getMinValue() const
{
    return minValue;
}

/**
     * @brief Sets the minimum allowed value.
     *
     * @param newMinValue The new minimum value to set.
     */
void Editable::setMinValue(int newMinValue)
{
    minValue = newMinValue;
}

/**
     * @brief Gets the editable field.
     *
     * @return The editable field.
     */
QString Editable::getEditField() const
{
    return EditField;
}

/**
     * @brief Sets the editable field.
     *
     * @param newEditField The new editable field to set.
     */
void Editable::setEditField(const QString &newEditField)
{
    EditField = newEditField;
}

