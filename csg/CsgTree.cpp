#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include <utility>
#include <string>
#include <sstream>
#include "CsgNode.h"
#include "CsgTree.h"
#include "CsgOperation.h"
#include "CsgDisk.h"
#include "CsgPrimitive.h"
#include "CsgRegularPolygon.h"

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
// SECTION DES METHODES
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
        {
            bb = leftChild->getOperation().getBoundingBox() + rightChild->getOperation().getBoundingBox();
            Vec2f ulp1 = leftChild->getOperation().getBoundingBox().getUpperLeftPoint();
            Vec2f ulp2 = rightChild->getOperation().getBoundingBox().getUpperLeftPoint();
            Vec2f lrp1 = leftChild->getOperation().getBoundingBox().getLowerRightPoint();
            Vec2f lrp2 = rightChild->getOperation().getBoundingBox().getLowerRightPoint();
            std::cout << "BB1 from " << ulp1[0] << ", " << ulp1[1] << "to " << lrp1[0] << ", " << lrp1[1] << std::endl;
            std::cout << "BB2 from " << ulp2[0] << ", " << ulp2[1] << "to " << lrp2[0] << ", " << lrp2[1] << std::endl;
            break;
        }
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
    std::cout << "checking from " << bb.getUpperLeftPoint()[0] << ", " << bb.getUpperLeftPoint()[1] << " to " <<
                 bb.getLowerRightPoint()[0] << ", " << bb.getLowerRightPoint()[1] << std::endl;


    //debug
    point[0] = bb.getUpperLeftPoint()[0];
    point[1] = bb.getUpperLeftPoint()[1];
    local = inverse * point;
    std::cout << "internally from " << local[0] << ", " << local[1] << std::endl;
    point[0] = bb.getLowerRightPoint()[0];
    point[1] = bb.getLowerRightPoint()[1];
    local = inverse * point;
    std::cout << "up to " << local[0] << ", " << local[1] << std::endl;

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
            //std::cout << "point to test " << point[0] << " " << point[1] << std::endl;
            // le pixel est dessiné en blanc s'il est dans l'opération
            if (node->isInsideOperation(point))
            {
                    img(i, j) = 255;
            }
        }
    }
}

// Fonction         : getAsciiGraph
// Argument(s)		: /
// Valeur de retour	: une chaine de caractères
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne une version du graphe sous forme de chaine de caractères
//                    ex :
//                    Tree 0 :
//                    Node 0 : UNION -> Node 1, Node 2
//                    Node 1 : PRIMITIVE -> CsgDisk
//                    Node 2 : PRIMITIVE -> CsgRegularPolygon [4]
std::string CsgTree::getAsciiGraph()
{
    std::string graph = "";

    // parcours de chaque arbre à l'aide d'un itérateur
    std::map<int, CsgNode *, csgNodeComparator>::iterator it = _roots.begin();

    while(it != _roots.end())
    {
        // noeud racine
        int key = it->first;
        CsgNode *node = it->second;

        // traitement de l'arbre
        std::cout << "writting tree of id into ascii string" << key << std::endl;
        graph += __getAsciiNode(node);

        it++;
    }

    return graph;
}

