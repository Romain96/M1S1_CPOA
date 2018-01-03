#ifndef __BOUNDINGBOX_H__
#define __BOUNDINGBOX_H__

#include "Vector.h"
#include "Utils.h"

// représente les boîtes englobantes en coordonnées 2D float (vec2f)
// les boîtes englobantes sont alignées sur les axes
class BoundingBox
{
protected:
    Vec2f _upper_left_point;
    Vec2f _upper_right_point;
    Vec2f _lower_left_point;
    Vec2f _lower_right_point;
public:
    // constructeurs
    BoundingBox();
    BoundingBox(Vec2f& ulp, Vec2f& urp, Vec2f& llp, Vec2f& lrp);

    // getters
    const Vec2f& getUpperLeftPoint() const;
    const Vec2f& getUpperRightPoint() const;
    const Vec2f& getLowerLeftPoint() const;
    const Vec2f& getLowerRightPoint() const;

    // setters
    void setUpperLeftPoint(Vec2f& ulp);
    void setUpperRightPoint(Vec2f& urp);
    void setLowerLeftPoint(Vec2f& llp);
    void setLowerRightPoint(Vec2f& lrp);
};

// union
BoundingBox& operator +(BoundingBox &bb1, BoundingBox &bb2);
// intersection
BoundingBox& operator ^(BoundingBox &bb1, BoundingBox &bb2);
// différence
BoundingBox& operator -(BoundingBox &bb1, BoundingBox &bb2);

#endif // __BOUNDINGBOX_H__
