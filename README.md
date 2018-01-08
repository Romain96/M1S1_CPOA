# PROJET PARTICULES

## Description

Projet réalisé dans le cadre de l'UE "Création et Programmation Objets Avancés"

* Auteur : Romain PERRIN
* Language de programmation : C++
* Interface : Qt
* Année : 2017-2018
* Etablissement : Université de Strasbourg
* Niveau : Master I
* Semestre : S1
* UE : CPOA

## Description des classes (hors interface)

| **Sous projet** | **Classe**        | **Héritage** | **Description**                                                                                          |
|-----------------|-------------------|--------------|----------------------------------------------------------------------------------------------------------|
| vectorMatrix    | Array             | -            | Représente les tableaux statiques. Template du type T et du nombre d'éléments N                          |
| vectorMatrix    | Vector            | Array        | Représente les vecteurs. Template du type T                                                              |
| vectorMatrix    | Matrix33d         | -            | Représente les matrices de transformation en 2D en coordonnées homogènes                                 |
| Image           | Image2D           | -            | Représente les images en 2D. Template du type de pixel T                                                 |
| Image           | Image2Grey        | Image2D      | Représente les images en niveau de gris. Permet de charger et sauvegarder des images au format PGM ascii |
| Image           | Image2RGB         | Image2D      | Représente les images au format RGB. Permet de charger et suavegarder des images au format PPM ascii     |
| CSG             | BoundingBox       | -            | Représente les boîtes englobantes alignées sur les axes                                                  |
| CSG             | CsgPrimitive      | -            | Représente les primitive graphiques                                                                      |
| CSG             | CsgDisk           | CsgPrimitive | Représente les disques de diamètre 1                                                                     |
| CSG             | CsgRegularPolygon | CsgPrimitive | Représente les polygones de plus de 2 sommets                                                            |
| CSG             | CsgOperation      | -            | Représente les opérations CSG (union, intersection, différence)                                          |
| CSG             | CsgNode           | -            | Représente les noeuds de l'arbre CSG                                                                     |
| CSG             | CsgTree           | -            | Représente le(s) arbre(s) CSG                                                                            |
| Particle        | Particle          | -            | Représente les particules                                                                                |
| Particle        | ParticleQueue     | -            | Représente la file (de priorité) de particules                                                           |

## Milestones

| **Milestone** | **Date début** | **Date fin** |
|---------------|----------------|--------------|
| Array/Vector/Matrix | 2017-10-08 | 2017-11-14 |
| Image2D/Image2Grey/Image2RGB | 2017-10-21 | 2017-11-14 |
| BoundingBox | 2017-12-30 | 2018-01-06 |
| CsgPrimitive/CsgDisk/CsgRegularPolygon | 2017-12-30 | 2018-01-07 |
| CsgNode/CsgTree | 2018-01-01 | 2018-01-07 |
| Particules | 2018-01-07 | en cours |
