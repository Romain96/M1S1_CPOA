/*
* Classe vector template étendant la classe template array
* N le nombre d'éléments
* T le type des éléments
*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>
#include <cstdlib>
#include "Array.h"

template <int N, typename T> class Vector : public Array<N, T>
{
public:
    // Fonction         : Vector (constructeur vide)
	// Argument(s)		: /
	// Valeur de retour	: /
	// Pré-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: initialise un vector en appelant le constructeur de array
	Vector() : Array<N, T>()
	{
		this->size = N;
	}

    // Fonction         : operator []
	// Argument(s)		: - i : un entier contenant l'indice de l'élément à retourner
	// Valeur de retour	: une valeur de type T contenant le ième élément du vecteur
	// Pré-condition(s)	: i doit être positif et inférieur à la taille du vector
    // Post-condition(s): /
	// Commentaire(s)	: version const
	T operator [](const int i) const
	{
		// indice hors limite
		if (i < 0)
		{
			fprintf(stderr, "Vector::operator [] ERROR : indice négatif (%d)\n", i);
			exit(1);
		}
		if (i > this->size)
		{
			fprintf(stderr, "Vector::operator [] ERROR : indice supérieur à la taille du vector (%d >= %d)\n", i, this->size);
			exit(1);
		}

		// sinon ok
		return this->data_[i];
	}

    // Fonction         : operator []
	// Argument(s)		: - i : un entier contenant l'indice de l'élément à retourner
	// Valeur de retour	: une valeur de type T contenant le ième élément du vector
	// Pré-condition(s)	: i doit être positif et inférieur à la taille du vector
    // Post-condition(s): /
	// Commentaire(s)	: version non const de la précédente
	T& operator [](const int i)
	{
		return this->data_[i];
	}

    // Fonction         : operator == (opérateur de comparaison)
	// Argument(s)		: - v : une référence sur un vector
	// Valeur de retour	: vrai si le contenu des vecteurs est identique, faux sinon
	// Pré-condition(s)	: les deux vectors doivent avoir la même taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	bool operator ==(const Vector<N, T>& v)
	{
		// tailles différentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::operator == ERROR : les vectors ont des tailles différentes(%d et %d)\n", this->size, v.size);
			exit(1);
		}

		// sinon ok
		for (int i = 0; i<this->size; i++)
		{
			if (this->data_[i] != v.data_[i])
			{
				return false;
			}
		}
		return true;
	}

    // Fonction         : operator = (opérateur d'affectation)
	// Argument(s)		: - v : une référence sur un vector
	// Valeur de retour	: /
	// Pré-condition(s)	: les vectors doivent avoir la même taille
    // Post-condition(s): /
	// Commentaire(s)	: affecte le vector courant des valeurs de v
	void operator =(const Vector<N, T>& v)
	{
		// tailles différentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::operator = ERROR : les vectors ont des tailles différentes(%d et %d)\n", this->size, v.size);
			exit(1);
		}

		// sinon ok
		for (int i = 0; i<this->size; i++)
		{
			this->data_[i] = v.data_[i];
		}
	}

    // Fonction         : print
	// Argument(s)		: /
	// Valeur de retour	: /
	// Pré-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: affiche les valeurs du vector (DEBUG)
	void print()
	{
		Array<N, T>::print();
	}

    // Fonction         : operator + (opérateur de somme)
	// Argument(s)		: - v : une référence sur un vector
	// Valeur de retour	: un nouveau vector résultat de la somme du vector courant et de v
	// Pré-condition(s)	: les vectors doivent avoir la même taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	Vector<N, T> operator+(const Vector<N, T>& v)
	{
		// tailles différentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::operator + ERROR : les vectors ont des tailles différentes(%d et %d)\n", this->size, v.size);
			exit(1);
		}

		// sinon ok
		Vector<N, T> res;
		for (int i = 0; i<this->getSize(); i++)
		{
			res[i] = this->data_[i] + v[i];
		}
		return res;
	}

    // Fonction         : operator - (opérateur de différence)
	// Argument(s)		: - v : une référence sur un vector
	// Valeur de retour	: un nouveau vector résultat de la différence du vector courant et de v
	// Pré-condition(s)	: les vectors doivent avoir la même taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	Vector<N, T> operator-(const Vector<N, T>& v)
	{
		// tailles différentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::operator - ERROR : les vectors ont des tailles différentes(%d et %d)\n", this->size, v.size);
			exit(1);
		}
	
		// sinon ok
		Vector<N, T> res;
		for (int i = 0; i<this->getSize(); i++)
		{
			res[i] = this->data_[i] - v[i];
		}
		return res;
	}

    // Fonction         : operator += (opérateur de somme et d'affectation)
	// Argument(s)		: - v : une référence sur un vector
	// Valeur de retour	: /
	// Pré-condition(s)	: les vectors doivent avoir la même taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	void operator+=(const Vector<N, T>& v)
	{
		// tailles différentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::operator += ERROR : les vectors ont des tailles différentes(%d et %d)\n", this->size, v.size);
			exit(1);
		}

		// sinon ok
		for (int i = 0; i<this->getSize(); i++)
		{
			this->data_[i] = this->data_[i] + v[i];
		}
	}

    // Fonction         : operator -= (opérateur de différence et d'affectation)
	// Argument(s)		: - v : une référence sur un vector
	// Valeur de retour	: /
	// Pré-condition(s)	: les vectors doivent avoir la même taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	void operator-=(const Vector<N, T>& v)
	{
		for (int i = 0; i<this->getSize(); i++)
		{
			this->data_[i] = this->data_[i] - v[i];
		}
	}

    // Fonction         : operator *= (opérateur de produit et d'affectation)
	// Argument(s)		: - f : un flottant
	// Valeur de retour	: /
	// Pré-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: multiplie les valeurs du vector courant par f
	void operator*=(const float f)
	{
		for (int i = 0; i<this->getSize(); i++)
		{
			this->data_[i] *= f;
		}
	}

    // Fonction         : operator /= (opérateur de division et affectation)
	// Argument(s)		: - f : un flottant
	// Valeur de retour	: /
	// Pré-condition(s)	: f != 0
    // Post-condition(s): /
	// Commentaire(s)	: divise les valeurs du vector courant par f
	void operator/=(const float f)
	{
		// f nul
		if ((f - f) > 1e-9)
		{
			fprintf(stderr, "Vector::operator /= ERROR : division par 0 (%f)\n", f);
			exit(1);
		}

		// sinon ok
		for (int i = 0; i<this->getSize(); i++)
		{
			this->data_[i] /= f;
		}
	}

    // Fonction         : dot (produit scalaire)
	// Argument(s)		: - v : une référence sur un vector
	// Valeur de retour	: le résultat du produit scalaire du vector courant avec v
	// Pré-condition(s)	: les vectors doivent avoir la même taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	int dot(const Vector<N, T>& v)
	{
		// tailles différentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::dot ERROR : les vectors ont des tailles différentes(%d et %d)\n", this->size, v.size);
			exit(1);
		}

		// sinon ok
		int res = 0;
		for (int i = 0; i<this->getSize(); i++)
		{
			res += (int)this->data_[i] * (int)v[i];
		}
		return res;
	}

    // Fonction         : cross (produit vectoriel)
	// Argument(s)		: - v : une référence sur un vector
	// Valeur de retour	: le résultat du produit vectoriel du vector courant avec v
	// Pré-condition(s)	: les vectors doivent avoir la même taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	Vector<N, T> cross(const Vector<N, T>& v)
	{
		// tailles différentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::dot ERROR : les vectors ont des tailles différentes(%d et %d)\n", this->size, v.size);
			exit(1);
		}

		// sinon ok
		Vector<N, T> res;
		res[0] = this->data_[1] * v[2] - this->data_[2] * v[1];
		res[1] = this->data_[2] * v[0] - this->data_[0] * v[2];
		res[2] = this->data_[0] * v[1] - this->data_[1] * v[0];
		return res;
	}
};

// Fonction         : operator *
// Argument(s)		: - v : une référence sur un vector
//                    - f : un flottant
// Valeur de retour	: un nouveau vector résultat du produit de v par f
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
template <int N, typename T> Vector<N, T> operator*(Vector<N, T>& v, const float f)
{
	Vector<N, T> res;
	for (int i = 0; i<v.getSize(); i++)
	{
		res[i] = v[i] * f;
	}
	return res;
}

// Fonction         : operator *
// Argument(s)		: - f : un flottant
//                    - v : une référence sur un vector
// Valeur de retour	: un nouveau vector résultat du produit de f par v
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
template <int N, typename T> Vector<N, T> operator*(const float f, Vector<N, T>& v)
{
	Vector<N, T> res;
	for (int i = 0; i<v.getSize(); i++)
	{
		res[i] = v[i] * f;
	}
	return res;
}

// Fonction         : operator /
// Argument(s)		: - f : un flottant
//                    - v : une référence sur un vector
// Valeur de retour	: un nouveau vector résultat de la division de f par v
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
template <int N, typename T> Vector<N, T> operator/(const float f, Vector<N, T>& v)
{
	Vector<N, T> res;
	for (int i = 0; i<v.getSize(); i++)
	{
		res[i] = v[i] / f;
	}
	return res;
}

// Fonction         : operator /
// Argument(s)		: - v : une référence sur un vector
//                    - f : un flottant
// Valeur de retour	: un nouveau vector résultat de la division de v par f
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
template <int N, typename T> Vector<N, T> operator/(Vector<N, T>& v, const float f)
{
	Vector<N, T> res;
	for (int i = 0; i<v.getSize(); i++)
	{
		res[i] = v[i] / f;
	}
	return res;
}

#endif
