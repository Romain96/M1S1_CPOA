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
// Valeur de retour	: une node
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le node d'indice i
CsgNode* CsgTree::getNode(int i)
{
    return _nodes[i];
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

// Fonction         : addPrimitive
// Argument(s)		: - primitive : nouvelle primitive à ajouter
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: ajoute un nouvel arbre contenant la primitve
void CsgTree::addPrimitive(CsgPrimitive *primitive)
{
    // génération d'un noeud sans opération
    CsgNode *node = new CsgNode(operationTypes::NONE);
    node->setLeftChildIsPrimitive(true);
    node->setLeftChildPrimitive(primitive);

    // ce noeud représente un nouvel arbre
    _roots[_treeCounter++] = node;

    // et il est référencé dans la liste des noeuds
    _nodes[_nodeCounter++] = node;
}
