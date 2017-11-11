/*
* Cette classe template repr�sente un array param�tr� par
* N la taille de l'array (le nombre d'�l�ments qu'il peut contenir)
* T le type de donn�es de l'array
*/

#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <iostream>

using std::cout;
using std::endl;

template <int N, typename T> class Array
{
protected:
	T data_[N]; // tableau de N �l�ments de type T
	int size;   // la taille du tableau des gard� en m�moire

public:
	// constructeur
	Array() : data_{ 0,0 }, size(N)
	{
	}

	/*
	* Retourne la taille du de l'array
	*/
	int getSize() const
	{
		return this->size;
	}

	const T* data_pos() const
	{
		return data_;
	}

	/*
	* DEBUG : affiche le contenu de l'array
	*/
	void print() const
	{
		cout << "printing array : " << endl;
		for (int i = 0; i<this->size; i++)
		{
			cout << this->data_[i] << " ";
		}
		cout << " " << endl;
	}

	/*
	* Echange deux arrays
	*/
	void swap(Array<N, T>& a)
	{
		T tmp;
		for (int i = 0; i<this->size; i++)
		{
			tmp = this->data_[i];
			this->data_[i] = a.data_[i];
			a.data_[i] = tmp;
		}
	}

	/*
	* Op�rateur d'acc�s : retourne le i�me �l�ment de l'array courant
	*/
	T operator [](const int i) const
	{
		if (i >= 0 && i<this->size)
		{
			return this->data_[i];
		}
	}

	/*
	* Idem mais en version non const
	*/
	T& operator [](const int i)
	{
		return this->data_[i];
	}

	/*
	* Op�rateur d'affectation : affecte les donn�es de l'array
	* en param�tre � l'array courant
	*/
	void operator =(const Array<N, T>& a)
	{
		for (int i = 0; i<this->size; i++)
		{
			this->data_[i] = a.data_[i];
		}
	}

	/*
	* Op�rateur de comparaison : compare les donn�es de l'array
	* en param�tre avec celles de d'array courant
	*/
	bool operator ==(const Array<N, T>& a)
	{
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
