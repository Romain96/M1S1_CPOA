#ifndef __PARTICLEQUEUE_H__
#define __PARTICLEQUEUE_H__

#include <vector>
#include <queue>

#include "Image2Grey.h"
#include "Particle.h"


// foncteur de comparaison de particules
// l'élément le plus prioritaire est le plus "grand"
// dans notre cas celui qui a le temps le plus faible (le plus en retard)
struct ParticleCompare
{
    bool operator ()(Particle& l, Particle& r)
    {
        return l.getDate() > r.getDate();
    }
};

// Représente la file de priorité des particules
class ParticleQueue
{
protected:
    // la file de particule (file de priorité)
    std::priority_queue<Particle, std::vector<Particle>, ParticleCompare> _queue;
    // date global absolu
    int _date;

public:
    // Constructeur
    ParticleQueue();

    // getters
    int getDate();
    std::priority_queue<Particle, std::vector<Particle>, ParticleCompare>& getQueue();

    // setters
    void setDate(int date);

    // méthodes
    void addParticle(int x, int y);
    void iterateForTimeStep(Image2Grey& img, Image2D<Vec2f>& grad, int timeStep);
};

#endif // __PARTICLEQUEUE_H__
