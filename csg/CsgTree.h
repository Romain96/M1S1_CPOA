#ifndef __CSGTREE_H__
#define __CSGTREE_H__

#include <iostream>
#include <map>
#include <string>
#include "CsgNode.h"
#include "Image2Grey.h"

// comparateur de nodes
struct csgNodeComparator
{
    bool operator ()(const int& key1, const int& key2) const
    {
        return key1 < key2;
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
    std::map<int, CsgNode*, csgNodeComparator> _roots;

    // liste de tous les noeuds de tous les arbres
    std::map<int, CsgNode*, csgNodeComparator> _nodes;

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
    void joinPrimitives(CsgOperation *operation, CsgNode *leftChild, CsgNode *rightChild);

    // inverse le fils gauche et droit (dans le cas d'un noeud qui n'est pas une primitive)
    void swapChildren(int id);

    // supprime le noeud et créer deux arbres avec les fils gauche et droit
    void unjoin(int id);

    // clone un sous-graphe dont la racine est le noeud courant
    void cloneSubTree(int id);
    int __cloneCopyNode(CsgNode *node);

    // dessin de l'arbre sur l'image
    void drawInImage(Image2Grey& img);

    // dessine un noeud (utilisé sur la racine de chaque arbre)
    void __drawNode(Image2Grey& img, CsgNode *node);

    // transforme le graphe en une chaine de caractères afin d'être affichée dans la zone graph
    std::string getAsciiGraph();
    std::string __getAsciiNode(CsgNode *node);

    // sauvegarde le graphe dans un fichier
    void saveCsg(std::string filename);

    // charge le graphe depuis un fichier
    void loadCsg(std::string filename);
};

#endif // __CSGTREE_H__
