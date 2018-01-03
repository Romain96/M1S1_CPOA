#include "BoundingBox.h"

// Fonction         : BoundingBox
// Argument(s)		: /
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: constructeur non paramétré
BoundingBox::BoundingBox() :
    _upper_left_point(Vec2f()),
    _upper_right_point(Vec2f()),
    _lower_left_point(Vec2f()),
    _lower_right_point(Vec2f())
{
    // rien
}

// Fonction         : BoundingBox
// Argument(s)		: - ulp : vecteur contenant les coordonnées du point supérieur gauche
//                    - urp : vecteur contenant les coordonnées du point supérieur droit
//                    - llp : vecteur contenant les coordonnées du point inférieur gauche
//                    - lrp : vecteur contenant les coordonnées du point inférieur droit
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: constructeur paramétré
BoundingBox::BoundingBox(Vec2f &ulp, Vec2f &urp, Vec2f &llp, Vec2f &lrp) :
    _upper_left_point(ulp),
    _upper_right_point(urp),
    _lower_left_point(llp),
    _lower_right_point(lrp)
{
    // rien
}

// Fonction         : getUpperLeftPoint
// Argument(s)		: /
// Valeur de retour	: un vecteur contenant les coordonnées du point supérieur gauche
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne les coordonnées actuelles du point supérieur gauche de la bounding box
const Vec2f& BoundingBox::getUpperLeftPoint() const
{
    return _upper_left_point;
}

// Fonction         : getUpperRightPoint
// Argument(s)		: /
// Valeur de retour	: un vecteur contenant les coordonnées du point supérieur droit
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne les coordonnées actuelles du point supérieur droit de la bounding box
const Vec2f& BoundingBox::getUpperRightPoint() const
{
    return _upper_right_point;
}

// Fonction         : getLowerLeftPoint
// Argument(s)		: /
// Valeur de retour	: un vecteur contenant les coordonnées du point inférieur gauche
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne les coordonnées actuelles du point inférieur gauche de la bounding box
const Vec2f& BoundingBox::getLowerLeftPoint() const
{
    return _lower_left_point;
}

// Fonction         : getLowerRightPoint
// Argument(s)		: /
// Valeur de retour	: un vecteur contenant les coordonnées du point inférieur droit
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne les coordonnées actuelles du point inférieur droit de la bounding box
const Vec2f& BoundingBox::getLowerRightPoint() const
{
    return _lower_right_point;
}

// Fonction         : operator +
// Argument(s)		: - bb1 : bounding box 1
//                    - bb2 : bounding box 2
// Valeur de retour	: une nouvelle bounding box
// Pré-condition(s)	: toutes les coordonnées doivent être comprises dans l'image
// Post-condition(s): /
// Commentaire(s)	: crée une nouvelle bounding box résultat de l'union des deux bounding box arguments
BoundingBox& operator +(BoundingBox& bb1, BoundingBox& bb2)
{
    // nouveaux points délimitant la bounding box union
    Vec2f ulp;
    Vec2f urp;
    Vec2f llp;
    Vec2f lrp;

    // le point supérieur gauche est (x plus petit, y plus petit)
    if (bb1.getUpperLeftPoint()[0] < bb2.getUpperLeftPoint()[0])
        ulp[0] = bb1.getUpperLeftPoint()[0];
    else
        ulp[0] = bb2.getUpperLeftPoint()[0];

    if (bb1.getUpperLeftPoint()[1] < bb2.getUpperLeftPoint()[1])
        ulp[1] = bb1.getUpperLeftPoint()[1];
    else
        ulp[1] = bb2.getUpperLeftPoint()[1];

    // le point supérieur droit est  (x plus grand, y plus petit)
    if (bb1.getUpperRightPoint()[0] > bb2.getUpperRightPoint()[0])
        urp[0] = bb1.getUpperRightPoint()[0];
    else
        urp[0] = bb2.getUpperRightPoint()[0];

    if (bb1.getUpperRightPoint()[1] < bb2.getUpperRightPoint()[1])
        urp[1] = bb1.getUpperRightPoint()[1];
    else
        urp[1] = bb2.getUpperRightPoint()[1];

    // le point inférieur gauche est (x plus petit, y plus grand)
    if (bb1.getLowerLeftPoint()[0] < bb2.getLowerLeftPoint()[0])
        llp[0] = bb1.getLowerLeftPoint()[0];
    else
        llp[0] = bb2.getLowerLeftPoint()[0];

    if (bb1.getLowerLeftPoint()[1] > bb2.getLowerLeftPoint()[1])
        llp[1] = bb1.getLowerLeftPoint()[1];
    else
        llp[1] = bb2.getLowerLeftPoint()[1];

    // le point inférieur droit est  (x plus grand, y plus grand)
    if (bb1.getLowerRightPoint()[0] > bb2.getLowerRightPoint()[0])
        lrp[0] = bb1.getLowerRightPoint()[0];
    else
        lrp[0] = bb2.getLowerRightPoint()[0];

    if (bb1.getLowerRightPoint()[1] > bb2.getLowerRightPoint()[1])
        lrp[1] = bb1.getLowerRightPoint()[1];
    else
        lrp[1] = bb2.getLowerRightPoint()[1];

    // DEBUG
    std::cout << "upper left point : " << ulp[0] << "," << ulp[1] << std::endl;
    std::cout << "upper right point : " << urp[0] << "," << urp[1] << std::endl;
    std::cout << "lower left point : " << llp[0] << "," << llp[1] << std::endl;
    std::cout << "lower right point : " << lrp[0] << "," << lrp[1] << std::endl;

    // on retourne la nouvelle bounding box
    static BoundingBox bb = BoundingBox(ulp, lrp, llp, lrp);
    return bb;
}

