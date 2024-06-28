#ifndef EDITABLE_H
#define EDITABLE_H

#include <QString>

/**
 * @class Editable
 * @brief Represents an editable object.
 *
 * This class represents an editable object with a value, maximum and minimum value constraints,
 * and an editable field.
 */
class Editable
{
private:
    int value = 0;          /**< Current value of the editable object. */
    int maxValue;           /**< Maximum allowed value. */
    int minValue;           /**< Minimum allowed value. */
    QString EditField;      /**< Editable field for additional information. */


public:
    /**
     * @brief Constructs an Editable object.
     */
    Editable();

    /**
     * @brief Gets the current value of the editable object.
     *
     * @return The current value.
     */
    int getValue() const;

    /**
     * @brief Sets the value of the editable object.
     *
     * @param newValue The new value to set.
     */
    void setValue(int newValue);

    /**
     * @brief Gets the maximum allowed value.
     *
     * @return The maximum allowed value.
     */
    int getMaxValue() const;

    /**
     * @brief Sets the maximum allowed value.
     *
     * @param newMaxValue The new maximum value to set.
     */
    void setMaxValue(int newMaxValue);

    /**
     * @brief Gets the minimum allowed value.
     *
     * @return The minimum allowed value.
     */
    int getMinValue() const;

    /**
     * @brief Sets the minimum allowed value.
     *
     * @param newMinValue The new minimum value to set.
     */
    void setMinValue(int newMinValue);

    /**
     * @brief Gets the editable field.
     *
     * @return The editable field.
     */
    QString getEditField() const;

    /**
     * @brief Sets the editable field.
     *
     * @param newEditField The new editable field to set.
     */
    void setEditField(const QString &newEditField);
};

#endif // EDITABLE_H
