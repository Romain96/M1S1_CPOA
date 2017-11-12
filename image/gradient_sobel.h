#ifndef __GRADIENT_SOBEL_H__
#define __GRADIENT_SOBEL_H__

// définition des filtres de convolution

// direction verticale
const int __sobel_horizontal[5][5] = {
	{1, 2, 0, -2, -1},
	{4, 8, 0, -8, -4},
	{6, 12, 0, -12, -6},
	{4, 8, 0, -8, -4},
	{1, 2, 0, -2, -1}
};

// direction horizontale
const int __sobel_vertical[5][5] = {
	{1, 4, 6, 4, 1},
	{2, 8, 12, 8, 2},
	{0, 0, 0, 0, 0},
	{-2, -8, -12, -8, -2},
	{-1, -4, -6, -4, -1}
};

#endif
