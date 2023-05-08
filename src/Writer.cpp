#include "Writer.h"

/**
 * @brief Function to write a tree to a provided filename
 * 
 * @param fileName, name of the file
 */
void Writer::createFile(std::string fileName)
{
    this->out = std::ofstream(fileName);
    this->writeTreeToFile();
}

/**
 * @brief Function to write a tree to a file output stream
 * 
 */
void Writer::writeTreeToFile()
{
    this->out << "Parsed Tree \n";
    writeNodes(this->tree); 
    this->out.close(); 
}

/**
 * @brief A function to write a list of tags with the
 * level, type and value to an output stream
 * 
 * @param node 
 */
void Writer::writeNodes(std::shared_ptr<Node> node)
{
    this->out << "Node: " << node->value->getValue() << 
    " Level: " << node->level;
    if(node->value->type() == ElementType::Tag){
        this->out << " Type: " 
            << node->value->getTagTypeAsString(node->value->tagType()) << "\n";
    }else{
        this->out << " Type: " 
            << node->value->getTypeAsString(node->value->type()) << "\n";
    }
    if(node->children.size() > 0)
    {
        for(std::shared_ptr<Node> child : node->children)
        {
            writeNodes(child); 
        }
    }
}

/**
 * @brief A function to write a key value pair to
 * the file output stream
 * 
 * @param elementSpacing, a string with tabs
 * @param key a string with the name of the key
 * @param value the string containing the value tied to the key
 */
void Writer::writePair(
            std::string elementSpacing, 
            std::string key, 
            std::string value)
{
    this->out   << "\t" << elementSpacing 
                << "\"" << key << "\": \""  
                << value<< "\"";
}

/**
 * @brief Function to write a key value pair using types
 * to the file output stream
 * 
 * @param elementSpacing string with tabs
 * @param value an Element
 */
void Writer::writeTypePair(
    std::string elementSpacing, 
    std::shared_ptr<Element> value)
{
    if(value->type() == ElementType::Tag)
    {
        writePair(elementSpacing, "type", 
            value->getTagType());
    }else{
        writePair(elementSpacing, "type", 
            value->getType());
    }
}

/**
 * @brief A function to write key value pairs for
 * props to the file output stream
 * 
 * @param elementSpacing, a string with tabs
 * @param props, a vector of props to write
 */
void Writer::writeProps(
    std::string elementSpacing, 
    std::vector<std::shared_ptr<Prop>> props)
{
    this->out   << "\t" << elementSpacing 
                << "\"" << "props" << "\": [\n";
    int i = 0; 
    for(std::shared_ptr<Prop> prop : props)
    {
        if(i != 0)
        {
            this->out << ",\n";
        }

        this->out << elementSpacing << "\t\t{\n";
        writePair(elementSpacing+"\t\t", "name", prop->getName() );
        this->out << ", \n"; 
        writePair(elementSpacing+"\t\t", "type", prop->getType() );
        this->out << ", \n"; 
        writePair(elementSpacing+"\t\t", "value", prop->getValue()->getValue() );
        this->out << ", \n"; 
        writePair(elementSpacing+"\t\t", "value-type", prop->getValue()->getType() );
        this->out << "\n"; 
        this->out << elementSpacing << "\t\t}";
        i++;
    }
    this->out << "\n"; 
    this->out   << "\t" << elementSpacing 
                << "]";
}

/**
 * @brief a function to write the Abstract Syntax Tree (Node) as an object
 * 
 * @param node 
 * @param isChild 
 */
void Writer::writeNodesAsObject(std::shared_ptr<Node> node, bool isChild)
{
    std::string spacing = ""; 
    for(int i = 0; i < node->level; i++)
    {
        spacing += "\t";
    }

    std::string elementSpacing = spacing += "\t";
    
    this->out   << spacing << "{ \n";
    writePair(elementSpacing, "name", node->value->getValue() );
    this->out   << ",\n";
    writePair(elementSpacing, "level", std::to_string(node->level) );
    this->out   << ",\n";
    writeTypePair(elementSpacing, node->value);

    if(node->value->type() == ElementType::Tag ||
        node->value->type() == ElementType::DocumentTag)
    {
        std::vector<std::shared_ptr<Prop>> props = node->value->getProps();

        if(props.size() > 0)
        {
            this->out << ",\n";
            writeProps(elementSpacing, props);
        }
    }
    if(node->children.size() > 0)
    {
        this->out << ",\n"; 
        this->out << "\t" << elementSpacing << "\"children\": [\n"; 
        size_t i = 0; 
        for(std::shared_ptr<Node> child : node->children)
        {

            this->writeNodesAsObject(child, i < node->children.size() -1); 
            i++; 
        }
        this->out << "\t" << spacing << "]\n";

    }else{
        
        this->out << "\n"; 
    }

    if(isChild)
    {
        this->out << elementSpacing << "},\n"; 
    }
    else{
        this->out << elementSpacing << "}\n"; 
    }
}

/**
 * @brief a function to write the Abstract Syntax Tree (Node)
 * as a JSON file
 * 
 */
void Writer::writeTreeAsJSON()
{
    writeNodesAsObject(this->tree, false); 
    this->out.close(); 
}