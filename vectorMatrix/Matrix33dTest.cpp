#include "Vector.h"
#include "Matrix33dTest.h"
#include "Matrix33d.h"
#include "Utils.h"
#include <cmath>
#include <iostream>

// test de l'inversion d'une matrice
bool testInverse()
{
	Matrix33d m1;   // matrice identité
	// matrice ((3, 0, 2), (2, 0, -2), (0, 1, 1))
    	m1(0,0) = 3.0;
    	m1(0,1) = 0.0;
    	m1(0,2) = 2.0;
    	m1(1,0) = 2.0;
    	m1(1,1) = 0.0;
    	m1(1,2) = -2.0;
    	m1(2,0) = 0.0;
    	m1(2,1) = 1.0;
    	m1(2,2) = 1.0;

    	// inversion de la matrice
    	Matrix33d m2 = m1.inverse();

    	// vérification donne normalement la matrice (0.2, 0.2, 0, -0.2, 0.3, 1, 0.2, -0.3, 0)
    	if( (m2(0,0)-0.2)<1e-9 && (m2(0,1)-0.2)<1e-9 && m2(0,2)<1e-9 &&
		(m2(1,0)+0.2)<1e-9 && (m2(1,1)-0.3)<1e-9 && (m2(1,2)-1.0)<1e-9 &&
            	(m2(2,0)-0.2)<1e-9 && (m2(2,1)+0.3)<1e-9 && m2(2,2)<1e-9 )
    	{
        	return true;
    	}
    	else
    	{
        	return false;
    	}
}

// test de la matrice de translation
bool testTranslationStatique()
{
    	Matrix33d m;
    	Matrix33d trans = m.staticTranslation(1.0, 2.0);

    	// vérification donne normalement la matrice (1.0, 0, 0, 0, 2.0, 0, 0, 0, 1.0)
    	if( (trans(0,0)-1.0)<1e-9 && trans(0,1)<1e-9 && trans(0,2)<1e-9 &&
		trans(1,0)<1e-9 && (trans(1,1)-1.0)<1e-9 && trans(1,2)<1e-9 &&
            	(trans(2,0)-1.0)<1e-9 && (trans(2,1)-2.0)<1e-9 && (trans(2,2)-1.0)<1e-9 )
    	{
        	return true;
    	}
    	else
    	{
        	return false;
    	}
}

// test de la matrice de rotation
bool testRotationStatique()
{
    	Matrix33d m;
    	Matrix33d rot = m.staticRotation(45.0);

    	// vérification donne normalement la matrice (cos(45), sin(45), 0, -sin(45), cos(45), 0, 0, 0, 1.0)
    	if( (rot(0,0)-std::cos(45.0))<1e-9 && (rot(0,1)+std::sin(45.0))<1e-9 && rot(0,2)<1e-9 &&
            	(rot(1,0)-std::sin(45.0))<1e-9 && (rot(1,1)-std::cos(45.0))<1e-9 && rot(1,2)<1e-9 &&
            	rot(2,0)<1e-9 && rot(2,1)<1e-9 && (rot(2,2)-1.0)<1e-9 )
    	{
        	return true;
    	}
    	else
    	{
        	return false;
    	}
}

// test de la matrice d'homothétie
bool testHomothetieStatique()
{
    	Matrix33d m;
    	Matrix33d homo = m.staticShrink(1.0,2.0);

    	// vérification donne normalement la matrice (0, 0, 1.0, 0, 0, 2.0, 0, 0, 1.0)
    	if( (m(0,0)-1.0)<1e-9 && m(0,1)<1e-9 && m(0,2)<1e-9 &&
            	m(1,0)<1e-9 && (m(1,1)-2.0)<1e-9 && m(1,2)<1e-9 &&
            	m(2,0)<1e-9 && m(2,1)<1e-9 && (m(2,2)-1.0)<1e-9 )
    	{
        	return true;
    	}
    	else
    	{
        	return false;
    	}
}

