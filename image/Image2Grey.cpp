#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include "Image2D.h"
#include "Image2Grey.h"
#include "Matrix33d.h"
#include "Vector.h"
#include "Utils.h"
#include "gradient_sobel.h"

// Fonction		: Image2Grey()
// Argument(s)		: - width : un entier contenant la largeur de l'image
//			  - height : un entier contenant la hauteur de l'image
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: positione l'imatensité maximale à 0
Image2Grey::Image2Grey(int width, int height) : Image2D(width, height), _max_intensity(0)
{}

// Fonction		: subsampling (sous-échanillonage) 
// Argument(s)		: - img : référence sur l'image à traiter
// Valeur de retour	: une nouvelle image de dimensions/2
// Pré-condition(s)	: l'image doit avoir une largeur/hauteur paire (sinon la dernière ligne/colonne est ignorée)
// Post-condition(s)	: /
// Commentaire(s)	: réalise un sous-échantillonage c'est-à-dire diminue la taille de l'image par 2
Image2Grey *Image2Grey::subsampling(Image2Grey& img)
{
	int w = img.getWidth()/2;
	int h = img.getHeight()/2;
	unsigned int pixel_val = 0;

	// nouvelle image
	Image2Grey *new_img = new Image2Grey(w, h);

	// parcours de l'image
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			// somme des 4 pixels (en unsigned int ) cause du débordement possible des unsigned char)
			pixel_val = img(2*i, 2*j) + img(2*i + 1, 2*j) + img(2*i, 2*j + 1) + img(2*i + 1, 2*j + 1);
			pixel_val = pixel_val / 4;
			// remplissage avec la valeur en unsigned char
			new_img->data_[i*w + j] = (unsigned char)pixel_val;
		}
	}
	
	// retourner l'image
	return new_img;
}

// Fonction		: smoothing (lissage)
// Argument(s)		: - img : une référence sur l'image à lisser
//			  - n : l'épaisseur du lissage (ie le nombre de voisins est (2n+1)² c-à-d une bordure de 1 pixel autour du pixel à traiter)
// Valeur de retour	: une nouvelle image lissée
// Pré-condition(s)	: n doit être positif et "pas trop grand"
// Post-condition(s)	: les bords ne sont pas traités (ie les n lignes/colonnes extérieures)
// Commentaire(s)	: lisse l'image en faisant la noyenne pour chaque pixel avec les (2n+1)² autour
Image2Grey *Image2Grey::smoothing(Image2Grey& img, int n)
{
	// vérification du seuil
	if (n < 0)
	{
		fprintf(stderr, "smoothing ERROR : n (%d) is negative\n", n);
		exit(1);	
	}
	// pas de vérification pour la taille max...

	// allocation de la nouvelle image
	Image2Grey *new_img = new Image2Grey(img.getWidth(), img.getHeight());
	unsigned int voisins = 0;
	unsigned int nb_voisins = (unsigned int)(2*n + 1);
	int w = img.getWidth();

	// copie des valeurs de la bordure extérieure
	
	// les n premières colonnes de haut en bas
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < img.getHeight(); j++)
		{
			new_img->data_[i*w + j] = img(i,j);
		}
	}		

	// les n dernières colonnes de haut en bas
	for (int i = img.getWidth() - n; i < img.getWidth(); i++)
	{
		for (int j = 0; j < img.getHeight(); j++)
		{
			new_img->data_[i*w + j] = img(i,j);
		}
	}

	// les n premières lignes sans les coins et les n dernières lignes sans les coins
	for (int i = n; i < img.getWidth() - n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			new_img->data_[i*w + j] = img(i,j);
		}
		for (int k = img.getHeight() - n; k < img.getHeight(); k++)
		{
			new_img->data_[i*w + k] = img(i,k);
		}
	}

	// parcours de la nouvelle image (sauf la bordure extérieure)
	for (int i = n; i < img.getWidth() - n; i++)
	{
		for (int j = n; j < img.getHeight() - n; j++)
		{
			// somme des (2n+1)² voisins en passant par des unsigned int pour éviter le dépassement de capacité des unsigned char)
			voisins = 0;
			for (int k = i - n; k < i + n + 1; k++)
			{
				for (int l = j - n; l < j + n + 1; l++)
				{
					voisins += (unsigned int)img(k,l);
				}
			}
			// remplissage du pixel en unsigned char
			voisins = voisins / nb_voisins;
			new_img->data_[i*w + j] = (unsigned char)voisins;
		}
	}

	// retourner l'image
	return new_img;
}

