#include "image2d.h"
#include "image2grey.h"

// constructeur
Image2Grey::Image2Grey(int w, int h) : Image2D<unsigned char>(w, h)
{
}

// destructeur
Image2Grey::~Image2Grey()
{
	delete[] pixels_;
}

// sous-échantilonage (retourne la taille de l'image par 2)
Image2Grey Image2Grey::sous_echantillonage()
{
	// comment diviser ? au centre ? au coin supérieur gauche ? paramètres ?
	Image2Grey se(this->getWidth()/2, this->getHeight()/2);
	return se;
}

// lissage paramétré par les (2n+1)^2 pixels voisins
Image2Grey Image2Grey::lissage(int n)
{
	Image2Grey liss(this->getWidth(), this->getHeight());
	unsigned int moy = 0;

	// les bords ne sont pas traités !
	for (int i=n; i<this->getHeight()-n; i++)
	{
		for (int j=n; j<this->getWidth()-n; j++)
		{
			moy = 0;
			// récupération des (2n+1)^2 pixels voisins de (i,j)
			for (int k=i-n; k<i+n; k++)
			{
				for (int l=j-n; l<j+n; j++)
				{
					moy += pixels_[l+k*this->getWidth()];
				}
			}
			// calcul de la moyenne
			moy = moy / ((2*n+1)*(2*n+1));
			// pixel lissé
			liss(i,j) = moy;
		}
	}
	
	return liss;
}

// suillage par une valeur
Image2Grey Image2Grey::seuillage(int seuil)
{
	Image2Grey s(this->getWidth(), this->getHeight());	// nouvelle image
	
	// remplissage des pixels de la nouvelle image
	for (int i=0; i<this->getHeight(); i++)
	{
		for (int j=0; j<this->getWidth(); j++)
		{
			if (pixels_[j+i*this->getWidth()] < seuil)
			{
				// 0 en dessous du seuil
				s(i,j) = pixels_[j+i*this->getWidth()];
			}
			else
			{
				// 255 sinon
				s(i,j) = pixels_[j+i*this->getWidth()];
			}
		}
	}

	return s;
}
