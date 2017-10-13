// programme de test des classes array et vector

#include <iostream>
#include "array.h"
#include "vector.h"
#include "arrayTest.h"
#include "vectorTest.h"

using std::cout;
using std::endl;

int main()
{
	// tests sur la classe template Array
	bool tRemplissage = testRemplissage();
	bool tAffectation = testAffectation();
	bool tEgalite = testEgalite();
	bool tNonEgalite = testNonEgalite();
	bool tEchange = testEchange();

	// tests sur la classe template Vector (dérivée de Array)
	bool tSomme = testSomme();
	bool tDifference = testDifference();
	bool tSommeAffectation = testSommeAffectation();
	bool tDifferenceAffectation = testDifferenceAffectation();
	bool tProduitParScalaire = testProduitParScalaire();
	bool tDivisionParScalaire = testDivisionParScalaire();
	bool tProduitAffectationParScalaire = testProduitAffectationParScalaire();
	bool tDivisionAffectationParScalaire = testDivisionAffectationParScalaire();
	bool tProduitScalaire = testProduitScalaire();
	bool tProduitVectoriel = testProduitVectoriel();

	// affichage des résultats
	using std::cout;
	using std::endl;

	cout << "=============================================" << endl;
	cout << "Programme de test des classes Array et Vector" << endl;
	cout << "=============================================" << endl;
	cout << "Array : remplissage (add) = " << tRemplissage << endl;
	cout << "Array : affectation (=) = " << tAffectation << endl;
	cout << "Array : test d'égalité (==) = " << tEgalite << endl;
	cout << "Array : test de non égalité (== et !=) = " << tNonEgalite << endl;
	cout << "Array : test d'échange (swap) = " << tEchange << endl;
	cout << "=============================================" << endl;
	if (tRemplissage && tAffectation && tEgalite && tNonEgalite && tEchange)
		cout << "RESULTAT ARRAY : OK" << endl;
	else
		cout << "RESULTAT ARRAY : PAS OK" << endl;
	cout << "=============================================" << endl;
	cout << "Vector : somme (+) = " << tSomme << endl;
	cout << "Vector : différence (-) = " << tDifference << endl;
	cout << "Vector : somme et affectation (+=) = " << tSommeAffectation << endl;
	cout << "Vector : différence et affectation (-=) = " << tDifferenceAffectation << endl;
	cout << "Vector : produit par un scalaire (*) = " << tProduitParScalaire << endl;
	cout << "Vector : division par un scalaire (/) = " << tDivisionParScalaire << endl;
	cout << "Vector : somme et affectation par un scalaire (*=) = " << tProduitAffectationParScalaire << endl;
	cout << "Vector : division et affectation par un scalaire (/=) = " << tDivisionAffectationParScalaire << endl;
	cout << "Vector : produit scalaire (dot) = " << tProduitScalaire << endl;
	cout << "Vector : produit vectoriel (cross) = " << tProduitVectoriel << endl;
	cout << "=============================================" << endl;
	if (tSomme && tDifference && tSommeAffectation && tDifferenceAffectation &&
	tProduitParScalaire && tDivisionParScalaire && tProduitAffectationParScalaire &&
	tDivisionAffectationParScalaire && tProduitScalaire && tProduitVectoriel)
		cout << "RESULTAT VECTOR : OK" << endl;
	else
		cout << "RESULTAT VECTOR : PAS OK" << endl;
	cout << "=============================================" << endl;
}
