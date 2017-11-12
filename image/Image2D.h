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
	// Fonction		: Image2D 
	// Argument(s) 		: /
	// Valeur de retour	: /
	// Pré-condition(s)	: /
	// Post-condition(s)	: /
	// Commentaire(s)	: le constructeur vide est interdit
	Image2D() = delete;

	// Fonction		: Image2D
	// Argument(s)		: - width : entier contenant la largeur de l'image (ie le nombre de colonnes)
	//			  - heigh : entier contenant la hauteur de l'image (ie le nombre de lignes)
	// Valeur de retour	: /
	// Pré-condition(s)	: /
	// Post-condition(s)	: /
	// Commentaire(s)	: alloue un tableau de width*height pixels
	Image2D(int width, int height) : w_(width), h_(height)
	{
		data_ = new T[height*width];
	}

	// Fonction		: ~Image2D
	// Argument(s)		: /
	// Valeur de retour	: /
	// Pré-condition(s)	: /
	// Post-condition(s)	: /
	// Commentaire(s)	: libère la mémoire allouée pour le tableau de pixels
	~Image2D()
	{
		delete[] data_;
	}

	// Fonction		: getWidth
	// Argument(s)		: /
	// Valeur de retour	: un entier contenant la largeur actuelle de l'image
	// Pré-condition()	: /
	// Post-condition(s)	: /
	// Commentaire(s)	: /
	int getWidth()
	{
		return this->w_;
	}

	// Fonction		: getHeight
	// Argument(s)		: /
	// Valeur de retour	: un entier contenant la hauteur actuelle de l'image
	// Pré-condition(s)	: /
	// Post-condition(s)	: /
	// Commentaire(s)	: /
	int getHeight()
	{
		return this->h_;
	}
	
	// Fonction		: operator ()
	// Argument(s)		: - i : entier contenant le numéro de ligne du pixel
	//			  - i : entier contenant la numéro de colonne du pixel
	// Valeur de retour	: une variable de type T contenant la valeur du pixel en (i,j)
	// Pré-condition(s)	: i et j doivent être valides (ie 0 <= i < largeur et 0 <= j < hauteur)
	// Post-condition(s)	: /
	// Commentaire(s)	: /
	T operator ()(int i, int j) const
	{
		return data_[i*w_ + j];
	}

	T& operator ()(int i, int j)
	{
		return data_[i*w_ + j];
	}

	// Fonction		: cropping (sous-image)
	// Argument(s)		: - img : une référence sur un objet de type Image2D
	//			  - x : un entier contenant le numéro de la ligne du pixel en haut à gauche
	//			  - y : un entier contenant le numéro de la colonne du pixel en haut à gauche
	//			  - width : la largeur de la sous-image
	//			  - height : la hauteur de la sous-image
	// Valeur de retour	: une nouvelle image aux dimensions choisies
	// Pré-condition(s)	: x et y dans l'image, width et height respectivement <= img.width - x et img.height - y
	// Post-condition(s)	: /
	// Commentaire(s)	: retourne une nouvelle image partant du pixel (x,y) et de dimensions width*height
	Image2D *cropping(Image2D& img, int x, int y, int width, int height)
	{
		// vérification des paramètres
		if (x < 0)
		{
			fprintf(stderr, "cropping ERROR : x (%d) is negative\n", x);
			exit(1);
		}
		if (x > img.getWidth())
		{
			fprintf(stderr, "cropping ERROR : x (%d) is greater than image width (%d)\n", x, img.getWidth());
			exit(1);
		}
		if (y < 0)
		{
			fprintf(stderr, "cropping ERROR : y (%d) is negative\n", y);
			exit(1);
		}
		if (y > img.getHeight())
		{
			fprintf(stderr, "cropping ERROR : y (%d) is greater than image height (%d)\n", y, img.getHeight());
			exit(1);
		}
		if (width < 0)
		{
			fprintf(stderr, "cropping ERROR : width (%d) is negative\n", width);
			exit(1);
		}
		if (height < 0)
		{
			fprintf(stderr, "cropping ERROR : height (%d) is negative\n", height);
		}
		if (width > img.getWidth() - x)
		{
			fprintf(stderr, "cropping ERROR : width (%d) is greater than image width - x (%d)\n", width, img.getWidth() - x);
			exit(1);
		}
		if (height > img.getHeight() - y)
		{
			fprintf(stderr, "cropping ERROR : height (%d) is greater than image height - y (%d)\n", height, img.getHeight() - y);
			exit(1);
		}

		// allocation de la nouvelle image
		Image2D *crop = new Image2D(width, height);

		printf("Cropping image with x=%d y=%d width=%d height=%d\n", x, y, width, height);
		// parcours de l'image
		int indicex = 0;
		int indicey = 0;
		for (int i = x; i < x + width; i++)
		{
			for (int j = y; j < height + y; j++)
			{
				T pixel = this->data_[i*this->getWidth() + j];
				crop->data_[indicex*width + indicey] = pixel;
				indicey++;
			}
			indicex++;
		}

		// retourner l'image
		return crop;
	}

	// Fonction		: swap (échange de deux images 2D)
	// Argument(s		: - img1 : référence sur une image 2D
	//			  - img2 : référence sur une image 2D
	// Valeur de retour	: /
	// Pré-condition(s)	: img1 et img2 doivent avoir des dimensions identiques
	// Post-condition(s)	: /
	// Commentaire(s)	: échange de deux images statiquement
	static void swap(Image2D& img1, Image2D& img2)
	{
		// vérification des dimensions
		if (img1.getWidth() != img2.getWidth())
		{
			fprintf(stderr, "swap ERROR : images have different widths\n");
			exit(1);	
		}
		if (img1.getHeight() != img2.getHeight())
		{
			fprintf(stderr, "swap ERROR : images have different heights\n");
			exit(1);
		}

		// échange des tableau de pixels (échange des pointeurs)
		T *tmp = img1.data_;
		img1.data_ = img2.data_;
		img2.data = tmp;
	}
};

#endif
