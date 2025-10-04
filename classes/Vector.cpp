#include "Vector.h"
#include "Utils.hpp"


double Vector::getModule() const {
    return sqrt(m_x * m_x + m_y * m_y);
}
double Vector::getAngle() const {
    if (m_x == 0 && m_y == 0) {
        return 0;
    }
    return atan2(m_y, m_x);
}
double Vector::getModuleSquared() const {
    return m_x * m_x + m_y * m_y;
}


std::string Vector::str() const {
    std::ostringstream oss;
    oss << "(" << m_x << ", " << m_y << ")";
    return oss.str();
}

Vector Vector::operator+(const Vector& v) const {
    return Vector(m_x + v.m_x, m_y + v.m_y);
}
Vector Vector::operator-(const Vector& v) const {
    return Vector(m_x - v.m_x, m_y - v.m_y);
}
Vector Vector::operator*(double scalar) const {
    return Vector(m_x * scalar, m_y * scalar);
}
bool Vector::operator==(const Vector& v) const{
    return Utils::isEqual(m_x, v.m_x) && Utils::isEqual(m_y, v.m_y);
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << v.str();
    return os;
}