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
    T data_[N]; // tableau de N éléments de type T
    int size;   // la taille du tableau des gardé en mémoire

public:
    // constructeur
    Array() : data_ {0,0}, size(N)
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
        for (int i=0; i<this->size; i++)
        {
            cout << this->data_[i] << " ";
        }
        cout << " " << endl;
    }

    /*
     * Echange deux arrays
     */
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

    /*
     * Opérateur d'accès : retourne le ième élément de l'array courant
     */
    T operator [](const int i) const
    {
        if (i>=0 && i<this->size)
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
