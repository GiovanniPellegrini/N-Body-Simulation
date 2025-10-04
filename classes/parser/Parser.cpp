#ifndef PARSER_H
#define PARSER_H


#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <memory>
#include "../System.h"
#include "../Star.h"
#include "../Planet.h"
#include "../Moon.h"
#include "../Comet.h"
#include "../TestMass.h"

class Parser {
public:
    explicit Parser(const std::string& filename)
        : m_filename(filename)
    {
        registerFactories();
    }

    // single-pass parse: build a System with all objects and parent/child links
    std::unique_ptr<System> parse() {
        std::unique_ptr system = std::make_unique<System>();
        std::ifstream file(m_filename);
        if (!file) {
            throw std::runtime_error("Cannot open file: " + m_filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line.front() == '#') continue;
            parseLine(line, *system);
        }
        return system;
    }

protected: 
    using Factory = std::function<std::unique_ptr<Object>(
        const std::string&,
        const Vector&,
        const Vector&,
        double)>;

    void registerFactories() {
        m_factories["Star"]   = &create<Star>;
        m_factories["Planet"] = &create<Planet>;
        m_factories["Moon"]   = &create<Moon>;
        m_factories["Comet"]  = &create<Comet>;
        m_factories["TestMass"] = &create<TestMass>;
    }
    void expectChar(std::istream& is, char expected) {
        char ch;
        is >> ch;
        if (ch != expected) {
            std::ostringstream err;
            err << "Parsing error: expected '" << expected << "', but got '" << ch << "'";
            throw std::runtime_error(err.str());
        }
    }

    template<typename T>
    static std::unique_ptr<Object> create(
        const std::string& name,
        const Vector&      pos,
        const Vector&      vel,
        double             mass)
    {
        return std::make_unique<T>(name, pos, vel, mass);
    }

    void parseLine(const std::string& line, System& system) {
        std::istringstream iss(line);
        std::string type, name; iss >> type >> name;
        expectChar(iss, '[');
        Vector pos = readVector(iss);
        expectChar(iss, ',');
        Vector vel = readVector(iss);
        expectChar(iss, ',');
        double mass; iss >> mass;
        expectChar(iss, ']');
        expectChar(iss, ';');

        // check for parent
        std::string parentToken, parentName;
        if (iss >> parentToken && parentToken.rfind("parent=",0)==0) {
            parentName = parentToken.substr(7);
        }

        // create and register
        auto objPtr = m_factories.at(type)(name,pos,vel,mass);
        Object* rawPtr = objPtr.get();
        system.addObject(std::move(objPtr));
        std::cout<<"Adding object: " << rawPtr->str() << std::endl;
        m_registry[name] = rawPtr;

        // ENFORCE: parent must pre‐exist
        if (!parentName.empty()) {
            auto it = m_registry.find(parentName);
            if (it == m_registry.end()) {
                throw std::runtime_error(
                    "Parent \"" + parentName + "\" for object \"" 
                    + name + "\" not found (input out of order).");
            }
            Object* parent = it->second;
            parent->addChild(rawPtr);
            rawPtr->addParent(parent);
        }
    }

    Vector readVector(std::istringstream& iss) {
        expectChar(iss, '(');
        double x, y;
        iss >> x;
        expectChar(iss, ',');
        iss >> y;
        expectChar(iss, ')');
        return Vector(x, y);
    }

private:
    std::string m_filename;
    std::unordered_map<std::string,Factory> m_factories;
    std::unordered_map<std::string,Object*> m_registry;
};

#endif