#ifndef __IMAGE2D_H__
#define __IMAGE2D_H__

/*
 * Classe représentant une image en 2D
 * elle est template du type de pixel T
 */

#include <utility>

template <typename T> class Image2D
{
protected:
	T* pixels_;	// tableau de pixels de type T
	int w_;		// largeur de l'image
	int h_;		// longueur de l'image

public:
	// constructeur d'une image paramétrée par la longueur et la largeur
	Image2D(int w, int h) : w_(w), h_(h)
	{
		pixels_ = new T[w*h];	// allocation dynamique de l'image
	}

	// constructeur vide
	Image2D() = delete;

	// desctructeur
	~Image2D()
	{
		delete[] pixels_;
	}

	// retourne la largeur de l'image
	int getWidth() const
	{
		return w_;
	}

	// retourne la longueur de l'image
	int getHeight() const
	{
		return h_;
	}

	// retourne le contenu de l'image
	T* data_pix()
	{
		return pixels_;
	}

	// accès au pixel (i,j)
	T& operator ()(int i, int j)
	{
		return pixels_[i+j*w_];
	}

	// idem en version const
	const T& operator()(int i, int j) const
	{
		return pixels_[i+j*w_];
	}

	// échange de deux images (si les dimensions concordent)
	void swap_pixels(Image2D<T>& im)
	{
		assert(im.getWidth()==this->getWidth() && im.getHeight()==this->getHeight());
		std::swap(im.pixels_, this->pixels_);
	}

	// cropping (retourne une sous-image)
	// paramétrée par le pixel de départ (i,j) et la longueur/largeur de la sous-image
	Image2D<T> cropping(int i, int j, int w, int h)
	{
		// seulement si (i,j) est dans l'image et i+w,j+h est une dimension inclue dans la sous-image
		assert(i<this->getWidth() && j<this->getHeight() && (i+w)<this->getWidth() && (j+h)<getHeight());
		
		Image2D<T> crop(i, j, w, h);	// sous-image
		int width = this->getWidth() - i;	// nouvelle largeur		

		// remplissage de la sous-image
		for (int k=j; k<j+h; k++)
		{
			for (int l=i; l<i+w; l++)
			{
				crop(k,l) = this->pixels[k+l*width];
			}
		}
			
		return crop;
	}
};

#endif
