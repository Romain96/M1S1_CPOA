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
	bool tMultiplicationVec3fMatrix33d = testMultiplicationVec3fMatrix33d();
	bool tMultiplicationMatrix33dVec3f = testMultiplicationMatrix33dVec3f();
	bool tMultiplicationVec2fMatrix33d = testMultiplicationVec2fMatrix33d();
	bool tMultiplicationMatrix33dVec2f = testMultiplicationMatrix33dVec2f();

        cout << "=============================================" << endl;
        cout << "Programme de test de la classe Matrix33d" << endl;
        cout << "=============================================" << endl;
        cout << "Matrix33d : inversion de matrice = " << tInverse << endl;
        cout << "Matrix33d : translation statique = " << tTranslationStatique << endl;
        cout << "Matrix33d : rotation statique = " << tRotationStatique << endl;
        cout << "Matrix33d : homothétie statique = " << tHomothetieStatique << endl;
	cout << "Matrix33d : multiplication Vec3f * Matrix33d = " << tMultiplicationVec3fMatrix33d << endl;
	cout << "Matrix33d : multiplication Matrix33d * Vec3f = " << tMultiplicationMatrix33dVec3f << endl;
	cout << "Matrix33d : multiplication Vec2f * Matrix33d = " << tMultiplicationVec2fMatrix33d << endl;
	cout << "Matrix33d : multiplication Matrix33d * Vec2f = " << tMultiplicationMatrix33dVec2f << endl;
        cout << "=============================================" << endl;
        if (tInverse && tTranslationStatique && tRotationStatique && tRotationStatique && tHomothetieStatique && 
		tMultiplicationVec3fMatrix33d && tMultiplicationMatrix33dVec3f && 
		tMultiplicationVec2fMatrix33d && tMultiplicationVec2fMatrix33d )
                cout << "RESULTAT MATRIX33D : OK" << endl;
        else
                cout << "RESULTAT MATRIX33D : PAS OK" << endl;
}