// Fonction		: thresholding (seuillage par une valeur)
// Argument(s)		: - img : une référence sur l'image à lisser 
//			  - n : un entier contenant la valeur du seuil
// Valeur de retour	: une nouvelle image seuillée
// Pré-condition(s)	: aucune puisque l'argument est de type unsigned char il ne peut excéder 255 ni être négatif
// Post-condition(s)	: /
// Commentaire(s)	: retourne une image seuillée par n
Image2Grey *Image2Grey::thresholding(Image2Grey& img, unsigned char n)
{
	// allocation de la nouvelle image
	Image2Grey *new_img = new Image2Grey(img.getWidth(), img.getHeight());
	int w = img.getWidth();

	// parcours de l'image
	for (int i = 0; i < img.getWidth(); i++)
	{
		for (int j = 0; j < img.getHeight(); j++)
		{
			// seuillage : pixel < seuil = 0, pixel >= seuil = 255
			if (img(i,j) < n)
			{
				new_img->data_[i*w + j] = 0;
			}
			else
			{
				new_img->data_[i*w + j] = 255;
			}
		}
	}

	// retourner l'image
	return new_img;
}

// Fonction		: gradient_sobel
// Argument(s)		: - img : une référence sur une image de type Image2Grey (image de niveaux de gris)
// Valeur de retour	: une image de type Image2D<Vec2f> ou Vec2f est un vecteur de 2 float
// Pré-condition(s)	: /
// Post-condition(s)	: les bords ne sont pas traités
// Commentaire(s)	: calcule une convolution avec le gradient de Sobel
Image2D<Vec2f> *Image2Grey::gradient_sobel(Image2Grey &img)
{
	int vertical_conv = 0;
	int horizontal_conv = 0;

	// allocation de l'image
	Image2D<Vec2f> *new_img = new Image2D<Vec2f>(img.getWidth(), img.getHeight());
	Vec2f gradient;

	// remplissage des bords

	// parcours de l'image sans les bords
	for (int i = 2; i < img.getWidth() - 2; i++)
	{
		for (int j = 2; j < img.getHeight() - 2; j++)
		{
			// convolution verticale et horizontale
			vertical_conv = 0;
			horizontal_conv = 0;
			for (int k = i - 2; k < i + 3; k++)
			{
				for (int l = j - 2; l < j + 3; l++)
				{
					vertical_conv += img(k,l);
					horizontal_conv += img(k,l);
				}
			}
			// remplissage du vec2f
			//gradient[0] = sqrt((float)(vertical_conv*vertical_conv) + (float)(horizontal_conv*horizontal_conv));
			//gradient[1] = atan((float)horizontal_conv / (float)vertical_conv);
			gradient[0] = (float)vertical_conv;
			gradient[1] = (float)horizontal_conv;
			(*new_img)(i,j) = gradient;
		}
	}

	// retourner l'image
	return new_img;
}

// Fonction		: load
// Argument(s)		: - filename : une chaine de caractères contenant le nom du fichier à lire
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: lit le fichier et remplit l'image avec les données du fichier
void Image2Grey::load(std::string filename)
{
	int w = 0;
	int h = 0;
	int max = 0;
	int *tmp_data = NULL;

	// lecture des données
	__read(filename, w, h, max, &tmp_data);

	// conversion des données de int en unsigned char
	this->h_ = h;
	this->w_ = w;
	this->_max_intensity = max;
	delete[] this->data_;
	this->data_ = new unsigned char[h*w];
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			this->data_[i*w + j] = (unsigned char)*(tmp_data + (i*w + j));
		}
	}

	// libération de la mémoire allouée pour le buffer temporaire
	delete[] tmp_data;
}

// Fonction		: save
// Argument(s)		: - filename : une chaine de caractères contenant le nom du fichier où sauvegarder l'image
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: sauvegarde l'image actuelle dans un fichier nommé filename
void Image2Grey::save(std::string filename)
{
	// création d'un buffer temporaire contenant les données converties de unsigned char vers int
	int *tmp_data = NULL;
	tmp_data = new int[this->w_*this->h_];

	for (int i = 0; i < this->h_; i++)
	{
		for (int j = 0; j < this->w_; j++)
		{
			*(tmp_data + (i*this->w_ + j)) = (int)this->data_[i*this->w_ + j];
		}
	}

	// écriture des données du buffer temporaire
	__write(filename, this->w_, this->h_, tmp_data);

	// libération de la mémoire allouée pour le buffer temporaire
	delete[] tmp_data;
}

