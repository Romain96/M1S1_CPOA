#include "CsgPrimitive.h"
#include "CsgOperation.h"
#include "CsgNode.h"

// Fonction         : CsgNode
// Argument(s)		: - operation : le type d'opération du noeud
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: constructeur paramétré
CsgNode::CsgNode(CsgOperation &operation) :
    _operation(operation),
    _leftChildIsPrimitive(true),
    _leftChildPrimitive(nullptr),
    _leftChildOperation(nullptr),
    _rightChildIsPrimitive(true),
    _rightChildPrimitive(nullptr),
    _rightChildOperation(nullptr)
{
    // rien
}

// Fonction         : ~CsgNode
// Argument(s)		: /
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: destructeur
CsgNode::~CsgNode()
{
    if (_leftChildPrimitive != nullptr)
        delete _leftChildPrimitive;
    if (_leftChildOperation != nullptr)
        delete _leftChildOperation;
    if (_rightChildPrimitive != nullptr)
        delete _rightChildPrimitive;
    if (_rightChildOperation != nullptr)
        delete _rightChildOperation;
}

//-----------------------------------------------------------------------------
// SECTION DES GETTERS
//-----------------------------------------------------------------------------

// Fonction         : getOperation
// Argument(s)		: /
// Valeur de retour	: un CsgOperation représentant le type d'opération du noeud
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
CsgOperation& CsgNode::getOperation()
{
    return _operation;
}

// Fonction         : getLeftChildIsPrimitive
// Argument(s)		: /
// Valeur de retour	: vrai si le fils gauche est une primitive, faux sinon
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
bool CsgNode::getLeftChildIsPrimitive()
{
    return _leftChildIsPrimitive;
}

// Fonction         : getRightChildIsPrimitive
// Argument(s)		: /
// Valeur de retour	: vrai si le fils droit est une primitive, faux sinon
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
bool CsgNode::getRightChildIsPrimitive()
{
    return _rightChildIsPrimitive;
}

// Fonction         : getLeftChildPrimitive
// Argument(s)		: /
// Valeur de retour	: un pointeur sur un CsgPrimitive
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le fils gauche en tant que primitive
CsgPrimitive *CsgNode::getLeftChildPrimitive()
{
    return _leftChildPrimitive;
}

// Fonction         : getRightChildPrimitive
// Argument(s)		: /
// Valeur de retour	: un pointeur sur un CsgPrimitive
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le fils droit en tant que primitive
CsgPrimitive *CsgNode::getRightChildPrimitive()
{
    return _rightChildPrimitive;
}

// Fonction         : getLeftChildOperation
// Argument(s)		: /
// Valeur de retour	: un pointeur sur une CsgOperation
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le fils gauche en tant qu'opération
CsgOperation *CsgNode::getLeftChildOperation()
{
    return _leftChildOperation;
}

// Fonction         : getRightChildOperation
// Argument(s)		: /
// Valeur de retour	: un pointeur sur une CsgOperation
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le fils droit en tant qu'opération
CsgOperation *CsgNode::getRightChildOperation()
{
    return _rightChildOperation;
}

//-----------------------------------------------------------------------------
// SECTION DES SETTERS
//-----------------------------------------------------------------------------

// Fonction         : setOperation
// Argument(s)		: - operation : le nouveau type d'opération
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le type d'opération du noeud
void CsgNode::setOperation(CsgOperation &operation)
{
    _operation = operation;
}

// Fonction         : setLeftChildIsPrimitive
// Argument(s)		: - isPrimitve : booléen indiquant si le fils gauche est une primitive
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le pointeur à utiliser (vrai pour une primitive, faux pour une opération)
void CsgNode::setLeftChildIsPrimitive(bool isPrimitive)
{
    _leftChildIsPrimitive = isPrimitive;
}

// Fonction         : setRightChildIsPrimitive
// Argument(s)		: - isPrimitve : booléen indiquant si le fils droit est une primitive
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le pointeur à utiliser (vrai pour une primitive, faux pour une opération)
void CsgNode::setRightChildIsPrimitive(bool isPrimitive)
{
    _rightChildIsPrimitive = isPrimitive;
}

// Fonction         : setLeftChildPrimitive
// Argument(s)		: - leftChild : pointeur sur un CsgPrimitive
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le pointeur du fils gauche en tant que primitive
void CsgNode::setLeftChildPrimitive(CsgPrimitive *leftChild)
{
    if (_leftChildPrimitive != nullptr)
        delete _leftChildPrimitive;
    _leftChildPrimitive = leftChild;
}

// Fonction         : setRightChildPrimitive
// Argument(s)		: - rightChild : pointeur sur un CsgPrimitive
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le pointeur du fils droit en tant que primitive
void CsgNode::setRightChildPrimitive(CsgPrimitive *rightChild)
{
    if (_rightChildPrimitive != nullptr)
        delete _rightChildPrimitive;
    _rightChildPrimitive = rightChild;
}

// Fonction         : setLeftChildOperation
// Argument(s)		: - leftChild : pointeur sur un CsgOperation
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le pointeur du fils gauche en tant qu'opération
void CsgNode::setLeftChildOperation(CsgOperation *leftChild)
{
    if (_leftChildOperation != nullptr)
        delete _leftChildOperation;
    _leftChildOperation = leftChild;
}

// Fonction         : setRightChildOperation
// Argument(s)		: - rightChild : pointeur sur un CsgPrimitive
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le pointeur du fils droit en tant qu'opération
void CsgNode::setRightChildOperation(CsgOperation *rightChild)
{
    if (_rightChildOperation != nullptr)
        delete _rightChildOperation;
    _rightChildOperation = rightChild;
}
