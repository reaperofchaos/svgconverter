#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "../Types/Component.h"
#include "../Types/Primitive.h"
#include "../Types/Element.h"
#include "../Handlers/PropHandlers.h"
#include "../Utils/ComponentUtilities.h"

/**
 * A class used to create Elements from Component vectors
 */
class ElementHandlers {
    public:
        static std::shared_ptr<DocumentTag> buildDocumentTagElement(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);
        
        static std::shared_ptr<Tag> buildTagElement(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);
        
        static std::shared_ptr<CloseTagElement> buildCloseTagElement(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);
        
        static std::shared_ptr<CommentTagElement> buildCommentTagElement(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);

        static std::shared_ptr<NestedString> buildNestedString(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);
        
        static std::shared_ptr<NestedObject> buildNestedObject(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);
};