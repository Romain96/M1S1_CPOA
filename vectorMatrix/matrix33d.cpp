#include "matrix33d.h"
#include "vector.h"
#include "utils.h"
#include <cmath>

Matrix33d::Matrix33d() : data_()
{
    	// retourne une matrice identité par défaut
    	this->data_[0] = 1.0;	// M[0][0]
    	this->data_[4] = 1.0;	// M[1][1]
    	this->data_[8] = 1.0;	// M[2][2]
}

// opérateur d'accès version const
double Matrix33d::operator ()(const int i, const int j) const
{
    	return this->data_[3*i + j];
}

// version non const

double& Matrix33d::operator ()(const int i, const int j)
{
    	return this->data_[3*i + j];
}

// opérateur d'affectation d'une matrice 33 à une autre matrice 33
void Matrix33d::operator =(const Matrix33d& m)
{
    	for (int i=0; i<9; i++)
    	{
        	this->data_[i] = m.data_[i];
    	}
}

// retourne l'inverse de la matrice si celle-ci est inversible
Matrix33d Matrix33d::inverse()
{
    	Matrix33d inv;
	
	// calcul du déterminant de la matrice courante
    	int det = this->data_[0] * this->data_[4] * this->data_[8] +
		this->data_[1] * this->data_[5] * this->data_[6] +
            	this->data_[2] * this->data_[3] * this->data_[7] -
            	this->data_[2] * this->data_[4] * this->data_[6] -
            	this->data_[0] * this->data_[5] * this->data_[7] -
            	this->data_[1] * this->data_[3] * this->data_[8];

	// si le déterminant est nul, la matrice n'est pas inversible
    	if (det == (double)0.0)
    	{
        	// TODO : revoyer une erreur ???
        	return inv; // id pour l'instant
    	}

	// calcul des composantes de la matrice inverse
    	inv.data_[0] = (this->data_[4] * this->data_[8] - this->data_[5] * this->data_[7]) / det;
    	inv.data_[3] = -(this->data_[3] * this->data_[8] - this->data_[6] * this->data_[5]) / det;
    	inv.data_[6] = (this->data_[3] * this->data_[7] - this->data_[6] * this->data_[4]) / det;

    	inv.data_[1] = -(this->data_[1] * this->data_[8] - this->data_[7] * this->data_[2]) / det;
    	inv.data_[4] = (this->data_[0] * this->data_[8] - this->data_[6] * this->data_[2]) / det;
    	inv.data_[7] = -(this->data_[0] * this->data_[7] - this->data_[6] * this->data_[1]) / det;

    	inv.data_[2] = (this->data_[1] * this->data_[5] - this->data_[4] * this->data_[2]) / det;
    	inv.data_[5] = -(this->data_[0] * this->data_[5] - this->data_[3] * this->data_[2]) / det;
    	inv.data_[8] = (this->data_[0] * this->data_[4] - this->data_[3] * this->data_[1]) / det;

    	return inv;
}

// Retourne une matrice de translation statique paramétrée par le déplacement en x et en y
Matrix33d Matrix33d::staticTranslation(const double dx, const double dy)
{
    	Matrix33d trans;

	// modification en partant de la matrice identité
    	trans.data_[6] = dx;	// M[2][0]
    	trans.data_[7] = dy;	// M[2][1]

    	return trans;
}

// retourne une matrice de rotation statique paramétrée par l'angle alpha
Matrix33d Matrix33d::staticRotation(const double alpha)
{
	Matrix33d rot;

	// en partant de la matrice identité
	// matrice de rotation est ((cos(a), -sin(a), 0), (sin(a), cos(a), 0), (0, 0, 1))
    	rot.data_[0] = std::cos(alpha);
    	rot.data_[1] = -std::sin(alpha);
    	rot.data_[3] = std::sin(alpha);
    	rot.data_[4] = std::cos(alpha);

    return rot;
}

// retourne une matrice d'homothétie statique paramétrée par le coefficient en x et en y
Matrix33d Matrix33d::staticShrink(const double hx, const double hy)
{
    	Matrix33d homo;
	
	// en partant de la matrice identité
    	homo.data_[0] = hx;	// M[0][2]
    	homo.data_[4] = hy;	// M[1][2]

    	return homo;
}

// effectue la multiplication d'un vecteur de float 3D par une matrice 33 double
Vec3f operator *(const Vec3f& v, const Matrix33d& m)
{
	Vec3f res;

	res[0] = v[0] * m(0,0) + v[1] * m(1,0) + v[2] * m(2,0);
	res[1] = v[0] * m(0,1) + v[1] * m(1,1) + v[2] * m(2,1); 
	res[2] = v[0] * m(0,2) + v[1] * m(1,2) + v[2] * m(2,2);

	return res;
}

// idem dans l'autre sens
Vec3f operator *(const Matrix33d& m, const Vec3f& v)
{
	Vec3f res;

	res[0] = v[0] * m(0,0) + v[1] * m(1,0) + v[2] * m(2,0);
	res[1] = v[0] * m(0,1) + v[1] * m(1,1) + v[2] * m(2,1);
	res[2] = v[0] * m(0,2) + v[1] * m(1,2) + v[2] * m(2,2);

	return res;
}

// application d'une matrice de transformation à un vecteur 2D float
Vec3f operator *(const Vec2f& v, const Matrix33d& m)
{
	Vec3f res;

	// remplacement de v[2] par 1.0 (coordonnée homogène)
	res[0] = v[0] * m(0,0) + v[1] * m(1,0) + 1.0 * m(2,0);
	res[1] = v[1] * m(0,1) + v[1] * m(1,1) + 1.0 * m(2,1);
	res[2] = v[2] * m(0,2) + v[1] * m(1,2) + 1.0 * m(2,2);	

	return res;
}

// idem dans l'autre sens
Vec3f operator *(const Matrix33d& m, const Vec2f& v)
{
	Vec3f res;

	// replacement de v[2] par 1.0 (coordonnée homogène)
	res[0] = v[0] * m(0,0) + v[1] * m(1,0) + 1.0 * m(2,0);
	res[1] = v[0] * m(0,1) + v[1] * m(1,1) + 1.0 * m(2,1);
	res[2] = v[0] * m(0,2) + v[1] * m(1,2) + 1.0 * m(2,2);

	return res;
}
