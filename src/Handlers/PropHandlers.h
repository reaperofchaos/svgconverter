#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "../Types/Component.h"
#include "../Types/Primitive.h"
#include "../Types/Prop.h"
#include "../Handlers/PrimitiveHandlers.h"
#include "../Utils/ComponentUtilities.h"

/**
 * A class used to create Props from Component vectors
 */
class PropHandlers {
    public:
        static std::shared_ptr<Prop> buildProp(
            std::vector<std::shared_ptr<Component>> &components, 
            size_t &m_index);

        static std::shared_ptr<ObjectProp> buildObjectProp(
            std::vector<std::shared_ptr<Component>> &components,
            std::shared_ptr<Name> name,
            size_t &m_index);
        
        static std::shared_ptr<StringProp> buildStringProp(
            std::vector<std::shared_ptr<Component>> &components,
            std::shared_ptr<Name> name,
            size_t &m_index);
        
        static std::shared_ptr<BooleanProp> buildBooleanProp(
            std::vector<std::shared_ptr<Component>> &components,
            std::shared_ptr<Name> name,
            size_t &m_index);
        
        static std::shared_ptr<BooleanProp> buildBooleanProp(
            std::shared_ptr<Name> name);
};