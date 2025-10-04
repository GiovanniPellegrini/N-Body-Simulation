#include "System.h"
#include "Utils.hpp"
#include <filesystem>

void System::addObject(std::unique_ptr<Object> object)
{
    m_objects.push_back(std::move(object));
}

void System::addListObjects(std::vector<std::unique_ptr<Object>> objects)
{
    for (auto &obj : objects)
    {
        m_objects.push_back(std::move(obj));
    }
}

Object *System::getObject(size_t index) const
{
    if (index < m_objects.size())
    {
        return m_objects[index].get(); // raw non‑owning ptr
    }
    std::cerr << "Index " << index << " out of range" << std::endl;
    return nullptr;
}

std::vector<Object *> System::getAllObjects() const
{
    std::vector<Object *> view;
    view.reserve(m_objects.size());
    for (const auto &up : m_objects)
    {
        view.push_back(up.get());
    }
    return view;
}
size_t System::getNumberOfObjects() const
{
    return m_objects.size();
}

double System::getTotalKinetic() const
{
    double totalEnergy = 0.0;
    for (const auto &object : m_objects)
    {
        totalEnergy += object->getKineticEnergy();
    }
    return totalEnergy;
}

double System::getTotalPotential() const
{
    double totalEnergy = 0.0;
    int warning = 0;
    for (size_t i = 0; i < m_objects.size(); ++i)
    {
        for (size_t j = i + 1; j < m_objects.size(); ++j)
        {
            Vector difference = m_objects[i]->getPosition() - m_objects[j]->getPosition();
            if (difference == Vector(0, 0))
            {
                ++warning;
                std::cerr << "[WARNING] Objects '" << m_objects[i]->getName() << "' and '" << m_objects[j]->getName() << "' are overlapping" << std::endl;
                continue;
            }
            else
            {
                double distance = difference.getModule();
                double energy = -(PhysicsConstants::G * m_objects[i]->getMass() * m_objects[j]->getMass()) / distance;
                totalEnergy += energy;
            }
        }
    }
    return totalEnergy;
}

void System::setAllRelevantHillRadius()
{
    for (const auto &object : m_objects)
    {
        object->setRelevantHillRadius();
    }
}

void System::resetAllForces()
{
    for (const auto &object : m_objects)
    {
        object->resetForce();
    }
}

void System::computeAllForces(const Force &force)
{
    for (const auto &object_a : m_objects)
    {
        for (Object *object_b : object_a->getRelevantObjects(*this))
        {
            if (object_a.get() != object_b)
            {
                Vector forceVector = force.compute(object_a.get(), object_b);
                object_a->addForce(forceVector);
            }
        }
    }
}
void System::evolveAll(double dt, const Force &force, const bool useLeapfrog)
{
    if (!useLeapfrog)
    {
        resetAllForces();
        computeAllForces(force);
        for (const auto &object : m_objects)
        {
            object->evolve(dt);
        }
    }
    else
    {
        if (!m_leapfrogInitialized)
        {
            resetAllForces();
            computeAllForces(force);
            m_leapfrogInitialized = true;
        }
        // first half step and drift
        for (auto &obj : m_objects)
        {
            obj->evolvePreIntegrate(dt);
        }
        resetAllForces();
        computeAllForces(force);

        // second half step
        for (auto &obj : m_objects)
        {
            obj->evolvePostIntegrate(dt);
        }
    }
}

void System::setReferenceObject(Object *object)
{
    m_referenceObject = object;
}
void System::setReferencePosition(const Vector &position)
{
    m_referencePosition = position;
}

void System::positionsToFile(const std::string runname, const std::string filename) const
{

    std::filesystem::create_directory(runname);

    std::string fullPath = runname + "/" + filename;

    std::ofstream file;
    file.open(fullPath, std::ios_base::app);
    if (!file)
    {
        std::cerr << "Error opening file: " << fullPath << std::endl;
        return;
    }

    Vector origin = (m_referenceObject) ? m_referenceObject->getPosition() : m_referencePosition;

    for (const auto &obj : m_objects)
    {

        Vector relativePosition = obj->getPosition() - origin;

        file << obj->getName() << " " << relativePosition << std::endl;
    }
    file << "\n";
    file.close();
}

void System::energyToFile(const std::string runname, const std::string filename, int step) const
{

    std::filesystem::create_directory(runname);

    std::string fullPath = runname + "/" + filename;

    std::ofstream file;
    file.open(fullPath, std::ios_base::app);
    if (!file)
    {
        std::cerr << "Error opening file: " << fullPath << std::endl;
        return;
    }

    double kinetic = getTotalKinetic();
    double potential = getTotalPotential();
    double total = kinetic + potential;

    file << "Step " << step
         << " E_kin " << std::scientific << std::setprecision(15) << kinetic
         << " E_pot " << std::scientific << std::setprecision(15) << potential
         << " E_tot " << std::scientific << std::setprecision(15) << total
         << std::endl;
    file.close();
}

std::string System::str() const
{
    std::stringstream oss;
    std::stringstream ss;
    ss << "System:" << "\n"
       << "number of bodies=" << m_objects.size() << "\n"
       << "kinetic energy=" << getTotalKinetic() << "\n"
       << "potential energy=" << getTotalPotential() << "\n"
       << "total energy=" << getTotalKinetic() + getTotalPotential() << "\n";
    return ss.str();
}

std::ostream &operator<<(std::ostream &os, const System &system)
{
    os << system.str();
    return os;
}
