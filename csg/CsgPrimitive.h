#ifndef __CSGPRIMITIVE_H__
#define __CSGPRIMITIVE_H__

#include "Vector.h"
#include "Utils.h"
#include "BoundingBox.h"

// Représente toutes les primitives graphiques
class CsgPrimitive
{
protected:
    Vec2f _center;
    float _distanceToOrigin;
    BoundingBox _boundingBox;
    int _previousTranslateX;
    int _previousTranslateY;

public:
    // constructeur
    CsgPrimitive(Vec2f center, float distanceToOrigin);

    // getters
    Vec2f& getCenter();
    float& getDistanceToOrigin();
    BoundingBox& getBoundingBox();

    // setters
    void setCenter(Vec2f& center);
    void setDistanceToOrigin(float distanceToOrigin);
    void setBoundingBox(BoundingBox& bb);

    // méthodes
    virtual bool isInsidePrimitive(Vec2f& point);
    virtual void updateBoundingBox(Vec2f& center, int tx, int ty, int angle, double scale);
    void applyTransfo();
};

#endif // __CSGPRIMITIVE_H__
