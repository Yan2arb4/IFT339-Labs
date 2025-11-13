//
//  fonction.h
//  par un AVL
//
//  Jean Goulet 17-03-17.
//  Copyleft 2017 UdeS
//  Modification 2023 : retrait de m_size redondant
//
//  modification 2024 : Marie-Flavie Auclair-Fortier
//  modification 2025 : Marie-Flavie Auclair-Fortier
//

#ifndef map_h
#define map_h

#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <ostream>
#include <stdexcept>

template <typename T_CLE, typename T_VALEUR>
class fonction
{
public:
    class iterateur;
    class iterateurVersConst;
    
    typedef std::pair<const T_CLE, T_VALEUR> T_paire; // facilite la lecture
    
private:
    struct noeud
    {
        T_paire *m_contenu;
        noeud   *m_parent;
        noeud   *m_gauche;
        noeud   *m_droite;
        
        int m_indice;
        
        // constructeurs et destructeur
        noeud(const T_CLE&, const T_VALEUR&, noeud* /*e_parent*/, noeud* /*e_gauche*/, noeud* /*e_droite*/); // noeud parent, gauche et droite en entree, dans l'ordre

        noeud(const T_CLE&, const T_VALEUR&, noeud* /*e_parent*/); // noeud parent en entree

        noeud();

        ~noeud();
  };

    // representation de la fonction
    noeud   *m_fin;
    
    static void avance(noeud*&);
    static void recule(noeud*&);

    //fonctions privees
    noeud*& referenceSur(noeud*);

    void vide(noeud*&);
    void copie(noeud*, noeud*&, noeud*);

    bool insere(const T_CLE&, const T_VALEUR&, noeud*&, iterateur&);
    bool ajouteAGauche(const T_CLE&, const T_VALEUR&, noeud*&, iterateur&);
    bool ajouteADroite(const T_CLE&, const T_VALEUR&, noeud*&, iterateur&);

    bool supprime(const T_CLE&, noeud*&, noeud*&);
    bool retireDeGauche(const T_CLE&, noeud*&, noeud*&);
    bool retireDeDroite(const T_CLE&, noeud*&, noeud*&);
    bool supprime(noeud*&, noeud*&);

    void allongeAGauche(noeud*&);
    void allongeADroite(noeud*&);
    void rotationGaucheDroite(noeud*&);
    void rotationDroiteGauche(noeud*&);

    void affiche(std::ostream&, noeud*, size_t, std::vector<std::string>&, double&, size_t&) const;
    void afficheArcs(std::ostream& out, const std::vector<std::string>&, size_t)const;
public:
    fonction();
    ~fonction();
    fonction(const fonction&);
    fonction& operator=(const fonction&);
    void echange(fonction&);

    size_t taille() const {
        return m_fin->m_indice;
    }
    bool estVide()const {
        return taille() == 0;
    }
    void nettoie();

    iterateur trouve(const T_CLE&) const;
    iterateur borneInf(const T_CLE&)const;    // à implémenter

    T_VALEUR& operator[](const T_CLE&);
    T_VALEUR& at(const T_CLE&);
    
    std::pair<iterateur, bool> ajoute(const T_CLE&, const T_VALEUR&);
    iterateur insere(iterateur, const T_CLE&, const T_VALEUR&);

    size_t retire(const T_CLE&);
    iterateur supprime(iterateur);

    //fonctions d'iteration
    iterateur begin();
    iterateur end();

    iterateurVersConst begin() const;
    iterateurVersConst end() const;

    // fonctions de mise au point
    int hauteur(std::ostream&, noeud* = nullptr) const; // voir utilisation dans l'entete de la fonction
    void affiche(std::ostream&) const;
};

//////////////////////////////////////////////////////////////////////////
// classes d'iterateurs defini dans un fichier a part pour faciliter la lecture.

#include "iterateurs.h"

//////////////////////////////////////////////////////////////////////////
// implementations de la struc. privee noeud

template <typename T_CLE, typename T_VALEUR>
fonction<T_CLE, T_VALEUR>::noeud::noeud(
      const T_CLE& e_cle,
      const T_VALEUR& e_contenu,
      noeud* e_parent
) : noeud(e_cle, e_contenu, e_parent, nullptr, nullptr)
{ }

template <typename T_CLE, typename T_VALEUR>
fonction<T_CLE, T_VALEUR>::noeud::noeud() : m_contenu(nullptr), m_parent(nullptr), m_gauche(nullptr), m_droite(nullptr), m_indice(0)
{ }

