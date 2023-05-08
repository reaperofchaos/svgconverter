#pragma once
#include <vector>
#include <memory>
#include <string>
#include <cassert>
#include "Primitive.h"

enum class PropType
{
    Prop, 
    ObjectProp,
    StringProp,
    BooleanProp
};

class Prop{
    private:
        std::string name;
        std::shared_ptr<Primitive> value; 
    
    public:
        Prop(){};

        virtual ~Prop() = default;
        virtual std::string getTypeAsString(PropType type){
            switch (type)
            {
                case PropType::ObjectProp:
                    return "Object prop";
                case PropType::BooleanProp:
                    return "Boolean prop";
                case PropType::StringProp:
                    return "String prop";
                default: 
                    return "Unknown";
            }
        }
        
        virtual PropType type(){ return PropType::Prop;}
        virtual std::string inspect() { return this->getType() + " - " + this->name + " : " + this->value->getValue(); }
        virtual std::string getName(){return this->name;}
        virtual std::shared_ptr<Primitive> getValue(){return this->value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}

};

class ObjectProp: public Prop{
    private:
        std::string name;
        std::shared_ptr<Primitive> value; 
    
    public:
        ObjectProp(std::shared_ptr<Name> name, std::shared_ptr<Primitive> value): Prop()
        {
            this->name = name->getValue(); 
            this->value = value;
        };

        ObjectProp(std::string name, std::shared_ptr<Primitive> value): Prop()
        {
            this->name = name; 
            this->value = value;
        };
        
        virtual PropType type(){ return PropType::ObjectProp;}
        virtual std::string inspect() { return this->getType() + " - " + this->name + " : " + this->value->getValue(); }
        virtual std::string getName(){return this->name;}
        virtual std::shared_ptr<Primitive> getValue(){return this->value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
};

class StringProp: public Prop{
    private:
        std::string name;
        std::shared_ptr<Primitive> value; 
    
    public:
        StringProp(std::shared_ptr<Name> name, std::shared_ptr<StringPrimitive> value): Prop()
        {
            this->name = name->getValue(); 
            this->value = value;
        };

        StringProp(std::string name, std::shared_ptr<StringPrimitive> value): Prop()
        {
            this->name = name; 
            this->value = value;
        };
        
        virtual PropType type(){ return PropType::StringProp;}
        virtual std::string inspect() { return this->getType() + " - " + this->name + " : " + this->value->getValue(); }
        virtual std::string getName(){return this->name;}
        virtual std::shared_ptr<Primitive> getValue(){return this->value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
};

class BooleanProp: public Prop{
    private:
        std::string name;
        std::shared_ptr<Primitive> value; 
    
    public:
        BooleanProp(std::shared_ptr<Name> value): Prop()
        {
            this->name = value->getValue(); 
            this->value = std::make_shared<BooleanPrimitive>(value);
        };

        BooleanProp(std::shared_ptr<Name> name, std::shared_ptr<Name> value): Prop()
        {
            this->name = name->getValue(); 
            this->value = std::make_shared<BooleanPrimitive>(value);
        };

        BooleanProp(std::shared_ptr<Name> name, std::shared_ptr<BooleanPrimitive> value): Prop()
        {
            this->name = name->getValue(); 
            this->value = value;
        };
        
        virtual PropType type(){ return PropType::BooleanProp;}
        virtual std::string inspect() { return this->getType() + " - " + this->name + " : " + this->value->getValue(); }
        virtual std::string getName(){return this->name;}
        virtual std::shared_ptr<Primitive> getValue(){return this->value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
};