#include "image2d.h"
#include "image2grey.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// constructeur
Image2Grey::Image2Grey(int w, int h) : Image2D<unsigned char>(w, h)
{
}

// reads the file named filename and loads the data into the picture object
void Image2Grey::read(std::string filename)
{
	int w = 0;
	int h = 0;
	int max = 0;
	int *tmp_data = NULL;
	__read(filename, w, h, max, &tmp_data);

	// convert data to unsigned char and allocate picture
	printf("reading height %d and width %d\n", h, w);
	this->h_ = h;
	this->w_ = w;
	this->max_intensity = max;
	this->pixels_ = new unsigned char[h*w];
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			this->pixels_[i*w + j] = (unsigned char)*(tmp_data + (i*w + j));
		}
	}
	delete[] tmp_data;
}

// saves the current stored picture in the file names filename
void Image2Grey::write(std::string filename)
{
	// creates temporary data storage for int from unsigned int
	int *tmp_data = NULL;
	tmp_data = new int[this->w_*this->h_];

	for (int i = 0; i < this->h_; i++)
	{
		for (int j = 0; j < this->w_; j++)
		{
			*(tmp_data + (i*this->w_ + j)) = (int)this->pixels_[i*this->w_ + j];
		}
	}
	__write(filename, this->w_, this->h_, tmp_data);
	delete[] tmp_data;
}

// sous-échantilonage (retourne la taille de l'image par 2)
Image2Grey Image2Grey::sous_echantillonage()
{
	int width = this->getWidth();
	int height = this->getHeight();
	printf("height : %d, width %d\n", height, width);
	// création de la nouvelle image (taille/2)
	Image2Grey imageDiv2(width/2, height/2);

	// parcours de l'ancienne image et moyenne sur les 4 cases telles que
	// nouvelle[i][j] = moyenne de ancienne[i][j], ancienne[i][j+1], ancienne[i+1][j], ancienne[i+1][j+1]
	for (int i = 0; i < height - 1; i+=2)
	{
		for (int j = 0; j < width - 1; j+=2)
		{
			// somme des 4 valeurs
			int val = pixels_[j + i*width] + pixels_[(j+1) + i*width] +
				pixels_[j + (i+1)*width] + pixels_[(j+1) + (i+1)*width];
			// moyenne
			val = val/4;
			// remplissage de la nouvelle image
			imageDiv2(i/2, j/2) = val;
		}
	}
	return imageDiv2;
}

// lissage paramétré par les (2n+1)^2 pixels voisins
Image2Grey Image2Grey::lissage(int n)
{
	Image2Grey liss(this->getWidth(), this->getHeight());
	unsigned int moy = 0;

	// les bords ne sont pas traités !
	for (int i=n; i<this->getHeight()-n; i++)
	{
		for (int j=n; j<this->getWidth()-n; j++)
		{
			moy = 0;
			// récupération des (2n+1)^2 pixels voisins de (i,j)
			for (int k=i-n; k<i+n; k++)
			{
				for (int l=j-n; l<j+n; j++)
				{
					moy += pixels_[l+k*this->getWidth()];
				}
			}
			// calcul de la moyenne
			moy = moy / ((2*n+1)*(2*n+1));
			// pixel lissé
			liss(i,j) = moy;
		}
	}
	
	return liss;
}

// suillage par une valeur
Image2Grey Image2Grey::seuillage(int seuil)
{
	Image2Grey s(this->getWidth(), this->getHeight());	// nouvelle image
	
	// remplissage des pixels de la nouvelle image
	for (int i=0; i<this->getHeight(); i++)
	{
		for (int j=0; j<this->getWidth(); j++)
		{
			if (pixels_[j+i*this->getWidth()] < seuil)
			{
				// 0 en dessous du seuil
				s(i,j) = pixels_[j+i*this->getWidth()];
			}
			else
			{
				// 255 sinon
				s(i,j) = pixels_[j+i*this->getWidth()];
			}
		}
	}

	return s;
}

