#pragma once
#include <fstream>
#include <memory>
#include "Types/Node.h"
#include "Types/Element.h"
#include "Types/Prop.h"

/**
 * @brief Class to write a tree to 
 * a file
 */
class Writer
{
    std::shared_ptr<Node> tree;
    std::ofstream out; 

    public:
        Writer(std::shared_ptr<Node> tree)
        {
            this->tree = tree;
        }

        ~Writer()
        {
            this->out.close(); 
        }

        void setFile(std::string fileName){ this->out = std::ofstream(fileName);}; 
        void createFile(std::string fileName);
        void writeTreeToFile();
        void writeNodes(std::shared_ptr<Node> node);
        void writeTreeAsJSON();
        void writeNodesAsObject(std::shared_ptr<Node> node, bool isChild);

        void writePair(
            std::string elementSpacing, 
            std::string key, 
            std::string value);

        void writeTypePair(
            std::string elementSpacing, 
            std::shared_ptr<Element> value);

        void writeProps(
            std::string elementSpacing, 
            std::vector<std::shared_ptr<Prop>> props);
};