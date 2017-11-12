#ifndef __IMAGE2RGB_H__
#define __IMAGE2RGB_H__

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "Image2D.h"
#include "Vector.h"
#include "Utils.h"

class Image2RGB : public Image2D<Vec3uc>
{
protected:
	int _max_rgb;
private:
	// met le caractère en majuscule
	char __capitalize(char c);
	// égalité de longueur en chaine de caractères sans tenir compte des majuscules
	bool __s_eq(std::string s1, std::string s2);
	// longueur de la chaine jusqu'au dernier blanc (0 = que des blancs)
	int __s_len(std::string s);
	// extrait le premier mot de la chaine s dans s1 et le reste de la chaine dans s2
	void __s_extract_first_word(std::string s, std::string &s1, std::string &s2);

	// vérifie les données
	void __check_data(int width, int height, int max_rgb, int *r_array, int *g_array, int *b_array);

	// lit le header
	void __read_header(std::ifstream &infile, int &width, int &height, int &max_rgb);
	// lit les données
	void __read_data(std::ifstream &infile, int width, int height, int *r_array, int *g_array, int *b_array);
	// lit le fichier
	void __read(std::string filename, int &width, int &height, int &max_rgb, int **r_array, int **g_array, int **b_array);

	// écrit le header
	void __write_header(std::ofstream &outfile, std::string filename, int width, int height, int max_rgb);
	// écrit les données
	void __write_data(std::ofstream &outfile, int width, int height, int *r_array, int *g_array, int *b_array);
	// écrit l'image dans le fichier
	void __write(std::string filename, int width, int height, int *r_array, int *g_array, int *b_array);

public:
	// contructeur vide interdit
	Image2RGB() = delete;

	// constructeur
	Image2RGB(int width, int height);

	// charger une image PPM
	void load(std::string filename);

	// écrire une image au format PPM
	void save(std::string filename);
};

#endif
