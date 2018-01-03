#ifndef __CSGNODE_H__
#define __CSGNODE_H__

#include "CsgPrimitive.h"
#include "CsgOperation.h"

// Représente les noeuds de l'arbre CSG
// Les noeuds sont des primitives ou des opérations ou un mélange des deux
class CsgNode
{
private:
    static int _nodeUniqueIdGenerator;

protected:
    // id du node (pour les comparer/classer)
    int _nodeId;

    // chaque noeud code une opération
    CsgOperation _operation;

    // et a un fils gauche (opération/primitive)
    bool _leftChildIsPrimitive;
    CsgPrimitive *_leftChildPrimitive;
    CsgNode *_leftChildOperation;

    // et a un fils droit (opération/primitive)
    bool _rightChildIsPrimitive;
    CsgPrimitive *_rightChildPrimitive;
    CsgNode *_rightChildOperation;

public:
    // constructeur
    CsgNode(CsgOperation operation);
    ~CsgNode();

    // getters
    int getId();
    CsgOperation& getOperation();
    bool getLeftChildIsPrimitive();
    bool getRightChildIsPrimitive();
    CsgPrimitive *getLeftChildPrimitive();
    CsgPrimitive *getRightChildPrimitive();
    CsgNode *getLeftChildOperation();
    CsgNode *getRightChildOperation();

    // setters
    void setId(int id);
    void setOperation(CsgOperation& operation);
    void setLeftChildIsPrimitive(bool isPrimitive);
    void setRightChildIsPrimitive(bool isPrimitive);
    void setLeftChildPrimitive(CsgPrimitive *leftChild);
    void setRightChildPrimitive(CsgPrimitive *rightChild);
    void setLeftChildOperation(CsgNode *leftChild);
    void setRightChildOperation(CsgNode *rightChild);
};

#endif // __CSGNODE_H__
