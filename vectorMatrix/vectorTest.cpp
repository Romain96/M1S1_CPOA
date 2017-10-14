// programme de test de la classe template vector définit dans vector.h

#include "vector.h"

// test de la somme +
bool testSomme()
{
    // instanciation et affectation
    Vector<3,int> v1;
    Vector<3,int> v2;

    for (int i=0; i<3; i++)
    {
        v1[i] = i;
        v2[i] = 2*i;
    }

    // somme
    Vector<3,int> res = v1+v2;

    // test de la somme
    for (int i=0; i<3; i++)
    {
        if (res[i] != 2*i + i)
            return false;
    }
    return true;
}

// test de la différence -
bool testDifference()
{
    // instanciation et affectation
    Vector<3,int> v1;
    Vector<3,int> v2;
    for (int i=0; i<3; i++)
    {
        v1[i] = i;
        v2[i] = 2*i;
    }

    // différence
    Vector<3,int> res = v1-v2;

    // test de la différence
    for (int i=0; i<3; i++)
    {
        if (res[i] != i - 2*i)
            return false;
    }
    return true;
}

// test de la somme puis affectation +=
bool testSommeAffectation()
{
    // instanciation et affectation
    Vector<3,int> v1;
    Vector<3,int> v2;
    for (int i=0; i<3; i++)
    {
        v1[i] = i;
        v2[i] = 2*i;
    }

    // somme plus affectation
    v1+=v2;

    // test de la somme plus affectation
    for (int i=0; i<3; i++)
    {
        if (v1[i] != i + v2[i])
            return false;
    }
    return true;
}

// test de la différence puis affectation -=
bool testDifferenceAffectation()
{
    // instanciation et affectation
    Vector<3,int> v1;
    Vector<3,int> v2;
    for (int i=0; i<3; i++)
    {
        v1[i] = i;
        v2[i] = 2*i;
    }

    // différence et affectation
    v1-=v2;

    // test de ma différence et affectation
    for (int i=0; i<3; i++)
    {
        if (v1[i] != i - v2[i])
            return false;
    }
    return true;
}

// test de la multiplication par un scalaire *
bool testProduitParScalaire()
{
    // instanciation et affectation
    Vector<3,double> v1;
    for (int i=0; i<3; i++)
    {
        v1[i] = (double)i;
    }

    // multiplication par un scalaire
    Vector<3,double> v2 = v1*1.5;

    // test de la multiplication
    for (int i=0; i<3; i++)
    {
        if (v2[i] - (v1[i] * 1.5) > 1e-9)
            return false;
    }
    return true;
}

// test de la division par un scalaire /
bool testDivisionParScalaire()
{
    // instanciation et affectation
    Vector<3,double> v1;
    for (int i=0; i<3; i++)
    {
        v1[i] = (double)i;
    }

    // division par un scalaire
    Vector<3,double> v2 = v1 / 2.0;

    // test de la division
    for (int i=0; i<3; i++)
    {
        if (v2[i] != v1[i] / 2.0)
            return false;
    }
    return true;
}

// test de la multiplication puis affectation par un scalaire *=
bool testProduitAffectationParScalaire()
{
    // instanciation et affectation
    Vector<3,double> v1;
    for (int i=0; i<3; i++)
    {
        v1[i] = (double)i;
    }

    // multiplication et affectation
    v1*=1.5;

    // test de la multiplication et affectation
    for (int i=0; i<3; i++)
    {
        if (v1[i] != (double)i*1.5)
            return false;
    }
    return true;
}

// test de la division puis affectation par un scalaire /=
bool testDivisionAffectationParScalaire()
{
    // instanciation et affectation
    Vector<3,double> v1;
    for (int i=0; i<3; i++)
    {
        v1[i] = (double)i;
    }

    // division e affectation
    v1/=2.0;

    // test de la division et affectation
    for (int i=0; i<3; i++)
    {
        if (v1[i] != (double)i / 2.0)
            return false;
    }
    return true;
}

// test de du produit scalaire
bool testProduitScalaire()
{
    // instanciation et affectation
    Vector<3,int> v1;
    Vector<3,int> v2;
    // vecteur (5,0,0)
    v1[0] = 5;
    v1[1] = 0;
    v1[2] = 0;
    // vecteur (0,10,0)
    v2[0] = 0;
    v2[1] = 10;
    v2[2] = 0;

    // produit scalaire
    int ps = v1.dot(v2);

    // test du produit scalaire
    if (ps == 0)
        return true;
    else
        return false;
}

#include <iostream>
using std::cout;
using std::endl;

// test du produit vectoriel
bool testProduitVectoriel()
{
    // instanciation et affectation
    Vector<3,int> v1;
    Vector<3,int> v2;
    // vecteur (2,3,4)
    v1[0] = 2;
    v1[1] = 3;
    v1[2] = 4;
    // vecteur (5,6,7)
    v2[0] = 5;
    v2[1] = 6;
    v2[2] = 7;

    // produit vectoriel
    Vector<3,int> v3 = v1.cross(v2);

    cout << "v3[0] = " << v3[0] << ", v3[1] = " << v3[1] << ", v3[2] = " << v3[2] <<endl;

    // test du produit vectoriel (-3,6,-3)
    if (v3[0] == -3 && v3[1] == 6 && v3[2] == -3)
        return true;
    else
        return false;
}
