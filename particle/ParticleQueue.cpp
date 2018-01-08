#include <iostream>
#include <queue>

#include "ParticleQueue.h"
#include "Particle.h"
#include "Image2Grey.h"
#include "Image2Grey.h"
#include "gradient_sobel.h"

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
//                    - grad : l'image contenant le gradient
//                    - timeStep : intervalle de temps en millisecondes
// Valeur de retour : /
// Pré-condition(s) : timeStep >= 0
// Post-condition(s): /
// Commentaire(s)   : effectue les itérations nécessaires au calcul des nouvelles positions des particules
//                    en faisant avancer le temps de timeStep millisecondes
void ParticleQueue::iterateForTimeStep(Image2Grey& img, Image2D<Vec2f>& grad, int timeStep)
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
    bool to_remove = false;
    // vecteur normal (lorsqu'il y a collision)
    Vec2f normal;
    // vecteur tangeant (lorsqu'il y a collision)
    Vec2f tangeant;

    // traitement tant que la particule la plus en retard est en retard sur la date à atteindre
    while (!_queue.empty() && (p = _queue.top()).getDate() < (_date + timeStep))
    {
        _queue.pop();
        previousX = p.getPosition()[0];
        previousY = p.getPosition()[1];
        particleStep = 0;
        to_remove = false;

        //std::cout << "treating particle " << p.getPosition()[0] << ", " << p.getPosition()[1] << std::endl;

        // tant que la particule n'a pas avancé de timeStep unités de temps
        while (particleStep < timeStep && !to_remove)
        {
            // tant que la particule n'a pas avancé d'un pixel, faire avancer la particule
            // de 1 milliseconde
            while ((p.getPosition()[0] - previousX) < 1.f && (p.getPosition()[1] - previousY) < 1.f && !to_remove)
            {
                //std::cout << "moving 100 ms" << std::endl;

                // calculer la future position de la particule suivant son vecteur vitesse
                newSpeed = p.getSpeed() + g * 0.1f;   // t = 100ms = 100/1000 s
                newPosition = p.getPosition() + p.getSpeed() + g * 0.005f;

                // test de collision
                if ((int)std::round(newPosition[0]) > 1023 || (int)std::round(newPosition[1]) > 1023 || (int)std::round(newPosition[1]) < 0)
                {
                    std::cout << "out of screen !" << std::endl;
                    to_remove = true;
                }
                else if (img((int)std::round(newPosition[0]), (int)std::round(newPosition[1])) > 0)
                {
                    std::cout << "collision !" << std::endl;

                    // le vecteur normal est donné par la direction du gradient
                    normal[0] = grad(newPosition[0], newPosition[1])[0];
                    normal[1] = grad(newPosition[0], newPosition[1])[1];

                    // le vecteur tangeant est orthogonal au vecteur normal
                    tangeant[0] = normal[1];
                    tangeant[1] = -normal[0];

                    // le nouveau vecteur vitesse est altéré par 0.9 * vt - 0.5* vn
                    newSpeed = 0.5f * tangeant - 0.5f * normal;

                    // calcul de la nouvelle position
                    newPosition = p.getPosition() + newSpeed + g * 0.005f;

                    p.setPosition(newPosition);
                    p.setSpeed(newSpeed);
                }
                else
                {
                    // validation des coordonnées
                    p.setPosition(newPosition);
                    p.setSpeed(newSpeed);
                }

                // la particule a avancé de 100 millisecondes
                p.setDate(p.getDate() + 100);
                particleStep += 100;
            }
            particleStep = timeStep;
        }
        // replacer la particule désormais en avance dans la file
        if (p.getPosition()[0] < 0 || p.getPosition()[0] > 1023 || p.getPosition()[1] < 0 || p.getPosition()[1] > 1023 || to_remove)
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
