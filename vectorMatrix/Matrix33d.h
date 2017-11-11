#ifndef __MATRIX33D_H__
#define __MATRIX33D_H__

/*
 * Cette classe représente les matrice des tranformation 2D en coordonnées
 * homogènes (matrices 3x3)
 */

#include "Array.h"
#include "Vector.h"
#include "Utils.h"

class Matrix33d
{
protected:
    Array<9,double> data_;  // stockage dans un seul array de 9 doubles

public:
	// constructeur vide (crée une matrice identité)
    	Matrix33d();

    	// opérateur d'accès (surcharge de () pour éviter de passer par une classe proxy [])
    	double operator ()(const int i, const int j) const;

    	// version non const
    	double& operator ()(const int i, const int j);

    	// opérateur d'affectation
    	void operator =(const Matrix33d& m);

    	// retourne l'inverse de la matrice courante
    	Matrix33d inverse();

    	// retourne la matrice de translation statique de coefficient (dx,dy)
    	Matrix33d staticTranslation(const double dx, const double dy);

    	// retourne la matrice de rotation statique d'angle alpha (degrès)
    	Matrix33d staticRotation(const double alpha);

    	// retourne la matrice d'homothétie statique de coefficient (hx,hy)
    	Matrix33d staticShrink(const double hx, const double hy);
};

// multiplication par un vecteur 3D (2D + coordonnée homogène) de flottant
Vec3f operator *(const Vec3f& v, const Matrix33d& m);

// idem dans l'autre sens
Vec3f operator *(const Matrix33d& m, const Vec3f& v);

// application d"une matrice de transformation à un vecteur 2D
Vec3f operator *(const Vec2f& v, const Matrix33d& m);

// idem dans l'autre sens
Vec3f operator *(const Matrix33d& m, const Vec2f& v);

#endif
