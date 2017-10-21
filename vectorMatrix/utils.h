#ifndef __UTILS_H__
#define __UTILS_H__

/*
 * Ce fichier contient quelques définitions de types
 * notamment pour les classes templates Array/Vector/Matrix33d
 */

#include "vector.h"

// défitinions des types de vecteurs VecDT pour D = 2,3,4 et T = int,float

using Vec2i = Vector<2,int>;
using Vec3i = Vector<3,int>;
using Vec4i = Vector<4,int>;

using Vec2f = Vector<2,float>;
using Vec3f = Vector<3,float>;
using Vec4f = Vector<4,float>;

#endif