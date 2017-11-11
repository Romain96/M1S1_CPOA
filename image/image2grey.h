#ifndef __IMAGE2GREY_H__
#define __IMAGE2GREY_H__

/*
 * Classe représentant les images 2D de type de pixel unsigned char
 */

#include "image2d.h"
#include <string>

class Image2Grey : public Image2D<unsigned char>
{
private:
	// check the data
	void __check_data(int width, int height, int max_intensity, int *data_array);

	// read the header
	void __read_header(std::ifstream& infile, int& width, int& height, int& max_intensity);
	// read the data
	void __read_data(std::ifstream& infile, int& width, int& height, int *data_array);
	// read the header and the data
	void __read(std::string filename, int& width, int& height, int& max_intensity, int **data_array);

	// write the header
	void __write_header(std::ofstream& outfile, std::string filename, int width, int height, int max_intensity);
	// write the data
	void __write_data(std::ofstream& outfile, int width, int height, int *data_array);
	// write the header and the data
	void __write(std::string filename, int width, int height, int *data_array);

	// compute the length of the string until the last blank
	int s_len_trim(std::string s);
	// extract the first word in s1 and the rest of the string in s2
	void s_word_extract_first(std::string s, std::string& s1, std::string& s2);
public:
	// empty constructor disabled
	Image2Grey() = delete;

	// constructor
	Image2Grey(int width, int height);

	// read a file
	void read(std::string filename);

	// write in a file
	void write(std::string filename);

	// sous-échantillonage (divise la taille de l'image par 2)
	Image2Grey sous_echantillonage();

	// lissage (moyenne des pixels avec les (2n+1)^2 pixels voisins)
	Image2Grey lissage(int n);

	// seuillage par une valeur (en paramètre)
	Image2Grey seuillage(int seuil);
};

#endif
