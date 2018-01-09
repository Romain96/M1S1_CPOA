#include "CsgPrimitive.h"
#include "CsgOperation.h"
#include "BoundingBox.h"
#include "CsgNode.h"

int CsgNode::_nodeUniqueIdGenerator = 0;

// Fonction         : CsgNode
// Argument(s)		: - operation : le type d'opération du noeud
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: constructeur paramétré
CsgNode::CsgNode(CsgOperation operation) :
    _operation(operation),
    _matrix(),
    _leftChild(nullptr),
    _rightChild(nullptr),
    _primitive(nullptr),
    _previousTranslationX(0),
    _previousTranslationY(0)
{
    // génération de l'id du noeud
    _nodeId = _nodeUniqueIdGenerator++;
}

// Fonction         : ~CsgNode
// Argument(s)		: /
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: destructeur
CsgNode::~CsgNode()
{
    if (_leftChild != nullptr)
        delete _leftChild;
    if (_rightChild != nullptr)
        delete _rightChild;
}

//-----------------------------------------------------------------------------
// SECTION DES GETTERS
//-----------------------------------------------------------------------------

// Fonction         : getId
// Argument(s)		: /
// Valeur de retour	: un entier
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne l'id du noeud
int CsgNode::getId()
{
    return _nodeId;
}

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

// Fonction         : getMatrix
// Argument(s)		: /
// Valeur de retour	: une matrix33d
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne la matrice de transformation de l'opération
Matrix33d& CsgNode::getMatrix()
{
    return _matrix;
}

// Fonction         : getLeftChild
// Argument(s)		: /
// Valeur de retour	: un pointeur sur une CsgNode
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le fils gauche en tant qu'opération
CsgNode *CsgNode::getLeftChild()
{
    return _leftChild;
}

// Fonction         : getRightChild
// Argument(s)		: /
// Valeur de retour	: un pointeur sur une CsgNode
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le fils droit en tant qu'opération
CsgNode *CsgNode::getRightChild()
{
    return _rightChild;
}

// Fonction         : getPrimitive
// Argument(s)		: /
// Valeur de retour	: un pointeur sur un CsgPrimitive
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le pointeur sur la primitive
CsgPrimitive *CsgNode::getPrimitive()
{
    return _primitive;
}

//-----------------------------------------------------------------------------
// SECTION DES SETTERS
//-----------------------------------------------------------------------------

// Fonction         : setId
// Argument(s)		: - id : le nouvel id du noeud
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie l'id du node
void CsgNode::setId(int id)
{
    _nodeId = id;
}

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

// Fonction         : CsgNode
// Argument(s)		: - mat : la nouvelle matrice
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie la matrice de transformation de l'opération
void CsgNode::setMatrix(Matrix33d &mat)
{
    _matrix = mat;
}

// Fonction         : setLeftChild
// Argument(s)		: - leftChild : pointeur sur un CsgNode
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le pointeur du fils gauche en tant qu'opération
void CsgNode::setLeftChild(CsgNode *leftChild)
{
    if (_leftChild != nullptr)
        delete _leftChild;
    _leftChild = leftChild;
}

// Fonction         : setRightChild
// Argument(s)		: - rightChild : pointeur sur un CsgNode
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le pointeur du fils droit en tant qu'opération
void CsgNode::setRightChild(CsgNode *rightChild)
{
    if (_rightChild != nullptr)
        delete _rightChild;
    _rightChild = rightChild;
}

// Fonction         : setPrimitive
// Argument(s)		: - rightChild : pointeur sur un CsgPrimitive
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le pointeur sur la primitive
void CsgNode::setPrimitive(CsgPrimitive *primitive)
{
    _primitive = primitive;
}

//-----------------------------------------------------------------------------
// SECTION DES METHODES
//-----------------------------------------------------------------------------

// Fonction         : isInsideOperation
// Argument(s)		: - point : vec2f contenant les coordonnées du point à tester
// Valeur de retour	: vrai si le point est dans la forme représentée par l'opération, faux sinon
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: /
bool CsgNode::isInsideOperation(Vec2f &point)
{
    Vec3f localLeftChild;
    Vec3f localRightChild;
    Vec2f pointLeftChild;
    Vec2f pointRightChild;

    switch (_operation.getOperationType())
    {
    // primitive : appel à isInsidePrimitive()
    case operationTypes::NONE:
        return _primitive->isInsidePrimitive(point);
        break;

    // union : pixel dans le fils droit ou dans le fils gauche
    case operationTypes::UNION:
        // postionnement du point dans les repères locaux des fils gauche et droit
        localLeftChild = _leftChild->getMatrix().inverse() * point;
        localRightChild = _rightChild->getMatrix().inverse() * point;
        pointLeftChild[0] = localLeftChild[0];
        pointLeftChild[1] = localLeftChild[1];
        pointRightChild[0] = localRightChild[0];
        pointRightChild[1] = localRightChild[1];

        return _leftChild->isInsideOperation(pointLeftChild) || _rightChild->isInsideOperation(pointRightChild);
        break;

    // intersection : pixel dans le fils droit et dans le fils gauche
    case operationTypes::INTERSECTION:
        // postionnement du point dans les repères locaux des fils gauche et droit
        localLeftChild = _leftChild->getMatrix().inverse() * point;
        localRightChild = _rightChild->getMatrix().inverse() * point;
        pointLeftChild[0] = localLeftChild[0];
        pointLeftChild[1] = localLeftChild[1];
        pointRightChild[0] = localRightChild[0];
        pointRightChild[1] = localRightChild[1];

        return _leftChild->isInsideOperation(pointLeftChild) && _rightChild->isInsideOperation(pointRightChild);
        break;

    // différence : pixel dans le fils gauche et pas dans le fils droit
    case operationTypes::DIFFERENCE:  
        // postionnement du point dans les repères locaux des fils gauche et droit
        localLeftChild = _leftChild->getMatrix().inverse() * point;
        localRightChild = _rightChild->getMatrix().inverse() * point;
        pointLeftChild[0] = localLeftChild[0];
        pointLeftChild[1] = localLeftChild[1];
        pointRightChild[0] = localRightChild[0];
        pointRightChild[1] = localRightChild[1];

        return _leftChild->isInsideOperation(pointLeftChild) && !_rightChild->isInsideOperation(pointRightChild);
        break;
    default:
        std::cout << "CsgNode::isInsideOperation unknown operation" << std::endl;
        return false;
        break;
    }
}

// Fonction         : ModifyNodeGeneratorValue
// Argument(s)		: - i : valeur de modification
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le compteur servant à générer les id de noeuds
void CsgNode::ModifyNodeGeneratorValue(int i)
{
    _nodeUniqueIdGenerator += i;
}
