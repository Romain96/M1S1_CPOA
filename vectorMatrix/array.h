/*
 * Cette classe template représente un array paramétré par  
 * N la taille de l'array (le nombre d'éléments qu'il peut contenir)
 * T le type de données de l'array
 */

#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <iostream>

using std::cout;
using std::endl;
 
template <int N, typename T> class Array
{
protected:
	T data_[N]; // tableau statique de N valeurs de type T
    	int size;   // taille du tableau (N)

public:
	// constructeur
    	Array() : data_ {0,0}, size(N)
    	{
    	}

	// retourne la taille de l'array (N)
    	int getSize() const
    	{
        	return this->size;
    	}

	// retourne un pointeur du le tableau de données
    	const T* data_pos() const
    	{
        	return data_;
    	}

	// DEBUG : affiche le contenu de l'array
    	void print() const
    	{
        	for (int i=0; i<this->size; i++)
        	{
            	cout << this->data_[i] << " ";
        	}
        	cout << " " << endl;
    	}

	// échange le contenu de deux arrays
    	void swap(Array<N,T>& a)
    	{
        	T tmp;
        	for (int i=0; i<this->size; i++)
        	{
            	tmp = this->data_[i];
            	this->data_[i] = a.data_[i];
            	a.data_[i] = tmp;
        	}
    	}

    
	// Opérateur d'accès : retourne le ième élément de l'array courant
    	T operator [](const int i) const
    	{
        	if (i>=0 && i<this->size)
        	{
            	return this->data_[i];
        	}
    	}

     	// Idem mais en version non const
    	T& operator [](const int i)
    	{
        	return this->data_[i];
    	}

    	/*
     	* Opérateur d'affectation : affecte les données de l'array
     	* en paramètre à l'array courant
     	*/
    	void operator =(const Array<N,T>& a)
    	{
        	for (int i=0; i<this->size; i++)
        	{
            		this->data_[i] = a.data_[i];
        	}	
    	}

    	/*
     	* Opérateur de comparaison : compare les données de l'array
     	* en paramètre avec celles de d'array courant
     	*/
    	bool operator ==(const Array<N,T>& a)
    	{
        	for (int i=0; i<this->size; i++)
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
