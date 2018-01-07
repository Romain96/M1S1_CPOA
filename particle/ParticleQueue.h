#ifndef __PARTICLEQUEUE_H__
#define __PARTICLEQUEUE_H__

#include <queue>
#include "Particle.h"
#include <vector>

// foncteur de comparaison de particules
// l'élément le plus prioritaire est le plus "grand"
// dans notre cas celui qui a le temps le plus faible (le plus en retard)
class ParticleCompare
{
public:
    bool operator ()(Particle& p1, Particle& p2)
    {
        return p1.getDate() < p2.getDate();
    }
};

// Représente la file de priorité des particules
class ParticleQueue
{
protected:
    // la file de particule (file de priorité)
    std::priority_queue<Particle, std::vector<Particle>, ParticleCompare> _queue;

public:
    // Constructeur
    ParticleQueue();

    // méthodes
    void addParticle(int x, int y);
};

#endif // __PARTICLEQUEUE_H__
