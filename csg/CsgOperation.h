#ifndef __CSGOPERATION_H__
#define __CSGOPERATION_H__

#include "CsgPrimitive.h"

enum class operationTypes {UNION, INTERSECTION, DIFFERENCE};

class CsgOperation
{
protected:
    // type d'opération
    operationTypes _operation;

    // fils gauche (primitive graphique ou opération)
    bool _leftChildIsOperation;
    CsgPrimitive *_leftChildPrimitive;
    CsgOperation *_leftChildOperation;

    // fils droit (primitive graphique ou opération)
    bool _rightChildIsOperation;
    CsgPrimitive *_rightChildPrimitive;
    CsgOperation *_rightChildOperation;


public:
    // constructeur
    CsgOperation(operationTypes operation);

    // getters
    operationTypes& getOperationType();
    bool getLeftChildIsOperation();
    bool getRightChildIsOperation();
    CsgPrimitive *getLeftChildPrimitive();
    CsgPrimitive *getRightChildPrimitive();
    CsgOperation *getLeftChildOperation();
    CsgOperation *getRightChildOperation();

    // setters
    void setOperationType(operationTypes operation);
    void setLeftChildIsOperation(bool isOperation);
    void setRightChildIsOperation(bool isOperation);
    void setLeftChildPrimitive(CsgPrimitive *leftChild);
    void setRightChildPrimitive(CsgPrimitive *rightChild);
    void setLeftChildOperation(CsgOperation *leftChild);
    void setRightChildOperation(CsgOperation *rightChild);
};

#endif // __CSGOPERATION_H__