// Fonction         : getAsciiNode
// Argument(s)		: - node : pointeur sur une CsgNode
// Valeur de retour	: une chaine de caractères
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne le noeud node sous forme de chaine de caractères
std::string CsgTree::__getAsciiNode(CsgNode *node)
{
    std::string nodeAscii = "";
    std::string leftAscii = "";
    std::string rightAscii = "";

    // la suite dépend de l'opération
    switch (node->getOperation().getOperationType())
    {
    case operationTypes::NONE:
        // CsgDisk
        if (CsgDisk *disk = dynamic_cast<CsgDisk *>(node->getPrimitive()))
        {
            nodeAscii += "Node " + std::to_string(node->getId()) + " -> CsgDisk [center=(" +
                    std::to_string(disk->getCenter()[0]) + "," + std::to_string(disk->getCenter()[1]) +
                    "), radius=" + std::to_string(disk->getDistanceToOrigin()) +"]\n";
        }
        // CsgRegularPolygon
        else if (CsgRegularPolygon *regPoly = dynamic_cast<CsgRegularPolygon *>(node->getPrimitive()))
        {
            nodeAscii += "Node " + std::to_string(node->getId()) + " -> CsgRegularPolygon [vertex=" +
                    std::to_string(regPoly->getVertexNumber()) + ", center=(" +
                    std::to_string(regPoly->getCenter()[0]) + "," + std::to_string(regPoly->getCenter()[1]) +
                    "), radius=" + std::to_string(regPoly->getDistanceToOrigin()) + "]\n";
        }
        // ???
        else
        {
            std::cerr << "CsgTree::__getAsciiNode error primitive is neither CsgDisk nor CsgRegularPolygon !";
        }

        return nodeAscii;
        break;
    case operationTypes::UNION:
        nodeAscii += "Node " + std::to_string(node->getId()) + " -> UNION with Node " +
                std::to_string(node->getLeftChild()->getId()) + " and Node " +
                std::to_string(node->getRightChild()->getId()) + "\n";

        // appel récursif sur les deux fils
        leftAscii = __getAsciiNode(node->getLeftChild());
        rightAscii = __getAsciiNode(node->getRightChild());
        return nodeAscii + leftAscii + rightAscii;
        break;
    case operationTypes::INTERSECTION:
        nodeAscii += "Node " + std::to_string(node->getId()) + " -> INTERSECTION with Node " +
                std::to_string(node->getLeftChild()->getId()) + " and Node " +
                std::to_string(node->getRightChild()->getId()) + "\n";

        // appel récursif sur les deux fils
        leftAscii = __getAsciiNode(node->getLeftChild());
        rightAscii = __getAsciiNode(node->getRightChild());
        return nodeAscii + leftAscii + rightAscii;
        break;
    case operationTypes::DIFFERENCE:
        nodeAscii += "Node " + std::to_string(node->getId()) + " -> DIFFERENCE with Node " +
                std::to_string(node->getLeftChild()->getId()) + " and Node " +
                std::to_string(node->getRightChild()->getId()) + "\n";

        // appel récursif sur les deux fils
        leftAscii = __getAsciiNode(node->getLeftChild());
        rightAscii = __getAsciiNode(node->getRightChild());
        return nodeAscii + leftAscii + rightAscii;
        break;
    default:
        std::cerr << "CsgTree::__getNodeAscii error operation is unknown !" << std::endl;
        return nodeAscii;
        break;
    }
    std::cerr << "CsgTree::__getNodeAscii error non return statement inside switch" << std::endl;
    return nodeAscii;
}