// Checks the data : it must be an ASCII PGM format
void Image2Grey::__check_data(int width, int height, int max_intensity, int *pixels_array)
{
	int i, j;
	int *index;

	// wrong width
	if (width <= 0)
	{
		fprintf(stderr, "__check_data ERROR : width is lesser or equal to zero\n");
		exit(1);
	}

	// wrong height
	if (height <= 0)
	{
		fprintf(stderr, "__check_data ERROR : height is lesser or equal to zero\n");
		exit(1);
	}

	// wrong pixels_array storage
	if (pixels_array == NULL)
	{
		fprintf(stderr, "__check_data ERROR : pixels_array is a NULL pointer");
		exit(1);
	}

	index = pixels_array;

	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			if (*index < 0)
			{
				fprintf(stderr, "__check_data ERROR : negative data\n");
				fprintf(stderr, "data(%d,%d) = %d\n", i, j, *index);
				exit(1);
			}
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

// reads the header
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

		if (input.eof())
		{
			fprintf(stderr, "__read_header ERROR : end of file\n");
			exit(1);
		}

		// ignore the comment lines starting with #
		if (line[0] == '#')
		{
			continue;
		}

		// step 0 : reading and checking the magic number
		if (step == 0)
		{
			// extracting the first word of the line
			s_word_extract_first(line, word, rest);

			// no word (0 = only blanks)
			if (s_len_trim(word) == 0)
			{
				continue;
			}
			line = rest;

			// wrong magic number
			if ((word[0] != 'P' && word[0] != 'p') ||
				word[1] != '2')
			{
				fprintf(stderr, "__read_header ERROR : bad magic number\n");
				fprintf(stderr, "privided magic number is %s but P2 was expected\n", word.c_str());
				exit(1);
			}
			step = 1;
		}

		// step 1 : reading the width of the picture
		if (step == 1)
		{
			// extracting the first word of the line
			s_word_extract_first(line, word, rest);

			// no word
			if (s_len_trim(word) == 0)
			{
				continue;
			}
			width = atoi(word.c_str());
			line = rest;
			step = 2;
		}

		// step 2 : reading the height of the picture
		if (step == 2)
		{
			// extracting the first word of the line
			s_word_extract_first(line, word, rest);

			// no word
			if (s_len_trim(word) == 0)
			{
				continue;
			}
			height = atoi(word.c_str());
			line = rest;
			step = 3;
		}

		// step 3 : reading the maximal grey intensity
		if (step == 3)
		{
			// extracting the first word of the line
			s_word_extract_first(line, word, rest);

			// no word
			if (s_len_trim(word) == 0)
			{
				continue;
			}
			max_intensity = atoi(word.c_str());
			break;
		}
	}
}

// reads the data
void Image2Grey::__read_data(std::ifstream& infile, int& width, int& height, int *pixels_array)
{
	int i, j;

	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			// storing word in data array
			infile >> *pixels_array;
			if (infile.eof())
			{
				exit(1);
			}
			pixels_array = pixels_array + 1;
		}
	}
}

// reads the header and the data
void Image2Grey::__read(std::string filename, int& width, int& height, int& max_intensity, int **pixels_array)
{
	std::ifstream input;
	int numbytes;

	input.open(filename.c_str());

	if (!input)
	{
		fprintf(stderr, "read ERROR : cannot open input file\n");
		exit(1);
	}
	// reads the header
	__read_header(input, width, height, max_intensity);
	// computing the size of the data
	numbytes = width * height * sizeof(int);
	// allocating memory space for data
	*pixels_array = new int[numbytes];
	// reads the data
	__read_data(input, width, height, *pixels_array);
	// close the file
	input.close();
}

// writes the header
void Image2Grey::__write_header(std::ofstream& outfile, std::string filename, int width, int height, int max_intensity)
{
	outfile << "P2\n";
	outfile << "# " << filename << " created by PGM.write\n";
	outfile << width << "  " << height << "\n";
	outfile << max_intensity << "\n";
}

// writes the data

void Image2Grey::__write_data(std::ofstream& outfile, int width, int height, int *pixels_array)
{
	int i;
	int *indexg;
	int j;
	int numval;

	indexg = pixels_array;
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

// writes the header and data
void Image2Grey::__write(std::string filename, int width, int height, int *pixels_array)
{
	std::ofstream output;
	int i;
	int *indexg;
	int j;
	int max_intensity;
	//
	//  Open the output file.
	//
	output.open(filename.c_str());

	if (!output)
	{
		fprintf(stderr, "write ERROR : cannot open the file\n");
		exit(1);
	}
	//
	//  Compute the maximum.
	//
	max_intensity = 0;
	indexg = pixels_array;

	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			if (max_intensity < *indexg)
			{
				max_intensity = *indexg;
			}
			indexg = indexg + 1;

		}
	}
	// writes the header
	__write_header(output, filename, width, height, max_intensity);
	// writes the data
	__write_data(output, width, height, pixels_array);
	// close the file
	output.close();
}

// returns the length of the string to the last non blank character (0 = entirely blank)
int Image2Grey::s_len_trim(std::string s)
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

// extracts the first word of a string
void Image2Grey::s_word_extract_first(std::string s, std::string &s1, std::string &s2)
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

