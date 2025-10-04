#ifndef OBJECT_H
#define OBJECT_H
#include "Vector.h"
#include <vector>
/*
 * Object class
 * Represents a physical object with position, velocity, mass, and relationships to other objects.
 * Provides methods for evolution and string representation.
 */

class System;
class Object
{

public:
    // constructor
    Object() = default;
    Object(const std::string & name,const Vector & position, const Vector & velocity, double mass);

    // destructor
    virtual ~Object() = default;

    // copy constructor
    Object(const Object &) = default;
    Object &operator=(const Object &) = default;

    // string representation
    virtual std::string str() const;

    // methods
    double getMass() const;
    const Vector& getPosition() const;
    const Vector& getForce() const;
    const Vector& getVelocity() const;
    double getKineticEnergy() const;
    double getRelevantRadius() const;
    std::string getName() const;

    void setMass(double mass);
    void setPosition(const Vector &position);
    void setVelocity(const Vector &velocity);
    
    void addForce(const Vector &force);
    void resetForce();

    void setRelevantRadius(double radius);
    virtual void setRelevantHillRadius()= 0; 

    // Parent relationship
    void addParent(Object *parent);
    const std::vector<Object *> &getParents() const;

    // Child relationship
    void addChild(Object *child);
    const std::vector<Object *> &getChildren() const;

    // evolution
    void evolve(double dt);
    void evolvePreIntegrate(double dt);
    void evolvePostIntegrate(double dt);
    
    //modify cache 
    void invalidateCache() {m_cacheFilled = false;}
    void setCacheFilled(bool filled) {m_cacheFilled = filled;}

    // Important objects: return relevant objects for the simulation
    // This method should be implemented in derived classes
    virtual std::vector<Object *> getRelevantObjects(const System&) const = 0;

protected:
    Vector m_position;
    Vector m_velocity;
    double m_mass;
    Vector m_force;
    std::vector<Object *> m_parents;
    std::vector<Object *> m_children;
    std::string m_name;
    mutable bool m_cacheFilled= false;
    mutable std::vector<Object *> m_relevantObjects;
    double m_relevantRadius;

};

std::ostream &operator<<(std::ostream &os, const Object &obj);

#endif