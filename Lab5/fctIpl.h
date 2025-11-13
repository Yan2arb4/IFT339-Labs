//
//  fctIpl.h
//
//  Auteur : Jean Goulet
//  Copyleft  2017 UdeS
//
//  Modifie par : Vincent Ducharme, Hiver 2018
//                Marie-Flavie Auclair-Fortier, Autommne 2024
//
//  Devoir fait par
//     Coéquipier 1 :
//     Coéquipier 2 :

#ifndef fctIpl_h
#define fctIpl_h

#include <algorithm>

///////////////////////////////////////////////////////////////////////////
// lower_bound O(log n)

template <typename Tclef, typename Tvaleur>
typename fonction<Tclef, Tvaleur>::iterateur fonction<Tclef, Tvaleur>::borneInf(const Tclef& c) const
{
    // code a remplacer
    return iterateur(nullptr);
}

///////////////////////////////////////////////////////////////////////////
//supprime a partir d'une position

template <typename Tclef, typename Tvaleur>
typename fonction<Tclef, Tvaleur>::iterateur fonction<Tclef, Tvaleur>::supprime(iterateur i)
{
    // code a remplacer

    assert(i != end());
    retire(i++->first);
    return i;
}

///////////////////////////////////////////////////////////////////////////
//insert avec indice

template <typename Tclef, typename Tvaleur>
typename fonction<Tclef, Tvaleur>::iterateur fonction<Tclef, Tvaleur>::
insere(iterateur j, const Tclef& c, const Tvaleur& val)
{
    // code a remplacer

    return ajoute(c, val).first;
}

///////////////////////////////////////////////////////////////////////////
// gestion de l'equilibre de l'arbre

//effectuer une rotation simple de la gauche vers la droite
template <typename Tclef, typename Tvaleur>
void fonction<Tclef, Tvaleur>::rotationGaucheDroite(noeud*& p)
{
    // code a remplacer

}

//effectuer une rotation simple de la droite vers la gauche
template <typename Tclef, typename Tvaleur>
void fonction<Tclef, Tvaleur>::rotationDroiteGauche(noeud*& p)
{
    // code a remplacer

}


#endif /* fctIpl_h */
