#ifndef __IMAGE2D_H__
#define __IMAGE2D_H__

#include <cstdlib>
#include <iostream>

template <typename T>
class Image2D
{
protected:
	int w_;			// largeur de l'image
	int h_;			// hauteur de l'image
	T *data_;		// tableau dynamique contenant les valeurs des pixels

public:
    // Fonction         : Image2D
	// Argument(s) 		: /
	// Valeur de retour	: /
	// Pr�-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: le constructeur vide est interdit
	Image2D() = delete;

    // Fonction         : Image2D
	// Argument(s)		: - width : entier contenant la largeur de l'image (ie le nombre de colonnes)
    //                    - heigh : entier contenant la hauteur de l'image (ie le nombre de lignes)
	// Valeur de retour	: /
	// Pr�-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: alloue un tableau de width*height pixels
	Image2D(int width, int height) : w_(width), h_(height)
	{
		data_ = new T[height*width];
	}

    // Fonction         : ~Image2D
	// Argument(s)		: /
	// Valeur de retour	: /
	// Pr�-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: lib�re la m�moire allou�e pour le tableau de pixels
	~Image2D()
	{
		delete[] data_;
	}

    // Fonction         : getWidth
	// Argument(s)		: /
	// Valeur de retour	: un entier contenant la largeur actuelle de l'image
	// Pr�-condition()	: /
    // Post-condition(s): /
	// Commentaire(s)	: /
	int getWidth()
	{
		return this->w_;
	}

    // Fonction         : getHeight
	// Argument(s)		: /
	// Valeur de retour	: un entier contenant la hauteur actuelle de l'image
	// Pr�-condition(s)	: /
    // Post-condition(s): /
	// Commentaire(s)	: /
	int getHeight()
	{
		return this->h_;
	}
	
    // Fonction         : operator ()
	// Argument(s)		: - i : entier contenant le num�ro de ligne du pixel
    //                    - i : entier contenant la num�ro de colonne du pixel
	// Valeur de retour	: une variable de type T contenant la valeur du pixel en (i,j)
	// Pr�-condition(s)	: i et j doivent �tre valides (ie 0 <= i < largeur et 0 <= j < hauteur)
    // Post-condition(s): /
	// Commentaire(s)	: version const
	T operator ()(int i, int j) const
	{
		// i et/ou j hors limite
		if (i < 0 || i >= w_ || j < 0 || j >= h_)
		{
			fprintf(stderr, "Image2D::operator () ERROR : i et/ou j hors limite (i=%d, j=%d)\n", i, j);
			exit(1);
		}

		// sinon ok
		return data_[i*w_ + j];
	}

    // Fonction         : operator ()
	// Argument(s)		: - i : entier contenant le num�ro de ligne du pixel
    //                    - j : entier contenant le num�ro de colonne du pixel
	// Valeur de retout	: une variable de type T contenant la valeur du pixel en (i,j)
	// Pr�-condition(s)	: i et j doivent �tre valides
    // Post-condition(s): /
	// Commentaire(s)	: version non const de la pr�c�dente
	T& operator ()(int i, int j)
	{
		// i et/ou j hors limite
		if (i < 0 || i >= w_ || j < 0 || j >= h_)
		{
			fprintf(stderr, "Image2D::operator () ERROR : i et/ou j hors limite (i=%d, j=%d)\n", i, j);
			exit(1);
		}

		// sinon ok
		return data_[i*w_ + j];
	}

    // Fonction         : cropping (sous-image)
	// Argument(s)		: - img : une r�f�rence sur un objet de type Image2D
    //                    - x : un entier contenant le num�ro de la ligne du pixel en haut � gauche
    //                    - y : un entier contenant le num�ro de la colonne du pixel en haut � gauche
    //                    - width : la largeur de la sous-image
    //                    - height : la hauteur de la sous-image
	// Valeur de retour	: une nouvelle image aux dimensions choisies
	// Pr�-condition(s)	: x et y dans l'image, width et height respectivement <= img.width - x et img.height - y
    // Post-condition(s): /
	// Commentaire(s)	: retourne une nouvelle image partant du pixel (x,y) et de dimensions width*height
	static Image2D *cropping(Image2D& img, int x, int y, int width, int height)
	{
		// v�rification des param�tres
		if (x < 0)
		{
			fprintf(stderr, "Image2D::cropping ERROR : x est n�gatif (%d)\n", x);
			exit(1);
		}
		if (x > img.getWidth())
		{
			fprintf(stderr, "Image2D::cropping ERROR : x est sup�rieur � la largeur de l'image (%d >=%d)\n", x, img.getWidth());
			exit(1);
		}
		if (y < 0)
		{
			fprintf(stderr, "Image2D::cropping ERROR : y est n�gative (%d)\n", y);
			exit(1);
		}
		if (y > img.getHeight())
		{
			fprintf(stderr, "Image2D::cropping ERROR : y est sup�rieur � la hauteur de l'image (%d >= %d)\n", y, img.getHeight());
			exit(1);
		}
		if (width < 0)
		{
			fprintf(stderr, "Image2D::cropping ERROR : la largeur est n�gative (%d)\n", width);
			exit(1);
		}
		if (height < 0)
		{
			fprintf(stderr, "Image2D::cropping ERROR : la hauteur est n�gative (%d)\n", height);
		}
		if (width > img.getWidth() - x)
		{
			fprintf(stderr, "Image2D::cropping ERROR : la largeur est sup�rieure � la largeur de l'image - x (%d >%d)\n", width, img.getWidth() - x);
			exit(1);
		}
		if (height > img.getHeight() - y)
		{
			fprintf(stderr, "Image2D::cropping ERROR : la hauteur est sup�rieure � la hauteur de l'image - y (%d >= %d)\n", height, img.getHeight() - y);
			exit(1);
		}

		// allocation de la nouvelle image
		Image2D *crop = new Image2D(width, height);

		// parcours de l'image
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				T pixel = img.data_[(i+x)*img.getWidth() + (j+y)];
				crop->data_[i*width + j] = pixel;
			}
		}

		// retourner l'image
		return crop;
	}

    // Fonction         : swap (�change de deux images 2D)
	// Argument(s		: - img1 : r�f�rence sur une image 2D
    //                    - img2 : r�f�rence sur une image 2D
	// Valeur de retour	: /
	// Pr�-condition(s)	: img1 et img2 doivent avoir des dimensions identiques
    // Post-condition(s): /
	// Commentaire(s)	: �change de deux images statiquement
	static void swap(Image2D& img1, Image2D& img2)
	{
		// v�rification des dimensions
		if (img1.getWidth() != img2.getWidth())
		{
			fprintf(stderr, "Image2D::swap ERROR : les images ont des largeurs diff�rentes\n");
			exit(1);	
		}
		if (img1.getHeight() != img2.getHeight())
		{
			fprintf(stderr, "Image2D::swap ERROR : les images ont des hauteurs diff�rentes\n");
			exit(1);
		}

		// �change des tableau de pixels (�change des pointeurs)
		T *tmp = img1.data_;
		img1.data_ = img2.data_;
		img2.data = tmp;
	}
};

#endif
