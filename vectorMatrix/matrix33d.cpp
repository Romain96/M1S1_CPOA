#include "matrix33d.h"
#include <cmath>

Matrix33d::Matrix33d() : data_()
{
    // retourne une matrice identité par défaut
    this->data_[0] = 1.0;
    this->data_[4] = 1.0;
    this->data_[8] = 1.0;
}

// opérateur d'accès version const
double Matrix33d::operator ()(const int i, const int j) const
{
    return this->data_[3*i + j];
}

// version non const

double& Matrix33d::operator ()(const int i, const int j)
{
    return this->data_[3*i + j];
}

// opérateur d'affectation
void Matrix33d::operator =(const Matrix33d& m)
{
    for (int i=0; i<9; i++)
    {
        this->data_[i] = m.data_[i];
    }
}

Matrix33d Matrix33d::inverse()
{
    Matrix33d inv;

    int det = this->data_[0] * this->data_[4] * this->data_[8] +
            this->data_[1] * this->data_[5] * this->data_[6] +
            this->data_[2] * this->data_[3] * this->data_[7] -
            this->data_[2] * this->data_[4] * this->data_[6] -
            this->data_[0] * this->data_[5] * this->data_[7] -
            this->data_[1] * this->data_[3] * this->data_[8];

    if (det == (double)0.0)
    {
        // erreur ?
        return inv; // id pour l'instant
    }

    inv.data_[0] = (this->data_[4] * this->data_[8] - this->data_[5] * this->data_[7]) / det;
    inv.data_[3] = (this->data_[3] * this->data_[8] - this->data_[6] * this->data_[5]) / det;
    inv.data_[6] = (this->data_[3] * this->data_[7] - this->data_[6] * this->data_[4]) / det;
    inv.data_[1] = (this->data_[1] * this->data_[8] - this->data_[7] * this->data_[2]) / det;
    inv.data_[4] = (this->data_[0] * this->data_[8] - this->data_[6] * this->data_[2]) / det;
    inv.data_[7] = (this->data_[0] * this->data_[7] - this->data_[6] * this->data_[1]) / det;
    inv.data_[2] = (this->data_[3] * this->data_[5] - this->data_[4] * this->data_[2]) / det;
    inv.data_[5] = (this->data_[0] * this->data_[5] - this->data_[3] * this->data_[2]) / det;
    inv.data_[8] = (this->data_[0] * this->data_[4] - this->data_[3] * this->data_[1]) / det;

    return inv;
}

// matrice de translation
Matrix33d Matrix33d::staticTranslation(const double dx, const double dy)
{
    Matrix33d trans;

    trans.data_[1] = dx;
    trans.data_[3] = dy;

    return trans;
}

// matrice de rotation (sens trigonométrique)
Matrix33d Matrix33d::staticRotation(const double alpha)
{
    Matrix33d rot;

    rot.data_[0] = std::cos(alpha);
    rot.data_[1] = -std::sin(alpha);
    rot.data_[3] = std::sin(alpha);
    rot.data_[4] = std::cos(alpha);

    return rot;
}

// matrice d'homotéthie
Matrix33d Matrix33d::staticShrink(const double hx, const double hy)
{
    Matrix33d homo;

    homo.data_[2] = hx;
    homo.data_[5] = hy;

    return homo;
}
