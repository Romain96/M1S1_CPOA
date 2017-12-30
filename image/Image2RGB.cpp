#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include "Image2RGB.h"

// Fonction         : Image2RGB
// Argument(s)		: - width : un entier contenant la largeur de l'image
//                    - height ; un entier contenant la hauteur de l'image
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: alloue la place pout stocker width*height pixels
Image2RGB::Image2RGB(int width, int height) : Image2D(width, height), _max_rgb(0)
{}

// Fonction         : load
// Argument(s)		: - filename : le nom du fichier dans lequel lire l'image
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: lit le fichier filename et charge l'image
void Image2RGB::load(std::string filename)
{
	int w = 0;
	int h = 0;
	int max_rgb = 0;
	int *r_array;
	int *g_array;
	int *b_array;

	// lire le fichier avec __read
	__read(filename, w, h, max_rgb, &r_array, &g_array, &b_array);

	// remplissage des données
	this->h_ = h;
	this->w_ = w;
	this->_max_rgb = max_rgb;
	delete[] this->data_;
	this->data_ = new Vec3uc[h * w];
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			Vec3uc rgb;
			rgb[0] = (unsigned char)*(r_array + (i*w + j));	// rouge
			rgb[1] = (unsigned char)*(g_array + (i*w + j));	// vert
			rgb[2] = (unsigned char)*(b_array + (i*w + j));	// bleu
			this->data_[i*w + j] = rgb;
		}
	}

	// libération de la mémoire allouée
	delete[] r_array;
	delete[] g_array;
	delete[] b_array;
}

// Fonction         : save
// Argument(s)		: - filename : nom du fichier dans lequel sauvegarder l'image
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: sauvegarde l'image au formar PPM dans le fichier filename
void Image2RGB::save(std::string filename)
{
	// création de 3 buffer temporaires pour RGB
	int *r_array = new int[this->h_ * this->w_];
	int *g_array = new int[this->h_ * this->w_];
	int *b_array = new int[this->h_ * this->w_];
	
	// remplissage des 3 buffers
	for (int i = 0; i < this->w_; i++)
	{
		for (int j = 0; j < this->h_; j++)
		{
			Vec3uc rgb = this->data_[i*this->w_ + j];
			r_array[i*this->w_ + j] = (int)rgb[0];
			g_array[i*this->w_ + j] = (int)rgb[1];
			b_array[i*this->w_ + j] = (int)rgb[2];
		}
	}
	__write(filename, this->w_, this->h_, r_array, g_array, b_array);
	
	// libération de la mémoire allouée
	delete[] r_array;
	delete[] g_array;
	delete[] b_array;
}

// Fonction         : __check_data
// Argument(s)		: - width : entier contenant la largeur de l'image
//                    - height : entier contenant la hauteur de l'image
//                    - max_rgb : entier contenant l'intensité maximale de RGB
//                    - r_array : tableau contenant les valeurs R de chaque pixel
//                    - g_array : tableau contenant les valeurs G de chaque pixel
//                    - b_array : tableau contenant les valeurs B de chaque pixel
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: vérifie que les données sont conformes au format PPM ascii
void Image2RGB::__check_data(int width, int height, int max_rgb, int *r_array, int *g_array, int *b_array)
{
	// largeur incorrecte
	if (width <= 0)
	{
		fprintf(stderr, "Image2RGB::__check_data ERROR : la largeur est inférieure ou égale à 0 (%d)\n", width);
		exit(1);
	}

	// hauteur incorrecte
	if (height <= 0)
	{
		fprintf(stderr, "Image2RGB::__check_data ERROR : la hauteur est inférieure ou égale à 0 (%d)\n", height);
		exit(1);
	}

	// pointer null en r
	if (r_array == NULL)
	{
		fprintf(stderr, "Image2RGB::__check_data ERROR : le tableau des valeurs R est NULL\n");
		exit(1);;
	}

	// pointer null en g
	if (g_array == NULL)
	{
		fprintf(stderr, "Image2RGB::__check_data ERROR : le tableau des valeurs G est NULL\n");
		exit(1);;
	}

	// pointeur null en b
	if (b_array == NULL)
	{
		fprintf(stderr, "Image2RGB::__check_data ERROR : le tableau des valeurs B est NULL\n");
		exit(1);
	}

	int *index = r_array;
	char c;

	// parcours des 3 couleurs (R,G,B)
	for (int k = 0; k < 3; k++)
	{

		if (k == 0)
		{
			index = r_array;
			c = 'R';
		}
		else if (k == 1)
		{
			index = g_array;
			c = 'G';
		}
		else if (k == 2)
		{
			index = b_array;
			c = 'B';
		}

		// parcours du buffer
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				if (*index < 0)
				{
					fprintf(stderr, "Image2RGB::__check_data ERROR : valeur de pixel négative %c(%d,%d) = %d", c, i, j, *index);
					exit(1);
				}
				else if (max_rgb < *index)
				{
					fprintf(stderr, "Image2RGB::__check_data ERROR : valeur de pixel supérieure à max_rgb %c(%d,%d) = %d > %d", c, i, j, *index, max_rgb);
					exit(1);
				}
				index = index + 1;
			}
		}
	}
}

