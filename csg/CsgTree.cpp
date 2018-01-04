#include <iostream>
#include <map>
#include "CsgNode.h"
#include "CsgTree.h"
#include "CsgOperation.h"

// initialisation du compteur de noeud et d'arbre
int CsgTree::_nodeCounter = 0;
int CsgTree::_treeCounter = 0;

// Fonction         : CsgTree
// Argument(s)      : /
// Valeur de retour : /
// Pré-condition(s) : /
// Post-condition(s): /
// Commentaire(s)   : constructeur
CsgTree::CsgTree() :
    _roots(),
    _nodes()
{
    // rien;
}

// Fonction         : getNode
// Argument(s)		: - i : le numéro du node
// Valeur de retour	: un node
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le node d'indice i
CsgNode* CsgTree::getNode(int i)
{
    return _nodes[i];
}

// Fonction         : getLastInsertedNode
// Argument(s)		: /
// Valeur de retour	: un node
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le dernier noeud inséré dans la liste des noeuds
CsgNode* CsgTree::getLastInsertedNode()
{
    std::cout << "returning node at index " << _nodeCounter - 1 << std::endl;
    return _nodes[_nodeCounter - 1];
}

// Fonction         : getLastNodeId
// Argument(s)		: /
// Valeur de retour	: un entier
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne l'e dernier noeud inséré dans la liste des noeuds'id di dernier noeud inséré
int CsgTree::getLastNodeId()
{
    return _nodeCounter - 1;
}

// Fonction         : setNode
// Argument(s)		: - node : le nouveau noeud
//                    - i : l'indice du noeud
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: modifie le noeud i
void CsgTree::setNode(CsgNode *node, int i)
{
    _nodes[i] = node;
}

// Fonction         : clear
// Argument(s)		: /
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: vide l'arbre et réinitialise les compteurs
void CsgTree::clear()
{
    _nodes.clear();
    _roots.clear();
    _nodeCounter = 0;
    _treeCounter = 0;
}

// Fonction         : addPrimitive
// Argument(s)		: - primitive : nouvelle primitive à ajouter
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: ajoute un nouvel arbre contenant la primiitve
void CsgTree::addPrimitive(CsgPrimitive *primitive)
{
    std::cout << "creating node" << std::endl;

    // génération d'un noeud sans opération
    CsgNode *node = new CsgNode(operationTypes::NONE);
    node->setLeftChildIsPrimitive(true);
    node->setLeftChildPrimitive(primitive);
    node->getOperation().setBoundingBox(primitive->getBoundingBox());

    // ce noeud représente un nouvel arbre
    _roots.insert(std::pair<int, CsgNode*>(_treeCounter, node));
    _treeCounter++;

    // et il est référencé dans la liste des noeuds
    _nodes.insert(std::pair<int, CsgNode*>(_nodeCounter, node));
    _nodeCounter++;
}

//-----------------------------------------------------------------------------
// VARIANTES DE JOINPRIMITIVES
//-----------------------------------------------------------------------------

// Fonction         : joinPrimitive
// Argument(s)		: - oper : pointeur sur l'opération
//                    - leftChild : pointeur sur une CsgPrimitive
//                    - rightChild : pointeur sur une CsgPrimitive
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: regroupe les deux primitives/opération dans un nouveau noeud
void CsgTree::joinPrimitives(CsgOperation *operation, CsgPrimitive *leftChild, CsgPrimitive *rightChild)
{
    // calcul de la bounding box du noeud
    BoundingBox bb;
    switch (operation->getOperationType())
    {
        case operationTypes::UNION:
            bb = leftChild->getBoundingBox() + rightChild->getBoundingBox();
            break;
        case operationTypes::INTERSECTION:
            bb = leftChild->getBoundingBox() ^ rightChild->getBoundingBox();
            break;
        case operationTypes::DIFFERENCE:
            bb = leftChild->getBoundingBox() - rightChild->getBoundingBox();
            break;
        case operationTypes::NONE:
        default:
            break;
    }
    operation->setBoundingBox(bb);

    // génération d'un nouveau noeud
    CsgNode *node = new CsgNode(operation->getOperationType());
    node->setLeftChildIsPrimitive(true);
    node->setRightChildIsPrimitive(true);
    node->setLeftChildPrimitive(leftChild);
    node->setRightChildPrimitive(rightChild);

    // ajout dans la liste des noeuds
    _nodes.insert(std::pair<int, CsgNode*>(_nodeCounter, node));
    _nodeCounter++;

    // ce noeud devient la racine d'un nouvel arbre
    _roots.insert(std::pair<int, CsgNode*>(_treeCounter, node));
    _treeCounter++;

    std::cout << "primitive & primitive regrouped into new node" << std::endl;
}

