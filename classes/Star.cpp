#include "Star.h"
#include "algorithm"

// string representation
std::string Star::str() const
{
    std::ostringstream oss;
    oss << "Star:" << std::endl
        << Object::str();
    return oss.str();
}

// Relevant of a star is infinite
void Star::setRelevantHillRadius()
{
    m_relevantRadius = std::numeric_limits<double>::infinity();
}

// Important objects: return relevant objects for the simulation
std::vector<Object *> Star::getRelevantObjects(const System &system) const
{
    if (!m_cacheFilled)
    {
        m_relevantObjects.clear();
        // For a star, we consider only stars in the system as relevant
        for (Object *object : system.getAllObjects())
        {
            if (object != this && dynamic_cast<Star *>(object))
            {
                m_relevantObjects.push_back(object);
            }
        }
        std::sort(m_relevantObjects.begin(), m_relevantObjects.end());
        m_relevantObjects.erase(std::unique(m_relevantObjects.begin(), m_relevantObjects.end()), m_relevantObjects.end());
        m_cacheFilled = true;
    }
    return m_relevantObjects;
}

std::ostream &operator<<(std::ostream &os, const Star &obj)
{
    os << obj.str();
    return os;
}