template <typename T_CLE, typename T_VALEUR>
fonction<T_CLE, T_VALEUR>::noeud::~noeud()
{
    delete m_contenu;
}
    
template <typename T_CLE, typename T_VALEUR>
fonction<T_CLE, T_VALEUR>::noeud::noeud(
      const T_CLE& e_cle,
      const T_VALEUR& e_val,
      noeud* e_parent,
      noeud* e_gauche,
      noeud* e_droite
      ) : m_parent(e_parent), m_gauche(e_gauche), m_droite(e_droite), m_indice(0)
{
    m_contenu = new T_paire(e_cle, e_val);
}



///////////////////////////////////////////////////////////////////////////
// fonctions d'iteration

template <typename T_CLE, typename T_VALEUR>
typename fonction<T_CLE, T_VALEUR>::iterateur fonction<T_CLE, T_VALEUR>::begin()
{
    noeud* p = m_fin;
    while(p->m_gauche != nullptr)
        p = p->m_gauche;
    return iterateur(p);
}

template <typename T_CLE, typename T_VALEUR>
typename fonction<T_CLE, T_VALEUR>::iterateur fonction<T_CLE, T_VALEUR>::end()
{
    return iterateur(m_fin);
}

template <typename T_CLE, typename T_VALEUR>
typename fonction<T_CLE, T_VALEUR>::iterateurVersConst fonction<T_CLE, T_VALEUR>::begin() const
{
    noeud* p = m_fin;
    while (p->m_gauche != nullptr)
        p = p->m_gauche;
    return iterateurVersConst(p);
}

template <typename T_CLE, typename T_VALEUR>
typename fonction<T_CLE, T_VALEUR>::iterateurVersConst fonction<T_CLE, T_VALEUR>::end() const
{
    return iterateurVersConst(m_fin);
}

///////////////////////////////////////////////////////////////////////////
// fonctions supplementaires de la class map
// ce sont des fonctions statiques, qui n'ont pas de paramètre imlicite

template <typename T_CLE, typename T_VALEUR>
void fonction<T_CLE, T_VALEUR>::avance(noeud*& p)
{
    //AVANCER le pointeur p vers le prochain noeud en inordre
    //cette fonction fait automatiquement exception
    //si on avance au-dela de la fin
    if (p->m_droite != nullptr)
        for (p = p->m_droite;p->m_gauche != nullptr;p = p->m_gauche);
    else
    {
        noeud* pa;
        for (pa = p->m_parent;pa->m_gauche != p;p = pa, pa = p->m_parent);
        p = pa;
    }
}

template <typename T_CLE, typename T_VALEUR>
void fonction<T_CLE, T_VALEUR>::recule(noeud*& p)
{
    //RECULER le pointeur p vers le noeud precedent en inordre
    //p sera nullptr si on recule au-dela du debut
    //cas limite: reculer de la fin
    if (p->m_gauche != nullptr)
        for (p = p->m_gauche;p->m_droite != nullptr;p = p->m_droite);
    else
    {
        noeud* pa;
        for (pa = p->m_parent;pa->m_droite != p;p = pa, pa = p->m_parent);
        p = pa;
    }
}

///////////////////////////////////////////////////////////////////////////
// fonctions privees

template <typename T_CLE, typename T_VALEUR>
typename fonction<T_CLE, T_VALEUR>::noeud*& fonction<T_CLE, T_VALEUR>::referenceSur(noeud*p)
{
    if (p == m_fin)
        return m_fin;
    else if (p->m_parent->m_gauche == p)
        return p->m_parent->m_gauche;
    else
        return p->m_parent->m_droite;
}


template <typename T_CLE, typename T_VALEUR>
void fonction<T_CLE, T_VALEUR>::vide(noeud*& p)
{
    if (p == nullptr)
        return;
    vide(p->m_gauche);
    vide(p->m_droite);
    delete p;
    p = nullptr;
}

template <typename T_CLE, typename T_VALEUR>
void fonction<T_CLE, T_VALEUR>::copie(noeud* source, noeud*& dest, noeud* parent)
{
    if (source == nullptr)
        return;
    
    dest = new noeud(*source);
    
    dest->m_parent = parent;
    dest->m_indice = source->m_indice;
    
    copie(source->m_droite, dest->m_droite, dest);
    copie(source->m_gauche, dest->m_gauche, dest);
}

