#include "Particle.h"
#include "Vector.h"
#include "Utils.h"

// Fonction         : Particle
// Argument(s)		: /
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: constructeur
Particle::Particle()
{
    // position
    Vec2f position;
    position[0] = 0.f;
    position[1] = 0.f;
    _position = position;
    _expectedPosition = position;

    // vecteur vitesse de départ est nul
    Vec2f speed;
    speed[0] = 0.f;
    speed[1] = 0.f;
    _speed = speed;
}

// Fonction         : Particle
// Argument(s)		: - x : entier représentant l'abscisse de la particule
//                    - y : entier représentant l'ordonnées de la particule
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: constructeur paramétré
Particle::Particle(float x, float y)
{
    // position
    Vec2f position;
    position[0] = x;
    position[1] = y;
    _position = position;
    _expectedPosition = position;

    // vecteur vitesse de départ est nul
    Vec2f speed;
    speed[0] = 0.f;
    speed[1] = 0.f;
    _speed = speed;
}

//-----------------------------------------------------------------------------
// SECTION DES GETTERS
//-----------------------------------------------------------------------------

// Fonction         : getX
// Argument(s)		: /
// Valeur de retour	: un Vec2f
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne la position de la particule
Vec2f& Particle::getPosition()
{
    return _position;
}

// Fonction         : getExpectedPosition
// Argument(s)		: /
// Valeur de retour	: un Vec2f
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne la position future de la particule
Vec2f& Particle::getExpectedPosition()
{
    return _expectedPosition;
}

// Fonction         : getSpeed
// Argument(s)		: /
// Valeur de retour	: un vec2f
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le vecteur de vitesse de la particule
Vec2f& Particle::getSpeed()
{
    return _speed;
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

// Fonction         : setPosition
// Argument(s)		: - pos : nouvelle position
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie la position de la particule
void Particle::setPosition(Vec2f& pos)
{
    _position = pos;
}

// Fonction         : setExpectedPosition
// Argument(s)		: - pos : nouvelle position future
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie la position future de la particule
void Particle::setExpectedPosition(Vec2f& pos)
{
    _expectedPosition = pos;
}

// Fonction         : setSpeed
// Argument(s)		: - speed : nouveau vecteur vitesse
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le vecteur vitesse de la particule
void Particle::setSpeed(Vec2f &speed)
{
    _speed = speed;
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

// Fonction         : validateExpectedCoordinates
// Argument(s)		: /
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: valide les coordonnées futures de la particule
//                    (devrait être utilisé seulement après détection de collision)
void Particle::validateExpectedCoordinates()
{
    // les coordonnées futures deviennent les coordonnées courantes
    _position = _expectedPosition;
}

// Fonction         : /
// Argument(s)		: /
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
