#include "TestMass.h"
#include <algorithm>

std::string TestMass::str() const
{
    std::ostringstream oss;
    oss << "Test Mass" << std::endl
        << Object::str();
    return oss.str();
}

// Important objects: return relevant objects for the simulation
std::vector<Object *> TestMass::getRelevantObjects(const System &system) const
{
    if (!m_cacheFilled)
    {
        m_relevantObjects.clear();
        // For a TestMass, we consider all the objects in the system as relevant
        for (Object *object : system.getAllObjects())
        {
            if (object != this && !dynamic_cast<TestMass *>(object))
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

std::ostream &operator<<(std::ostream &os, const TestMass &obj)
{
    os << obj.str();
    return os;
}
