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

    // - son vecteur de vitesse
    Vec2f _speed;

    // ainsi que sa date en temp absolu
    int _date;

    // et un comteur de rebonds
    int _jump;

public:
    // constructeurs
    Particle();
    Particle(float x, float y);

    // getters
    Vec2f& getPosition();
    Vec2f& getSpeed();
    int getDate();
    int getJump();

    // setters
    void setPosition(Vec2f& pos);
    void setSpeed(Vec2f& speed);
    void setDate(int date);
    void setJump(int jump);
};

#endif // __PARTICLE_H__
