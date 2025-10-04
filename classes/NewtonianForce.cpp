#ifndef NEWTONIANFORCE_H
#define NEWTONIANFORCE_H

#include "Force.h"
#include "Utils.hpp"


/*
 * NewtonianForce class
 * Represents a standard gravitational force between two objects.
 * Inherits from the Force class.
 */

class NewtonianForce : public Force
{
public:
    Vector compute(const Object *a, const Object *b) const override 
    {
        Vector difference = b->getPosition() - a->getPosition();
        // Avoid division by zero
        double distance = difference.getModule();
        if(Utils::isEqual(distance,0)){
            return Vector(0,0);
        }
        double forceMagnitude = (PhysicsConstants::G *a->getMass() * b->getMass()) / (distance * distance);
        return difference * (forceMagnitude / distance);
    }
};

#endif // NEWTONIANFORCE_H  