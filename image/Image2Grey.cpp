#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include "Image2D.h"
#include "Image2Grey.h"

// Fonction		: Image2Grey()
// Argument(s)		: - width : un entier contenant la largeur de l'image
//			  - height : un entier contenant la hauteur de l'image
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: positione l'imatensité maximale à 0
Image2Grey::Image2Grey(int width, int height) : Image2D(width, height), _max_intensity(0)
{}

// Fonction		: read
// Argument(s)		: - filename : une chaine de caractères contenant le nom du fichier à lire
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: lit le fichier et remplit l'image avec les données du fichier
void Image2Grey::read(std::string filename)
{
	int w = 0;
	int h = 0;
	int max = 0;
	int *tmp_data = NULL;

	// lecture des données
	__read(filename, w, h, max, &tmp_data);

	// conversion des données de int en unsigned char
	printf("reading height %d and width %d\n", h, w);
	this->h_ = h;
	this->w_ = w;
	this->_max_intensity = max;
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

// Fonction		: write
// Argument(s)		: - filename : une chaine de caractères contenant le nom du fichier où sauvegarder l'image
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: sauvegarde l'image actuelle dans un fichier nommé filename
void Image2Grey::write(std::string filename)
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
			// ou si une valur de pixel est plus élevée que l'intensité maximale
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
