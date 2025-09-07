/* * *********************************************************************
 \file main.cpp

 \brief Ce programme trouve la probabilité de gagner une mini loto.

 \author   Tiré du livre "starting out with C++" de Tony Gaddis
 \date     juillet 2016
 \modif    Marie-Flavie Auclair-Fortier, octobre 2020
 \version  2.0
 ********************************************************************** * */


#include <iostream>
#include <iomanip>
#include "modules.h"
#include "cassert"

using namespace std;

int main()
{

    // Declaration des fonctions
    void entrerInfosTirage(int&, int&);

    int nbChiffresTotaux;           // Le nombre total de chiffres
    int nbChiffresAChoisir;         // Le nombre de chiffre à choisir
    long int nbCombinaisons;        // Le nombre de combinaisons possibles

    cout << "Ce programme vous donne la probabilite de gagner la \"loto UdeS\". \n";
    entrerInfosTirage(nbChiffresTotaux, nbChiffresAChoisir);
    nbCombinaisons = calculeNbCombinaisons(nbChiffresTotaux, nbChiffresAChoisir);

    cout << fixed << showpoint << setprecision(4);
    cout << "\nVotre chance de gagner la lotterie est de " << "une chance sur " << nbCombinaisons << ".\n";
    cout << "Ce qui equivaut a une probabilite de " << (1.0 / nbCombinaisons) << "\n";

    return 0;
}

/* *****************************************************************

 \brief Ce module permet de demander et d'entrer les informations du tirage au clavier

 \param[out] s_nbChiffres : nb total de chiffres dans l'ensemble
 \param[out] s_nbChiffresAChoisir : nb de chiffres a choisir dans cet ensemble
 \post le nb total de chiffres devrait etre entre 1 et 12
 \post le nb a choisir devrait etre entre 1 et le nb total de chiffre

 ***************************************************************** */

void entrerInfosTirage(int& s_nbChiffres, int& s_nbChiffresAChoisir)
{
    cout << endl << "Parmi combien de chiffres (1 à 12) devez-vous choisir? ";
    cin >> s_nbChiffres;
    while (s_nbChiffres > 12 || s_nbChiffres < 1) {
        cout << endl << "Veuillez choisir un chiffre entre 1 à 12 : ";
        cin >> s_nbChiffres;
    }

    cout << "Combien de chiffre devez-vous choisir? ";
    cin >> s_nbChiffresAChoisir;
    while (s_nbChiffresAChoisir <= 0 || s_nbChiffres < s_nbChiffresAChoisir) {
        cout << endl << "Veuillez choisir un chiffre plus grand que 0 et moins haut que le nombre de chiffres choisis : ";
        cin >> s_nbChiffresAChoisir;
    }
}