// Fonction		: __check_data
// Argument(s)		: - width : entier contenant la largeur de l'image
//			  - height : entier contenant la hauteur de l'image
//			  - max_intensity : entier contenant la valeur de l'intensité maximale de gris
//			  - data_array : un pointeur sur un tableau contenant les données à vérifier
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: vérifie que les données sont conformes au format PGM ascii
void Image2Grey::__check_data(int width, int height, int max_intensity, int *data_array)
{
	int i, j;
	int *index;

	// largeur négative
	if (width <= 0)
	{
		fprintf(stderr, "__check_data ERROR : width is lesser or equal to zero\n");
		exit(1);
	}

	// hauteur négative
	if (height <= 0)
	{
		fprintf(stderr, "__check_data ERROR : height is lesser or equal to zero\n");
		exit(1);
	}

	// pointeur sur les données NULL
	if (data_array == NULL)
	{
		fprintf(stderr, "__check_data ERROR : data_array is a NULL pointer");
		exit(1);
	}

	index = data_array;

	// parcours des données
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			// erreur si une valeur de pixel est négtive
			if (*index < 0)
			{
				fprintf(stderr, "__check_data ERROR : negative data\n");
				fprintf(stderr, "data(%d,%d) = %d\n", i, j, *index);
				exit(1);
			}
			// ou si une valeur de pixel est plus élevée que l'intensité maximale
			else if (*index > max_intensity)
			{
				fprintf(stderr, "__check_data ERROR : value is superior to max_intensity\n");
				fprintf(stderr, "data(%d,%d) = %d and max_intensity is %d\n", i, j, *index, max_intensity);
				exit(1);
			}
			index = index + 1;
		}
	}
}

// Fonction		: __read_header
// Argument(s)		: - input : le flux d'entrée dans lequel lire le fichier
//			  - width :  une référence sur la variable contenant la largeur de l'image
//			  - height : une référence sur la variable contenant la hauteur de l'image
//			  - max_intensity : une référence sur la variable contenant l'intensité maximale de gris
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: lit le header et remplit les les variables width, height et max_intensity
void Image2Grey::__read_header(std::ifstream& input, int& width, int& height, int& max_intensity)
{
	std::string line;
	std::string rest;
	int step;
	std::string word;

	step = 0;

	while (1)
	{
		getline(input, line);

		// EOF
		if (input.eof())
		{
			fprintf(stderr, "__read_header ERROR : end of file\n");
			exit(1);
		}

		// on ignore les commentaire
		if (line[0] == '#')
		{
			continue;
		}

		// étape 0 : lire et vérifier le magic number
		if (step == 0)
		{
			// extraire le premier mot
			__s_extract_first_word(line, word, rest);

			// mot vide
			if (__s_len(word) == 0)
			{
				continue;
			}
			line = rest;

			// mauvais magic number
			if ((word[0] != 'P' && word[0] != 'p') ||
				word[1] != '2')
			{
				fprintf(stderr, "__read_header ERROR : bad magic number\n");
				fprintf(stderr, "privided magic number is %s but P2 was expected\n", word.c_str());
				exit(1);
			}
			step = 1;
		}

		// étape : lire la largeur de l'image
		if (step == 1)
		{
			// extraire le permier mot
			__s_extract_first_word(line, word, rest);

			// mot vide
			if (__s_len(word) == 0)
			{
				continue;
			}
			
			// lire la largeur de l'image
			width = atoi(word.c_str());
			line = rest;
			step = 2;
		}

		// étape 2 : lire la hauteur de l'image
		if (step == 2)
		{
			// extraire le premier mot
			__s_extract_first_word(line, word, rest);

			// mot vide
			if (__s_len(word) == 0)
			{
				continue;
			}

			// lecture de la hateur
			height = atoi(word.c_str());
			line = rest;
			step = 3;
		}

		// étape 3 : lire l'intensité maximale de gris
		if (step == 3)
		{
			// extraire le premier mot
			__s_extract_first_word(line, word, rest);

			// mot vide
			if (__s_len(word) == 0)
			{
				continue;
			}
			
			// lecture de l'intensité maximale de gris
			max_intensity = atoi(word.c_str());
			
			// fin de la lecture du header
			break;
		}
	}
}

// Fonction		: __read_data
// Argument(s)		: - infile : flux d'entrée dans lequel lire le fichier
//			  - width : référence sur la variable contenant la largeur de l'image
//			  - height : référence sur la variable contenant la hauteur de l'image
//			  - data_array : tableau contenant les données
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: lit les données du fichier et les place dans le tableau
void Image2Grey::__read_data(std::ifstream& infile, int& width, int& height, int *data_array)
{
	int i, j;

	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			// stockage dans data_array
			infile >> *data_array;
			if (infile.eof())
			{
				exit(1);
			}
			data_array = data_array + 1;
		}
	}
}

// Fonction		: __read
// Argument(s)		: - filename : flux d'entrée dans lequel lire l'image
//			  - width : référence sur la variable contenant la largeur de l'image
//			  - height : référence sur la variable contenant la hauteur de l'image
//			  - max_intensity : référence sur la variable contenant l'intensité maximale de gris
//			  - data_array : pointeur sur le tableau contenant les données
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: lit le fichier et remplit width, height, max_intensity et data_array
void Image2Grey::__read(std::string filename, int& width, int& height, int& max_intensity, int **data_array)
{
	std::ifstream input;
	int numbytes;

	input.open(filename.c_str());

	if (!input)
	{
		fprintf(stderr, "read ERROR : cannot open input file\n");
		exit(1);
	}
	// lecture du header avec __read_header
	__read_header(input, width, height, max_intensity);
	// calcul de la taille de l'image
	numbytes = width * height * sizeof(int);
	// allocation de la mémoire
	*data_array = new int[numbytes];
	// lecture des données avec __read_data
	__read_data(input, width, height, *data_array);
	// fermeture du fichier
	input.close();
}

