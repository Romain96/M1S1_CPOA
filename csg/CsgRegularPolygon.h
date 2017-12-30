#ifndef __CSGREGULARPOLYGON_H__
#define __CSGREGULARPOLYGON_H__

#include "Vector.h"
#include "Utils.h"
#include "BoundingBox.h"

// représente les polygones réguliers de plus de 2 sommets
class CsgRegularPolygon
{
protected:
    int _vertexNumber;
    Vec2f _center;
    float _diameter;
    BoundingBox _boundingBox;

public:
    // constructeur
    CsgRegularPolygon(int vertexNumber , Vec2f& center);

    // getters
    int getVertexNumber();
    Vec2f& getCenter();
    BoundingBox& getBoundingBox();

    // setters
    void setVertexNumber(int vertexNumber);
    void setCenter(Vec2f& center);
    void setBoundingBox(BoundingBox& bb);
};

#endif // __CSGREGULARPOLYGON_H__
