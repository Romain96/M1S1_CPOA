#include "Vector.h"
#include "Matrix33d.h"
#include "Utils.h"
#include "BoundingBox.h"
#include "CsgRegularPolygon.h"
#include <iostream>
#include <cmath>

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
    _vertexList = new Vec2f[_vertexNumber];
    _startingAngle = 0;

    Vec2f point;
    double angle = 360.f / (double)_vertexNumber;
    double currentAngle = _startingAngle;

    for (int i = 0; i < _vertexNumber; i++)
    {
        point[0] = _center[0] + _distanceToOrigin * cos(currentAngle * M_PI/180);
        point[1] = _center[1] + _distanceToOrigin * sin(currentAngle * M_PI/180);
        _vertexList[i] = point;
        std::cout << "init pts : " << point[0] << " " << point[1] << std::endl;
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
        if (((_vertexList[i][1] > point[1]) != (_vertexList[j][1] > point[1])) &&
                (point[0] < _vertexList[i][0] + (_vertexList[j][0] - _vertexList[i][0]) * (point[1] - _vertexList[i][1]) /
                                (_vertexList[j][1] - _vertexList[i][1])))
        {
            state = !state;
        }
        j = i;
    }

    return state;
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
void CsgRegularPolygon::updateBoundingBox(Vec2f& center, int tx, int ty, int angle, double scale)
{
    // les translations correspondent simplement au coordonnées de bounding box translatées
    // les homothéties et rotation demandent de recalculer les points temporairement
    std::cout << "updating BB for poly with tx = " << tx << " ty = " << ty << " angle = " << angle << " scale = " << scale << std::endl;

    Vec2f point;
    double angleStep = 360.f / (double)_vertexNumber;
    double currentAngle = (double)(_startingAngle + angle);
    std::cout << "starting angle is " << currentAngle << std::endl;
    int xmin = 1024;
    int xmax = 0;
    int ymin = 1024;
    int ymax = 0;

    int realTx = tx - _previousTranslateX;
    int realTy = ty - _previousTranslateY;
    _previousTranslateX = tx;
    _previousTranslateY = ty;

    for (int i = 0; i < _vertexNumber; i++)
    {
        point[0] = (center[0] + realTx) + (_distanceToOrigin * scale) * cos(currentAngle * M_PI/180.f);
        point[1] = (center[1] + realTy) + (_distanceToOrigin * scale) * sin(currentAngle * M_PI/180.f);
        std::cout << "new pts : " << point[0] << " " << point[1] << std::endl;
        currentAngle = std::fmod(currentAngle + angleStep, 360.f);
        if (point[0] < xmin)
            xmin = point[0];
        if (point[0] > xmax)
            xmax = point[0];
        if (point[1] < ymin)
            ymin = point[1];
        if (point[1] > ymax)
            ymax = point[1];
    }
    // la nouvelle bounding box a pour coordonnées
    Vec2f ulp;
    ulp[0] = std::max(0, (int)(center[0] - (center[0] - xmin) * scale));
    ulp[1] = std::max(0, (int)(center[1] - (center[1] - ymin) * scale));

    Vec2f urp;
    urp[0] = std::min(1023, (int)(center[0] + (xmax - center[0]) * scale));
    urp[1] = std::max(0, (int)(center[1] - (center[1] - ymin) * scale));

    Vec2f llp;
    llp[0] = std::max(0, (int)(center[0] - (center[0] - xmin) * scale));
    llp[1] = std::min(1023, (int)(center[1] + (ymax - center[1]) * scale));

    Vec2f lrp;
    lrp[0] = std::min(1024, (int)(center[0] + (xmax - center[0]) * scale));
    lrp[1] = std::min(1023, (int)(center[1] + (ymax - center[1]) * scale));

    // debug
    std::cout << "ulp " << ulp[0] << " " << ulp[1] << std::endl;
    std::cout << "urp " << urp[0] << " " << ulp[1] << std::endl;
    std::cout << "llp " << llp[0] << " " << llp[1] << std::endl;
    std::cout << "lrp " << lrp[0] << " " << lrp[1] << std::endl;

    _boundingBox = BoundingBox(ulp, urp, llp, lrp);

}
