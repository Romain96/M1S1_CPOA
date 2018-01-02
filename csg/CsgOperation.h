#ifndef __CSGOPERATION_H__
#define __CSGOPERATION_H__

#include "CsgPrimitive.h"
#include "BoundingBox.h"

// types d'opérations possibles
enum class operationTypes
{
    NONE,           // un arbre contenant uniquement un noeud avec un primtive (pas d'opération)
    UNION,          // union des fils gauche et droit du noeud
    INTERSECTION,   // intersection des fils gauche et droit du noeud
    DIFFERENCE      // différence du fils gauche par le fils droit du noeud
};

class CsgOperation
{
protected:
    // type d'opération
    operationTypes _operation;

    // bounding box de l'opération
    BoundingBox _boundingBox;

public:
    // constructeur
    CsgOperation(operationTypes operation);

    // getters
    operationTypes& getOperationType();
    BoundingBox& getBoundingBox();

    // setters
    void setOperationType(operationTypes operation);
    void setBoundingBox(BoundingBox& boundingBox);
};

#endif // __CSGOPERATION_H__
