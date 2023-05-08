#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <cassert>
#include "Prop.h"

enum class ElementType
{
    Element,
    DocumentTag,
    Tag,
    NestedObject,
    NestedString,
};

enum class TagType
{
    Tag,
    OpenTagElement,
    SelfClosingTagElement,
    CloseTagElement,
    CommentTagElement,
    PrologTag,
    NotATag
};

class Element
{
private:
    std::string value;
    std::string tagString;
    std::vector<std::shared_ptr<Prop>> props;

public:
    Element(){};
    virtual ~Element() = default;
    virtual std::string getTypeAsString(ElementType type)
    {
        switch (type)
        {
        case ElementType::DocumentTag:
            return "Document tag";
        case ElementType::Tag:
            return "Tag";
        case ElementType::NestedObject:
            return "Nested object";
        case ElementType::NestedString:
            return "Nested string";
        default:
            return "Unknown";
        }
    }

    virtual std::string getTagTypeAsString(TagType type)
    {
        switch (type)
        {
        case TagType::OpenTagElement:
            return "Open tag";
        case TagType::SelfClosingTagElement:
            return "Self closing tag";
        case TagType::CloseTagElement:
            return "Closing Tag";
        case TagType::CommentTagElement:
            return "Comment Tag";
        case TagType::PrologTag:
            return "Prolog Tag";
        default:
            return "Unknown Tag";
        }
    }

    virtual ElementType type() { return ElementType::Element; }
    virtual TagType tagType() { return TagType::NotATag; }
    virtual std::string inspect() { assert(0); }
    virtual std::vector<std::shared_ptr<Prop>> getProps() { return this->props; }
    virtual std::string getValue() { return value; }
    virtual std::string getType() { return this->getTypeAsString(this->type()); }
    virtual std::string getTagType() { return this->getTagTypeAsString(this->tagType()); }
};

class DocumentTag : public Element
{
private:
    std::string value;
    std::string tagString;
    std::vector<std::shared_ptr<Prop>> props;

public:
    DocumentTag(std::shared_ptr<DocumentTypeOpenTag> openTag, std::shared_ptr<Name> name, std::vector<std::shared_ptr<Prop>> props, std::shared_ptr<CloseTag> closeTag) : Element()
    {
        this->tagString = openTag->getValue() + " " + name->getValue() + " " + closeTag->getValue();
        this->value = name->getValue();
        this->props = props;
    }
    virtual ElementType type() { return ElementType::DocumentTag; }
    virtual std::string inspect()
    {
        std::string text = this->getType() + " - " + this->getValue() + "\n";
        if (this->props.size() > 0)
        {
            text += "\tProps \n";
            text += displayProps();
        }
        return text;
    }
    virtual std::vector<std::shared_ptr<Prop>> getProps() { return this->props; }
    virtual std::string getValue() { return value; }
    std::string getTagString() { return this->tagString; };
    std::string displayProps()
    {
        std::string propText = "";
        for (std::shared_ptr<Prop> prop : this->props)
        {
            propText += "\t";
            propText += prop->getType();
            propText += " - ";
            propText += prop->getName();
            propText += ": ";
            propText += prop->getValue()->getValue();
            propText += "\n";
        }
        return propText;
    }
    virtual std::string getType() { return this->getTypeAsString(this->type()); }
};

class Tag : public Element
{
private:
    std::string value;
    std::string tagString;
    std::vector<std::shared_ptr<Prop>> props;

public:
    virtual ElementType type() { return ElementType::Tag; }
    virtual TagType tagType() { return TagType::Tag; }

