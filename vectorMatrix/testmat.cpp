#include <iostream>
#include "array.h"
#include "matrix33d.h"
#include "matrix33dTest.h"

using std::cout;
using std::endl;

int main()
{
	// tests sur la classe Matrix33d
        bool tInverse = testInverse();
        bool tTranslationStatique = testTranslationStatique();
        bool tRotationStatique = testRotationStatique();
        bool tHomothetieStatique = testHomothetieStatique();

        cout << "=============================================" << endl;
        cout << "Programme de test de la classe Matrix33d" << endl;
        cout << "=============================================" << endl;
        cout << "Matrix33d : inversion de matrice = " << tInverse << endl;
        cout << "Matrix33d : translation statique = " << tTranslationStatique << endl;
        cout << "Matrix33d : rotation statique = " << tRotationStatique << endl;
        cout << "Matrix33d : homothétie statique = " << tHomothetieStatique << endl;
        cout << "=============================================" << endl;
        if (tInverse && tTranslationStatique && tRotationStatique && tRotationStatique && tHomothetieStatique)
                cout << "RESULTAT MATRIX33D : OK" << endl;
        else
                cout << "RESULTAT MATRIX33D : PAS OK" << endl;
}
