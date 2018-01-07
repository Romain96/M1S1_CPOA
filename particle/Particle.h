#ifndef __PARTICLE_H__
#define __PARTICLE_H__

// Représente un particule
class Particle
{
protected:
    // chaque particule conserve sa position courante
    int _x;
    int _y;
    // ainsi que sa date en temp absolu
    int _date;

public:
    // constructeur
    Particle(int x, int y);

    // getters
    int getX();
    int getY();
    int getDate();

    // setters
    void setX(int x);
    void setY(int y);
    void setDate(int date);

    // méthodes
    // TODO
};

#endif // __PARTICLE_H__
