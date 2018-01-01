#include "CsgPrimitive.h"
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
