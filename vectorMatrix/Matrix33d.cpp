#include "Matrix33d.h"
#include "Vector.h"
#include "Utils.h"
#include <cmath>

// Fonction         : Matrix33d (constructeur vide)
// Argument(s)		: /
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: initialise la matrice comme étant la matrice identité
Matrix33d::Matrix33d() : data_()
{
    	// retourne une matrice identité par défaut
    	this->data_[0] = 1.0;	// M[0][0]
    	this->data_[4] = 1.0;	// M[1][1]
    	this->data_[8] = 1.0;	// M[2][2]
}

// Fonction         : operator ()
// Argument(s)		: - i : un entier contenant le numéro de ligne de l'élément à retourner
//                    - j : un entier contenant le numéro de colonne de l'élément à retourner
// Valeur de retour	: un double contenant l'élément à la position (i,j) de la matrice
// Pré-condition(s)	: i et j entre 0 et 2
// Post-condition(s): /
// Commentaire(s)	: version const
double Matrix33d::operator ()(const int i, const int j) const
{
	// i et/ou i hors limite
	if (i < 0 || i > 2 || j < 0 || j > 2)
	{
		fprintf(stderr, "Matrix33d::operator () ERROR : i et/ou j hors limite (i=%d, j=%d)\n", i, j);
		exit(1);
	}
	
	// sinon ok
    	return this->data_[3*i + j];
}

// Fonction         : operator ()
// Argument(s)		: - i : un entier contenant le numéro de ligne de l'élément à retourner
//                    - j : un entier contenant le numéro de colonne de l'élément à retourner
// Valeur de retour	: un double contenant l'élément à la position (i,j) de la matrice
// Pré-condition(s)	: i et j entre 0 et 2
// Post-condition(s): /
// Commentaire(s)	: version non const
double& Matrix33d::operator ()(const int i, const int j)
{
    	// i et/ou i hors limite
	if (i < 0 || i > 2 || j < 0 || j > 2)
	{
		fprintf(stderr, "Matrix33d::operator () ERROR : i et/ou j hors limite (i=%d, j=%d)\n", i, j);
		exit(1);
	}
	
	// sinon ok
    	return this->data_[3*i + j];
}

// Fonction         : operator = (opérateur d'affectation)
// Argument(s)		: - m : une référence sur une matrix33d
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
void Matrix33d::operator =(const Matrix33d& m)
{
    	for (int i=0; i<9; i++)
    	{
        	this->data_[i] = m.data_[i];
    	}
}

// Fonction         : inverse
// Argument(s)		: /
// Valeur de retour	: une nouvelle matrice qui est l'inverse de la matrice courante si celle-ci est inversible
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
Matrix33d Matrix33d::inverse()
{
    	Matrix33d inv;
	
	// calcul du déterminant de la matrice courante
    	double det = this->data_[0] * this->data_[4] * this->data_[8] +
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

// Fonction         : staticTranslation
// Argument(s)		: - dx : un entier contenant la déplacement en x
//                    - dy : un entier contenant le déplacement en y
// Valeur de retour	: une nouvelle matrice de translation statique paramètrée par dx et dy
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
Matrix33d Matrix33d::staticTranslation(const double dx, const double dy)
{
    	Matrix33d trans;

	// modification en partant de la matrice identité
    	trans.data_[6] = dx;	// M[2][0]
    	trans.data_[7] = dy;	// M[2][1]

    	return trans;
}

// Fonction         : staticRotation
// Argument(s)		: - alpha : un double contenant la valeur de l'angle de rotation (sen trigonométrique)
// Valeur de retour	: une nouvelle matrice de rotation statique paramètrée par alpha
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
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

// Fonction         : staticShrink
// Argument(s)		: - hx : un entier contenant la coefficient d'homothétie en x
//                    - hy : un entier contenant le coefficient d'homothétie en y
// Valeur de retour	: une nouvelle matrice de homothétie statique paramètrée par hx et hy
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
Matrix33d Matrix33d::staticShrink(const double hx, const double hy)
{
    	Matrix33d homo;
	
	// en partant de la matrice identité
    	homo.data_[0] = hx;	// M[0][2]
    	homo.data_[4] = hy;	// M[1][2]

    	return homo;
}

// Fonction         : operator *
// Argument(s)		: - v : une référence sur un vec3f
//                    - m : une référence sur une matrix33d
// Valeur de retour	: un nouveau vec3f résultat de v*m
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
Vec3f operator *(const Vec3f& v, const Matrix33d& m)
{
	Vec3f res;

	res[0] = v[0] * m(0,0) + v[1] * m(1,0) + v[2] * m(2,0);
	res[1] = v[0] * m(0,1) + v[1] * m(1,1) + v[2] * m(2,1); 
	res[2] = v[0] * m(0,2) + v[1] * m(1,2) + v[2] * m(2,2);

	return res;
}

// Fonction         : operator *
// Argument(s)		: - m : une référence sur une matrix33d
//                    - v : une référence sur un vec3f
// Valeur de retour	: un nouveau vec3f résultat de m*v
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: idem mais dans l'autre sens
Vec3f operator *(const Matrix33d& m, const Vec3f& v)
{
	Vec3f res;

	res[0] = v[0] * m(0,0) + v[1] * m(1,0) + v[2] * m(2,0);
	res[1] = v[0] * m(0,1) + v[1] * m(1,1) + v[2] * m(2,1);
	res[2] = v[0] * m(0,2) + v[1] * m(1,2) + v[2] * m(2,2);

	return res;
}

// Fonction         : operator *
// Argument(s)		: - v : une référence sur un vec2f
//                    - m : une référence sur une matrix33d
// Valeur de retour	: un nouveau vec3f résultat de v*m
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: résultat en coordonnées homogènes
Vec3f operator *(const Vec2f& v, const Matrix33d& m)
{
	Vec3f res;

	// remplacement de v[2] par 1.0 (coordonnée homogène)
	res[0] = v[0] * m(0,0) + v[1] * m(1,0) + 1.0 * m(2,0);
	res[1] = v[1] * m(0,1) + v[1] * m(1,1) + 1.0 * m(2,1);
	res[2] = v[2] * m(0,2) + v[1] * m(1,2) + 1.0 * m(2,2);	

	return res;
}

// Fonction         : operator *
// Argument(s)		: - m : une référence sur une matrix33d
//                    - v : une référence sur un vec2f
// Valeur de retour	: un nouveau vec3f résultat de v*m
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: résultat en coordonnées homogènes, idem mais dans l'autre sens
Vec3f operator *(const Matrix33d& m, const Vec2f& v)
{
	Vec3f res;

	// replacement de v[2] par 1.0 (coordonnée homogène)
	res[0] = v[0] * m(0,0) + v[1] * m(1,0) + 1.0 * m(2,0);
	res[1] = v[0] * m(0,1) + v[1] * m(1,1) + 1.0 * m(2,1);
	res[2] = v[0] * m(0,2) + v[1] * m(1,2) + 1.0 * m(2,2);

	return res;
}
