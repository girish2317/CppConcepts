#include<iostream>
#include"privateClass.h"

class accessPrivate
{

public:

    accessPrivate(float x, float y, std::string shapeName = std::string())
    :accessPrivate(makeShape(x, y, shapeName))
    {
    }

    Point getPoint()
    {
        return shapePoints;
    }

    std::string getShape()
    {
        return shapeName;
    }

    

private: 

    static accessPrivate makeShape(float& x, float& y, std::string shapeName);

    accessPrivate(Point&& Point, std::string &shapeName)
    : shapePoints(std::move(Point))
    , shapeName{shapeName}
    {

    }

    float x1, y1;
    std::string shapeName;

    Point shapePoints;

};

accessPrivate accessPrivate::makeShape(float& x, float& y, std::string shapeNam)
{
    return accessPrivate(Point::makePolar(x, y), shapeNam);
}