#include "Vector.h"
#include "Matrix33d.h"
#include "Utils.h"
#include "BoundingBox.h"
#include "CsgPrimitive.h"

// Fonction         : CsgPrimitive
// Argument(s)		: - vertexNumber : le nombre de sommets du polygone
//                    - center : vecteur contenant les coordonnées du centre du polygon
// Valeur de retour	: /
// Pré-condition(s)	: vertexNumber >= 3
// Post-condition(s): /
// Commentaire(s)	: constructeur paramétré
CsgPrimitive::CsgPrimitive(Vec2f center, float distanceToOrigin) :
    _center(center),
    _distanceToOrigin(distanceToOrigin)
{
    Vec2f ulp;
    ulp[0] = center[0] - _distanceToOrigin;
    ulp[1] = center[1] - _distanceToOrigin;

    Vec2f urp;
    urp[0] = center[0] + _distanceToOrigin;
    urp[1] = center[1] - _distanceToOrigin;

    Vec2f llp;
    llp[0] = center[0] - _distanceToOrigin;
    llp[1] = center[1] + _distanceToOrigin;

    Vec2f lrp;
    lrp[0] = center[0] + _distanceToOrigin;
    lrp[1] = center[1] + _distanceToOrigin;

    // bounding box dépend du centre et de la distance à l'origine
    _boundingBox = BoundingBox(ulp, urp, llp, lrp);

    // aucune transformation au départ
    _previousTranslateX = 0;
    _previousTranslateY = 0;
}

// Fonction         : getCenter
// Argument(s)		: /
// Valeur de retour	: un vecteur contenant les coordonnées du centre
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne les coordonnées actuelles du centre du polygone régulier
Vec2f& CsgPrimitive::getCenter()
{
    return _center;
}

// Fonction         : getDistanceToOrigin
// Argument(s)		: /
// Valeur de retour	: un vecteur contenant la distance à l'origine
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne la distance à l'origine
float& CsgPrimitive::getDistanceToOrigin()
{
    return _distanceToOrigin;
}

// Fonction         : getBoundingBox
// Argument(s)		: /
// Valeur de retour	: une bounding box
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne la bounding box de la primivite
BoundingBox& CsgPrimitive::getBoundingBox()
{
    return _boundingBox;
}

// Fonction         : setCenter
// Argument(s)		: - center : vecteur contenant les nouvelles coordonnées du centre
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie les coordonnées du centre (et dnoc la bounding box)
void CsgPrimitive::setCenter(Vec2f &center)
{
    _center = center;

    Vec2f ulp;
    ulp[0] = _center[0] - _distanceToOrigin;
    ulp[1] = _center[1] - _distanceToOrigin;

    Vec2f urp;
    urp[0] = _center[0] + _distanceToOrigin;
    urp[1] = _center[1] - _distanceToOrigin;

    Vec2f llp;
    llp[0] = _center[0] - _distanceToOrigin;
    llp[1] = _center[1] + _distanceToOrigin;

    Vec2f lrp;
    lrp[0] = _center[0] + _distanceToOrigin;
    lrp[1] = _center[1] + _distanceToOrigin;

    BoundingBox bb = BoundingBox(ulp, urp, llp, lrp);
    setBoundingBox(bb);
}

// Fonction         : setDistanceToOrigin
// Argument(s)		: - distanceToOrigin : la nouvelle distance à l'origine
// Valeur de retour	: /
// Pré-condition(s)	: distanceToOigin > 0
// Post-condition(s): /
// Commentaire(s)	: modifie la distance à l'origine de la primitive (et donc la bounding box)
void CsgPrimitive::setDistanceToOrigin(float distanceToOrigin)
{
    _distanceToOrigin = distanceToOrigin;

    Vec2f ulp;
    ulp[0] = _center[0] - _distanceToOrigin;
    ulp[1] = _center[1] - _distanceToOrigin;

    Vec2f urp;
    urp[0] = _center[0] + _distanceToOrigin;
    urp[1] = _center[1] - _distanceToOrigin;

    Vec2f llp;
    llp[0] = _center[0] - _distanceToOrigin;
    llp[1] = _center[1] + _distanceToOrigin;

    Vec2f lrp;
    lrp[0] = _center[0] + _distanceToOrigin;
    lrp[1] = _center[1] + _distanceToOrigin;

    BoundingBox bb = BoundingBox(ulp, urp, llp, lrp);
    setBoundingBox(bb);
}

// Fonction         : setBoundingBox
// Argument(s)		: - bb : le nouvelle bounding box
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie la bounding box
void CsgPrimitive::setBoundingBox(BoundingBox &bb)
{
    _boundingBox = bb;
}

//-----------------------------------------------------------------------------
// SECTION DES METHODES
//-----------------------------------------------------------------------------

// Fonction         : isInsidePrimitive
// Argument(s)		: - point : vec2f contenant les coordonnées du point à tester
// Valeur de retour	: vrai si le point est dans la primitive, faux sinon
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: vérifie que le point est dans la primitive
bool CsgPrimitive::isInsidePrimitive(Vec2f &point)
{
    return false;
}

// Fonction         : updateBoundingBox
// Argument(s)		: - center : le centre de la bounding box actuelle
//                    - tx : translation en x (pixels)
//                    - ty : translation en y (pixels)
//                    - angle : angle de rotation (degrès)
//                    - scale : coefficient d'agrandissement/réduction (entier)
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: met à jour la bounding box de la pimitive après transformation
void CsgPrimitive::updateBoundingBox(Vec2f& center, int tx, int ty, int angle, double scale)
{
    // rien : dépend du la primitive elle-même
}

