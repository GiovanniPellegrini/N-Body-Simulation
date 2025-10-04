#include "Planet.h"
#include "Star.h"
#include <algorithm>

// string representation
std::string Planet::str() const
{
    std::ostringstream oss;
    oss << "Planet" << std::endl
        << Object::str();
    return oss.str();
}

// set the relevant radius of the planet using the Hill radius. If the planet has no parents, the relevant radius is set to 0.
void Planet::setRelevantHillRadius()
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
std::vector<Object *> Planet::getRelevantObjects(const System &system) const
{
    if (!m_cacheFilled)
    {
        m_relevantObjects.clear();
        // For a planet, we consider all the stars in the system as relevant
        for (Object *object : system.getAllObjects())
        {

            if (dynamic_cast<Star *>(object))
            {
                m_relevantObjects.push_back(object);
            }
        }
        // We also consider all the planets orbiting around the same parent as relevant
        for (Object *parent : this->getParents())
        {
            for (Object *child : parent->getChildren())
            {
                if (child != this && dynamic_cast<Planet *>(child))
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

std::ostream &operator<<(std::ostream &os, const Planet &obj)
{
    os << obj.str();
    return os;
}
