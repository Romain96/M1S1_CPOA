#ifndef __CSGOPERATION_H__
#define __CSGOPERATION_H__

#include "CsgPrimitive.h"

enum class operationTypes {UNION, INTERSECTION, DIFFERENCE};

class CsgOperation
{
protected:
    // type d'opération
    operationTypes _operation;

public:
    // constructeur
    CsgOperation(operationTypes operation);

    // getters
    operationTypes& getOperationType();

    // setters
    void setOperationType(operationTypes operation);
};

#endif // __CSGOPERATION_H__