// Fonction 		: __write_header
// Argument(s)		: - outfile : flux de sortie das lequel écrire le header
//			  - filename : non du fichier dans lequel écrire
//			  - width : entier contenant la largeur actuelle de l'image
//			  - height : entier contenant la hauteur actuelle de l'image
//			  - max_intensity : entier contenant l'intensité maximale de l'image
// Valeur de retour	: /
// Pré-condition(s)	: / 
// Post-condition(s)	: /
// Commentaire(s)	: écrit les informations du header dans le fichier
void Image2Grey::__write_header(std::ofstream& outfile, std::string filename, int width, int height, int max_intensity)
{
	outfile << "P2\n";
	outfile << "# " << filename << " created by Image2Grey::write\n";
	outfile << width << "  " << height << "\n";
	outfile << max_intensity << "\n";
}

// Fonction		: __write_data
// Argument(s)		: - outfile : flux de sortie dans lequel écrire les données
// 			  - width : entier contenant la largeur actuelle de l'image
//			  - height : entier contenant la hauteur actuelle de l'image
//			  - data_array : tableau contenant les données à écrire
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: écrit les données dans le fichier
void Image2Grey::__write_data(std::ofstream& outfile, int width, int height, int *data_array)
{
	int i;
	int *indexg;
	int j;
	int numval;

	indexg = data_array;
	numval = 0;

	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			outfile << *indexg;
			numval = numval + 1;
			indexg = indexg + 1;

			if (numval % 12 == 0 || i == width - 1 || numval == width * height)
			{
				outfile << "\n";
			}
			else
			{
				outfile << " ";
			}

		}
	}
}

// Fonction		: __write
// Argument(s)		: - filename : nom du fichier dans lequel sauvegarder l'image 
//			  - width : entier contenant la largeur de l'image
//			  - height : entier contenant la hauteur de l'image
//			  - data_array : tableau contenant les données
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: écrit le header et les données dans le fichier nommé filename
void Image2Grey::__write(std::string filename, int width, int height, int *data_array)
{
	std::ofstream output;

	// ouverture du fichier
	output.open(filename.c_str());
	if (!output)
	{
		fprintf(stderr, "write ERROR : cannot open the file\n");
		exit(1);
	}

	// calcul de l'intensité maximale
	int max_intensity = 0;
	int *indexg = data_array;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (max_intensity < *indexg)
			{
				max_intensity = *indexg;
			}
			indexg = indexg + 1;

		}
	}

	// écriture du header avec __write_header
	__write_header(output, filename, width, height, max_intensity);
	// écriture des données avec __write_data
	__write_data(output, width, height, data_array);
	// fermeture du fichier
	output.close();
}

// Fonction		: __s_len
// Argument(s)		: - s : chaine de caractères à traiter 
// Valeur de retour	: un entier contenant la longueur de la chaine jusq'au dernier blanc (0 = mot vide)
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: différent de strlen puisque l'on compte jusqu'au dernier blanc non jusqu'a \0
int Image2Grey::__s_len(std::string s)
{
	int n;
	n = s.length();

	while (0 < n)
	{
		if (s[n - 1] != ' ')
		{
			return n;
		}
		n = n - 1;
	}
	return n;
}

// Fonction		: __s_extract_first_word
// Argument(s)		: - s : chaine de caractères à traiter
//			  - s1 : référence sur une chaine de caractères qui contiendra le permier mot de s
//			  - s2 : référence sur une chaine de caractères qui contiendra le reste de s
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: extrait le permier mot de s dans s1 et place le reste dans s2
void Image2Grey::__s_extract_first_word(std::string s, std::string &s1, std::string &s2)
{
	int i;
	int mode;
	int s_len;

	s_len = s.length();
	s1 = "";
	s2 = "";
	mode = 1;

	for (i = 0; i < s_len; i++)
	{
		if (mode == 1)
		{
			if (s[i] != ' ')
			{
				mode = 2;
			}
		}
		else if (mode == 2)
		{
			if (s[i] == ' ')
			{
				mode = 3;
			}
		}
		else if (mode == 3)
		{
			if (s[i] != ' ')
			{
				mode = 4;
			}
		}
		if (mode == 2)
		{
			s1 = s1 + s[i];
		}
		else if (mode == 4)
		{
			s2 = s2 + s[i];
		}
	}
}