///////////////////////////////////////////////////////////////////////////
// fonctions privees d'insertion

template <typename T_CLE, typename T_VALEUR>
bool fonction<T_CLE, T_VALEUR>::
insere(const T_CLE& c, const T_VALEUR& val, noeud*& p, iterateur& r)
{
    if (c < p->m_contenu->first)
        return ajouteAGauche(c, val, p, r);
    else if (p->m_contenu->first < c)
        return ajouteADroite(c, val, p, r);
    else
        r = iterateur(p);
    return false;
}

template <typename T_CLE, typename T_VALEUR>
bool fonction<T_CLE, T_VALEUR>::ajouteAGauche(const T_CLE& c, const T_VALEUR& val, noeud*& p, iterateur& r)
{
    if (p->m_gauche == nullptr)
    {
        //nouvelle feuille
        p->m_gauche = new noeud(c, val, p);
        r = iterateur(p->m_gauche);
        ++(m_fin->m_indice);
        return(++(p->m_indice) == 1);
    }
    else if (insere(c, val, p->m_gauche, r))
    { //ajout general a gauche
        allongeAGauche(p);
        return (p->m_indice != 0);
    }
    else
        return false;
}

template <typename T_CLE, typename T_VALEUR>
bool fonction<T_CLE, T_VALEUR>::ajouteADroite(const T_CLE& c, const T_VALEUR& val, noeud*& p, iterateur& r)
{
    if (p->m_droite == nullptr)
    {         
        //nouvelle feuille
        p->m_droite = new noeud(c, val, p);
        r = iterateur(p->m_droite);
        ++(m_fin->m_indice);
        return(--(p->m_indice) == -1);
    }
    else if (insere(c, val, p->m_droite, r))
    { //ajout general a droite
        allongeADroite(p);
        return (p->m_indice != 0);
    }
    else
        return false;
}

///////////////////////////////////////////////////////////////////////////
// fonctions privees d'elimination

template <typename T_CLE, typename T_VALEUR>
bool fonction<T_CLE, T_VALEUR>::supprime(const T_CLE& c, noeud*& p, noeud*& aRemplacer)
{
    if (c < p->m_contenu->first)
        return retireDeGauche(c, p, aRemplacer);
    else if (p->m_contenu->first < c)
        return retireDeDroite(c, p, aRemplacer);
    else
    {
        aRemplacer = p;
        return retireDeGauche(c, p, aRemplacer);
    }
}

template <typename T_CLE, typename T_VALEUR>
bool fonction<T_CLE, T_VALEUR>::retireDeGauche(const T_CLE& c, noeud*& p, noeud*& aRemplacer)
{
    if (p->m_gauche == nullptr)
        return supprime(p, aRemplacer);
    else if (supprime(c, p->m_gauche, aRemplacer))
    {
        allongeADroite(p);
        return p->m_indice == 0;
    }
    else
        return false;
}

template <typename T_CLE, typename T_VALEUR>
bool fonction<T_CLE, T_VALEUR>::retireDeDroite(const T_CLE& c, noeud*& p, noeud*& aRemplacer)
{
    if (p->m_droite == nullptr)
        return supprime(p, aRemplacer);
    
    else if (supprime(c, p->m_droite, aRemplacer))
    {
        allongeAGauche(p);
        return p->m_indice == 0;
    }
    else
        return false;
}

// désalloue le contenu de aRemplacer, s'il y a lieu (retour vrai) et le remplace par le contenu de son enfant de gauche ou par celui de son enfant de droite si l'enfant de gauche n'existe pas
template <typename T_CLE, typename T_VALEUR>
bool fonction<T_CLE, T_VALEUR>::supprime(noeud*& p, noeud*& aRemplacer)
{
    if (aRemplacer != nullptr)
    {
        delete aRemplacer->m_contenu;
        aRemplacer->m_contenu = p->m_contenu;
        p->m_contenu = nullptr;
        aRemplacer = p;
        
        if (p->m_gauche == nullptr)
            p = p->m_droite;
        else 
            p = p->m_gauche;

        if (p != nullptr)
            p->m_parent = aRemplacer->m_parent;

        --(m_fin->m_indice);

        return true;
    }
    else
        return false;
}

///////////////////////////////////////////////////////////////////////////
// fonctions publiques

template <typename T_CLE, typename T_VALEUR>
fonction<T_CLE, T_VALEUR>::fonction()
    : m_fin(new noeud)
{ }