// Fonction         : joinPrimitive
// Argument(s)		: - oper : pointeur sur l'opération
//                    - leftChild : pointeur sur une CsgOperation
//                    - rightChild : pointeur sur une CsgPrimitive
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: regroupe les deux primitives/opération dans un nouveau noeud
void CsgTree::joinPrimitives(CsgOperation *operation, CsgNode *leftChild, CsgPrimitive *rightChild)
{
    // calcul de la bounding box du noeud
    BoundingBox bb;
    switch (operation->getOperationType())
    {
        case operationTypes::UNION:
            bb = leftChild->getOperation().getBoundingBox() + rightChild->getBoundingBox();
            break;
        case operationTypes::INTERSECTION:
            bb = leftChild->getOperation().getBoundingBox() ^ rightChild->getBoundingBox();
            break;
        case operationTypes::DIFFERENCE:
            bb = leftChild->getOperation().getBoundingBox() - rightChild->getBoundingBox();
            break;
        case operationTypes::NONE:
        default:
            break;
    }
    operation->setBoundingBox(bb);

    // génération d'un nouveau noeud
    CsgNode *node = new CsgNode(operation->getOperationType());
    node->setLeftChildIsPrimitive(false);
    node->setRightChildIsPrimitive(true);
    node->setLeftChildOperation(leftChild);
    node->setRightChildPrimitive(rightChild);

    // ajout dans la liste des noeuds
    _nodes.insert(std::pair<int, CsgNode*>(_nodeCounter, node));
    _nodeCounter++;

    // ce noeud devient la racine d'un nouvel arbre
    _roots.insert(std::pair<int, CsgNode*>(_treeCounter, node));
    _treeCounter++;

    std::cout << "operation & primitive regrouped into new node" << std::endl;
}

// Fonction         : joinPrimitive
// Argument(s)		: - oper : pointeur sur l'opération
//                    - leftChild : pointeur sur une CsgPrimitive
//                    - rightChild : pointeur sur une CsgNode
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: regroupe les deux primitives/opération dans un nouveau noeud
void CsgTree::joinPrimitives(CsgOperation *operation, CsgPrimitive *leftChild, CsgNode *rightChild)
{
    // calcul de la bounding box du noeud
    BoundingBox bb;
    switch (operation->getOperationType())
    {
        case operationTypes::UNION:
            bb = leftChild->getBoundingBox() + rightChild->getOperation().getBoundingBox();
            break;
        case operationTypes::INTERSECTION:
            bb = leftChild->getBoundingBox() ^ rightChild->getOperation().getBoundingBox();
            break;
        case operationTypes::DIFFERENCE:
            bb = leftChild->getBoundingBox() - rightChild->getOperation().getBoundingBox();
            break;
        case operationTypes::NONE:
        default:
            break;
    }
    operation->setBoundingBox(bb);

    // génération d'un nouveau noeud
    CsgNode *node = new CsgNode(operation->getOperationType());
    node->setLeftChildIsPrimitive(true);
    node->setRightChildIsPrimitive(false);
    node->setLeftChildPrimitive(leftChild);
    node->setRightChildOperation(rightChild);

    // ajout dans la liste des noeuds
    _nodes.insert(std::pair<int, CsgNode*>(_nodeCounter, node));
    _nodeCounter++;

    // ce noeud devient la racine d'un nouvel arbre
    _roots.insert(std::pair<int, CsgNode*>(_treeCounter, node));
    _treeCounter++;

    std::cout << "primitive & operation regrouped into new node" << std::endl;
}

// Fonction         : joinPrimitive
// Argument(s)		: - oper : pointeur sur l'opération
//                    - leftChild : pointeur sur une CsgOpération
//                    - rightChild : pointeur sur une CsgOpération
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: regroupe les deux primitives/opération dans un nouveau noeud
void CsgTree::joinPrimitives(CsgOperation *operation, CsgNode *leftChild, CsgNode *rightChild)
{
    // calcul de la bounding box du noeud
    BoundingBox bb;
    switch (operation->getOperationType())
    {
        case operationTypes::UNION:
            bb = leftChild->getOperation().getBoundingBox() + rightChild->getOperation().getBoundingBox();
            break;
        case operationTypes::INTERSECTION:
            bb = leftChild->getOperation().getBoundingBox() ^ rightChild->getOperation().getBoundingBox();
            break;
        case operationTypes::DIFFERENCE:
            bb = leftChild->getOperation().getBoundingBox() - rightChild->getOperation().getBoundingBox();
            break;
        case operationTypes::NONE:
        default:
            break;
    }
    operation->setBoundingBox(bb);

    // génération d'un nouveau noeud
    CsgNode *node = new CsgNode(operation->getOperationType());
    node->setLeftChildIsPrimitive(false);
    node->setRightChildIsPrimitive(false);
    node->setLeftChildOperation(leftChild);
    node->setRightChildOperation(rightChild);

    // ajout dans la liste des noeuds
    _nodes.insert(std::pair<int, CsgNode*>(_nodeCounter, node));
    _nodeCounter++;

    // ce noeud devient la racine d'un nouvel arbre
    _roots.insert(std::pair<int, CsgNode*>(_treeCounter, node));
    _treeCounter++;

    std::cout << "operation & operation regrouped into new node" << std::endl;
}
