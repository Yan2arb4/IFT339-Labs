/*
*  TAD Ensemble par une SD liste à enjambement
*
*  Auteur : Jean Goulet 2016
*  Cette version integre la rustine
*  ensemble<TYPEContenu>::to_string pour remplacer std::to_string
*
*  Modifié par : Vincent Ducharme, Automne 2022
*  Modifié par : MF Auclair-Fortier, Automne 2024
*/

#include <ostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <random>
#include <chrono>

#ifndef ensembleEnj_h
#define ensembleEnj_h

// affichage
// n'est fonctionnel que pour les types primitifs
// et les string (max 4 caracteres par element)
// le code est à la fin du fichier

template <typename TYPEContenu> std::string vers_string(const TYPEContenu& n);

template <typename TYPEContenu>
class ensemble
{
public:
    class iterateur;

    ensemble();
    ~ensemble();
    ensemble(const ensemble&);
    ensemble& operator=(const ensemble&);
    void echange(ensemble&);

    size_t taille()const;
    bool estVide()const;

    size_t nbInstances(const TYPEContenu&) const;
    iterateur trouve(const TYPEContenu&) const;
    iterateur borneInf(const TYPEContenu&) const;
    iterateur borneSup(const TYPEContenu&) const;

    std::pair<iterateur, bool> ajoute(const TYPEContenu&);
    iterateur insere(iterateur, const TYPEContenu&);
    size_t retire(const TYPEContenu&);  // retourne 0 si non trouvé et 1 si trouvé
    iterateur enleve(iterateur);
    void nettoie();

    iterateur begin()const;
    iterateur end()const;
    
private:
    struct cellule
    {
        TYPEContenu* m_contenu = nullptr;
        std::vector<cellule*> m_prec, m_suiv;
        cellule() = default;
        cellule(TYPEContenu* v) :m_contenu(v) {};
        ~cellule();
    };
    size_t m_taille;
    cellule* m_avant;

    static size_t nbCouchesAleatoires();
    
    cellule* insere(cellule*, const TYPEContenu&);
    
public:
    void friend afficher(std::ostream& out, const ensemble<TYPEContenu>& s)
    {
        out << "------------------------------------------\n";
        if (s.m_avant == nullptr)
        {
            out << "l'ensemble a ete detruit\n";
            return;
        }
        size_t nbniv = s.m_avant->m_suiv.size();
        std::string une_clef, lignes, clefs;
        TYPEContenu elem;

        lignes = vers_string(s.taille()) + " elements";
        for (size_t nb = nbniv; nb > 0;)
        {
            std::string clefs = " ";
            nb--;
            
            //afficher toute la couche nb
            out << lignes << "\n";
            lignes = "|";

            for (cellule* p=s.m_avant->m_suiv[0]; p->m_suiv[0] != nullptr; p = p->m_suiv[0])
            {
                if (p->m_suiv.size() > nb)
                {
                    elem = *(p->m_contenu);
                    une_clef = "-----" + vers_string(elem);
                    clefs += une_clef.substr(une_clef.size() - 6, 6);
                    lignes += "     |";
                }
                else
                {
                    clefs += "------";
                    lignes += "      ";
                }
            }

            clefs += "--";
            out << clefs << "\n";
            lignes += "  |";
        }
        out << "\n\n";
    };

};

/////////////////////////////////////////////////
// destructeur de cellule

template <typename TYPEContenu>
ensemble<TYPEContenu>::cellule::~cellule()
{
    delete m_contenu;
    
    for (auto& x : m_prec)
        x = nullptr;
    
    for (auto& x : m_suiv)
        x = nullptr;
}

/////////////////////////////////////////////////
// iterator

template <typename TYPEContenu>
class ensemble<TYPEContenu>::iterateur
{
private:
    cellule* m_pointeur;
    friend class ensemble<TYPEContenu>;
    iterateur(cellule* p = nullptr) :m_pointeur(p) {}
public:
    
    const TYPEContenu& operator*()const { return *m_pointeur->m_contenu; }
    iterateur operator++();     //++i
    iterateur operator++(int);  //i++
    iterateur operator--();     //--i
    iterateur operator--(int);  //i--
    bool operator==(const iterateur&i2)const { return m_pointeur == i2.m_pointeur; }
    bool operator!=(const iterateur&i2)const { return !(*this == i2); }
};


template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::iterateur::operator++()
{   // préincrément
    m_pointeur = m_pointeur->m_suiv[0];
    return *this;
}

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::iterateur::operator++(int)
{
    // postincrément
    iterateur r(m_pointeur);
    operator++();
    return r;
}

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::iterateur::operator--()
{
    //--i
    m_pointeur = m_pointeur->m_prec[0];
    return *this;
}

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::iterateur::operator--(int)
{ 
    //i--
    iterateur r(m_pointeur);
    operator--();
    return r;
}

/////////////////////////////////////////////////
// ensemble
// fonctions privees

template <typename TYPEContenu>
size_t ensemble<TYPEContenu>::nbCouchesAleatoires()
{
    //tirer au hasard le nombre de couches
    //prob 1/2 d'avoir 1
    //prob 1/4 d'avoir 2
    //prob 1/8 d'avoir 3 etc.
    //
    // Si vous voulez générer la même séquence pour vos tests, vous pouvez modifier la valeur de seed pour qu'elle soit égale à 0
    // static auto seed = 0;
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::minstd_rand0 generator(static_cast<unsigned int>(seed));
    size_t i = 1;
    auto g = generator();
    for (; g % 2 != 0; ++i)
        g /= 2;
    return i;
}


/////////////////////////////////////////////////
// ensemble
// fonctions publiques