// Fonction         : __read_header
// Argument(s)		: - infile : flux d'entrée dans lequel lire l'image
//                    - width : référence sur un entier contenant la largeur de l'image
//                    - height : référence sur un entier contenant la hauteur de l'image
//                    - max_rgb : référence sur un entier contenant l'intensité maximale de RGB
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: lit le header et positionne width, height et max_rgb
void Image2RGB::__read_header(std::ifstream &infile, int &width, int &height, int &max_rgb)
{
	std::string line;
	std::string rest;
	int step;
	std::string word;

	step = 0;

	while (1)
	{
		getline(infile, line);

		// EOF
		if (infile.eof())
		{
			fprintf(stderr, "Image2RGB::__read_header ERROR : EOF\n");
			exit(1);
		}

		// on ignore les commentaires
		if (line[0] == '#')
		{
			continue;
		}

		// étape 0 : lire P3 qui correspond à une image au format PPM ASCII
		if (step == 0)
		{
			// extraire le permier mot de la ligne
			__s_extract_first_word(line, word, rest);

			// ligne wide
			if (__s_len(word) <= 0)
			{
				continue;
			}

			// numéro magique différent de P3
			if (!__s_eq(word, "P3"))
			{
				fprintf(stderr, "Image2RGB::__read_header ERROR : mauvais numéro magique %s au lieu de P3\n", word.c_str());
				exit(1);
			}
			line = rest;
			step = 1;
		}

		// étape 1 : lire la largeur de l'image
		if (step == 1)
		{
			// extraire le permier mot
			__s_extract_first_word(line, word, rest);

			// mot vide
			if (__s_len(word) <= 0)
			{
				continue;
			}
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
			if (__s_len(word) <= 0)
			{
				continue;
			}
			height = atoi(word.c_str());
			line = rest;
			step = 3;
		}

		// étape 3 : lire l'intensité maximale de RGB
		if (step == 3)
		{
			// extraire le permier mot
			__s_extract_first_word(line, word, rest);

			// mot vide
			if (__s_len(word) <= 0)
			{
				continue;
			}
			max_rgb = atoi(word.c_str());
			line = rest;
			break;
		}
	}
}

// Fonction 		: __read_data
// Argument(s)		: - infile : flux d'entrée dans lequel lire les données 
//                    - width : entier contenant la largeur de l'image
//                    - height : entier contenant la hauteur de l'image
//                    - r_array : tableau contenant les valeurs R de chaque pixel
//                    - g_array : tableau contenant les valeurs G de chaque pixel
//                    - b_array : tableau contenant les valeurs B de chaque pixel
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire()	: lit les données et remplit les tableaux r_array, g_array et b_array
void Image2RGB::__read_data(std::ifstream &infile, int width, int height, int *r_array, int *g_array, int *b_array)
{
	// lecture de hauteur * largeur * 3 entiers
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			infile >> *r_array;
			if (infile.eof())
			{
				fprintf(stderr, "Image2RGB::__read_data ERROR : EOF (pixels R)\n");
				exit(1);
			}
			r_array = r_array + 1;

			infile >> *g_array;
			if (infile.eof())
			{
				fprintf(stderr, "Image2RGB::__read_data ERROR : EOF (pixels G)\n");
				exit(1);
			}
			g_array = g_array + 1;

			infile >> *b_array;
			if (infile.eof())
			{
				fprintf(stderr, "Image2RGB::__read_data ERROR : EOF (pixels B)\n");
				exit(1);
			}
			b_array = b_array + 1;
		}
	}
}

