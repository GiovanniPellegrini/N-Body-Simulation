#ifndef TESTMASS_H
#define TESTMASS_H
#include "Object.h"
#include "System.h"

/*
 * TestMass class
 * Represents a test in the simulation, inheriting from Object. It is influenced by every other object in the system, but does not influence them.
 *
 */

class TestMass : public Object
{
    // Constructor
public:
    TestMass() = default;
    TestMass(const std::string &name,const Vector &position, const Vector &velocity, double mass)
        : Object(name,position, velocity, mass) {}

    // destructor
    ~TestMass() override = default;    

    // string method
    std::string str() const override;

    // set the relevant radius of the test mass
     void setRelevantHillRadius() override {};
    
    // Important objects: return relevant objects for the simulation
    std::vector<Object *> getRelevantObjects(const System &) const override;
};

std::ostream &operator<<(std::ostream &os, const TestMass &obj);

#endif
    