    virtual std::string getTagTypeAsString(TagType type)
    {
        switch (type)
        {
        case TagType::OpenTagElement:
            return "Open tag";
        case TagType::SelfClosingTagElement:
            return "Self closing tag";
        case TagType::CloseTagElement:
            return "Closing Tag";
        case TagType::CommentTagElement:
            return "Comment Tag";
        case TagType::PrologTag:
            return "Prolog Tag";
        default:
            return "Unknown Tag";
        }
    }
    virtual std::string inspect()
    {
        std::string text = this->getTagType() + " - " + this->getValue() + "\n";
        if (this->props.size() > 0)
        {
            text += "Props \n";
            text += displayProps();
        }
        return text;
    }
    virtual std::vector<std::shared_ptr<Prop>> getProps() { return this->props; }
    virtual std::string getValue() { return value; }
    virtual std::string getTagString() { return this->tagString; };
    virtual std::string displayProps()
    {
        std::string propText = "";
        for (std::shared_ptr<Prop> prop : this->props)
        {
            propText += prop->getName();
            propText += " - ";
            propText += prop->getValue()->getValue();
            propText += "\n";
        }
        return propText;
    }
    virtual std::string getType() { return this->getTypeAsString(this->type()); }
    virtual std::string getTagType() { return this->getTagTypeAsString(this->tagType()); }
};

class OpenTagElement : public Tag
{
private:
    std::string value;
    std::string tagString;
    std::vector<std::shared_ptr<Prop>> props;

public:
    OpenTagElement(std::shared_ptr<OpenTag> openTag,
                   std::shared_ptr<Name> name,
                   std::vector<std::shared_ptr<Prop>> props,
                   std::shared_ptr<CloseTag> closeTag) : Tag()
    {
        this->tagString = openTag->getValue() + " " + name->getValue() + " " + closeTag->getValue();
        this->value = name->getValue();
        this->props = props;
    }
    virtual ElementType type() { return ElementType::Tag; }
    virtual TagType tagType() { return TagType::OpenTagElement; }
    virtual std::string inspect()
    {
        std::string text = this->getTagType() + " - " + this->getValue() + "\n";
        if (this->props.size() > 0)
        {
            text += "Props \n";
            text += displayProps();
        }
        return text;
    }
    virtual std::vector<std::shared_ptr<Prop>> getProps() { return this->props; }
    virtual std::string getValue() { return value; }
    std::string getTagString() { return this->tagString; };
    std::string displayProps()
    {
        std::string propText = "";
        for (std::shared_ptr<Prop> prop : this->props)
        {
            propText += prop->getName();
            propText += " - ";
            propText += prop->getValue()->getValue();
            propText += "\n";
        }
        return propText;
    }
    virtual std::string getType() { return this->getTypeAsString(this->type()); }
    virtual std::string getTagType() { return this->getTagTypeAsString(this->tagType()); }
};

class SelfClosingTagElement : public Tag
{
private:
    std::string value;
    std::string tagString;
    std::vector<std::shared_ptr<Prop>> props;

public:
    SelfClosingTagElement(std::shared_ptr<OpenTag> openTag,
                          std::shared_ptr<Name> name,
                          std::vector<std::shared_ptr<Prop>> props,
                          std::shared_ptr<ClosingCloseTag> closeTag) : Tag()
    {
        this->tagString = openTag->getValue() + " " + name->getValue() + " " + closeTag->getValue();
        this->value = name->getValue();
        this->props = props;
    }
    virtual TagType tagType() { return TagType::SelfClosingTagElement; }
    virtual ElementType type() { return ElementType::Tag; }
    virtual std::string inspect()
    {
        std::string text = this->getTagType() + " - " + this->getValue() + "\n";
        if (this->props.size() > 0)
        {
            text += "Props \n";
            text += displayProps();
        }
        return text;
    }
    virtual std::vector<std::shared_ptr<Prop>> getProps() { return this->props; }
    virtual std::string getValue() { return value; }
    std::string getTagString() { return this->tagString; };
    std::string displayProps()
    {
        std::string propText = "";
        for (std::shared_ptr<Prop> prop : this->props)
        {
            propText += prop->getName();
            propText += " - ";
            propText += prop->getValue()->getValue();
            propText += "\n";
        }
        return propText;
    }
    virtual std::string getType() { return this->getTypeAsString(this->type()); }
    virtual std::string getTagType() { return this->getTagTypeAsString(this->tagType()); }
};

class CloseTagElement : public Tag
{
private:
    std::string value;
    std::string tagString;

public:
    CloseTagElement(std::shared_ptr<ClosingOpenTag> openTag,
                    std::shared_ptr<Name> name,
                    std::shared_ptr<CloseTag> closeTag) : Tag()
    {
        this->tagString = openTag->getValue() + " " + name->getValue() + " " + closeTag->getValue();
        this->value = name->getValue();
    }

