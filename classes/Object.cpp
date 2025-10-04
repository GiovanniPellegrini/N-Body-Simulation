#include "Object.h"
#include <sstream>

// constructor
Object::Object(const std::string &name, const Vector &position, const Vector &velocity, double mass)
    : m_position(position), m_velocity(velocity), m_mass(mass), m_name(name),m_cacheFilled(false), m_relevantRadius(0.0) {}

// string representation
std::string Object::str() const
{
    std::ostringstream oss;
    oss << "Name: " << m_name << "\n"
        << "Mass: " << m_mass << "\n"
        << "Position: " << m_position.str() << "\n"
        << "Velocity: " << m_velocity.str() << "\n"
        << "Kinetic Energy: " << getKineticEnergy() << "\n";
    return oss.str();
}

// methods
double Object::getMass() const
{
    return m_mass;
}
const Vector &Object::getPosition() const
{
    return m_position;
}
const Vector &Object::getVelocity() const
{
    return m_velocity;
}
const Vector &Object::getForce() const
{
    return m_force;
}
double Object::getKineticEnergy() const
{
    return 0.5 * m_mass * pow(m_velocity.getModule(), 2);
}
double Object::getRelevantRadius() const
{
    return m_relevantRadius;
}
std::string Object::getName() const
{
    return m_name;
}

void Object::setMass(double mass)
{
    m_mass = mass;
}
void Object::setPosition(const Vector &position)
{
    m_position = position;
}
void Object::setVelocity(const Vector &velocity)
{
    m_velocity = velocity;
}

void Object::addForce(const Vector &force)
{
    m_force = m_force + force;
}
void Object::resetForce()
{
    m_force = Vector(0, 0);
}

void Object::setRelevantRadius(double radius)
{
    m_relevantRadius = radius;
}



// Parent relationship
void Object::addParent(Object *parent)
{
    m_parents.push_back(parent);
}
const std::vector<Object *> &Object::getParents() const
{
    return m_parents;
}

// Children relationship
void Object::addChild(Object *child)
{
    m_children.push_back(child);
}
const std::vector<Object *> &Object::getChildren() const
{
    return m_children;
}

// evolution
void Object::evolve(double dt)
{
    // Update velocity based on the force applied
    Vector acceleration = m_force * (1.0 / m_mass);
    // std::cout<<"Vecchia velocità"<<m_velocity<<std::endl;
    m_velocity = m_velocity + acceleration * dt;
    // std::cout<<"Nuova velocità"<<m_velocity<<std::endl;
    //  Update position based on the new velocity
    m_position = m_position + m_velocity * dt;
}

// Pre-integration step: half-step update of velocity and position
void Object::evolvePreIntegrate(double dt)
{
    Vector acceleration = m_force * (1.0 / m_mass);
    m_velocity = m_velocity + acceleration * (dt * 0.5);
    m_position = m_position + m_velocity * dt;
}
// Post-integration step: half-step update of velocity
void Object::evolvePostIntegrate(double dt)
{
    Vector acceleration = m_force * (1.0 / m_mass);
    m_velocity = m_velocity + acceleration * (dt * 0.5);
}

std::ostream &operator<<(std::ostream &os, const Object &obj)
{
    os << obj.str();
    return os;
}
