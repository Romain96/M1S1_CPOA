/*
 * Cette classe template représente un array paramétré par  
 * N la taille de l'array (le nombre d'éléments qu'il peut contenir)
 * T le type de données de l'array
 */

#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <iostream>
 
template <int N, typename T> class Array
{
protected:
    T data_[N]; // tableau de N éléments de type T
    int size;   // la taille du tableau des gardé en mémoire

public:
    // constructeur
    Array()
    {
        this->size = N;
        for (int i=0; i<N; i++)
        {
            data_[i] = T(0);
        }
    }

    /*
     * Retourne la taille du de l'array
    */
    int getSize()
    {
        return this->size;
    }

    void add(const int position, T value)
    {
        if (position >= 0 && position < this->size)
        {
            this->data_[position] = value;
        }
        else
        {
            std::cout << "add : erreur sur position !" << std::endl;
        }
    }

    /*
     * DEBUG : affiche le contenu de l'array
     */
    void print()
    {
        std::cout << "printing array : " << std::endl;
        for (int i=0; i<this->size; i++)
        {
            std::cout << this->data_[i] << " ";
        }
        std::cout << " " << std::endl;
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

    /*
     * Opérateur d'accès : retourne le ième élément de l'array courant
     */
    T operator [](const int i) const
    {
        if (i>=0 && i<this->size)
        {
            return this->tab[i];
        }
    }

    /*
     * Idem mais en version non const
     */
    T& operator [](const int i)
    {
        return this->data_[i];
    }
};

#endif