template <typename T_CLE, typename T_VALEUR>
fonction<T_CLE, T_VALEUR>::~fonction()
{
    nettoie();
    delete m_fin;
}

template <typename T_CLE, typename T_VALEUR>
fonction<T_CLE, T_VALEUR>::fonction(const fonction& source) :fonction()
{
    copie(source.m_fin->m_gauche, m_fin->m_gauche, nullptr);
    m_fin->m_indice = source.taille();
}

template <typename T_CLE, typename T_VALEUR>
fonction<T_CLE, T_VALEUR>& fonction<T_CLE, T_VALEUR>::operator=(const fonction& source)
{
    if (this != &source)
    {
        fonction<T_CLE, T_VALEUR> copie(source);
        this->echange(copie);
    }
    return *this;
}

template <typename T_CLE, typename T_VALEUR>
void fonction<T_CLE, T_VALEUR>::echange(fonction& source)
{
    std::swap(m_fin, source.m_fin);
}

template <typename T_CLE, typename T_VALEUR>
void fonction<T_CLE, T_VALEUR>::nettoie()
{
    vide(m_fin->m_gauche);
    m_fin->m_indice = 0;
}

template <typename T_CLE, typename T_VALEUR>
T_VALEUR& fonction<T_CLE, T_VALEUR>::at(const T_CLE& c)
{
    auto p = borneInf(c);
    if (p == end() || c < p->first)
        throw std::out_of_range("valeur absente du map");
    return p->second;
}


template <typename T_CLE, typename T_VALEUR>
typename fonction<T_CLE, T_VALEUR>::iterateur fonction<T_CLE, T_VALEUR>::trouve(const T_CLE& c)const
{
    iterateur retour = borneInf(c);
    if (retour == end() || c < retour->first)
        return end();
    return retour;
}

template <typename T_CLE, typename T_VALEUR>
T_VALEUR& fonction<T_CLE, T_VALEUR>::operator[](const T_CLE& c)
{
    auto r = this->ajoute(c);
    auto i = r.first;
    T_paire* pa = i.m_courant->m_contenu;
    return pa->second;
}


// retourne une paire contenant un itérateur sur l'élément ajouté et vrai si l'ajout est fait

template <typename T_CLE, typename T_VALEUR>
std::pair<typename fonction<T_CLE, T_VALEUR>::iterateur, bool>
fonction<T_CLE, T_VALEUR>::ajoute(const T_CLE& c, const T_VALEUR& val)
{
    iterateur retour;
    if (taille() == 0)
    {  //arbre vide, l'élément est inséré comme précédent de m_apres
        m_fin->m_gauche = new noeud(c, val, m_fin);
        m_fin->m_indice = 1;
        return std::make_pair(begin(), true);
    }
    bool valeur = insere(c, val, m_fin->m_gauche, retour);
    return std::make_pair(retour, valeur);
}

template <typename T_CLE, typename T_VALEUR>
size_t fonction<T_CLE, T_VALEUR>::retire(const T_CLE& c)
{
    size_t tailleOrig = taille();
    
    if (tailleOrig != 0)
    {
        noeud* aRemplacer = nullptr;
        supprime(c, m_fin->m_gauche, aRemplacer);
    }
    return tailleOrig - taille();
}

///////////////////////////////////////////////////////////////////////////
// gestion de l'equilibre de l'arbre

//incrementer l'indice et verifier
//si on doit transferer des elements et le faire
template <typename T_CLE, typename T_VALEUR>
void fonction<T_CLE, T_VALEUR>::allongeAGauche(noeud*& p)
{
    // si le neoud *p est trop haut a gauche
    // faire les rotations necessaires
    
    // code de test
    // std::cout<<"vers la droite de "<<p->m_contenu->first<<" ("<<p->m_indice<<")"<<std::endl;
    // fin code de test
    
    ++(p->m_indice);
    if (p->m_indice != 2)
        return;
    
    if (p->m_gauche->m_indice == -1)
        rotationDroiteGauche(p->m_gauche);
    
    rotationGaucheDroite(p);

}

