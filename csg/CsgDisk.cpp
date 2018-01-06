#include "Vector.h"
#include "Matrix33d.h"
#include "Utils.h"
#include "BoundingBox.h"
#include "CsgDisk.h"

// Fonction         : CsgDisk
// Argument(s)		: - center : vecteur contenant les coordonnées du centre du disque
//                    - radius : le rayon du disque
// Valeur de retour	: /
// Pré-condition(s)	: les coordonnées du centre doivent être dans l'image
// Post-condition(s): /
// Commentaire(s)	: constructeur paramétré
CsgDisk::CsgDisk(Vec2f &center, float radius) : CsgPrimitive(center, radius)
{
    // rien
}

// Fonction         : getRadius
// Argument(s)		: /
// Valeur de retour	: un flottant contenant la valeur du rayon
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le rayon actuel (de base) du disque
float CsgDisk::getRadius()
{
    // utilisation de getDistanceToOrigin
    return CsgPrimitive::getDistanceToOrigin();
}

// Fonction         : setRadius
// Argument(s)		: - radius : le nouveau rayon
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le rayon (c'est-à-dire la distance à l'origine et la bounding box)
void CsgDisk::setRadius(float radius)
{
    // utilisation du setDistanceToOrigin
    CsgPrimitive::setDistanceToOrigin(radius);
}

// Fonction         : isInsidePrimitive
// Argument(s)		: - point : vec2f contenant les coordonnées du point à tester
// Valeur de retour	: vrai si le point est dans la primitive, faux sinon
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: vérifie que le point est dans la primitive (disque)
bool CsgDisk::isInsidePrimitive(Vec2f &point)
{
    // le point est dans le disque s'il est à une distance inférieure ou égale du centre du disque
    float distanceSquared = (_center[0] - point[0])*(_center[0] - point[0]) + (_center[1] - point[1])*(_center[1] - point[1]);
    float radiusSquared = _distanceToOrigin * _distanceToOrigin;

    if (distanceSquared <= radiusSquared)
        return true;
    else
        return false;
}

// Fonction         : updateBoundingBox
// Argument(s)		: - tx : translation en x (pixels)
//                    - ty : translation en y (pixels)
//                    - angle : angle de rotation (degrès)
//                    - scale : coefficient d'agrandissement/réduction (entier)
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: met à jour la bounding box de la pimitive après transformation
void CsgDisk::updateBoundingBox(int tx, int ty, int angle, double scale)
{
    // les translations correspondent aux coordonnées de la bounding box translatées
    // la rotation n'a pas de sens pour un disque
    // les homothéties correspondent à un accroisement/une réduction du rayon
    std::cout << "updating BB for disk with tx = " << tx << " ty = " << ty << " angle = " << angle << " scale = " << scale << std::endl;

    Vec2f ulp;
    ulp[0] = (_center[0] + tx) - (_distanceToOrigin * scale);
    ulp[1] = (_center[1] + ty) - (_distanceToOrigin * scale);

    Vec2f urp;
    urp[0] = (_center[0] + tx) + (_distanceToOrigin * scale);
    urp[1] = (_center[1] + ty) - (_distanceToOrigin * scale);

    Vec2f llp;
    llp[0] = (_center[0] + tx) - (_distanceToOrigin * scale);
    llp[1] = (_center[1] + ty) + (_distanceToOrigin * scale);

    Vec2f lrp;
    lrp[0] = (_center[0] + tx) + (_distanceToOrigin * scale);
    lrp[1] = (_center[1] + ty) + (_distanceToOrigin * scale);

    // debug
    std::cout << "ulp " << ulp[0] << " " << ulp[1] << std::endl;
    std::cout << "urp " << urp[0] << " " << ulp[1] << std::endl;
    std::cout << "llp " << llp[0] << " " << llp[1] << std::endl;
    std::cout << "lrp " << lrp[0] << " " << lrp[1] << std::endl;

    _boundingBox = BoundingBox(ulp, urp, llp, lrp);
}
