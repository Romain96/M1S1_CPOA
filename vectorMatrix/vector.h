/*
 * Classe vector template étendant la classe template array
 * N le nombre d'éléments
 * T le type des éléments
 */

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "array.h"

template <int N, typename T> class Vector : public Array<N,T>
{
public:
    	// constructeur
    	Vector() : Array<N,T>()
    	{
        	this->size = N;
    	}

	// opérateur d'accès version const
    	T operator [](const int i) const
    	{
        	return this->data_[i];
    	}

	// opérateur d'accès version non const
   	 T& operator [](const int i)
    	{
        	return this->data_[i];
    	}

	// opérateur de comparaison
    	bool operator ==(const Vector<N,T>& v)
    	{
       	 	for (int i=0; i<this->size; i++)
        	{
            		if (this->data_[i] != v.data_[i])
            		{
                		return false;
            		}
        	}
        	return true;
    	}

	// opérateur d'affectation d'un vecteur à un autre
   	 void operator =(const Vector<N,T>& v)
    	{
        	for (int i=0; i<this->size; i++)
        	{
            		this->data_[i] = v.data_[i];
        	}
    	}

	// DEBUG : affiche le vecteur
    	void print()
    	{
       		Array<N,T>::print();
    	}

    	// somme de deux vecteurs
    	Vector<N,T> operator+(const Vector<N,T>& v)
    	{
        	Vector<N,T> res;

        	for (int i=0; i<this->getSize(); i++)
        	{
            		res[i] = this->data_[i] + v[i];
        	}

        	return res;
    	}

    	// différence de deux vecteurs
    	Vector<N,T> operator-(const Vector<N,T>& v)
    	{
       	 	Vector<N,T> res;

        	for (int i=0; i<this->getSize(); i++)
        	{
            		res[i] = this->data_[i] - v[i];
        	}

       		return res;
    }

    	// somme de deux vecteurs et affecation au vecteur courant
    	void operator+=(const Vector<N,T>& v)
    	{
        	for (int i=0; i<this->getSize(); i++)
        	{
            		this->data_[i] = this->data_[i] + v[i];
        	}
    	}

    	// différence de deux vectors dans le vector courant
    	void operator-=(const Vector<N,T>& v)
    	{
        	for (int i=0; i<this->getSize(); i++)
        	{
            		this->data_[i] = this->data_[i] - v[i];
        	}
    	}

    	// multiplication et affectation par un scalaire
    	void operator*=(const float f)
    	{
        	for (int i=0; i<this->getSize(); i++)
        	{
            		this->data_[i] *= f;
        	}
    	}

    	// division et affectation par un scalaire
    	void operator/=(const float f)
    	{
        	for (int i=0; i<this->getSize(); i++)
        	{
            		this->data_[i] /= f;
        	}
    	}

    	// produit scalaire
    	T dot(const Vector<N,T>& v)
    	{
        	T res = 0;
        	
		for (int i=0; i<this->getSize(); i++)
        	{
            		res += this->data_[i] * v[i];
        	}

        	return res;
    	}

    	// produit vectoriel lorsqu'il est défini
    	Vector<N,T> cross(const Vector<N,T>& v)
    	{
        	Vector<N,T> res;
		
		// TODO : vérifier les dimensions !
        	res[0] = this->data_[1] * v[2] - this->data_[2] * v[1];
        	res[1] = this->data_[2] * v[0] - this->data_[0] * v[2];
        	res[2] = this->data_[0] * v[1] - this->data_[1] * v[0];
        
		return res;
    	}
};

// multiplication par un scalaire (deux sens)
template <int N, typename T> Vector<N,T> operator*(Vector<N,T>& v, const double f)
{
    	Vector<N,T> res;

    	for (int i=0; i<v.getSize(); i++)
    	{
        	res[i] = v[i] * f;
    	}

    	return res;
}

template <int N, typename T> Vector<N,T> operator*(const double f, Vector<N,T>& v)
{
    	Vector<N,T> res;

    	for (int i=0; i<v.getSize(); i++)
    	{
        	res[i] = v[i] * f;
    	}
	
    	return res;
}

// division par un scalaire (deux sens)
template <int N, typename T> Vector<N,T> operator/(const double f, Vector<N,T>& v)
{
    	Vector<N,T> res;

    	for (int i=0; i<v.getSize(); i++)
    	{
        	res[i] = v[i] / f;
    	}

	return res;
}

template <int N, typename T> Vector<N,T> operator/(Vector<N,T>& v, const double f)
{
    	Vector<N,T> res;

    	for (int i=0; i<v.getSize(); i++)
    	{
        	res[i] = v[i] / f;
    	}

    	return res;
}

#endif
