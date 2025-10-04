#ifndef STAR_H
#define STAR_H
#include "Object.h"
#include "System.h"

/*
 * Star class
 * Represents a star in the simulation, inheriting from Object. Lower classes in the hierarchy: Planet, Moon, Comet
 *
 */

class Star : public Object
{

public:
    // constructor
    Star() = default;
    Star(const std::string &name,const Vector &position, const Vector &velocity, double mass)
        : Object(name, position, velocity, mass) {}

    // destructor
    ~Star() override = default;

    // string method
    std::string str() const override;

    // set the relevant radius of the planet
    void setRelevantHillRadius() override;

    // Important objects: return relevant objects for the simulation
    std::vector<Object *> getRelevantObjects(const System &) const override;
};

std::ostream &operator<<(std::ostream &os, const Star &obj);

#endif