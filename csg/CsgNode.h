#ifndef __CSGNODE_H__
#define __CSGNODE_H__

#include "CsgPrimitive.h"
#include "CsgOperation.h"
#include "Matrix33d.h"

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

    // et possède sa propre matrice de transformation
    Matrix33d _matrix;

    // et a un fils gauche (opération/primitive)
    CsgNode *_leftChild;

    // et a un fils droit (opération/primitive)
    CsgNode *_rightChild;

    // ou seulement une primitive (cas où operation est NONE)
    CsgPrimitive *_primitive;

    // transformations relatives
    int _previousTranslationX;
    int _previousTranslationY;

public:
    // constructeur
    CsgNode(CsgOperation operation);
    ~CsgNode();

    // getters
    int getId();
    CsgOperation& getOperation();
    Matrix33d& getMatrix();
    CsgNode *getLeftChild();
    CsgNode *getRightChild();
    CsgPrimitive *getPrimitive();

    // setters
    void setId(int id);
    void setOperation(CsgOperation& operation);
    void setMatrix(Matrix33d& mat);
    void setLeftChild(CsgNode *leftChild);
    void setRightChild(CsgNode *rightChild);
    void setPrimitive(CsgPrimitive *primitive);

    // méthodes
    bool isInsideOperation(Vec2f& point);
    void ModifyNodeGeneratorValue(int i);
};

#endif // __CSGNODE_H__
