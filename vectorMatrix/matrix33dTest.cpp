#include "matrix33dTest.h"
#include "matrix33d.h"
#include <cmath>
#include <iostream>

// test de l'inversion d'une matrice
bool testInverse()
{
    Matrix33d m1;   // matrice identité
    // matrice (3, 0, 2, 2, 0, -2, 0, 1, 1)
    m1(0,0) = 3.0;
    m1(0,1) = 0.0;
    m1(0,2) = 2.0;
    m1(1,0) = 2.0;
    m1(1,1) = 0.0;
    m1(1,2) = -2.0;
    m1(2,0) = 0.0;
    m1(2,1) = 1.0;
    m1(2,2) = 1.0;

    // inversion de la matrice
    Matrix33d m2 = m1.inverse();

    cout << m2(0,0) << endl;
    cout << m2(0,1) << endl;
    cout << m2(0,2) << endl;
    cout << m2(1,0) << endl;
    cout << m2(1,1) << endl;
    cout << m2(1,2) << endl;
    cout << m2(2,0) << endl;
    cout << m2(2,1) << endl;
    cout << m2(2,2) << endl;

    // vérification donne normalement la matrice (0.2, 0.2, 0, -0.2, 0.3, 1, 0.2, -0.3, 0)
    if( (m2(0,0)-0.2)<1e-9 && (m2(0,1)-0.2)<1e-9 && m2(0,2)<1e-9 &&
            (m2(1,0)+0.2)<1e-9 && (m2(1,1)-0.3)<1e-9 && (m2(1,2)-1.0)<1e-9 &&
            (m2(2,0)-0.2)<1e-9 && (m2(2,1)+0.3)<1e-9 && m2(2,2)<1e-9 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// test de la matrice de translation
bool testTranslationStatique()
{
    Matrix33d m;
    Matrix33d trans = m.staticTranslation(1.0, 2.0);

    // vérification donne normalement la matrice (1.0, 0, 0, 0, 2.0, 0, 0, 0, 1.0)
    if( (trans(0,0)-1.0)<1e-9 && trans(0,1)<1e-9 && trans(0,2)<1e-9 &&
            trans(1,0)<1e-9 && (trans(1,1)-2.0)<1e-9 && trans(1,2)<1e-9 &&
            trans(2,0)<1e-9 && trans(2,1)<1e-9 && (trans(2,2)-1.0)<1e-9 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// test de la matrice de rotation
bool testRotationStatique()
{
    Matrix33d m;
    Matrix33d rot = m.staticRotation(45.0);

    // vérification donne normalement la matrice (cos(45), sin(45), 0, -sin(45), cos(45), 0, 0, 0, 1.0)
    if( (rot(0,0)-std::cos(45.0))<1e-9 && (rot(0,1)-std::sin(45.0))<1e-9 && rot(0,2)<1e-9 &&
            (rot(1,0)+std::sin(45.0))<1e-9 && (rot(1,1)-std::cos(45.0))<1e-9 && rot(1,2)<1e-9 &&
            rot(2,0)<1e-9 && rot(2,1)<1e-9 && (rot(2,2)-1.0)<1e-9 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// test de la matrice d'homothétie
bool testHomothetieStatique()
{
    Matrix33d m;
    Matrix33d homo = m.staticShrink(1.0,2.0);

    // vérification donne normalement la matrice (0, 0, 1.0, 0, 0, 2.0, 0, 0, 1.0)
    if( m(0,0)<1e-9 && m(0,1)<1e-9 && (m(0,2)-1.0)<1e-9 &&
            m(1,0)<1e-9 && m(1,1)<1e-9 && (m(1,2)-2.0)<1e-9 &&
            m(2,0)<1e-9 && m(2,1)<1e-9 && (m(2,2)-1.0)<1e-9 )
    {
        return true;
    }
    else
    {
        return false;
    }
}
