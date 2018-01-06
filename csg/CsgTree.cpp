#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include <utility>
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
    node->setPrimitive(primitive);
    node->getOperation().setBoundingBox(primitive->getBoundingBox());

    // ce noeud représente un nouvel arbre
    _roots.insert(std::pair<int, CsgNode*>(_treeCounter, node));
    _treeCounter++;

    // et il est référencé dans la liste des noeuds
    _nodes.insert(std::pair<int, CsgNode*>(_nodeCounter, node));
    _nodeCounter++;
}

//-----------------------------------------------------------------------------
// METHODES
//-----------------------------------------------------------------------------

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

    // génération d'un nouveau noeud
    CsgNode *node = new CsgNode(operation->getOperationType());
    node->getOperation().setBoundingBox(bb);
    node->setLeftChild(leftChild);
    node->setRightChild(rightChild);

    // ajout dans la liste des noeuds
    _nodes.insert(std::pair<int, CsgNode*>(_nodeCounter, node));
    _nodeCounter++;

    // ce noeud devient la racine d'un nouvel arbre
    _roots.insert(std::pair<int, CsgNode*>(_treeCounter, node));
    _treeCounter++;

    // si les deux fils étaient des racines, ils ne le sont plus
    _roots.erase(leftChild->getId());
    _roots.erase(rightChild->getId());

    std::cout << "operation & operation regrouped into new node" << std::endl;
}

// Fonction         : drawInImage
// Argument(s)		: - img : pointeur sur une Image2Grey
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: dessine le(s) arbre(s) CSG sur l'image img
void CsgTree::drawInImage(Image2Grey &img)
{
    std::cout << "drawing in image now" << std::endl;

    std::map<int, CsgNode*, csgNodeComparator>::iterator it = _roots.begin();

    while (it != _roots.end())
    {
        int key = it->first;
        CsgNode *node = it->second;
        std::cout << "\tdrawing root node of id " << key << std::endl;
        __drawNode(img, node);
        it++;
    }

    std::cout << "drawing finished" << std::endl;
}

// Fonction         : __drawNode
// Argument(s)		: -img : pointeur sur une Image2Grey
//                    - node : pointeur sur un CsgNode
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: dessine le contenu du node (primitive ou opération)
void CsgTree::__drawNode(Image2Grey &img, CsgNode *node)
{
    BoundingBox bb = node->getOperation().getBoundingBox();
    Vec2f point;
    Vec3f local;
    Matrix33d inverse = node->getMatrix().inverse();
    std::cout << inverse(0,0) << " " << inverse(0,1) << " " << inverse(0,2) << std::endl;
    std::cout << inverse(1,0) << " " << inverse(1,1) << " " << inverse(1,2) << std::endl;
    std::cout << inverse(2,0) << " " << inverse(2,1) << " " << inverse(2,2) << std::endl;

    // parcours des pixels de la bounding box de l'opération (de la racine)
    for (int i = bb.getUpperLeftPoint()[0]; i <= bb.getUpperRightPoint()[0]; i++)
    {
        for (int j = bb.getUpperLeftPoint()[1]; j <= bb.getLowerLeftPoint()[1]; j++)
        {
            // le point doit être transformé dans le repère local de l'opération/la primitive
            point[0] = i;
            point[1] = j;
            local = inverse * point;
            point[0] = local[0];
            point[1] = local[1];
            std::cout << "point to test " << point[0] << " " << point[1] << std::endl;
            // le pixel est dessiné en blanc s'il est dans l'opération
            if (node->isInsideOperation(point))
            {
                    img(i, j) = 255;
            }
        }
    }
}