// Fonction         : saveCsg
// Argument(s)		: - filename : nom du fichier dans lequel sauvegarder le graphe CSG
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: écrit la structure du graphe CSG dans le fichier filemane
void CsgTree::saveCsg(std::string filename)
{
    std::cout << "saving CSG graph in file " << filename << std::endl;

    Matrix33d transfo;
    // ouverture du fichier
    std::ofstream output;
    output.open(filename);

    // commence par la chaine spéciale CSG_FILE
    output << "CSG_FILE\n";

    // parcours des noeuds
    std::map<int, CsgNode *, csgNodeComparator>::iterator it = _nodes.begin();
    while (it != _nodes.end())
    {
        int key = it->first;
        CsgNode *node = it->second;

        // contient les infos de chaque noeud
        std::cout << "saving node of id " << key << std::endl;

        // écriture de l'id du noeud
        output << node->getId() << " ";

        switch (node->getOperation().getOperationType())
        {
        // soit une primitive
        // [id node] [CsgDisk|CsgRegularPolygon] [/|nbVertex]
        // matrice de transfo personnelle du noeud
        case operationTypes::NONE:
            if (CsgDisk *disk = dynamic_cast<CsgDisk *>(node->getPrimitive()))
            {
                output << "CsgDisk\n";
                transfo = node->getMatrix();
                output << transfo(0,0) << " " << transfo(0,1) << " " << transfo(0,2) << "\n" <<
                          transfo(1,0) << " " << transfo(1,1) << " " << transfo(1,2) << "\n" <<
                          transfo(2,0) << " " << transfo(2,1) << " " << transfo(2,2) << "\n";
            }
            else if (CsgRegularPolygon *regPoly = dynamic_cast<CsgRegularPolygon *>(node->getPrimitive()))
            {
                // le nombre de sommets doit être précisé
                output << "CsgRegularPolygon " << regPoly->getVertexNumber() << "\n";
                transfo = node->getMatrix();
                output << transfo(0,0) << " " << transfo(0,1) << " " << transfo(0,2) << "\n" <<
                          transfo(1,0) << " " << transfo(1,1) << " " << transfo(1,2) << "\n" <<
                          transfo(2,0) << " " << transfo(2,1) << " " << transfo(2,2) << "\n";
            }
            else
            {
                std::cerr << "CsgTree::savsCsg error primitive is neither CsgDisk nor CsgRegularPolygon !" << std::endl;
            }
            break;
        // soit un noeud opération
        // [id node] [UNION|INTERSECTION|DIFFERENCE] [id node left] [id node right]
        // matrice de transfo personnelle du noeud
        case operationTypes::UNION:
            output << "UNION " << node->getLeftChild()->getId() << " " << node->getRightChild()->getId() << "\n";
            transfo = node->getMatrix();
            output << transfo(0,0) << " " << transfo(0,1) << " " << transfo(0,2) << "\n" <<
                      transfo(1,0) << " " << transfo(1,1) << " " << transfo(1,2) << "\n" <<
                      transfo(2,0) << " " << transfo(2,1) << " " << transfo(2,2) << "\n";
            break;
        case operationTypes::INTERSECTION:
            output << "INTERSECTION " << node->getLeftChild()->getId() << " " << node->getRightChild()->getId() << "\n";
            transfo = node->getMatrix();
            output << transfo(0,0) << " " << transfo(0,1) << " " << transfo(0,2) << "\n" <<
                      transfo(1,0) << " " << transfo(1,1) << " " << transfo(1,2) << "\n" <<
                      transfo(2,0) << " " << transfo(2,1) << " " << transfo(2,2) << "\n";
            break;
        case operationTypes::DIFFERENCE:
            output << "DIFFERENCE " << node->getLeftChild()->getId() << " " << node->getRightChild()->getId() << "\n";
            transfo = node->getMatrix();
            output << transfo(0,0) << " " << transfo(0,1) << " " << transfo(0,2) << "\n" <<
                      transfo(1,0) << " " << transfo(1,1) << " " << transfo(1,2) << "\n" <<
                      transfo(2,0) << " " << transfo(2,1) << " " << transfo(2,2) << "\n";
            break;
        default:
            std::cerr << "CsgTree::saveCsg error operation of node is unknown" << std::endl;
            break;
        }
        // pour plus de lisibilité : une ligne vide entre deux noeuds
        output << "\n";

        it++;
    }

    // fermeture du fichier
    output.close();

    std::cout << "save completed" << std::endl;
}

// Fonction         : loadCsg
// Argument(s)		: - filename : nom du fichier dans lequel lire la structure du graphe
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: lit et initialise le graphe CSG avec la structure de graphe lue dans le fichier filename
void CsgTree::loadCsg(std::string filename)
{
    std::cout <<  "loading CSG graph from file " << filename << std::endl;

    std::ifstream input;
    std::string line;
    int nodeId, leftNodeId, rightNodeId;
    int vertex;
    std::string operationOrPrimitiveName;
    std::string header;
    Matrix33d transfo;
    bool matrixRead1 = false;
    bool matrixRead2 = false;
    bool matrixRead3 = false;

    // ouverture du fichier
    input.open(filename);

    // vérification de l'en-tête du fichier (CSG_FILE)
    std::getline(input, line);
    std::istringstream iss(line);
    if (iss >> header && header.compare("CSG_FILE") == 0)
        std::cout << "file has correct header " << header << std::endl;
    else
    {
        std::cerr << "file has incorrect header " << header << std::endl;
        return;
    }

    // TODO LIRE LA SUITE ...

    // remise à zéro des id et suppression des noeuds existants
    this->clear();

    // fermeture du fichier
    input.close();

    std::cout << "CSG graph read" << std::endl;
}
