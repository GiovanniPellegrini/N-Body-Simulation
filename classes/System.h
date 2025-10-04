#ifndef SYSTEM_H
#define SYSTEM_H
#include "Object.h"
#include "NewtonianForce.cpp"
#include <fstream>
#include <memory>

/*
 * System class
 * Represents a system of objects evolve them using time and a Force.
 */

class System
{
public:
    // constructor
    System() = default;
    explicit System(std::vector<std::unique_ptr<Object>>&& objects): m_objects(std::move(objects)) {}
    System(System&&) = default;
    

    // destructor
    virtual ~System() = default;

    // copy constructor
    System(const System &) = default;
    System &operator=(const System &) = default;

    // sting method
    std::string str() const;

    // add and get object/s to/from the system
    void addObject(std::unique_ptr<Object> object);
    void addListObjects(std::vector<std::unique_ptr<Object>> objects);

    Object* getObject(size_t index) const;
    std::vector<Object*>  getAllObjects() const;
    size_t getNumberOfObjects() const;

    // kinetic energy of the system
    double getTotalKinetic() const;
    double getTotalPotential() const;

    void setAllRelevantHillRadius();
    // evolution
    void computeAllForces(const Force &);
    void resetAllForces();
    void evolveAll(double dt, const Force &, const bool useLeapFrog = false);

    //reference object
    void setReferenceObject(Object *object);
    void setReferencePosition(const Vector &position);
       

    //writing on file
    void positionsToFile(const std::string, const std::string) const;
    void energyToFile(const std::string, const std::string,int) const;

private:
    std::vector<std::unique_ptr<Object>> m_objects;
    bool m_leapfrogInitialized = false;
    Object* m_referenceObject = nullptr;
    Vector m_referencePosition = Vector(0, 0);
};

std::ostream &operator<<(std::ostream &os, const System &system);
#endif