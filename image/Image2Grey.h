#ifndef __IMAGE2GREY_H__
#define __IMAGE2GREY_H__

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "Image2D.h"
#include "Utils.h"
#include "gradient_sobel.h"

class Image2Grey : public Image2D<unsigned char>
{
protected:
	int _max_intensity;
private:
	// varifie les données
	void __check_data(int width, int height, int max_intensity, int *data_array);

	// lit le header du fichier
	void __read_header(std::ifstream& infile, int& width, int& height, int& max_intensity);
	// lit les données du fichier
	void __read_data(std::ifstream& infile, int& width, int& height, int *data_array);
	// lit le header et les données du fichier
	void __read(std::string filename, int& width, int& height, int& max_intensity, int **data_array);

	// écrit le header dans le fichier
	void __write_header(std::ofstream& outfile, std::string filename, int width, int height, int max_intensity);
	// écrit les données dans le fichier
	void __write_data(std::ofstream& outfile, int width, int height, int *data_array);
	// écrit le header et les données
	void __write(std::string filename, int width, int height, int *data_array);

	// calcule la longueur de la chaine s jusqu'au dernier blanc
	int __s_len(std::string s);
	// extrait le permier mot de la chaine s dans la chaine s1 et le reste dans la chaine s2
	void __s_extract_first_word(std::string s, std::string& s1, std::string& s2);
public:
	// le constructeur vide est interdit
	Image2Grey() = delete;

	// constructeur
	Image2Grey(int width, int height);

	// sous-échantillonnage
	static Image2Grey *subsampling(Image2Grey& img);

	// lissage
	static Image2Grey *smoothing(Image2Grey& img, int n);

	// seuillage par une valeur
	static Image2Grey *thresholding(Image2Grey& img, unsigned char n);

	// gradient de sobel
	static Image2D<Vec2f> *gradient_sobel(Image2Grey& img);

	// charge l'image depuis le fichier
	void load(std::string filename);

	// sauvegarde l'image dans le fichier
	void save(std::string filename);
};

#endif
