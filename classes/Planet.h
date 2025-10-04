#ifndef PLANET_H
#define PLANET_H
#include "Object.h"
#include "System.h"

/*
 * Planet class
 * Represents a planet in the simulation, inheriting from Object. Lower classes in the hierarchy: Moon, Comet
 *
 */

class Planet : public Object
{
public:
    // constructor
    Planet() = default;
    Planet(const std::string &name,const Vector &position, const Vector &velocity, double mass)
        : Object(name,position, velocity, mass) {}

    // destructor
    ~Planet() override = default;

    // string method
    std::string str() const override;

    // set the relevant radius of the planet
    void setRelevantHillRadius() override;
    
    // Important objects: return relevant objects for the simulation
    std::vector<Object *> getRelevantObjects(const System &) const override;
};

std::ostream &operator<<(std::ostream &os, const Planet &obj);

#endif