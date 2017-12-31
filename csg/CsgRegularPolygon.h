#ifndef __CSGREGULARPOLYGON_H__
#define __CSGREGULARPOLYGON_H__

#include "Vector.h"
#include "Matrix33d.h"
#include "Utils.h"
#include "BoundingBox.h"
#include "CsgPrimitive.h"

// représente les polygones réguliers de plus de 2 sommets
class CsgRegularPolygon : public CsgPrimitive
{
protected:
    int _vertexNumber;

public:
    // constructeur
    CsgRegularPolygon(int vertexNumber , Vec2f& center, float distanceToOrigin);

    // getters
    int getVertexNumber();

    // setters
    void setVertexNumber(int vertexNumber);
};

#endif // __CSGREGULARPOLYGON_H__
