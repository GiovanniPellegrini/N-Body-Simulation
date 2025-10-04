#include "Object.h"

/*
* Force Abstract Class. 
* It rapresent a generic force that can be applied to objects in a simulation.
*
*/

class Force
{
public:
    // constructor
    Force() = default;

    // destructor
    ~Force() = default;

    virtual Vector compute(const Object *, const Object *) const = 0;
};