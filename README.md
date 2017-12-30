# PROJET PARTICULES (Projet de CPOA)

## Description

Projet réalisé dans le cadre de l'UE "Création et Programmation Objets Avancés"

## Description des classes [en construction]

| **Classe** | **Héritage** | **Description** |
|--------|-------------|-------------|
| Array | - | Représente les tableaux statiques. Template du type T et du nombre d'éléments N |
| Vector | Array | Représente les vecteurs. Template du type T |
| Matrix33d | - | Représente les matrices de transformation en 2D en coordonnées homogènes |
| Image2D | - | Représente les images en 2D. Template du type de pixel T |
| Image2Grey | Image2D | Représente les images en niveau de gris. Permet de charger et sauvegarder des images au format PGM ascii |
| Image2RGB | Image2D | Représente les images au format RGB. Permet de charger et suavegarder des images au format PPM ascii |
| BoundingBow | - | Représente les boîtes englobantes alignées sur les axes |
| CsgDisk | - | Représente les disques de diamètre 1 |
| CsgRegulaPolygon | - | Représente les polygones de plus de 2 sommets |
| CsgOperation | - | Représente les opérations CSG (union, intersection, différence) |
| CsgNode | - | Représente les noeuds de l'arbre CSG |
| CsgTree | - | Représente le(s) arbre(s) CSG |

## Milestones [en construction]

| **Milestone** | **Date début** | **Date fin** |
|---------------|----------------|--------------|
| Array/Vector/Matrix | 2017-10-08 | en cours |
| Image2D/Image2Grey/Image2RGB | 2017-10-21 | en cours |
| BoundingBox | 2017-12-30 | en cours |
| CsgCircle/CsgRegularPolygon | 2017-12-30 | en cours |

## Informations

Auteur : Romain PERRIN (étudiant en M1 Informatique et Science de l'Image)

Outils utilisés :
* Interface graphique : Qt
* Langage de programmation : C++


