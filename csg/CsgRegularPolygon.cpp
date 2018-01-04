#include "Vector.h"
#include "Matrix33d.h"
#include "Utils.h"
#include "BoundingBox.h"
#include "CsgRegularPolygon.h"
#include <iostream>
#include <map>
#include <math.h>

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
    _vertexList = std::map<int, Vec2f>();
    Vec2f point;
    double angle = 360.f / (double)_vertexNumber;
    double currentAngle = 0.f;

    for (int i = 0; i < _vertexNumber; i++)
    {
        point[0] = _distanceToOrigin * cos(currentAngle);
        point[1] = _distanceToOrigin * sin(currentAngle);
        _vertexList.insert(std::pair<int, Vec2f>(i, point));
        currentAngle += angle;
    }
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

// Fonction         : isInsidePrimitive
// Argument(s)		: - point : vec2f contenant les coordonnées du point à tester
// Valeur de retour	: vrai si le point est dans la primitive, faux sinon
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: vérifie que le point est dans la primitive (polygone)
bool CsgRegularPolygon::isInsidePrimitive(Vec2f &point)
{
    // algorithme du lancer de rayon avec comme rayon [(point[0],point[1]);(0,0)]
    // le point est dans le polygone si le nombre d'intersections avec les arêtes du polygone est impair
    int j = _vertexNumber - 1;
    bool state = false;

    for (int i = 0; i < _vertexNumber; i++)
    {
        if ((_vertexList[i][1] > point[1]) != (_vertexList[j][1] > point[1]) &&
                (point[0] < _vertexList[i][0]) + (_vertexList[j][0] - _vertexList[i][0]) * (point[1] - _vertexList[i][1]) /
                (_vertexList[j][1] - _vertexList[i][1]))
        {
            state = !state;
        }
        j = i;
    }

    return state;
}
