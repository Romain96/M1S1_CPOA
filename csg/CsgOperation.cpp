#include "CsgPrimitive.h"
#include "BoundingBox.h"
#include "CsgOperation.h"

// Fonction         : CsgOperation
// Argument(s)		: - operation : le type d'opération
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: constructeur (sans initialisation des fils)
CsgOperation::CsgOperation(operationTypes operation) :
    _operation(operation)
{
    // rien
}

// Fonction         : getOperationType
// Argument(s)		: /
// Valeur de retour	: un enum operationTypes
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le type d'opération courant
operationTypes& CsgOperation::getOperationType()
{
    return _operation;
}

// Fonction         : getBoundingBox
// Argument(s)		: /
// Valeur de retour	: une bounding box
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne la bounding box de l'opération
BoundingBox& CsgOperation::getBoundingBox()
{
    return _boundingBox;
}

// Fonction         : setOperationType
// Argument(s)		: - operation : le nouveau type d'opération
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le type d'opération
void CsgOperation::setOperationType(operationTypes operation)
{
    _operation = operation;
}

// Fonction         : setBoundingBox
// Argument(s)		: - boundingBox : la nouvelle bounding box
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie la bounding box
void CsgOperation::setBoundingBox(BoundingBox &boundingBox)
{
    _boundingBox = boundingBox;
}
