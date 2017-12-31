#include "CsgPrimitive.h"
#include "CsgOperation.h"

// Fonction         : CsgOperation
// Argument(s)		: - operation : le type d'opération
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: constructeur (sans initialisation des fils)
CsgOperation::CsgOperation(operationTypes operation) :
    _operation(operation),
    _leftChildIsOperation(false),
    _leftChildPrimitive(nullptr),
    _leftChildOperation(nullptr),
    _rightChildIsOperation(false),
    _rightChildPrimitive(nullptr),
    _rightChildOperation(nullptr)
{
    // rien
}

//-----------------------------------------------------------------------------
// GETTERS
//-----------------------------------------------------------------------------

// Fonction         : getOperationType
// Argument(s)		: /
// Valeur de retour	: - un enum operationTypes
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le type d'opération courant
operationTypes& CsgOperation::getOperationType()
{
    return _operation;
}

// Fonction         : getLeftChildIsOperation
// Argument(s)		: /
// Valeur de retour	: vrai si le fils gauche est une opération, faux si c'est une primitive
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
bool CsgOperation::getLeftChildIsOperation()
{
    return _leftChildIsOperation;
}

// Fonction         : getRightChildIsOperation
// Argument(s)		: /
// Valeur de retour	: vrai si le fils droit est une opération, faux si c'est une primitive
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
bool CsgOperation::getRightChildIsOperation()
{
    return _rightChildIsOperation;
}

// Fonction         : getLeftChildPrimitive
// Argument(s)		: /
// Valeur de retour	: le pointeur sur le fils gauche en tant que primitive
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
CsgPrimitive *CsgOperation::getLeftChildPrimitive()
{
    return _leftChildPrimitive;
}

// Fonction         : getLeftChildOperation
// Argument(s)		: /
// Valeur de retour	: le pointeur sur le fils gauche en tant qu'opération
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
CsgOperation *CsgOperation::getLeftChildOperation()
{
    return _leftChildOperation;
}

// Fonction         : getRightChildPrimitive
// Argument(s)		: /
// Valeur de retour	: le pointeur sur le fils droit en tant que primitive
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
CsgPrimitive *CsgOperation::getRightChildPrimitive()
{
    return _rightChildPrimitive;
}

// Fonction         : getRightChildOperation
// Argument(s)		: /
// Valeur de retour	: le pointeur sur le fils droit en tant qu'opération
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
CsgOperation *CsgOperation::getRightChildOperation()
{
    return _rightChildOperation;
}

//-----------------------------------------------------------------------------
// SETTERS
//-----------------------------------------------------------------------------

// Fonction         : setLeftChildIsOperation
// Argument(s)		: - isOperation : booléen
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le type associé au fils gauche
void CsgOperation::setLeftChildIsOperation(bool isOperation)
{
    _leftChildIsOperation = isOperation;
}

// Fonction         : setRightChildIsOperation
// Argument(s)		: - isOperation : booléen
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le type associé au fils droit
void CsgOperation::setRightChildIsOperation(bool isOperation)
{
    _leftChildIsOperation = isOperation;
}

// Fonction         : setLeftChildPrimitive
// Argument(s)		: - leftChild : le fils gauche en tant que primitive
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
void CsgOperation::setLeftChildPrimitive(CsgPrimitive *leftChild)
{
    _leftChildPrimitive = leftChild;
}

// Fonction         : setLeftChildOperation
// Argument(s)		: - leftChild : le fils gauche en tant qu'opération
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
void CsgOperation::setLeftChildOperation(CsgOperation *leftChild)
{
    _leftChildOperation = leftChild;
}

// Fonction         : setRightChildIsPrimitive
// Argument(s)		: - rightChild : le fils droit en tant que primitive
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
void CsgOperation::setRightChildPrimitive(CsgPrimitive *rightChild)
{
    _rightChildPrimitive = rightChild;
}

// Fonction         : setRightChildIsOperation
// Argument(s)		: - rightChild : le fils droit en tant qu'opération
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
void CsgOperation::setRightChildOperation(CsgOperation *rightChild)
{
    _rightChildOperation = rightChild;
}
