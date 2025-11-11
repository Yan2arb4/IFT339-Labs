#include "ensemble.h"
#include <iostream>

using namespace std;

int main() {

	ensemble<int> ensembleTest = ensemble<int>();
	for (size_t i = 1; i <= 10; i++)
	{
		ensembleTest.ajoute(i);
	}

	cout << "Ensemble de base : \n";
	afficher(cout, ensembleTest);
	


	cout << "---------------------------------\n";
	cout << "-------Test constructeur---------\n";
	cout << "---------------------------------\n\n";

	cout << "Ensemble de base : \n";
	afficher(cout, ensembleTest);

	cout << "On appel le constructeur par copie pour ensembleCopie\n";
	ensemble<int> ensembleCopie = ensemble<int>(ensembleTest);
	cout << "Contenu ensembleCopie : \n";
	afficher(cout, ensembleCopie);



	cout << "---------------------------------\n";
	cout << "--------Test destructeur---------\n";
	cout << "---------------------------------\n\n";

	cout << "EnsembleCopie avant destruction :\n";
	afficher(cout, ensembleCopie);
	cout << "EnsembleCopie apres destruction :\n";
	ensembleCopie.~ensemble();
	afficher(cout, ensembleCopie);
	cout << "\n\n";
	


	cout << "---------------------------------\n";
	cout << "-----------Test enleve-----------\n";
	cout << "---------------------------------\n\n";
	//Retourne second vrai element de l'ensemble. 
	ensemble<int>::iterateur itEnleve = ensembleTest.second();
	cout << "Enleve le 2e element (devrait etre 2)\n\n";
	cout << "Avant le retrait :\n";
	afficher(cout, ensembleTest);
	cout << "Apres le retrait :\n";
	ensembleTest.enleve(itEnleve);
	afficher(cout, ensembleTest);



	cout << "---------------------------------\n";
	cout << "-----------Test trouve-----------\n";
	cout << "---------------------------------\n";
	cout << "\nDevrait trouve 8\n";
	ensemble<int>::iterateur it8 = ensembleTest.trouve(8);
	cout << "Element trouve : " << *it8 << "\n\n";
	cout << "\nDevrait trouve 3\n";
	ensemble<int>::iterateur it3 = ensembleTest.trouve(3);
	cout << "Element trouve : " << *it3 << "\n\n";
	cout << "\nDevrait trouve 10\n";
	ensemble<int>::iterateur it10 = ensembleTest.trouve(10);
	cout << "Element trouve : " << *it10 << "\n\n";



	cout << "---------------------------------\n";
	cout << "-----------Test retire-----------\n";
	cout << "---------------------------------\n";
	cout << "Enleve l'element a valeur 5\n\n";
	cout << "Avant le retrait :\n";
	afficher(cout, ensembleTest);
	cout << "Apres le retrait :\n";
	ensembleTest.retire(5);
	afficher(cout, ensembleTest);

	return 0;
}

/*
int main() {
	std::cout << "Test Aucune donnée";

	ensemble<int> ensembleTest = ensemble<int>();

	afficher(std::cout, ensembleTest);


	std::cout << "Test 15 données\n";
	for (size_t i = 0; i < 15; i++)
	{
		ensembleTest.ajoute(i);
	}
	ensembleTest.ajoute(5);
	std::cout << "Ajout d'un doublon, l'ensemble ne devrait pas changer :\n";
	afficher(std::cout, ensembleTest);

	std::cout << "---------------------------------\n";
	std::cout << "-----------Test retire-----------\n";
	std::cout << "---------------------------------\n";
	ensembleTest.retire(6);
	afficher(std::cout, ensembleTest);
	ensembleTest.retire(7);
	afficher(std::cout, ensembleTest);

	std::cout << "Retrait d'un element inexistant\n";
	ensembleTest.retire(99);
	afficher(std::cout, ensembleTest);

	std::cout << "---------------------------------\n";
	std::cout << "-----------Test trouve-----------\n";
	std::cout << "---------------------------------\n";
	std::cout << "\n";
	std::cout << "Devrait trouve 10\n";
	ensemble<int>::iterateur it = ensembleTest.trouve(10);
	std::cout << "Element trouvé : " << *it << "\n";
	std::cout << "\n";

	std::cout << "Devrait pas trouve alors print l'avant dernier element\n";
	ensemble<int>::iterateur it6 = ensembleTest.trouve(6);
	std::cout << "Element trouvé : " << *--it6 << "\n";
	ensemble<int>::iterateur it7 = ensembleTest.trouve(7);
	std::cout << "Element trouvé : " << *--it7 << "\n";


	std::cout << "---------------------------------------\n";
	std::cout << "-------Test constructeur copieur-------\n";
	std::cout << "---------------------------------------\n";

	ensemble<int> ensembleCopie = ensemble<int>(ensembleTest);
	afficher(std::cout, ensembleCopie);

	std::cout << "On modifie l'original pour s'assurer que la copie ne change pas en ajoutant 67\n";


	ensembleTest.ajoute(67);

	std::cout << "L'original \n\n";
	afficher(std::cout, ensembleTest);
	std::cout << "La copie \n\n";
	afficher(std::cout, ensembleCopie);

	std::cout << "---------------------------\n";
	std::cout << "-------Test borneSup-------\n";
	std::cout << "---------------------------\n";

	std::cout << "Borne superieur 65 devrait donner 67\n";

	ensemble<int>::iterateur it8 = ensembleTest.borneSup(65);
	std::cout << "Element trouvé : " << *it8 << "\n";

	std::cout << "Borne superieur 13 devrait donner 14\n\n";


	ensemble<int>::iterateur it10 = ensembleTest.borneSup(13);
	std::cout << "Element trouvé : " << *it10 << "\n";

	std::cout << "Borne superieur 67 devrait donner la fin donc afficher 67\n\n";

	ensemble<int>::iterateur it9 = ensembleTest.borneSup(67);
	std::cout << "Element trouvé : " << *--it9 << "\n";


}
*/