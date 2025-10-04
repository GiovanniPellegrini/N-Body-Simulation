#ifndef VECTOR_H
#define VECTOR_H


#include <math.h>
#include <iostream>
#include <iomanip>



class Vector{
    public:
    //constructors
    Vector()=default;
    Vector(double x, double y): m_x(x), m_y(y){};
    //destructor
     virtual ~Vector(){};

    //copy constructor
    Vector(const Vector& v): m_x(v.m_x), m_y(v.m_y){};
    Vector& operator=(const Vector&) = default;
    
    // string representation
    std::string str() const;

    //methods
    double getX() const { return m_x; }
    double getY() const { return m_y; }

    double getModule() const;
    double getAngle() const;
    double getModuleSquared() const;

    void setX(double x) { m_x = x; }
    void setY(double y) { m_y = y; }

    

    // operator overloads
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(double scalar) const;
    bool operator==(const Vector& v) const;



    private:
        double m_x;
        double m_y;
};
std::ostream& operator<<(std::ostream& os, const Vector& v);
#endif