// Fonction         : __read
// Argument(s)		: - filename : nom du fichier dans lequel lire l'image
//                    - width : référence sur un entier contenant la largeur de l'image
//                    - height : référence sur une entier contenant la hauteur de l'image
//                    - max_rgb : référence sur un entier contenant l'intensité maximala RGB
//                    - r_array : pointeur sur un tableau contenant les valeurs R de chaque pixel
//                    - g_array : pointeur sur un tableau contenant les valeurs G de chaque pixel
//                    - b_array : pointeur sur un tableau contenant les valeurs B de chaque pixel
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: lit le fichier filename, positionne width, height et max_rgb et remplit les tableaux r_array, g_array et b_array
void Image2RGB::__read(std::string filename, int &width, int &height, int &max_rgb, int **r_array, int **g_array, int **b_array)
{
	std::ifstream input;
	int numbytes;

	// ouverture du fichier
	input.open(filename.c_str());
	if (!input)
	{
		fprintf(stderr, "Image2RGB::__read ERROR : impossible d'ouvrir le fichier %s\n", filename.c_str());
		exit(1);
	}

	// lecture du header
	__read_header(input, width, height, max_rgb);

	// allocation de 3 buffer pour les couleurs
	numbytes = width * height * sizeof(int);

	*r_array = new int[numbytes];
	*g_array = new int[numbytes];
	*b_array = new int[numbytes];

	// lecture des données
	__read_data(input, width, height, *r_array, *g_array, *b_array);

	// fermeture du fichier
	input.close();
}

// Fonction         : __write_header
// Argument(s)		: - outfile : flux de sortie dans lequel écrire le header
//                    - filename : nom du fichier dans lequel écrire
//                    - width : entier contenant la largeur actuelle de l'image
//                    - height : entier contenant le hauteur actuelle de l'image
//                    - max_rgb : entier contenant l'intensité maximale actuelle de RGB
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: écrit le header dans le flux de sortie outfile
void Image2RGB::__write_header(std::ofstream &outfile, std::string filename, int width, int height, int max_rgb)
{
	outfile << "P3\n";
	outfile << "# " << filename << " created by Image2RGB::write\n";
	outfile << width << "  " << height << "\n";
	outfile << max_rgb << "\n";
}

// Fonction         : __write_data
// Argument(s)		: - outfile : flux de sortie dans lequel écrire l'image
//                    - width : entier contenant la largeur actuelle de l'image
//                    - height : entier contenant la hauteur actuelle de l'image
//                    - r_array : tableau contenant les valeurs R de chaque pixel
//                    - g_array : tableau contenant les valeurs G de chaque pixel
//                    - b_array : tableau contenant les valeurs B de chaque pixel
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: écrit les données dans le flux de sortie outfile
void Image2RGB::__write_data(std::ofstream &outfile, int width, int height, int *r_array, int *g_array, int *b_array)
{
	int *r_index = r_array;
	int *g_index = g_array;
	int *b_index = b_array;
	int rgb_num = 0;	// nombre de valeurs écrites

	// parcours des valeurs R, G et B
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			// écriture du triplet R G B du pixel (i,j)
			outfile << *r_index << " " << *g_index << " " << *b_index;
			rgb_num = rgb_num + 3;
			r_index = r_index + 1;
			g_index = g_index + 1;
			b_index = b_index + 1;

			// saut de ligne ou espace
			if (rgb_num % 12 == 0 || i == width - 1 || rgb_num == 3 * width * height)
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

// Fonction 		: __write
// Argument(s)		: - filename : nom du fichier dans lequel écrire l'image 
//                    - width : entier contenant la largeur actuelle de l'image
//                    - height : entier contenant la hauteur actuelle de l'image
//                    - r_array : tableau contenant les valeurs R de chaque pixel
//                    - g_array : tableau contenant les valeurs G de chaque pixel
//                    - b_array : tableau contenant les valeurs B de chaque pixel
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: écrit le header et les données dans le fichier filename
void Image2RGB::__write(std::string filename, int width, int height, int *r_array, int *g_array, int *b_array)
{
	std::ofstream output;
	
	// ouverture du fichier
	output.open(filename.c_str());

	if (!output)
	{
		fprintf(stderr, "Image2RGB::__write ERROR : impossible d'ouvrir le fichier %s\n", filename.c_str());
		exit(1);
	}
	
	// calcul du maximal
	int max_rgb = 0;
	int *r_index = r_array;
	int *g_index = g_array;
	int *b_index = b_array;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (max_rgb < *r_index)
			{
				max_rgb = *r_index;
			}
			r_index = r_index + 1;

			if (max_rgb < *g_index)
			{
				max_rgb = *g_index;
			}
			g_index = g_index + 1;

			if (max_rgb < *b_index)
			{
				max_rgb = *b_index;
			}
			b_index = b_index + 1;
		}
	}
	
	// écriture du header
	__write_header(output, filename, width, height, max_rgb);
	
	// écriture des données
	__write_data(output, width, height, r_array, g_array, b_array);
	
	// fermeture de fichier
	output.close();
}

