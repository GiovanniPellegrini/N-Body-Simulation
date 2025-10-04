#include "Comet.h"
#include "Star.h"
#include <algorithm>

// string representation
std::string Comet::str() const
{
    std::ostringstream oss;
    oss << "Comet" << std::endl
        << Object::str();
    return oss.str();
}

// set the relevant radius of the comet using the Hill radius. If the comet has no parents, the relevant radius is set to 0.
void Comet::setRelevantHillRadius()
{
    if (m_parents.empty())
    {
        return;
    }
    double distance = (m_position - m_parents[0]->getPosition()).getModule();
    double mass_parent = m_parents[0]->getMass();
    double mass_planet = m_mass;
    double hill_radius = distance * pow(mass_planet / (3 * mass_parent), 1.0 / 3.0);
    m_relevantRadius = hill_radius;
}

// Important objects: return relevant objects for the simulation
std::vector<Object *> Comet::getRelevantObjects(const System &system) const
{
    std::vector<Object *> relevantObjects;
    // For a Comet, we consider all the object which are in the R_bias radius
    for (Object *object : system.getAllObjects())
    {
        if (object == this)
            continue;
        double distanceSquared = (object->getPosition() - m_position).getModuleSquared();
        if (distanceSquared < object->getRelevantRadius())
        {
            relevantObjects.push_back(object);
        }
    }
    std::sort(relevantObjects.begin(), relevantObjects.end());
    relevantObjects.erase(std::unique(relevantObjects.begin(), relevantObjects.end()), relevantObjects.end());
    return relevantObjects;
}

std::ostream &operator<<(std::ostream &os, const Comet &obj)
{
    os << obj.str();
    return os;
}
