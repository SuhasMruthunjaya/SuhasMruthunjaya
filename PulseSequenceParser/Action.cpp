#include "Action.h"

/**
     * @brief Constructs an Action object.
     * @param reader Reference to the XML stream reader.
     */
Action::Action(QXmlStreamReader& reader) : XMLElement(XMLElement::Settings,reader)
{
}

/**
     * @brief Destructor for the Action object.
     */
Action::~Action()
{
}

/**
     * @brief Performs a sanity check on the Action.
     * @return True if the action is nested directly inside a Channel tag, false otherwise.
     * @throw std::runtime_error if the action is not nested directly inside a Channel tag.
     */
bool Action::sanityCheck()
{
    XMLTag parentTag = getParent() -> getType();
    if(parentTag != XMLTag::Channel)
        throw std::runtime_error("Action is not nested directly inside of Channel Tag");
    else
        return true;
}

/**
     * @brief Parses the attributes of the Action.
     * Currently does nothing.
     */
void Action::parseAttributes()
{
    // nothing as of now
}

/**
     * @brief Prints the Action to an output stream.
     * @param os The output stream.
     */
void Action::print(std::ostream &os) const
{
    os << "Action:" << std::endl;

    for(auto const& entry: childList)
    {
        os << "--->" << *entry << std::endl;
    }
}