// Fonction         : operator ^
// Argument(s)		: - bb1 : bounding box 1
//                    - bb2 : bounding box 2
// Valeur de retour	: une nouvelle bounding box
// Pré-condition(s)	: toutes les coordonnées doivent être comprises dans l'image
// Post-condition(s): /
// Commentaire(s)	: crée une nouvelle bounding box résultat de l'intersection des deux bounding box arguments
BoundingBox& operator ^(BoundingBox& bb1, BoundingBox& bb2)
{
    // nouveaux points délimitant la bounding box union
    Vec2f ulp;
    Vec2f urp;
    Vec2f llp;
    Vec2f lrp;

    // le point supérieur gauche est (x plus grand, y plus grand)
    if (bb1.getUpperLeftPoint()[0] > bb2.getUpperLeftPoint()[0])
        ulp[0] = bb1.getUpperLeftPoint()[0];
    else
        ulp[0] = bb2.getUpperLeftPoint()[0];

    if (bb1.getUpperLeftPoint()[1] > bb2.getUpperLeftPoint()[1])
        ulp[1] = bb1.getUpperLeftPoint()[1];
    else
        ulp[1] = bb2.getUpperLeftPoint()[1];

    // le point supérieur droit est  (x plus petit, y plus grand)
    if (bb1.getUpperRightPoint()[0] < bb2.getUpperRightPoint()[0])
        urp[0] = bb1.getUpperRightPoint()[0];
    else
        urp[0] = bb2.getUpperRightPoint()[0];

    if (bb1.getUpperRightPoint()[1] > bb2.getUpperRightPoint()[1])
        urp[1] = bb1.getUpperRightPoint()[1];
    else
        urp[1] = bb2.getUpperRightPoint()[1];

    // le point inférieur gauche est (x plus grand, y plus petit)
    if (bb1.getLowerLeftPoint()[0] > bb2.getLowerLeftPoint()[0])
        llp[0] = bb1.getLowerLeftPoint()[0];
    else
        llp[0] = bb2.getLowerLeftPoint()[0];

    if (bb1.getLowerLeftPoint()[1] < bb2.getLowerLeftPoint()[1])
        llp[1] = bb1.getLowerLeftPoint()[1];
    else
        llp[1] = bb2.getLowerLeftPoint()[1];

    // le point inférieur droit est  (x plus petit, y plus petit)
    if (bb1.getLowerRightPoint()[0] < bb2.getLowerRightPoint()[0])
        lrp[0] = bb1.getLowerRightPoint()[0];
    else
        lrp[0] = bb2.getLowerRightPoint()[0];

    if (bb1.getLowerRightPoint()[1] < bb2.getLowerRightPoint()[1])
        lrp[1] = bb1.getLowerRightPoint()[1];
    else
        lrp[1] = bb2.getLowerRightPoint()[1];

    // DEBUG
    std::cout << "upper left point : " << ulp[0] << "," << ulp[1] << std::endl;
    std::cout << "upper right point : " << urp[0] << "," << urp[1] << std::endl;
    std::cout << "lower left point : " << llp[0] << "," << llp[1] << std::endl;
    std::cout << "lower right point : " << lrp[0] << "," << lrp[1] << std::endl;

    // on retourne la nouvelle bounding box
    static BoundingBox bb = BoundingBox(ulp, lrp, llp, lrp);
    return bb;
}

// Fonction         : operator -
// Argument(s)		: - bb1 : bounding box 1
//                    - bb2 : bounding box 2
// Valeur de retour	: une nouvelle bounding box
// Pré-condition(s)	: toutes les coordonnées doivent être comprises dans l'image
// Post-condition(s): /
// Commentaire(s)	: crée une nouvelle bounding box résultat de la différence des deux bounding box arguments
BoundingBox& operator -(BoundingBox& bb1, BoundingBox& bb2)
{
    // nouveaux points délimitant la bounding box union
    Vec2f ulp = bb1.getUpperLeftPoint();
    Vec2f urp = bb1.getUpperRightPoint();
    Vec2f llp = bb1.getLowerLeftPoint();
    Vec2f lrp = bb1.getLowerRightPoint();

    // traité le plus simplement possible : bounding box de bb1

    // DEBUG
    std::cout << "upper left point : " << ulp[0] << "," << ulp[1] << std::endl;
    std::cout << "upper right point : " << urp[0] << "," << urp[1] << std::endl;
    std::cout << "lower left point : " << llp[0] << "," << llp[1] << std::endl;
    std::cout << "lower right point : " << lrp[0] << "," << lrp[1] << std::endl;

    // on retourne la nouvelle bounding box
    static BoundingBox bb = BoundingBox(ulp, lrp, llp, lrp);
    return bb;
}
