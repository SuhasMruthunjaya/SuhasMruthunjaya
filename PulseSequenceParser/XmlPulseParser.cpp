#include "XmlPulseParser.h"
#include <iostream>
#include <QDebug>
#include <QFile>

#include "Settings.h"
#include "Param.h"
#include "Channel.h"
#include "Constants.h"
#include "Delay.h"
#include "Loop.h"
#include "Pulse.h"
#include "Increment.h"
#include "Sequence.h"
#include "Action.h"


template<>
inline void XmlPulseParser::parseChild<Sequence>()
{
    XMLElement* child = new Sequence(*_reader);

    if(child->sanityCheck())
    {
        pushParent(child);

        child->parseAttributes();
    }

}

/**
     * @brief Constructs an XmlPulseParser object with the specified file path.
     * @param filePath The path to the XML file to be parsed.
     */
XmlPulseParser::XmlPulseParser(QString const& filePath) : PulseSequenceParser(filePath)
{
    this->_reader = nullptr;

}

/**
     * @brief Processes the XML tag and determines its type.
     * @param xmlreader The XML stream reader.
     * @return The type of the XML tag.
     */
XMLElement::XMLTag XmlPulseParser::processXMLTag (const QXmlStreamReader& xmlreader)
{
    const QString name = xmlreader.name().toString();

    if(name == QStringLiteral("Settings"))
        return XMLElement::Settings;
    else if(name == QStringLiteral("Param"))
        return XMLElement::Param;
    else if(name == QStringLiteral("Channel"))
        return XMLElement::Channel;
    else if(name == QStringLiteral("Loop"))
        return XMLElement::Loop;
    else if(name == QStringLiteral("Pulse"))
        return XMLElement::Pulse;
    else if(name == QStringLiteral("Action"))
        return XMLElement::Action;
    else if(name == QStringLiteral("Delay"))
        return XMLElement::Delay;
    else if(name == QStringLiteral("Increment"))
        return XMLElement::Increments;
    else if(name == QStringLiteral("Const"))
        return XMLElement::Constants;
    else if(name == QStringLiteral("Sequence"))
        return XMLElement::Sequence;
    else
        return XMLElement::Undefined;

}

/**
     * @brief Parses the XML document.
     * @return RC_t indicating the success or failure of parsing the document.
     */
RC_t XmlPulseParser::parseDoc() {

    QFile file(filePath);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Error: Cannot open file" << filePath;
        return RC_ERROR;
    }

    _reader = new QXmlStreamReader(&file);

    parseDocHeader();
    while (getNextField()) {}

    return RC_SUCCESS;
}

/**
     * @brief Pops the top parent element from the stack.
     * @return Pointer to the popped parent element.
     */
XMLElement *XmlPulseParser::popParent()
{
    XMLElement* popObj = _latest.top();

    _latest.pop();

    return popObj;
}

/**
     * @brief Parses the XML document header.
     * @return True if the header is parsed successfully, false otherwise.
     */
bool XmlPulseParser::parseDocHeader()
{
    QXmlStreamReader::TokenType token = _reader->readNext();
    return token == QXmlStreamReader::StartDocument;
}


/**
     * @brief Gets the next XML field from the document and processes it.
     * @return True if there are more fields to process, false otherwise.
     */
bool XmlPulseParser::getNextField()
{
    QXmlStreamReader::TokenType token = _reader->readNext();


    switch(token)
    {

    case QXmlStreamReader::StartElement:{

       // qDebug() << "start: " << _reader->name();


        XMLElement::XMLTag tag = processXMLTag(*_reader);
        parseStartElement();
        break;
    }

    case QXmlStreamReader::EndElement: {

        //qDebug() << "end: " << _reader->name();

        XMLElement* popObj = popParent();
        Sequence* pSequence = dynamic_cast<Sequence*>(popObj);
        if(pSequence != nullptr)
        {
        //PRINT SEQUENCE OBJECTS
            std::cout << *pSequence;
        }
        break;
    }

    case QXmlStreamReader::Comment: {

        break;
    }

    case QXmlStreamReader::Characters:{
        if(_reader->isWhitespace() || _reader->isComment())
        {
            break;
        }
    }

    default:
    {
        // qDebug() << "unknown token:" << token;
        // qDebug() << _reader->name();
    }
    }

    return !_reader->atEnd();
}

/**
     * @brief Parses the start element of an XML tag.
     */
void XmlPulseParser::parseStartElement()
{
    XMLElement::XMLTag start_tag = processXMLTag(*_reader);
    // qDebug() <<" token: "<< start_tag;

    switch(start_tag)
    {

    case XMLElement::Sequence:
    {
        parseChild<Sequence>();
        break;
    }

    case XMLElement::Settings:
    {

        parseChild<Settings>();
        break;

    }

    case XMLElement::Param:
    {
        parseChild<Param>();
        break;
    }

    case XMLElement::Channel:
    {
        parseChild<Channel>();
        break;
    }

    case XMLElement::Action:
    {
        parseChild<Action>();
        break;
    }

    case XMLElement::Pulse:
    {
        parseChild<Pulse>();
        break;
    }
    case XMLElement::Delay:
    {
        parseChild<Delay>();
        break;
    }
    case XMLElement::Loop:
    {
        parseChild<Loop>();
        break;
    }
    case XMLElement::Increments:
    {
        parseChild<Increment>();
        break;
    }
    case XMLElement::Constants:
    {
        parseChild<Constants>();
        break;
    }

    default:
        break;
    }
}


