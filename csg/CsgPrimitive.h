#ifndef __CSGPRIMITIVE_H__
#define __CSGPRIMITIVE_H__

#include "Vector.h"
#include "Matrix33d.h"
#include "Utils.h"
#include "BoundingBox.h"

// Représente toutes les primitives graphiques
class CsgPrimitive
{
protected:
    Vec2f _center;
    float _distanceToOrigin;
    Matrix33d _matrix;
    BoundingBox _boundingBox;

public:
    // constructeur
    CsgPrimitive(Vec2f center, float distanceToOrigin);

    // getters
    Vec2f& getCenter();
    float& getDistanceToOrigin();
    Matrix33d& getMatrix();
    BoundingBox& getBoundingBox();

    // setters
    void setCenter(Vec2f& center);
    void setDistanceToOrigin(float distanceToOrigin);
    void setMatrix(Matrix33d& mat);
    void setBoundingBox(BoundingBox& bb);

    // méthodes
    virtual bool isInsidePrimitive(Vec2f& point);
};

#endif // __CSGPRIMITIVE_H__
