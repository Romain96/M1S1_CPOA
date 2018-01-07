/*
* Classe vector template �tendant la classe template array
* N le nombre d'�l�ments
* T le type des �l�ments
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
	// Pr�-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: initialise un vector en appelant le constructeur de array
	Vector() : Array<N, T>()
	{
		this->size = N;
	}

    // Fonction         : operator []
	// Argument(s)		: - i : un entier contenant l'indice de l'�l�ment � retourner
	// Valeur de retour	: une valeur de type T contenant le i�me �l�ment du vecteur
	// Pr�-condition(s)	: i doit �tre positif et inf�rieur � la taille du vector
    // Post-condition(s): /
	// Commentaire(s)	: version const
	T operator [](const int i) const
	{
		// indice hors limite
		if (i < 0)
		{
			fprintf(stderr, "Vector::operator [] ERROR : indice n�gatif (%d)\n", i);
			exit(1);
		}
		if (i > this->size)
		{
			fprintf(stderr, "Vector::operator [] ERROR : indice sup�rieur � la taille du vector (%d >= %d)\n", i, this->size);
			exit(1);
		}

		// sinon ok
		return this->data_[i];
	}

    // Fonction         : operator []
	// Argument(s)		: - i : un entier contenant l'indice de l'�l�ment � retourner
	// Valeur de retour	: une valeur de type T contenant le i�me �l�ment du vector
	// Pr�-condition(s)	: i doit �tre positif et inf�rieur � la taille du vector
    // Post-condition(s): /
	// Commentaire(s)	: version non const de la pr�c�dente
	T& operator [](const int i)
	{
		return this->data_[i];
	}

    // Fonction         : operator == (op�rateur de comparaison)
	// Argument(s)		: - v : une r�f�rence sur un vector
	// Valeur de retour	: vrai si le contenu des vecteurs est identique, faux sinon
	// Pr�-condition(s)	: les deux vectors doivent avoir la m�me taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	bool operator ==(const Vector<N, T>& v)
	{
		// tailles diff�rentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::operator == ERROR : les vectors ont des tailles diff�rentes(%d et %d)\n", this->size, v.size);
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

    // Fonction         : operator = (op�rateur d'affectation)
	// Argument(s)		: - v : une r�f�rence sur un vector
	// Valeur de retour	: /
	// Pr�-condition(s)	: les vectors doivent avoir la m�me taille
    // Post-condition(s): /
	// Commentaire(s)	: affecte le vector courant des valeurs de v
	void operator =(const Vector<N, T>& v)
	{
		// tailles diff�rentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::operator = ERROR : les vectors ont des tailles diff�rentes(%d et %d)\n", this->size, v.size);
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
	// Pr�-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: affiche les valeurs du vector (DEBUG)
	void print()
	{
		Array<N, T>::print();
	}

    // Fonction         : operator + (op�rateur de somme)
	// Argument(s)		: - v : une r�f�rence sur un vector
	// Valeur de retour	: un nouveau vector r�sultat de la somme du vector courant et de v
	// Pr�-condition(s)	: les vectors doivent avoir la m�me taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	Vector<N, T> operator+(const Vector<N, T>& v)
	{
		// tailles diff�rentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::operator + ERROR : les vectors ont des tailles diff�rentes(%d et %d)\n", this->size, v.size);
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

    // Fonction         : operator - (op�rateur de diff�rence)
	// Argument(s)		: - v : une r�f�rence sur un vector
	// Valeur de retour	: un nouveau vector r�sultat de la diff�rence du vector courant et de v
	// Pr�-condition(s)	: les vectors doivent avoir la m�me taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	Vector<N, T> operator-(const Vector<N, T>& v)
	{
		// tailles diff�rentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::operator - ERROR : les vectors ont des tailles diff�rentes(%d et %d)\n", this->size, v.size);
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

    // Fonction         : operator += (op�rateur de somme et d'affectation)
	// Argument(s)		: - v : une r�f�rence sur un vector
	// Valeur de retour	: /
	// Pr�-condition(s)	: les vectors doivent avoir la m�me taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	void operator+=(const Vector<N, T>& v)
	{
		// tailles diff�rentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::operator += ERROR : les vectors ont des tailles diff�rentes(%d et %d)\n", this->size, v.size);
			exit(1);
		}

		// sinon ok
		for (int i = 0; i<this->getSize(); i++)
		{
			this->data_[i] = this->data_[i] + v[i];
		}
	}

    // Fonction         : operator -= (op�rateur de diff�rence et d'affectation)
	// Argument(s)		: - v : une r�f�rence sur un vector
	// Valeur de retour	: /
	// Pr�-condition(s)	: les vectors doivent avoir la m�me taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	void operator-=(const Vector<N, T>& v)
	{
		for (int i = 0; i<this->getSize(); i++)
		{
			this->data_[i] = this->data_[i] - v[i];
		}
	}

    // Fonction         : operator *= (op�rateur de produit et d'affectation)
	// Argument(s)		: - f : un flottant
	// Valeur de retour	: /
	// Pr�-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: multiplie les valeurs du vector courant par f
	void operator*=(const float f)
	{
		for (int i = 0; i<this->getSize(); i++)
		{
			this->data_[i] *= f;
		}
	}

    // Fonction         : operator /= (op�rateur de division et affectation)
	// Argument(s)		: - f : un flottant
	// Valeur de retour	: /
	// Pr�-condition(s)	: f != 0
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
	// Argument(s)		: - v : une r�f�rence sur un vector
	// Valeur de retour	: le r�sultat du produit scalaire du vector courant avec v
	// Pr�-condition(s)	: les vectors doivent avoir la m�me taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	int dot(const Vector<N, T>& v)
	{
		// tailles diff�rentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::dot ERROR : les vectors ont des tailles diff�rentes(%d et %d)\n", this->size, v.size);
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
	// Argument(s)		: - v : une r�f�rence sur un vector
	// Valeur de retour	: le r�sultat du produit vectoriel du vector courant avec v
	// Pr�-condition(s)	: les vectors doivent avoir la m�me taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	Vector<N, T> cross(const Vector<N, T>& v)
	{
		// tailles diff�rentes
		if (this->size != v.size)
		{
			fprintf(stderr, "Vector::dot ERROR : les vectors ont des tailles diff�rentes(%d et %d)\n", this->size, v.size);
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
// Argument(s)		: - v : une r�f�rence sur un vector
//                    - f : un flottant
// Valeur de retour	: un nouveau vector r�sultat du produit de v par f
// Pr�-condition(s)	: /
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
//                    - v : une r�f�rence sur un vector
// Valeur de retour	: un nouveau vector r�sultat du produit de f par v
// Pr�-condition(s)	: /
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
//                    - v : une r�f�rence sur un vector
// Valeur de retour	: un nouveau vector r�sultat de la division de f par v
// Pr�-condition(s)	: /
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
// Argument(s)		: - v : une r�f�rence sur un vector
//                    - f : un flottant
// Valeur de retour	: un nouveau vector r�sultat de la division de v par f
// Pr�-condition(s)	: /
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
