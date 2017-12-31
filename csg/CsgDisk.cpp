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
