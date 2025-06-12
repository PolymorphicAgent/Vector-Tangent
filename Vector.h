#include <ostream>

class Vector{
public:
    //constructor declaration
    Vector(float x, float y);
    
    //setter declarations
    void setX(float i);
    void setY(float i);
    
    //getter declarations
    float x();
    float y();
    
    //scale function definition
    void scale(float a);
    //slope function definition
    float slope();
    
    //operator definition
    friend std::ostream& operator<<(std::ostream& os, Vector& v);
private:
    //member definitions
    float m_x, m_y;
};