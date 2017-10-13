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
    {}

    T operator [](const int i) const
    {
        return Array<N,T>::operator[](i);
    }

    T& operator [](const int i)
    {
        return Array<N,T>::operator [](i);
    }

    bool operator ==(const Vector<N,T>& v)
    {
        return Array<N,T>::operator[](v);
    }

    void operator =(const Vector<N,T>& v)
    {
        Array<N,T>::operator=(v);
    }

    void print()
    {
        Array<N,T>::print();
    }

    // somme de deux vectors
    Vector<N,T> operator+(const Vector<N,T>& v)
    {
        Vector<N,T> res;
        for (int i=0; i<this->getSize(); i++)
        {
            res.add(i,this->data_[i] + v.data_[i]);
        }
        return res;
    }

    // différence de deux vectors
    Vector<N,T> operator-(const Vector<N,T>& v)
    {
        Vector<N,T> res;
        for (int i=0; i<this->getSize(); i++)
        {
            res.add(i,this->data_[i] - v.data_[i]);
        }
        return res;
    }

    // somme de deux vectors dans le vector courant
    void operator+=(const Vector<N,T>& v)
    {
        for (int i=0; i<this->getSize(); i++)
        {
            this->add(i, this->data_[i] + v.data_[i]);
        }
    }

    // différence de deux vectors dans le vector courant
    void operator-=(const Vector<N,T>& v)
    {
        for (int i=0; i<this->getSize(); i++)
        {
            this->add(i, this->data_[i] - v.data_[i]);
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
    int dot(const Vector<N,T>& v)
    {
        int res = 0;
        for (int i=0; i<this->getSize(); i++)
        {
            res += (int)this->data_[i] * (int)v.data_[i];
        }
        return res;
    }

    // produit vectoriel lorsqu'il est défini
    Vector<N,T> cross(const Vector<N,T>& v)
    {
        Vector<3,T> res;
        res.add(0, this->data_[1] * v.data_[2] - v.data_[1] * this->data_[2]);
        res.add(1, this->data_[2] * v.data_[0] - v.data_[2] * this->data_[0]);
        res.add(2, this->data_[0] * v.data_[1] - v.data_[0] * this->data_[1]);
        return res;
    }
};

// multiplication par un scalaire (deux sens)
template <int N, typename T> Vector<N,T> operator*(Vector<N,T>& v, const double f)
{
    Vector<N,T> res;
    for (int i=0; i<v.getSize(); i++)
    {
        res.add(i, v[i] * f);
    }
    return res;
}

template <int N, typename T> Vector<N,T> operator*(const double f, Vector<N,T>& v)
{
    Vector<N,T> res;
    for (int i=0; i<v.getSize(); i++)
    {
        res.add(i, v[i] * f);
    }
    return res;
}

// division par un scalaire (deux sens)
template <int N, typename T> Vector<N,T> operator/(const double f, Vector<N,T>& v)
{
    Vector<N,T> res;
    for (int i=0; i<v.getSize(); i++)
    {
        res.add(i, v[i] / f);
    }
	return res;
}

template <int N, typename T> Vector<N,T> operator/(Vector<N,T>& v, const double f)
{
    Vector<N,T> res;
    for (int i=0; i<v.getSize(); i++)
    {
        res.add(i, v[i] / f);
    }
    return res;
}

#endif
