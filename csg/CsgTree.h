#ifndef __CSGTREE_H__
#define __CSGTREE_H__

#include <iostream>
#include <map>
#include "CsgNode.h"

// comparateur de nodes
struct csgNodeComparator
{
    bool operator ()(CsgNode& node1, CsgNode& node2)
    {
        return node1.getId() < node2.getId();
    }
};

// Représente le(s) arbre(s) CSG
class CsgTree
{
private:
    static int _nodeCounter;
    static int _treeCounter;

protected:
    // liste de tous les arbres CSG
    std::map<int, CsgNode*> _roots;

    // liste de tous les noeuds de tous les arbres
    std::map<int, CsgNode*> _nodes;

public:
    // constructeur
    CsgTree();

    // getters
    CsgNode* getNode(int i);
    CsgNode* getLastInsertedNode();
    int getLastNodeId();

    // setters
    void setNode(CsgNode *node, int i);

    // vide l'arbre
    void clear();

    // ajout de primitives
    void addPrimitive(CsgPrimitive *primitive);

    // regroupement de primitives en noeud
    void joinPrimitives(CsgOperation *operation, CsgPrimitive *leftChild, CsgPrimitive *rightChild);
    void joinPrimitives(CsgOperation *operation, CsgPrimitive *leftChild, CsgNode *rightChild);
    void joinPrimitives(CsgOperation *operation, CsgNode *leftChild, CsgPrimitive *rightChild);
    void joinPrimitives(CsgOperation *operation, CsgNode *leftChild, CsgNode *rightChild);
};

#endif // __CSGTREE_H__