template <typename TYPEContenu>
ensemble<TYPEContenu>::ensemble()
{
    m_taille = 0;
    m_avant = new cellule(nullptr);
    cellule* apres = new cellule(nullptr);
    m_avant->m_prec.push_back(apres);
    m_avant->m_suiv.push_back(apres);
    apres->m_prec.push_back(m_avant);
    apres->m_suiv.push_back(nullptr);
}

template <typename TYPEContenu>
ensemble<TYPEContenu>& ensemble<TYPEContenu>::operator=(const ensemble<TYPEContenu>& source)
{
    if (this != &source)
    {
        ensemble copie(source);
        echange(copie);
    }
    return *this;
}

template <typename TYPEContenu>
void ensemble<TYPEContenu>::echange(ensemble<TYPEContenu>& src)
{
    std::swap(m_taille, src.m_taille);
    std::swap(m_avant, src.m_avant);
}

template <typename TYPEContenu>
size_t ensemble<TYPEContenu>::taille()const
{
    return m_taille;
}

template <typename TYPEContenu>
bool ensemble<TYPEContenu>::estVide()const
{
    return taille() == 0;
}

template <typename TYPEContenu>
size_t ensemble<TYPEContenu>::nbInstances(const TYPEContenu& t)const
{
    auto it = trouve(t);
    if (it == end())
        return 0;
    else
        return 1;
}

/////////////////////////////////////////////////
// les trois fonctions d'insertion
// deux fonctions publiques et une fonction privée


// retourne une paire : iterateur vers le contenu et un booléen a vrai si le contenu n'existait pas et a ete ajoute et faux s'il existait.
template <typename TYPEContenu>
std::pair<typename ensemble<TYPEContenu>::iterateur, bool> ensemble<TYPEContenu>::ajoute(const TYPEContenu& val)
{
    //insertion par valeur seulement
    iterateur it = borneInf(val);
    TYPEContenu* p = it.m_pointeur->m_contenu;
    
    if (p == nullptr || val<*p)
        return std::make_pair(iterateur(insere(it.m_pointeur, val)), true);
    else
        return std::make_pair(it, false);
}

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::insere(iterateur it, const TYPEContenu& val)
{
    //insertion avec indice a verifier
    //verifier que l'on est a la bonne place
    cellule* apres = it.m_pointeur;
    cellule* avant = apres->m_prec[0];
    
    TYPEContenu* ava = avant->m_contenu;
    
    if (apres->m_contenu != nullptr // on n'est pas à la fin
        && (*apres->m_contenu<val))    // la valeur à insérer n'est pas plus petite ou égale, donc l'itérateur ne pointe pas au bon endroit, on appelle la fonction qui détermine le bon endroit
        return ajoute(val).first;
    
    else if (ava == nullptr)       // début de la liste (donc apres->m_contenu != nullptr est vrai) : et la valeur est plus petite que le contenu pointé (car *apres->m_contenu<val est faux) , donc on insere au devant après qui est le premier élément de la liste
        return iterateur(insere(apres, val));
    
    else if (*ava<val)             // on n'est pas au début (ava == nullptr est faux), la valeur est plus petite que la valeur pointée par l'itérateur mais plus grande que le précédent (*ava<val est vrai), on insère là, inclue la fin
        return iterateur(insere(apres, val));
    
    else
        return ajoute(val).first;   // on est à la fin (apres->m_contenu != nullptr est faux) et la valeur est plus grande que le précédent (*ava<val est faux), on appelle la fonction qui détermine le bon endroit
}

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::cellule* ensemble<TYPEContenu>::insere(typename ensemble<TYPEContenu>::cellule* ap, const TYPEContenu& val)
{
    size_t nbniv_orig = m_avant->m_suiv.size();
    cellule* fin = m_avant->m_prec[0];
    cellule* av = ap->m_prec[0];
    cellule* nouv = new cellule(new TYPEContenu(val));
    size_t nbniv = nbCouchesAleatoires();

    for (size_t i = 0; i<nbniv;)
    {
        nouv->m_prec.push_back(av);
        nouv->m_suiv.push_back(ap);
        av->m_suiv[i] = nouv;
        ap->m_prec[i] = nouv;
        ++i;
        if (i<nbniv){
            if (i == nbniv_orig)
            {  //ajouter une couche vide
                m_avant->m_suiv.push_back(ap = fin);
                fin->m_prec.push_back(av = m_avant);
                ++nbniv_orig;
            }
            else
            {
                while (av->m_suiv.size() == i)
                    av = av->m_prec.back();
                ap = av->m_suiv[i];
            }
        }
    }
    ++m_taille;
    return nouv;
}

/////////////////////////////////////////////////////////////////
// clear
// vide la liste en temps O(n)

template <typename TYPEContenu>
void ensemble<TYPEContenu>::nettoie()
{
    cellule* p = m_avant->m_suiv[0], *prochain;
    while (taille() != 0)
    {
        --m_taille;
        prochain = p->m_suiv[0];
        delete p;
        p = prochain;
    }

    m_avant->m_suiv.clear();
    m_avant->m_suiv.push_back(m_avant->m_prec[0]);
    m_avant->m_prec[0]->m_prec.clear();
    m_avant->m_prec[0]->m_prec.push_back(m_avant);
}

/////////////////////////////////////////////////
// iteration

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::begin()const
{
    return iterateur(m_avant->m_suiv[0]);
}

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::end()const
{
    return iterateur(m_avant->m_prec[0]);
}

template <typename T>
std::string vers_string(const T& n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
}

////////////////////////////////////////////////////////////

#include "ensembleIpl.h"

#endif
