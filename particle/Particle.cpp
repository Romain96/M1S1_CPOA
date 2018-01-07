#include "Particle.h"

// Fonction         : Particle
// Argument(s)		: - x : entier représentant l'abscisse de la particule
//                    - y : entier représentant l'ordonnées de la particule
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: constructeur paramétré
Particle::Particle(int x, int y) :
    _x(x),
    _y(y),
    _date(0)
{
    // rien
}

//-----------------------------------------------------------------------------
// SECTION DES GETTERS
//-----------------------------------------------------------------------------

// Fonction         : getX
// Argument(s)		: /
// Valeur de retour	: un entier
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne l'abscisse de la particule
int Particle::getX()
{
    return _x;
}

// Fonction         : getY
// Argument(s)		: /
// Valeur de retour	: un entier
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne l'ordonnée de la particule
int Particle::getY()
{
    return _y;
}

// Fonction         : getDate
// Argument(s)		: /
// Valeur de retour	: un entier
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne la date de la particule
int Particle::getDate()
{
    return _date;
}

//-----------------------------------------------------------------------------
// SECTION DES SETTERS
//-----------------------------------------------------------------------------

// Fonction         : setX
// Argument(s)		: - : nouvelle abscisse
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie l'abscisse de la particule
void Particle::setX(int x)
{
    _x = x;
}

// Fonction         : setY
// Argument(s)		: - y : nouvelle ordonnée
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie l'odronnée de la particule
void Particle::setY(int y)
{
    _y = y;
}

// Fonction         : setDate
// Argument(s)		: - date : nouvelle date
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie la date de la particule
void Particle::setDate(int date)
{
    _date = date;
}

//-----------------------------------------------------------------------------
// SECTION DES METHODES
//-----------------------------------------------------------------------------

// Fonction         : /
// Argument(s)		: /
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
