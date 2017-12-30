#include "Vector.h"
#include "Utils.h"
#include "BoundingBox.h"
#include "CsgDisk.h"

// Fonction         : CsgDisk
// Argument(s)		: - center : vecteur contenant les coordonnées du centre du cercle
// Valeur de retour	: /
// Pré-condition(s)	: les coordonnées du centre doivent être dans l'image
// Post-condition(s): /
// Commentaire(s)	: constructeur paramétré
CsgDisk::CsgDisk(Vec2f &center) :
    _diameter(1.f),
    _center(center)
{
    Vec2f ulp;
    ulp[0] = center[0] - _diameter/2.f;
    ulp[1] = center[1] - _diameter/2.f;

    Vec2f urp;
    urp[0] = center[0] + _diameter/2.f;
    urp[1] = center[1] - _diameter/2.f;

    Vec2f llp;
    llp[0] = center[0] - _diameter/2.f;
    llp[1] = center[1] + _diameter/2.f;

    Vec2f lrp;
    lrp[0] = center[0] + _diameter/2.f;
    lrp[1] = center[1] + _diameter/2.f;

    _boundingBox = BoundingBox(ulp, urp, llp, lrp);
}

// Fonction         : getDiameter
// Argument(s)		: /
// Valeur de retour	: un flottant contenant la valeur du diamètre
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le diamètre actuel (de base) du disque
float CsgDisk::getDiameter()
{
    return _diameter;
}

// Fonction         : getCenter
// Argument(s)		: /
// Valeur de retour	: un vecteur contenant les coordonnées actuelles de du centre du disque
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne les coordonnées du centre
Vec2f& CsgDisk::getCenter()
{
    return _center;
}

// Fonction         : getBoundingBox
// Argument(s)		: /
// Valeur de retour	: une bounding box
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne la bounding box du disque
BoundingBox& CsgDisk::getBoundingBox()
{
    return _boundingBox;
}

// Fonction         : setDiameter
// Argument(s)		: - diameter : le nouveau diamètre
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le diamètre (et la bounding box)
void CsgDisk::setDiameter(float diameter)
{
    _diameter = diameter;

    Vec2f ulp;
    ulp[0] = _center[0] - _diameter/2.f;
    ulp[1] = _center[1] - _diameter/2.f;

    Vec2f urp;
    urp[0] = _center[0] + _diameter/2.f;
    urp[1] = _center[1] - _diameter/2.f;

    Vec2f llp;
    llp[0] = _center[0] - _diameter/2.f;
    llp[1] = _center[1] + _diameter/2.f;

    Vec2f lrp;
    lrp[0] = _center[0] + _diameter/2.f;
    lrp[1] = _center[1] + _diameter/2.f;

    BoundingBox bb = BoundingBox(ulp, urp, llp, lrp);
    setBoundingBox(bb);
}

// Fonction         : setCenter
// Argument(s)		: - center :  les nouvelles coordonnées du centre
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le centre (et la bounding box
void CsgDisk::setCenter(Vec2f &center)
{
    _center = center;

    Vec2f ulp;
    ulp[0] = center[0] - _diameter/2.f;
    ulp[1] = center[1] - _diameter/2.f;

    Vec2f urp;
    urp[0] = center[0] + _diameter/2.f;
    urp[1] = center[1] - _diameter/2.f;

    Vec2f llp;
    llp[0] = center[0] - _diameter/2.f;
    llp[1] = center[1] + _diameter/2.f;

    Vec2f lrp;
    lrp[0] = center[0] + _diameter/2.f;
    lrp[1] = center[1] + _diameter/2.f;

    BoundingBox bb = BoundingBox(ulp, urp, llp, lrp);
    setBoundingBox(bb);
}

// Fonction         : setBoundingBox
// Argument(s)		: - bb : la bounding box
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie la bounding box
void CsgDisk::setBoundingBox(BoundingBox &bb)
{
    _boundingBox = bb;
}
