/*
* Cette classe template représente un array paramétré par
* N la taille de l'array (le nombre d'éléments qu'il peut contenir)
* T le type de données de l'array
*/

#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

template <int N, typename T> class Array
{
protected:
	T data_[N]; // tableau de N éléments de type T
	int size;   // la taille du tableau des gardé en mémoire

public:
    // Fonction         : Array (constructeur vide)
	// Argument(s)		: /
	// Valeur de retour	: /
	// Pré-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: initialise la taille et l'array à 0
	Array() : data_{ 0,0 }, size(N)
	{}

    // Fonction         : getSize
	// Argument(s)		: /
	// Valeur de retour	: un entier contenant la taille actuelle de l'array
	// Pré-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: /
	int getSize() const
	{
		return this->size;
	}

    // Fonction         : data_pos
	// Argument(s)		: /
	// Valeur de retour	: un pointeur sur le tableau de données
	// Pré-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: /
	const T* data_pos() const
	{
		return data_;
	}

    // Fonction         : print
	// Argument(s)		: /
	// Valeur de retour	: /
	// Pré-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: affiche le contenu de l'array (DEBUG)
	void print() const
	{
		cout << "printing array : " << endl;
		for (int i = 0; i<this->size; i++)
		{
			cout << this->data_[i] << " ";
		}
		cout << " " << endl;
	}

    // Fonction         : swap
	// Argument(s)		: - a : une référence sur un array
	// Valeur de retour	: /
	// Pré-condition(s)	: les arrays doivent avoir la même taille
    // Post-condition(s): /
	// Commentaire(s)	: échange le contenu de l'array courant avec
	void swap(Array<N, T>& a)
	{
		// tailles différentes
		if (this->size != a.size)
		{
			fprintf(stderr, "Array::swap ERROR : tailles des array différentes (%d et %d)\n", this->size, a.size);
			exit(1);
		}

		T tmp;
		for (int i = 0; i<this->size; i++)
		{
			tmp = this->data_[i];
			this->data_[i] = a.data_[i];
			a.data_[i] = tmp;
		}
	}

    // Fonction         : operator []
	// Argument(s)		: - i : un entier contenant l'indice de l'élément à retourner
	// Valeur de retour	: un valeur de type T contenant le ième élément de l'array
	// Pré-condition(s)	: i doit être positif et inférieur à la taile de l'array
    // Post-condition(s): /
	// Commentaire(s)	: version const
	T operator [](const int i) const
	{
		// indice hors limite
		if (i < 0)
		{
			fprintf(stderr, "Array::operator [] ERROR : indice négatif (%d)\n", i);
			exit(1);
		}
		if (i >= this->size)
		{
			fprintf(stderr, "Array::operator [] ERROR : indice supérieur à la taille de l'array (%d >= %d)\n", i, this->size);
			exit(1);
		}
		// sinon ok
		return this->data_[i];
	}

    // Fonction         : operator []
	// Argument(s)		: - i : un entier contenant l'indice de l'élément à retourner
	// Valeur de retour	: une valeur de type T contenant le ième élément de l'array
	// Pré-condition(s)	: i doit être positif et inférieur à la taille de l'array
    // Post-condition(s): /
	// Commentaire(s)	: version non const de la précédente
	T& operator [](const int i)
	{
		// indice hors limite
		if (i < 0)
		{
			fprintf(stderr, "Array::operator [] ERROR : indice négatif (%d)\n", i);
			exit(1);
		}
		if (i > this->size)
		{
			fprintf(stderr, "Array::operator [] : indice supérieur à la taille de l'array (%d >= %d)\n", i, this->size);
		}
		// sinon ok
		return this->data_[i];
	}

    // Fonction         : operator =
	// Argument(s)		: - a : une référence sur un array
	// Valeur de retour	: /
	// Pré-condition(s)	: les deux arrays doivent avoir la même taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	void operator =(const Array<N, T>& a)
	{
		// arrays de tailles différentes
		if (this->size != a.size)
		{
			fprintf(stderr, "Array::operator = ERROR : les arrays sont de tailles différentes (%d et %d)\n", this->size, a.size);
			exit(1);
		}

		// sinon ok
		for (int i = 0; i<this->size; i++)
		{
			this->data_[i] = a.data_[i];
		}
	}

    // Fonction         : operator ==
	// Argument(s)		: - a : une référence sur un array
	// Valeur de retour	: vrai si le contenu des deux arrays est identique
	// Pré-condition(s)	: les arrays doivent avoir la même taille
    // Post-condition(s): /
	// Commentaire(s)	: /
	bool operator ==(const Array<N, T>& a)
	{
		// tailles différentes
		if (this->size != a.size)
		{
			fprintf(stderr, "Array::operator == ERREUR : les arrays sont de tailles différentes (%d et %d)\n", this->size, a.size);
			exit(1);
		}

		// sinon ok
		for (int i = 0; i<this->size; i++)
		{
			if (this->data_[i] != a.data_[i])
			{
				return false;
			}
		}
		return true;
	}
};

#endif