// test de la multiplication d'un Vec3f par une Matrix33d
bool testMultiplicationVec3fMatrix33d()
{
	// déclaration et affectation d'un Vec3f et d'une Matrix33d
	Vec3f v;
	Matrix33d m;

	// vecteur (1.0, 2.5, 5.0)
	v[0] = 1.0; 
	v[1] = 2.5;
	v[2] = 5.0;

	// matrice ((1, 2, 3), (4, 5, 6), (7, 8, 9))
	m(0,0) = 1.0; m(0,1) = 2.0; m(0,2) = 3.0;
	m(1,0) = 4.0; m(1,1) = 5.0; m(1,2) = 6.0;
	m(2,0) = 7.0; m(2,1) = 8.0; m(2,2) = 9.0;

	// application de la multiplication
	Vec3f res = v*m;

	// test de la multiplication (résultat est (46, 54.5, 63))
	if ( (res[0]-46.0)<1e-9 && (res[1]-54.5)<1e-9 && (res[2]-63.0)<1e-9 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

// test de la multiplication d'une Matrix33d par un Vec3f
bool testMultiplicationMatrix33dVec3f()
{
	// déclaration et affectation d'une Matrix33d et d'un Vec3f
	Matrix33d m;
	Vec3f v;

	// vecteur (1.0, 2.5, 5.0)
	v[0] = 1.0;
	v[1] = 2.5;
	v[2] = 5.0;

	// matrice ((1, 2, 3), (4, 5, 6), (7, 8, 9))
	m(0,0) = 1.0; m(0,1) = 2.0; m(0,2) = 3.0;
	m(1,0) = 4.0; m(1,1) = 5.0; m(1,2) = 6.0;
	m(2,0) = 7.0; m(2,1) = 8.0; m(2,2) = 9.0;

	// application de la multiplication
	Vec3f res = m*v;

	// test de la multiplication (résultat est (46, 54.5, 63))
	if ( (res[0]-46.0)<1e-9 && (res[1]-54.5)<1e-9 && (res[2]-63.0)<1e-9 )
	{
		return true;
	}
	else
	{
		return false;
	}
	//return false;
}

// test de la multiplication d'un Vec2f par une Matrix33d
bool testMultiplicationVec2fMatrix33d()
{
	// déclaration et affectation d'un Vec2f et d'une Matrix33d
	Vec2f v;
	Matrix33d m;

	// vecteur (1.0, 2.5) mais comme il sera transformé en coordonnées homogènes (1.0, 2.5, 1.0)
	v[0] = 1.0;
	v[1] = 2.0;

	// matrice ((1, 2, 3), (4, 5, 6), (7, 8, 9))
	m(0,0) = 1.0; m(0,1) = 2.0; m(0,2) = 3.0;
	m(1,0) = 4.0; m(1,1) = 5.0; m(1,2) = 6.0;
	m(2,0) = 7.0; m(2,1) = 8.0; m(2,2) = 9.0;

	// application de la multiplication
	Vec3f res = v*m;

	// test de la multiplication (résultat est (18, 22.5, 27))
	if ( (res[0]-18.0)<1e-9 && (res[1]-22.5)<1e-9 && (res[2]-27.0)<1e-9 )
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
// test de la multiplication d'une Matrix33d par un Vec2f
bool testMultiplicationMatrix33dVec2f()
{
	// déclaration et affectation d'un Matrix33d et d'un Vec2f
	Matrix33d m;
	Vec2f v;

	// vecteur (1.0, 2.5) mais il sera transformé en coordonnées homogènes (1.0, 2.5, 1.0)	
	v[0] = 1.0;
	v[1] = 2.5;
	
	// matrice ((1, 2, 3), (4, 5, 6), (7, 8, 9))
	m(0,0) = 1.0; m(0,1) = 2.0; m(0,2) = 3.0;
	m(1,0) = 4.0; m(1,1) = 5.0; m(1,2) = 6.0;
	m(2,0) = 7.0; m(2,1) = 8.0; m(2,2) = 9.0; 

	// application de la multiplication
	Vec3f res = m*v;

	// test de la multiplication (résultat est (18, 22.5, 27))
	if ( (res[0]-18.0)<1e-9 && (res[1]-22.5)<1e-9 && (res[2]-27.0)<1e-9 )
	{
		return true;
	}
	else
	{
		return false;
 	}
}
