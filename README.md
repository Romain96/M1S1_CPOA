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

## Notes importantes

* Le problème du crash au lors de l'ajout de primitives a finalement été corrigé. Un simple appel à updateDataTexture() dans le constructeur de RenderImg corrige le problème du au fait que le pointeur m_ptrTex était toujours positionné à NULL. Plus besoin donc de charger une image vierge au lancement, le programme est désormais prêt à l'emploi.

* Les translations et homothéties semblent se comporter normalement dans la plupart des cas. Les rotations sont erronées, il est clair que le centre de rotation (centre de la bounding box de la primitive ou de l'opération) soit incorrect lors de l'application de la rotation mais tout en étant correct pour l'affichage...

* Les formes composées peuvent être bougées mais les bounding box semblent ne pas suivre le mouvement correctement. Il en résult une disparition de(s) forme(s) de l'écran.

* Il est possible de sauver et de charger une image pgm

* Il est possible de sauvegarder et de charger le graphe CSG (la fonction appendCsg n'est pas encore implémentée)

* Il est possible de cloner un noeud (feuille ou bien sous-arbre), d'échanger les fils droit et gauche d'un noeud opération et de défaire une opération ensembliste (seulement si le noeud en question est la racine d'un arbre)

* Il est possible de lancer des particules en appuyant sur **A** puis en cliquant sur l'écran (clic droit) afin d'afficher un mur de particules au haut de l'écran. Enfin pour lancer les particules il suffit d'appuyer sur **E**.


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
| Particules | 2018-01-07 | 2018-01-09 |
