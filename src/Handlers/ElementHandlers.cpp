#include "ElementHandlers.h"

//Creates a document tag element
std::shared_ptr<DocumentTag> ElementHandlers::buildDocumentTagElement(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,  
    size_t &start)
{
    std::shared_ptr<DocumentTypeOpenTag> openTag = std::dynamic_pointer_cast<DocumentTypeOpenTag>(components[start]); 
    ComponentUtilities::IncrementIndex(components, m_index);
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);

    std::shared_ptr<Name> tagName = std::dynamic_pointer_cast<Name>(components[m_index]);
    ComponentUtilities::IncrementIndex(components, m_index);
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);

    //build props
    std::vector<std::shared_ptr<Prop>> props; 
    while(components[m_index]->type() == ComponentType::Name){
        props.push_back(PropHandlers::buildProp(components, m_index));
    }
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);

    std::shared_ptr<CloseTag> closeTag= std::dynamic_pointer_cast<CloseTag>(components[m_index]);
    ComponentUtilities::IncrementIndex(components, m_index);
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);

    return std::make_shared<DocumentTag>(openTag, tagName,  props, closeTag);
}

/**
 * @brief Builds a tag element from the provided components
 * 
 * @param components 
 * @param m_index 
 * @param start 
 * @return std::shared_ptr<Tag> 
 */
std::shared_ptr<Tag> ElementHandlers::buildTagElement(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,  
    size_t &start)
{
    std::shared_ptr<OpenTag> openTag = std::dynamic_pointer_cast<OpenTag>(components[start]); 
    ComponentUtilities::IncrementIndex(components, m_index);
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);
    std::shared_ptr<Name> tagName = std::dynamic_pointer_cast<Name>(components[m_index]);
    ComponentUtilities::IncrementIndex(components, m_index);
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);

    //build props
    std::vector<std::shared_ptr<Prop>> props; 
    while(components[m_index]->type() == ComponentType::Name){
        std::shared_ptr<Prop> prop = PropHandlers::buildProp(components, m_index);
        props.push_back(prop);
    }
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);

    if(components[m_index]->type() == ComponentType::CloseTag)
    {
        std::shared_ptr<CloseTag> closeTag = std::dynamic_pointer_cast<CloseTag>(components[m_index]); 
        ComponentUtilities::IncrementIndex(components, m_index);
        ComponentUtilities::IgnoreWhiteSpace(components, m_index);
        return std::make_shared<OpenTagElement>(openTag, tagName, props,  closeTag);
    }

    if(components[m_index]->type() == ComponentType::ClosingCloseTag)
    {
        std::shared_ptr<ClosingCloseTag> closingCloseTag = std::dynamic_pointer_cast<ClosingCloseTag>(components[m_index]); 
        ComponentUtilities::IncrementIndex(components, m_index);
        ComponentUtilities::IgnoreWhiteSpace(components, m_index);
        return std::make_shared<SelfClosingTagElement>(openTag, tagName, props, closingCloseTag);
    }

    return {};
}

/**
 * @brief Builds a close tag element from the provided components
 * 
 * @param components 
 * @param m_index 
 * @param start 
 * @return std::shared_ptr<CloseTagElement> 
 */
std::shared_ptr<CloseTagElement> ElementHandlers::buildCloseTagElement(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,  
    size_t &start)
{
    std::shared_ptr<ClosingOpenTag> openClosingTag = std::dynamic_pointer_cast<ClosingOpenTag>(components[start]);
    ComponentUtilities::IncrementIndex(components, m_index);
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);

    std::shared_ptr<Name> tagName = std::dynamic_pointer_cast<Name>(components[m_index]);
    ComponentUtilities::IncrementIndex(components, m_index);
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);

    std::shared_ptr<CloseTag> closeTag = std::dynamic_pointer_cast<CloseTag>(components[m_index]);
    ComponentUtilities::IncrementIndex(components, m_index);
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);

    std::shared_ptr<CloseTagElement> closeElement = std::make_shared<CloseTagElement>(openClosingTag, tagName, closeTag);
    return closeElement;
}

/**
 * @brief Builds a comment tag from the provided components
 * 
 * @param components 
 * @param m_index 
 * @param start 
 * @return std::shared_ptr<CommentTagElement> 
 */
std::shared_ptr<CommentTagElement> ElementHandlers::buildCommentTagElement(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,  
    size_t &start)
{
    std::shared_ptr<CommentOpenTag> openTag = std::dynamic_pointer_cast<CommentOpenTag>(components[start]); 
    ComponentUtilities::IncrementIndex(components, m_index);
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);
    std::vector<std::shared_ptr<Component>> comment; 

    while(components[m_index]->type() != ComponentType::CommentCloseTag)
    {
        comment.push_back(components[m_index]);
        ComponentUtilities::IncrementIndex(components, m_index);
    }

    std::shared_ptr<CommentCloseTag> closeTag = std::dynamic_pointer_cast<CommentCloseTag>(components[m_index]);
    ComponentUtilities::IncrementIndex(components, m_index);
    ComponentUtilities::IgnoreWhiteSpace(components, m_index);

    return std::make_shared<CommentTagElement>(openTag, comment, closeTag);
}

/**
 * @brief Builds a nested string from the provided components
 * 
 * @param components 
 * @param m_index 
 * @param start 
 * @return std::shared_ptr<NestedString> 
 */
std::shared_ptr<NestedString> ElementHandlers::buildNestedString(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,  
    size_t &start)
{
    std::string value = ""; 
    value += components[start]->getValue();
    ComponentUtilities::IncrementIndex(components, m_index);

    while(components[m_index]->type() != ComponentType::ClosingOpenTag &&
        components[m_index]->type() != ComponentType::OpenTag)
    {
        value += components[m_index]->getValue();
        ComponentUtilities::IncrementIndex(components, m_index);
    }
    std::shared_ptr<StringType> stringValue = std::make_shared<StringType>(value);
    
    return std::make_shared<NestedString>(stringValue);
}

/**
 * @brief Creates a nested object from the provided components
 * 
 * @param components 
 * @param m_index 
 * @param start 
 * @return std::shared_ptr<NestedObject> 
 */
std::shared_ptr<NestedObject> ElementHandlers::buildNestedObject(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,  
    size_t &start)
{
    std::string value = ""; 
    value += components[start]->getValue();
    ComponentUtilities::IncrementIndex(components, m_index);

    while(components[m_index]->type() != ComponentType::CloseObject)
    {
        value += components[m_index]->getValue();
        ComponentUtilities::IncrementIndex(components, m_index);
    }

    if(components[m_index]->type() == ComponentType::CloseParenthesisComponent)
    {
        value += components[m_index]->getValue();
        ComponentUtilities::IncrementIndex(components, m_index);
    }

    if(components[m_index]->type() == ComponentType::CloseObject)
    {
        value += components[m_index]->getValue();
        ComponentUtilities::IncrementIndex(components, m_index);
    }

    std::shared_ptr<StringType> stringValue = std::make_shared<StringType>(value);
    
    return std::make_shared<NestedObject>(stringValue);
}