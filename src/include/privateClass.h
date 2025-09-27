

#include<iostream>
#include<math.h>

/**
 * Notes: Using private constructors can help enforce certain design constraints and ensure that objects are created in a controlled manner. 
 * However, it also means that the class cannot be instantiated directly from outside the class or its friend classes. 
 * This can be useful in scenarios where you want to limit the creation of objects or implement specific design patterns
 */
class Point
{

private:
    float x1, y1;
    Point(float x, float y)
    : x1(x)
    , y1(y)
    {}

public:

    /**
    public static functions to create instances 
    */
    static Point makePolar(float r, float a)
    {
        return Point(r * cos(a), r*sin(a));
    }

    void display() {
        std::cout << "x: " << x1 << ", y: " << y1 << std::endl;
    }

};