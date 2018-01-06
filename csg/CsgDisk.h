#ifndef __CSGDISK_H__
#define __CSGDISK_H__

#include "BoundingBox.h"
#include "Vector.h"
#include "Matrix33d.h"
#include "Utils.h"
#include "CsgPrimitive.h"

// représente les disques de diamètre 1 centré sur l'origine (repère local)
class CsgDisk : public CsgPrimitive
{
    // pas de nouveaux attribus (le rayon est distanceToOrigin)
public:
    // constructeur
    CsgDisk(Vec2f& center, float radius);

    // getters
    float getRadius();

    // setters
    void setRadius(float radius);

    // méthodes
    bool isInsidePrimitive(Vec2f &point);
    void updateBoundingBox(int tx, int ty, int angle, double scale);
};

#endif // __CSGDISK_H__
