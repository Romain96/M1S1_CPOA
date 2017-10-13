#include <iostream>
#include "matrix33d.h"

int main()
{

	Matrix33d m1 = Matrix33d::identity();

	std::cout << "translate(3.5f,2.4f) "<<  std::endl;
	m1.translate(3.5f,2.4f);
	std::cout << m1 <<  std::endl;

	x = 0.0;
	y = 0.0;
	m1.applyTransformation(x,y);
	std::cout << "0,0 => "<< x << "," << y << std::endl;

	m1.rotate(0.4);
	Matrix33d m2 = m1.inverse();

	std::cout << m1 << std::endl<<"*"<< std::endl<<m2<< "=" << std::endl<< m1*m2 << std::endl;


	return 0;
}
