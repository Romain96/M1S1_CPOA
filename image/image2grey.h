#ifndef __IMAGE2GREY_H__
#define __IMAGE2GREY_H__

/*
 * Classe représentant les images 2D de type de pixel unsigned char
 */

#include "image2d.h"

class Image2Grey : public Image2D<unsigned char>
{
public:
	// constructeur
	Image2Grey(int w, int h);
	
	// destructeur
	~Image2Grey();

	// sous-échantillonage (divise la taille de l'image par 2)
	Image2Grey sous_echantillonage();

	// lissage (moyenne des pixels avec les (2n+1)^2 pixels voisins)
	Image2Grey lissage(int n);

	// seuillage par une valeur (en paramètre)
	Image2Grey seuillage(int seuil);
};

#endif
