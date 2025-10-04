#ifndef COMET_H
#define COMET_H
#include "Object.h"
#include "System.h"

/*
 * Comet class
 * Represents a comet in the simulation, inheriting from Object. No hierarchy, Objects are relevant for the simulation if the comet passes nearby.
 *
 */

class Comet : public Object
{

public:
    // constructor
    Comet() = default;
    Comet(const std::string &name,const Vector &position, const Vector &velocity, double mass)
        : Object(name,position, velocity, mass) {}

    // destructor
    ~Comet() override = default;

    // string method
    std::string str() const override;

    void setRelevantHillRadius() override;

    // Important objects: return relevant objects for the simulation
    std::vector<Object *> getRelevantObjects(const System &) const override;
};

std::ostream &operator<<(std::ostream &os, const Comet &obj);

#endif