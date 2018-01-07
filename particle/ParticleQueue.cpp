#include "ParticleQueue.h"
#include "Particle.h"
#include "Image2Grey.h"
#include <iostream>
#include <queue>
#include "Image2Grey.h"

// Fonction         : ParticleQueue
// Argument(s)      : /
// Valeur de retour : /
// Pré-condition(s) : /
// Post-condition(s): /
// Commentaire(s)   : constructeur
ParticleQueue::ParticleQueue() :
    _queue(),
    _date(0)
{
    // rien
}

//-----------------------------------------------------------------------------
// SECTION DES GETTERS
//-----------------------------------------------------------------------------

// Fonction         : getDate
// Argument(s)      : /
// Valeur de retour : un entier
// Pré-condition(s) : /
// Post-condition(s): /
// Commentaire(s)   : retourne la date absolue
int ParticleQueue::getDate()
{
    return _date;
}

// Fonction         : getQueue
// Argument(s)      : /
// Valeur de retour : une référence sur la priority queue
// Pré-condition(s) : /
// Post-condition(s): /
// Commentaire(s)   : retourne la priority queue
std::priority_queue<Particle, std::vector<Particle>, ParticleCompare>& ParticleQueue::getQueue()
{
    return _queue;
}

//-----------------------------------------------------------------------------
// SECTION DES SETTERS
//-----------------------------------------------------------------------------

// Fonction         : setDate
// Argument(s)      : - date : la nouvelle date
// Valeur de retour : /
// Pré-condition(s) : /
// Post-condition(s): /
// Commentaire(s)   : modifie la date absolue
void ParticleQueue::setDate(int date)
{
    _date = date;
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
    Particle p((float)x, (float )y);
    _queue.push(p);
}

// Fonction         : iterateForTimeStep
// Argument(s)      : - img : l'image contenant la forme CSG dessinée
//                    - timeStep : intervalle de temps en millisecondes
// Valeur de retour : /
// Pré-condition(s) : timeStep >= 0
// Post-condition(s): /
// Commentaire(s)   : effectue les itérations nécessaires au calcul des nouvelles positions des particules
//                    en faisant avancer le temps de timeStep millisecondes
void ParticleQueue::iterateForTimeStep(Image2Grey& img, int timeStep)
{
    // vecteur g (accélération de la gravité 9.81 m/s^2 vers le centre de la Terre)
    Vec2f g;
    g[0] = 0.f;
    g[1] = 9.81;
    // particule à traiter
    Particle p;
    // position actuelle de la particule
    float previousX;
    float previousY;
    // avancement (temporel) actuel de la particule
    int particleStep = 0;
    // nouveau vecteur vitesse de la particule
    Vec2f newSpeed;
    // nouveau vecteur position de la particule
    Vec2f newPosition;

    // traitement tant que la particule la plus en retard est en retard sur la date à atteindre
    while (!_queue.empty() && (p = _queue.top()).getDate() < (_date + timeStep))
    {
        _queue.pop();
        previousX = p.getPosition()[0];
        previousY = p.getPosition()[1];
        particleStep = 0;

        //std::cout << "treating particle " << p.getPosition()[0] << ", " << p.getPosition()[1] << std::endl;

        // tant que la particule n'a pas avancé de timeStep unités de temps
        while (particleStep < timeStep)
        {
            // tant que la particule n'a pas avancé d'un pixel, faire avancer la particule
            // de 1 milliseconde
            while ((p.getPosition()[0] - previousX) < 1.f && (p.getPosition()[1] - previousY) < 1.f)
            {
                //std::cout << "moving 100 ms" << std::endl;

                // calculer la future position de la particule suivant son vecteur vitesse
                newSpeed = p.getSpeed() + g * 0.1f;   // t = 100ms = 100/1000 s
                newPosition = p.getPosition() + p.getSpeed() + g * 0.5f;

                // test de collision
                if (img((int)std::round(newPosition[0]), (int)std::round(newPosition[1])) > 0)
                {
                    std::cout << "collision !" << std::endl;
                }
                else
                {
                    // les coordonnées sont validées
                }

                //std::cout << "old pos " << p.getPosition()[0] << ", " << p.getPosition()[1] << std::endl;
                //std::cout << "new pos " << newPosition[0] << ", " << newPosition[1] << std::endl;
                //std::cout << "speed " << newSpeed[0] << ", " << newSpeed[1] << std::endl;

                // validation
                p.setPosition(newPosition);
                p.setSpeed(newSpeed);

                // la particule a avancé de 1 milliseconde
                p.setDate(p.getDate() + 100);
                particleStep += 100;
            }
            particleStep = timeStep;
        }
        // replacer la particule désormais en avance dans la file
        if (p.getPosition()[0] < 0 || p.getPosition()[0] > 1023 || p.getPosition()[1] < 0 || p.getPosition()[1] > 1023)
        {
            //std::cout << "removing particle out of screen" << std::endl;
        }
        else
        {
            //std::cout << "replacing particle in priority queue" << std::endl;
            _queue.push(p);
        }
    }

    std::cout << "iteration finished" << std::endl;

    // la date globale a désormais avancé de timeStep millisecondes
    _date += timeStep;
}
