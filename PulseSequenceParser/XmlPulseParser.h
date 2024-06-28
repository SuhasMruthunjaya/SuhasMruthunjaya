#ifndef XMLPULSEPARSER_H
#define XMLPULSEPARSER_H

#include "PulseSequenceParser.h"
#include "XMLElement.h"
#include <QXmlStreamReader>
#include <stack>
#include <QDebug>

/**
 * @class XmlPulseParser
 * @brief Parses XML files containing pulse sequences.
 */
class XmlPulseParser : public PulseSequenceParser
{
private:
    std::stack<XMLElement*> _latest;        /**< Stack to keep track of the latest parsed elements. */
    QXmlStreamReader* _reader;              /**< Pointer to the XML stream reader. */
public:

    /**
     * @brief Constructs an XmlPulseParser object with the specified file path.
     * @param filePath The path to the XML file to be parsed.
     */
    XmlPulseParser(QString const& fileName = " ");

    /**
     * @brief Processes the XML tag and determines its type.
     * @param xmlreader The XML stream reader.
     * @return The type of the XML tag.
     */
    XMLElement::XMLTag processXMLTag (const QXmlStreamReader& xmlReader);

    /**
     * @brief Parses the XML document.
     * @return RC_t indicating the success or failure of parsing the document.
     */
    RC_t parseDoc();    // Method to parse the XML document

private:

    /**
     * @brief Peeks at the top parent element in the stack.
     * @return Pointer to the top parent element.
     */
    XMLElement* peekParent() {return _latest.top();}

    /**
     * @brief Pushes a parent element onto the stack.
     * @param element Pointer to the parent element to be pushed.
     */
    void pushParent(XMLElement* element) { _latest.push(element);}

    /**
     * @brief Pops the top parent element from the stack.
     * @return Pointer to the popped parent element.
     */
    XMLElement* popParent();

    /**
     * @brief Parses the XML document header.
     * @return True if the header is parsed successfully, false otherwise.
     */
    bool parseDocHeader();

    /**
     * @brief Gets the next XML field from the document and processes it.
     * @return True if there are more fields to process, false otherwise.
     */
    bool getNextField();

    /**
     * @brief Parses the start element of an XML tag.
     */
    void parseStartElement();

    /**
     * @brief Template method to parse child elements of a specific type.
     * @tparam Type The type of the child element to be parsed.
     */
    template <typename Type>
    inline void  parseChild()
    {
        XMLElement* child = new Type(*_reader);

        child->setParent(peekParent());

        if(child->sanityCheck())
        {
            child->getParent()->addtoParent(child);

            pushParent(child);

            child->parseAttributes();
        }
    }


};

#endif // XMLPULSEPARSER_H