// Fonction         : __capitalize
// Argument(s)		: c : un caractère à traiter
// Valeur de retour	: un caractère (le même si c n'est pas une lettre, la majuscule corespondante sinon)
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: retourne c en majuscule si c'est une lettre, sinon retourne c
char Image2RGB::__capitalize(char c)
{
	char cc = c;
	if (97 <= c && c <= 122)
	{
		cc = c - 32;
	}
	return cc;
}

// Fonction         : s_eqi
// Argument(s)		: - s1 : une chaine de caractère
//                    - s2 : autre chaine de caractère
// Valeur de retour	: vrai si les deux chaines sont égales
// Pré-condition(s)	: /
// Post-condition(s): /
// Commentaire(s)	: le test d'égalité est différent de string::compare puisqu'il ne tient pas compte de la casse
bool Image2RGB::__s_eq(std::string s1, std::string s2)
{
	int i;
	int nchar;
	int s1_length;
	int s2_length;

	s1_length = s1.length();
	s2_length = s2.length();

	if (s1_length < s2_length)
	{
		nchar = s1_length;
	}
	else
	{
		nchar = s2_length;
	}
	
	// longueurs différentes = chaines non égales
	for (i = 0; i < nchar; i++)
	{

		if (__capitalize(s1[i]) != __capitalize(s2[i]))
		{
			return false;
		}
	}
	
	// si la plus longue inclue des caractères non blancs à la fin elles ne sont pas égales
	if (nchar < s1_length)
	{
		for (i = nchar; i < s1_length; i++)
		{
			if (s1[i] != ' ')
			{
				return false;
			}
		}
	}
	else if (nchar < s2_length)
	{
		for (i = nchar; i < s2_length; i++)
		{
			if (s2[i] != ' ')
			{
				return false;
			}
		}
	}

	return true;
}

// Fonction         : __s_len
// Argument(s)		: - s : une chaine de caractère
// Valeur de retour	: un entier correspondant à la longueur de la chaine
// Pré-condition	: /
// Post-condition(s): /
// Commentaire(s)	: la longueur est différente de string::length 
//			  la longueur est calculée jusqu'au dernier blanc
int Image2RGB::__s_len(std::string s)
{
	int n = s.length();

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

// Fonction         : s_word_extract_first
// Argument(s)		: - s : chaine de caractère à traiter
//                    - s1 : référence sur une chaine de caractères
//                    - s2 : référence sur une chaine de caractères
// Valeur de retour	: /
// Pré-condition(s)	: /
// Post-condition(s)	: /
// Commentaire(s)	: extrait le premier mot de s dans s1 et place le reste dans s2
void Image2RGB::__s_extract_first_word(std::string s, std::string &s1, std::string &s2)
{
	int s_len = s.length();
	s1 = "";
	s2 = "";
	int mode = 1;

	for (int i = 0; i < s_len; i++)
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