//decrementer l'indice et verifier
//si on doit transferer des elements et le faire
template <typename T_CLE, typename T_VALEUR>
void fonction<T_CLE, T_VALEUR>::allongeADroite(noeud*& p)
{
    //si le neoud *p est trop haut a droite
    //faire les rotations necessaires
    
    // code de test
    //std::cout<<"vers la gauche de "<<p->m_contenu->first<<" ("<<p->m_indice<<")"<<std::endl;
    // fin code de test
    
    --(p->m_indice);
    if (p->m_indice != -2)
        return;
    if (p->m_droite->m_indice == 1)
        rotationGaucheDroite(p->m_droite);
    rotationDroiteGauche(p);
}



///////////////////////////////////////////////////////////////////////////
// fonctions de mise au point
// utilisation
//      obj.hauteur(std::cerr) pour avoir la hauteur de l'AVL complet
//      obj.hauteur(std::cerr, p) pour avoir la hauteur du sous-AVL qui commence au ptr de noeud p

template <typename T_CLE, typename T_VALEUR>
int fonction<T_CLE, T_VALEUR>::hauteur(std::ostream& out, noeud* p)const
{
    if (p == nullptr)
    { //pour l'appel initial sans parametres
        if (m_fin->m_gauche == nullptr)  // fct vide
            return 0;
        else
            p = m_fin->m_gauche;
    }
    int hg = 0, hd = 0;
    
    if (p->m_gauche != nullptr)
        hg = hauteur(out, p->m_gauche);
    
    if (hg == -1)
        return -1;
    
    if (p->m_droite != nullptr)
        hd = hauteur(out, p->m_droite);
    
    if (hd == -1)
        return -1;
    
    int ind = hg - hd;
    
    if (ind > 1 || ind < -1) // arbre débalancé, pas supposé arriver
    {
        out << "le noeud " << p->m_contenu->first;
        out << " n'est pas en equilibre: gauche=" << hg;
        out << ", droite=" << hd << std::endl;
        return -1;
    }
    
    else
        return 1 + std::max(hg, hd);
}


template <typename T_CLE, typename T_VALEUR>
void fonction<T_CLE, T_VALEUR>::affiche(std::ostream& out) const
{
    double total = 0.;
    size_t max = 0;
    out << "-------------------------------\n";
    std::vector<std::string> barres;
    barres.push_back("    ");
    affiche(out, m_fin->m_gauche, 1, barres, total, max);
    total = total / taille();
    out << taille() << " element";
    if (taille() > 1)
        out << "s";
    out << "\n";
    out << "log(" << taille() << "): " << log2(double(taille())) << "\n";
    out << "hauteur moyenne: " << total << "\n";
    out << "hauteur maximale: " << max << "\n";
    out << "-------------------------------" << std::endl;
}


template <typename T_CLE, typename T_VALEUR>
void fonction<T_CLE, T_VALEUR>::
affiche(
         std::ostream& out,
         typename fonction<T_CLE, T_VALEUR>::noeud* p,
         size_t niveau,
         std::vector<std::string>& barres,
         double& total,
         size_t& max
         ) const
{
    if (p == 0)
        return;
    
    total += niveau;
    if (niveau > max)
        max = niveau;
    if (niveau >= barres.size())
        barres.push_back("    ");

    affiche(out, p->m_droite, niveau + 1, barres, total, max);

    //si on est un enfant de gauche arreter les barres a ce niveau
    if (p->m_parent != 0 && p->m_parent->m_gauche == p)
        barres[niveau - 1] = "    ";

    //cout<<niveau;
    afficheArcs(out, barres, niveau);
    out << "---> [";
    out << p->m_contenu->first << "," << p->m_contenu->second << "] (" << p->m_indice;
    //out<<", "<<p;
    //out<<", par="<<p->m_parent;
    //out<<", gau="<<p->m_gauche;;
    //out<<", dro="<<p->m_droite;
    out << ")\n";

    //si on est un enfant de droite barre a mon niveau
    if (p->m_parent->m_droite == p)
        barres[niveau - 1] = "   |";

    //si on a un enfant a gauche mettre des barres apres
    if (p->m_gauche != 0)
        barres[niveau] = "   |";
    else
        barres[niveau] = "    ";

    //cout<<niveau;
    afficheArcs(out, barres, niveau + 1);
    out << "\n";

    affiche(out, p->m_gauche, niveau + 1, barres, total, max);
}

template <typename T_CLE, typename T_VALEUR>
void fonction<T_CLE, T_VALEUR>::
afficheArcs(std::ostream& out, const std::vector<std::string>& barres, size_t n) const
{
    for (size_t i = 0; i < n; ++i)
        out << barres[i];
}

#include "fctIpl.h"

#endif /* map_h */
