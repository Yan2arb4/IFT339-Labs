
long int factorielle(int num) {
	if (num == 0)
		return 1;

	int count = num - 1;

	while (count > 1) {		//factioral formula ->	n * (n - 1)!
		num *= count;
		count--;
	}

	return num;
}
/*
* Amount of combinations formula ->		n!/(k!(n-k)!
*/
long int calculeNbCombinaisons(int nbChiffresTotaux, int nbChiffresAChoisir) {
	
	int n = factorielle(nbChiffresTotaux);
	int k = factorielle(nbChiffresAChoisir);
	int sub = factorielle(nbChiffresTotaux - nbChiffresAChoisir);
	
	long int nbCombinations = n / (k * sub);

	return nbCombinations;
}