#include "Vector.h"
#include "Matrix33d.h"
#include "Utils.h"
#include "BoundingBox.h"
#include "CsgRegularPolygon.h"

// Fonction         : CsgRegularPolygon
// Argument(s)		: - vertexNumber : le nombre de sommets du polygone
//                    - center : vecteur contenant les coordonnées du centre du polygon
//                    - distanceToOrigin : distance des points du polygone au centre
// Valeur de retour	: /
// Pré-condition(s)	: vertexNumber >= 3
// Post-condition(s): /
// Commentaire(s)	: constructeur paramétré
CsgRegularPolygon::CsgRegularPolygon(int vertexNumber, Vec2f &center, float distanceToOrigin) :
    CsgPrimitive(center, distanceToOrigin)
{
    _vertexNumber = vertexNumber;
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
