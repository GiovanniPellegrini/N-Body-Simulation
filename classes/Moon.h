#ifndef MOON_H
#define MOON_H
#include "Object.h"
#include "System.h"

/*
 * Moon class
 * Represents a Moon in the simulation, inheriting from Object. Lower classes in the hierarchy: Comet 
 *  
 */

class Moon : public Object
{

public:
    // constructor
    Moon() = default;
    Moon(const std::string &name,const Vector &position, const Vector &velocity, double mass)
        : Object(name,position, velocity, mass) {}

    // destructor
    ~Moon() override = default;

    // string method
    std::string str() const override;

    // set the relevant radius of the moon
    void setRelevantHillRadius() override;

    // Important objects: return relevant objects for the simulation
    std::vector<Object *> getRelevantObjects(const System &) const override;
};

std::ostream &operator<<(std::ostream &os, const Moon &obj);

#endif