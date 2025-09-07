#include <cassert>

long int factorielle(int num) {

	assert(num >= 0);
	assert(num <= 12);

	if (num == 0) return 1;

	long int result = 1;
	for (int i = 2; i <= num; ++i) {
		result *= i;
	}

	return result;
}
/*
* Amount of combinations formula ->		n!/(k!(n-k)!
*/
long int calculeNbCombinaisons(int nbChiffresTotaux, int nbChiffresAChoisir) {
	assert(nbChiffresTotaux >= 1 && nbChiffresTotaux <= 12);
	assert(nbChiffresAChoisir >= 1 && nbChiffresAChoisir <= nbChiffresTotaux);

	long int n = factorielle(nbChiffresTotaux);
	long int k = factorielle(nbChiffresAChoisir);
	long int sub = factorielle(nbChiffresTotaux - nbChiffresAChoisir);
	
	long int nbCombinations = n / (k * sub);

	return nbCombinations;
}