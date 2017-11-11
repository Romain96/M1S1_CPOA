#ifndef __IMAGE2D_H__
#define __IMAGE2D_H__

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
	T operator ()(int i, int j)
	{
		return data_[i*w_ + j];
	}	
};

#endif
