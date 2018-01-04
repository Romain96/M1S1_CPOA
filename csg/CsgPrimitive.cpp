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
    // matrice de transformation identité au départ
    _matrix = Matrix33d();

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

// Fonction         : getMatrix
// Argument(s)		: /
// Valeur de retour	: la matrice de transformation actuelle
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne la matrice de transformation actuelle de la primitive
Matrix33d& CsgPrimitive::getMatrix()
{
    return _matrix;
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

// Fonction         : setMatrix
// Argument(s)		: - mat :  la nouvelle matrice de transformation
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie la matrice de transformation de la primitive
void CsgPrimitive::setMatrix(Matrix33d &mat)
{
    _matrix = mat;
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

// Fonction         : isInsidePrimitive
// Argument(s)		: - point : vec2f contenant les coordonnées du point à tester
// Valeur de retour	: vrai si le point est dans la primitive, faux sinon
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: vérifie que le point est dans la primitive
bool CsgPrimitive::isInsidePrimitive(Vec2f &point)
{
    // rien
    return false;
}

