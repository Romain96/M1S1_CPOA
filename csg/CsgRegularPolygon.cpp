#include "Vector.h"
#include "Utils.h"
#include "BoundingBox.h"
#include "CsgRegularPolygon.h"

// Fonction         : CsgRegularPolygon
// Argument(s)		: - vertexNumber : le nombre de sommets du polygone
//                    - center : vecteur contenant les coordonnées du centre du polygon
// Valeur de retour	: /
// Pré-condition(s)	: vertexNumber >= 3
// Post-condition(s): /
// Commentaire(s)	: constructeur paamétré
CsgRegularPolygon::CsgRegularPolygon(int vertexNumber, Vec2f& center) :
    _vertexNumber(vertexNumber),
    _center(center),
    _diameter(0.5f)
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

// Fonction         : getVertexNumber
// Argument(s)		: /
// Valeur de retour	: un entier contenant le nombre de sommets
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le nombre de sommets actuels du polygone régulier
int CsgRegularPolygon::getVertexNumber()
{
    return _vertexNumber;
}

// Fonction         : getCenter
// Argument(s)		: /
// Valeur de retour	: un vecteur contenant les coordonnées du centre
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne les coordonnées actuelles du centre du polygone régulier
Vec2f& CsgRegularPolygon::getCenter()
{
    return _center;
}

// Fonction         : getBoundingBox
// Argument(s)		: /
// Valeur de retour	: une bounding box
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne la bounding box du polygone régulier
BoundingBox& CsgRegularPolygon::getBoundingBox()
{
    return _boundingBox;
}

// Fonction         : setVertexNumber
// Argument(s)		: - vertexNumber : nouveau nombre de sommets
// Valeur de retour	: /
// Pré-condition(s)	: vertexNumber >= 3
// Post-condition(s): /
// Commentaire(s)	: modifie le nombre de sommets
void CsgRegularPolygon::setVertexNumber(int vertexNumber)
{
    _vertexNumber = vertexNumber;
}

// Fonction         : setCenter
// Argument(s)		: - center : vecteur contenant les nouvelles coordonnées du centre
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie les coordonnées du centre (et dnoc la bounding box)
void CsgRegularPolygon::setCenter(Vec2f &center)
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
// Argument(s)		: - bb : le nouvelle bounding box
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie la bounding box
void CsgRegularPolygon::setBoundingBox(BoundingBox &bb)
{
    _boundingBox = bb;
}
