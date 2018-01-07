#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Vector.h"
#include "Utils.h"

// Représente un particule
class Particle
{
protected:
    // chaque particule conserve :

    // - sa position courante
    Vec2f _position;

    // - sa position future (validée si non collision)
    Vec2f _expectedPosition;

    // - son vecteur de vitesse
    Vec2f _speed;

    // ainsi que sa date en temp absolu
    int _date;

public:
    // constructeurs
    Particle();
    Particle(float x, float y);

    // getters
    Vec2f& getPosition();
    Vec2f& getExpectedPosition();
    Vec2f& getSpeed();
    int getDate();

    // setters
    void setPosition(Vec2f& pos);
    void setExpectedPosition(Vec2f& pos);
    void setSpeed(Vec2f& speed);
    void setDate(int date);

    // méthodes
    void validateExpectedCoordinates();
};

#endif // __PARTICLE_H__
