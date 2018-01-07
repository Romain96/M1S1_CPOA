#include "ParticleQueue.h"
#include "Particle.h"
#include <iostream>
#include <queue>

// Fonction         : ParticleQueue
// Argument(s)      : /
// Valeur de retour : /
// Pré-condition(s) : /
// Post-condition(s): /
// Commentaire(s)   : constructeur
ParticleQueue::ParticleQueue() :
    _queue()
{
    // rien
}

//-----------------------------------------------------------------------------
// SECTION DES METHODES
//-----------------------------------------------------------------------------

// Fonction         : addParticle
// Argument(s)      : - x : entier représentant l'abscisse de la particule
//                    - y : entier représentant l'ordonnées de la particule
// Valeur de retour : /
// Pré-condition(s) : /
// Post-condition(s): /
// Commentaire(s)   : ajoute une nouvelle particule dans la file
void ParticleQueue::addParticle(int x, int y)
{
    _queue.push(Particle(x, y));
}

