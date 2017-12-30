#ifndef __CSGDISK_H__
#define __CSGDISK_H__

#include "BoundingBox.h"
#include "Vector.h"
#include "Utils.h"

// représente les disques de diamètre 1 centré sur l'origine (repère local)
class CsgDisk
{
protected:
    float _diameter;
    Vec2f _center;
    BoundingBox _boundingBox;
public:
    // constructeur
    CsgDisk(Vec2f& center);

    // getters
    float getDiameter();
    Vec2f& getCenter();
    BoundingBox& getBoundingBox();

    // setters
    void setDiameter(float diameter);
    void setCenter(Vec2f& center);
    void setBoundingBox(BoundingBox& bb);
};

#endif // __CSGDISK_H__
