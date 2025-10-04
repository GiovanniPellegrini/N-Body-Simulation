#include "Planet.h"
#include "Star.h"
#include "Moon.h"
#include <algorithm>

// string representation
std::string Moon::str() const
{
    std::ostringstream oss;
    oss << "Moon" << std::endl
        << Object::str();
    return oss.str();
}

// set the relevant radius of the moon using the Hill radius. if the moon has no parents, the relevant radius is set to 0.
void Moon::setRelevantHillRadius()
{
    if (m_parents.empty())
    {
        return;
    }
    const auto& planet = m_parents[0];
    
    double distance = (m_position - planet->getPosition()).getModule();
    double mass_parent = planet->getMass();
    double mass_planet = m_mass;
    double hill_radius = distance * pow(mass_planet / (3 * mass_parent), 1.0 / 3.0);
    m_relevantRadius = hill_radius;
}
// Important objects: return relevant objects for the simulation
std::vector<Object *> Moon::getRelevantObjects(const System &system) const
{
    if (!m_cacheFilled)
    {
        m_relevantObjects.clear();
        // For a moon, we consider all the stars and planets in the system as relevant
        for (Object *object : system.getAllObjects())
        {

            if (dynamic_cast<Star *>(object) || dynamic_cast<Planet *>(object))
            {
                m_relevantObjects.push_back(object);
            }
        }
        // Additionally, we consider all moons that are children of the same parents as relevant
        for (Object *parent : this->getParents())
        {
            for (Object *child : parent->getChildren())
            {
                if (child != this && dynamic_cast<Moon *>(child))
                {
                    m_relevantObjects.push_back(child);
                }
            }
        }

        std::sort(m_relevantObjects.begin(), m_relevantObjects.end());
        m_relevantObjects.erase(std::unique(m_relevantObjects.begin(), m_relevantObjects.end()), m_relevantObjects.end());
        m_cacheFilled = true;
    }
    return m_relevantObjects;
}

std::ostream &operator<<(std::ostream &os, const Moon &obj)
{
    os << obj.str();
    return os;
}
