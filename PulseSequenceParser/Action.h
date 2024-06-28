#ifndef ACTION_H
#define ACTION_H

#include "XMLElement.h"

/**
 * @brief Represents an action element in XML.
 */
class Action : public XMLElement
{
private:

public:
    /**
     * @brief Constructs an Action object.
     * @param reader Reference to the XML stream reader.
     */
    Action(QXmlStreamReader& reader);

    /**
     * @brief Destructor for the Action object.
     */
    virtual ~Action();

    /**
     * @brief Performs a sanity check on the Action.
     * @return True if the action is nested directly inside a Channel tag, false otherwise.
     * @throw std::runtime_error if the action is not nested directly inside a Channel tag.
     */
    bool sanityCheck();

    /**
     * @brief Parses the attributes of the Action.
     * Currently does nothing.
     */
    void parseAttributes();

    /**
     * @brief Prints the Action to an output stream.
     * @param os The output stream.
     */
    void print(std::ostream& os) const;

};

#endif // ACTION_H
