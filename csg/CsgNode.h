#ifndef __CSGNODE_H__
#define __CSGNODE_H__

#include "CsgPrimitive.h"
#include "CsgOperation.h"

// Représente les noeuds de l'arbre CSG
// Les noeuds sont des primitives ou des opérations ou un mélange des deux
class CsgNode
{
protected:
    // chaque noeud code une opération
    CsgOperation _operation;

    // et a un fils gauche (opération/primitive)
    bool _leftChildIsPrimitive;
    CsgPrimitive *_leftChildPrimitive;
    CsgOperation *_leftChildOperation;

    // et a un fils droit (opération/primitive)
    bool _rightChildIsPrimitive;
    CsgPrimitive *_rightChildPrimitive;
    CsgOperation *_rightChildOperation;

public:
    // constructeur
    CsgNode(CsgOperation& operation);

    // getters
    CsgOperation& getOperation();
    bool getLeftChildIsPrimitive();
    bool getRightChildIsPrimitive();
    CsgPrimitive *getLeftChildPrimitive();
    CsgPrimitive *getRightChildPrimitive();
    CsgOperation *getLeftChildOperation();
    CsgOperation *getRightChildOperation();

    // setters
    void setOperation(CsgOperation& operation);
    void setLeftChildIsPrimitive(bool isPrimitive);
    void setRightChildIsPrimitive(bool isPrimitive);
    void setLeftChildPrimitive(CsgPrimitive *leftChild);
    void setRightChildPrimitive(CsgPrimitive *rightChild);
    void setLeftChildOperation(CsgOperation *leftChild);
    void setRightChildOperation(CsgOperation *rightChild);
};

#endif // __CSGNODE_H__
