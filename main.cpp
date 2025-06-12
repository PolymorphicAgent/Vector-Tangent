#include "Vector.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <map>

#include <cstdint>  // for std::uint32_t
#include <cstring>  // for std::memcpy

bool g_precision;

//the famous algorithm!
float Q_rsqrt(float number) {
    float x2 = number * 0.5F;
    float y  = number;
    std::uint32_t i;

    //bit-level hack to reinterpret float bits as integers
    std::memcpy(&i, &y, sizeof(i));

    //some crap with logarithms (idk)
    i  = 0x5f3759df - (i >> 1);

    //convert bits back to float
    std::memcpy(&y, &i, sizeof(y));

    //one iteration of Newton's method for refinement
    y  = y * (1.5F - (x2 * y * y));
    
    //second iteration for further refinement
    if(g_precision) y  = y * (1.5F - (x2 * y * y));

    return y;
}

float inversePythagoreanTheorum(float x, float y){
    //a is the inverse square root of x^2 + y^2
    return Q_rsqrt(x*x + y*y);
}

Vector* bisectAndScale(Vector *a, Vector *b){
    //add the vectors
    Vector *result = new Vector(a->x()+b->x(), a->y()+b->y());
    
    //get the scale factor
    float a_ = inversePythagoreanTheorum(result->x(), result->y());
    
    //apply the scale factor
    result->scale(a_);
    
    return result;
}

//cross product for vector comparison
float cross(Vector *a, Vector *b) {
    return a->x() * b->y() - a->y() * b->x();
}

/// we know the angle because we keep cutting it in half
/// the vector is made to the same length as the original two using inverse pythagorean theourum
/// 1 = sqrt((ax)^2 + (ay)^2); then multiply x and y by a
/// once enough iterations have occured, tan(theta) = the slope of the vector.

int main() {
    
    //grab the angle, depth, and mode from the user
    float angle;
    std::cout<<"Enter an angle in degrees: ";
    std::cin>>angle;
    
    int depth;
    std::cout<<"How many bisections? (10 yeilds decent precision): "; //more --> better precision but longer compute time
    std::cin>>depth;
    
    std::string inp;
    std::cout<<"Favor precision or speed? ";
    std::cin>>inp;
    
    if(inp == "precision")  g_precision = true;
    else if(inp == "speed") g_precision = false;
    else {
        std::cout<<"Error: unrecognized input. Favoring precision...\n";
        g_precision = true;
    }
    
    //bound the angle between 0 and 360
    float boundedAngle = angle;
    int circles = 0;
    while(boundedAngle > 360){
        boundedAngle -= 360;
        circles++;
    }
    while(boundedAngle < 0){
        boundedAngle +=360;
        circles--;
    }
    
    //check the easy values of tangent
    if(boundedAngle == 0.0F){
        std::cout<<"tan(0) = 0.";
        return 0;
    }
    else if(boundedAngle == 90.0F){
        std::cout<<"tan(90) is undefined.";
        return 0;
    }
    else if(boundedAngle == 180.0F){
        std::cout<<"tan(180) = 0.";
        return 0;
    }
    else if(boundedAngle == 270.0F){
        std::cout<<"tan(270) is undefined.";
        return 0;
    }
    else if(boundedAngle == 360.0F){
        std::cout<<"tan(360) = 0.";
        return 0;
    }
    
    //determine which quadrant the angle lies in, which gives us our starting vectors
    Vector *b1, *b2;
    float currentAngle;
    if(boundedAngle > 0.0F && boundedAngle < 90.0F){ //+
        //we are in quadrant 1
        b1 = new Vector(0.0F, 1.0F);
        b2 = new Vector(1.0F, 0.0F);
        currentAngle = 90.0F;
    }
    else if(boundedAngle > 90.0F && boundedAngle < 180.0F){ //-
        //we are in quadrant 2
        b1 = new Vector(-1.0F, 0.0F);
        b2 = new Vector(0.0F, 1.0F);
        currentAngle = 180.0F;
    }
    else if(boundedAngle > 180.0F && boundedAngle < 270.0F){ //+
        //we are in quadrant 3
        b1 = new Vector(0.0F, -1.0F);
        b2 = new Vector(-1.0F, 0.0F);
        currentAngle = 270.0F;
    }
    else { //-
        //we are in quadrant 4
        b1 = new Vector(1.0F, 0.0F);
        b2 = new Vector(0.0F, -1.0F);
        currentAngle = 360.0F;
    }
    
    //begin iterating!
    float cutAngle = 90.0F;
    Vector *finalVector = nullptr;
    for(int i = 0; i<depth; i++){
        //bisect the vectors
        Vector *bisected = bisectAndScale(b1, b2);
        
        // this is the first bisection
        if(finalVector == nullptr){
            cutAngle /= 2;
            currentAngle -= cutAngle;
        }
        else if (cross(finalVector, bisected) > 0){ //If cross(a, b) > 0: b is counterclockwise of a
            cutAngle /= 2;
            currentAngle += cutAngle;
        }
        else {
            cutAngle /= 2;
            currentAngle -= cutAngle;
        }
        
        //make sure we have an updated finalVector
        finalVector = bisected;
        
        //check which side of the bisection is closest to the target angle (or if we've reached the target angle)
        if(boundedAngle == currentAngle){
            //we've reached the exact angle!
            float vecVal = bisected->slope();
            float exVal = std::tan(angle * M_PI / 180);
            
            std::cout<<"\n-----------------------------------------------------------------------------\nResults:\n";
            std::cout<<"After "<< i+1 <<" iterations, an angle of "<<currentAngle+(360*circles)<<" degrees was reached.\n\n";
            std::cout<<"tan("  <<angle<<") = "<<      vecVal       << " <- Vectors found the exact value! (Please excuse floating-point error...)\n";
            std::cout<<"tan("  <<angle<<") = "<<      exVal        << " <- This is the value found using std::tan.\n";
            if(std::abs(vecVal-exVal) > 0.1F) 
                std::cout      <<"\nGood Job. You broke the algorithm with weird numbers. Happy?\n";
            std::cout<<"-----------------------------------------------------------------------------";
            return 0;
        }
        else if(boundedAngle > currentAngle){
            //set the lower bound to the bisected vector
            b2 = bisected;
        }
        else{//boundedAngle is less than currentAngle
            //set the upper bound to the bisected vector
            b1 = bisected;
        }
    }
    
    //we didn't quite reach the target angle with the supplied number of iterations
    std::cout<<"\n-----------------------------------------------------------------------------\n";
    std::cout<<"After "<<depth<<" iterations, an angle of "<<currentAngle+(360*circles)<<" degrees was reached.\n\n";
    
    //at this point, our approximation of tangent should equal the slope of finalVector
    float vecVal = finalVector->slope();
    float exVal = std::tan(angle * M_PI / 180);
    
    std::cout<<"tan("<<angle<<") ≈ "<<vecVal<<" <--- This is the approximated value found with vector bisection."<<std::endl;
    std::cout<<"tan("<<angle<<") = "<<exVal<<" <--- This is the actual value found using std::tan."<<std::endl;
    if(std::abs(vecVal-exVal) > 0.1F) 
        std::cout<<"\nGood Job. You broke the algorithm with weird numbers. Happy?\n";
    std::cout<<"-----------------------------------------------------------------------------";
    return 0;
}
