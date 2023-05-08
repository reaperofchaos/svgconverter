#include "PropHandlers.h"

/**
 * @brief Creates a prop from the provided components
 * 
 * @param components 
 * @param m_index 
 * @return std::shared_ptr<Prop> 
 */
std::shared_ptr<Prop> PropHandlers:: buildProp(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index)
{
    size_t start = m_index;
    if(components[start]->type() == ComponentType::Name)
    {

        std::shared_ptr<Name> name = std::dynamic_pointer_cast<Name>(components[start]); 
        ComponentUtilities::IncrementIndex(components, m_index);
        ComponentUtilities::IgnoreWhiteSpace(components, m_index);

        if(components[m_index]->type() == ComponentType::EqualComponent)
        {
            ComponentUtilities::IncrementIndex(components, m_index);
            ComponentUtilities::IgnoreWhiteSpace(components, m_index);

            switch(components[m_index]->type())
            {
                case ComponentType::Name:
                    return PropHandlers::buildBooleanProp(components, name, m_index);
                case ComponentType::StringType:
                    return PropHandlers::buildStringProp(components, name, m_index);
                case ComponentType::OpenObject:
                    return PropHandlers::buildObjectProp(components, name, m_index);
                default:
                    ComponentUtilities::IncrementIndex(components, m_index);
                    return NULL; 
            }
        }
        return PropHandlers::buildBooleanProp(name);
    }

    return NULL;
}

/**
 * @brief Creates a string prop from the provided components
 * 
 * @param components 
 * @param name 
 * @param m_index 
 * @return std::shared_ptr<StringProp> 
 */
std::shared_ptr<StringProp> PropHandlers::buildStringProp(
    std::vector<std::shared_ptr<Component>> &components,
    std::shared_ptr<Name> name,
    size_t &m_index)
{
    std::shared_ptr<StringPrimitive> stringPrimitive = PrimitiveHandlers::buildStringPrimitive(components, m_index);
    return std::make_shared<StringProp>(name, stringPrimitive);
}

/**
 * @brief Creates an object prop from the provided components
 * 
 * @param components 
 * @param name 
 * @param m_index 
 * @return std::shared_ptr<ObjectProp> 
 */
std::shared_ptr<ObjectProp> PropHandlers::buildObjectProp(
    std::vector<std::shared_ptr<Component>> &components,
    std::shared_ptr<Name> name,
    size_t &m_index)
{
    ComponentUtilities::IncrementIndex(components, m_index);

    if(components[m_index]->type() == ComponentType::OpenObject)
    {
        std::shared_ptr<ObjectPrimitive> objectPrimitive = PrimitiveHandlers::buildObject(components, m_index);
        ComponentUtilities::IncrementIndex(components, m_index);
        return std::make_shared<ObjectProp>(name, objectPrimitive);

    }else{
        std::vector<std::shared_ptr<Component>> characters; 

        while(components[m_index]->type() != ComponentType::CloseObject){
            characters.push_back(components[m_index]);
            ComponentUtilities::IncrementIndex(components, m_index);
        }
        
        if(components[m_index+1]->type() == ComponentType::CloseObject){
            characters.push_back(components[m_index]);
            ComponentUtilities::IncrementIndex(components, m_index);
        }

        std::shared_ptr<StringPrimitive> stringPrimitive = std::make_shared<StringPrimitive>(characters);
        ComponentUtilities::IncrementIndex(components, m_index);

        return std::make_shared<ObjectProp>(name, stringPrimitive);
    }

}

/**
 * @brief Creates a boolean prop from the provided components
 * 
 * @param components 
 * @param name 
 * @param m_index 
 * @return std::shared_ptr<BooleanProp> 
 */
std::shared_ptr<BooleanProp> PropHandlers::buildBooleanProp(
    std::vector<std::shared_ptr<Component>> &components,
    std::shared_ptr<Name> name,
    size_t &m_index)
{
    std::shared_ptr<BooleanPrimitive> booleanPrimitive = PrimitiveHandlers::buildBooleanPrimitive(components[m_index], m_index);
    return std::make_shared<BooleanProp>(name, booleanPrimitive);
}

/**
 * @brief Builds a boolean prop from a name component
 * 
 * @param name 
 * @return std::shared_ptr<BooleanProp> 
 */
std::shared_ptr<BooleanProp> PropHandlers::buildBooleanProp(
    std::shared_ptr<Name> name)
{
    return std::make_shared<BooleanProp>(name);
}