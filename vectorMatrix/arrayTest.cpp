// classe de test de array.h

#include "array.h"
#include "arrayTest.h"

// test de remplissage
bool testRemplissage()
{
	// déclaration et affectation
	Array<10,int> test;
	for (int i=0; i<10; i++)
	{
                test[i] = i;
	}

	// test du remplissage des valeurs
	for (int i=0; i<10; i++)
	{
		if (test[i] != i)
			return false;
	}
	return true;
}

// test de l'opérateur ==
bool testEgalite()
{
	// déclaration et affectation
	Array<10,int> a1;
	Array<10,int> a2;
	for (int i=0; i<10; i++)
	{
                a1[i] = i;
                a2[i] = i;
	}

	// test de l'égalité
	if (a1==a2)
		return true;
	else
		return false;
}

// test de l'opérateur == (faux)
bool testNonEgalite()
{
	// déclaration et affectation
	Array<10,int> a1;
	Array<10,int> a2;
	for (int i=0; i<10; i++)
	{
                a1[i] = i;
                a2[i] = i+1;
	}

	// test de la non égalité
	if (a1==a2)
		return false;
	else
		return true;
}

// test de l'opérateur =
bool testAffectation()
{
	// déclaration et affectation
	Array<10,int> a1;
	Array<10,int> a2;
	for (int i=0; i<10; i++)
	{
                a1[i] = 0;
                a2[i] = i;
	}

	// affectation de a2 à a1
	a1=a2;

	// test de l'affectation
	for (int i=0; i<10; i++)
	{
		if (a1[i] != a2[i])
			return false;
	}
	return true;
}

// test de l'échange
bool testEchange()
{
	// déclaration et affectation
	Array<10,int> a1;
	Array<10,int> a2;
	for (int i=0; i<10; i++)
	{
                a1[i] = i;
                a2[i] = 2*i;
	}

	// échange
	a1.swap(a2);
	
	// test de l'échange
	for (int i=0; i<10; i++)
	{
		if (a1[i] != 2*a2[i])
			return false;
	}
	return true;
}
