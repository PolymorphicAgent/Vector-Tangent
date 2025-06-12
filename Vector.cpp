#include "Vector.h"

//constructor
Vector::Vector(float _x, float _y){
    this->m_x = _x;
    this->m_y = _y;
}

//setters for x and y
void Vector::setX(float _x){this->m_x = _x;}
void Vector::setY(float _y){this->m_y = _y;}

//getters for x and y
float Vector::x(){return this->m_x;}
float Vector::y(){return this->m_y;}

//multiplies x and y by a
void Vector::scale(float a){
    this->m_x = this->m_x * a;
    this->m_y = this->m_y * a;
}

//returns the slope of the vector
float Vector::slope(){
    return this->m_y / this->m_x;
}

//for debugging purposes, outputs the vector in human-readable form
std::ostream& operator<<(std::ostream& os, Vector& v) {
    os << "<" << v.x() << ", " << v.y() << ">";
    return os;
}