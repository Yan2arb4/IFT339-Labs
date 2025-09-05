//
//  modules.h
//  Labo6 - modules
//
//  Created by Marie-Flavie Auclair-Fortier on 2020-10-13.
//

#ifndef modules_h
#define modules_h

#include <stdio.h>

/* *****************************************************************

 \brief Ce module permet de calculer le nombre de combinaisons
    differentes de k éléments choisi dans un ensemble de n.

 \param[in] nb total de chiffres dans l'ensemble (n)
 \param[in] nb de chiffres a choisir dans cet ensemble (k)
 \return le nombre de combinaisons possibles
 \pre le nb a choisir devrait etre entre 1 et le nb total de chiffre
 \post la formule est     n!
                       --------
                       k!(n-k)!
 \remark le denominateur ne devrait pas etre calcule avant de faire
    la division pour éviter des debordements.

 ***************************************************************** */

long int calculeNbCombinaisons(int, int);
long int factorielle(int);

/* *****************************************************************

 \brief Ce module permet de calculer la factorielle d'un nombre

 \param[in] le nombre (n)
 \return la factorielle de n
 \pre n >= 0
 \post la formule est  n! =   n * (n-1) * (n-2) ... * 1
 \post 0! = 1

 ***************************************************************** */


#endif /* modules_h */
