#ifndef __CSGREGULARPOLYGON_H__
#define __CSGREGULARPOLYGON_H__

#include "Vector.h"
#include "Matrix33d.h"
#include "Utils.h"
#include "BoundingBox.h"
#include "CsgPrimitive.h"
#include <iostream>

// représente les polygones réguliers de plus de 2 sommets
class CsgRegularPolygon : public CsgPrimitive
{
protected:
    int _vertexNumber;
    Vec2f *_vertexList;
    int _startingAngle;

public:
    // constructeur
    CsgRegularPolygon(int vertexNumber , Vec2f& center, float distanceToOrigin);

    // getters
    int getVertexNumber();

    // setters
    void setVertexNumber(int vertexNumber);

    // méthodes
    bool isInsidePrimitive(Vec2f &point);
    void updateBoundingBox(Vec2f& center, int tx, int ty, int angle, double scale);
};

#endif // __CSGREGULARPOLYGON_H__