    virtual TagType tagType() { return TagType::CloseTagElement; }
    virtual ElementType type() { return ElementType::Tag; }
    virtual std::string inspect()
    {
        std::string text = this->getTagType() + " - " + this->getValue() + "\n";
        return text;
    }
    virtual std::string getValue() { return value; }
    std::string getTagString() { return this->tagString; };
    virtual std::string getType() { return this->getTypeAsString(this->type()); }
    virtual std::string getTagType() { return this->getTagTypeAsString(this->tagType()); }
};

class PrologTag : public Tag
{
private:
    std::string value;
    std::string tagString;
    std::vector<std::shared_ptr<Prop>> props;

public:
    PrologTag(std::shared_ptr<OpenPrologComponent> openTag,
              std::shared_ptr<Name> name,
              std::vector<std::shared_ptr<Prop>> props,
              std::shared_ptr<ClosePrologComponent> closeTag) : Tag()
    {
        this->tagString = openTag->getValue() + " " + name->getValue() + " " + closeTag->getValue();
        this->value = name->getValue();
        this->props = props;
    }
    virtual TagType tagType() { return TagType::PrologTag; }
    virtual ElementType type() { return ElementType::Tag; }
    virtual std::string inspect()
    {
        std::string text = this->getTagType() + " - " + this->getValue() + "\n";
        if (this->props.size() > 0)
        {
            text += "Props \n";
            text += displayProps();
        }
        return text;
    }
    virtual std::vector<std::shared_ptr<Prop>> getProps() { return this->props; }
    virtual std::string getValue() { return value; }
    std::string getTagString() { return this->tagString; };
    std::string displayProps()
    {
        std::string propText = "";
        for (std::shared_ptr<Prop> prop : this->props)
        {
            propText += prop->getName();
            propText += " - ";
            propText += prop->getValue()->getValue();
            propText += "\n";
        }
        return propText;
    }
    virtual std::string getType() { return this->getTypeAsString(this->type()); }
    virtual std::string getTagType() { return this->getTagTypeAsString(this->tagType()); }
};

class CommentTagElement : public Tag
{
private:
    std::string value;
    std::string tagString;

public:
    CommentTagElement(std::shared_ptr<CommentOpenTag> openTag,
                      std::vector<std::shared_ptr<Component>> comments,
                      std::shared_ptr<CommentCloseTag> closeTag) : Tag()
    {
        std::string value = "";

        for (std::shared_ptr<Component> comment : comments)
        {
            value += comment->getValue();
        }

        this->value = value;
        this->tagString = openTag->getValue() + " " + value + " " + closeTag->getValue();
    }
    virtual TagType tagType() { return TagType::CommentTagElement; }
    virtual ElementType type() { return ElementType::Tag; }
    virtual std::string inspect()
    {
        std::string text = this->getTagType() + " - " + this->getValue() + "\n";
        return text;
    }
    virtual std::string getValue() { return value; }
    std::string getTagString() { return this->tagString; };
    virtual std::string getType() { return this->getTypeAsString(this->type()); }
    virtual std::string getTagType() { return this->getTagTypeAsString(this->tagType()); }
};

class NestedString : public Element
{
private:
    std::string value;

public:
    NestedString(std::shared_ptr<StringType> stringValue)
    {
        this->value = stringValue->getValue();
    }
    virtual ElementType type() { return ElementType::NestedString; }
    virtual std::string inspect()
    {
        std::string text = this->getType() + " - " + this->getValue() + "\n";
        return text;
    }
    virtual std::string getValue() { return value; }
    virtual std::string getType() { return this->getTypeAsString(this->type()); }
};

class NestedObject : public Element
{
private:
    std::string value;

public:
    NestedObject(std::shared_ptr<StringType> stringValue)
    {
        this->value = stringValue->getValue();
    }
    virtual ElementType type() { return ElementType::NestedObject; }
    virtual std::string inspect()
    {
        std::string text = this->getType() + " - " + this->getValue() + "\n";
        return text;
    }
    virtual std::string getValue() { return value; }
    virtual std::string getType() { return this->getTypeAsString(this->type()); }
};