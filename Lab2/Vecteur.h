//
//  Nom du fichier : vector.h
//  Auteur : Jean Goulet
//  Date :   Septembre 2016
//
//  Modifié par : Vincent Ducharme, Septembre 2022
//
//

#ifndef _vector_h
#define _vector_h

#include <ostream>
#include <stdexcept> // Pour les exceptions standards dans vecteurIpl.h
#include <utility> // Pour std::swap

template <typename T>
class vecteur
{
private:
    T *m_debut, *m_finDim, *m_finCap;
    
public:
    vecteur();
    vecteur(size_t);
    ~vecteur();
    vecteur(const vecteur&);
    vecteur& operator=(const vecteur&);
    
    // classes d'itérateurs
    class iterateur;
    class const_iterateur;
    
    void resize(size_t);
    void reserve(size_t);
    size_t size()const;
    bool empty()const;
    void clear();
    void swap(vecteur&);
    
    T& back();
    const T& back()const;
    T& front();
    const T& front()const;
    void push_back(const T&);
    void pop_back();
    T& operator[](size_t);
    const T& operator[](size_t)const;
    T& at(size_t);
    const T& at(size_t)const;
    
    //fonctions d'iteration du vector
    iterateur begin();
    iterateur end();
	const_iterateur begin() const;
    const_iterateur end() const;

    //code jetable
    void afficher(std::ostream&)const;
};

template <typename T>
std::ostream& operator<<(std::ostream&, const vecteur<T>&);

////////////////////////////////////////////////////////////////
//classes d'iteration

template<typename T>
class vecteur<T>::iterateur
{
friend class vecteur<T>;

private:
    T *m_pointeur;
    iterateur(T *p=nullptr):m_pointeur(p){}
public:    
    T& operator*();
    iterateur operator++(){return iterateur(++m_pointeur);}    //++i
    iterateur operator++(int){return iterateur(m_pointeur++);} //i++
    iterateur operator--(){return iterateur(--m_pointeur);}    //--i
    iterateur operator--(int){return iterateur(m_pointeur--);} //i--
    bool operator==(const iterateur& droite) const {return m_pointeur==droite.m_pointeur;}
    bool operator!=(const iterateur& droite) const {return m_pointeur!=droite.m_pointeur;}
};

template<typename T>
class vecteur<T>::const_iterateur
{
friend class vecteur<T>;

private:
    T *m_pointeur;
    const_iterateur(T *ptr=nullptr): m_pointeur(ptr) {}
public:
    const T& operator*() const;
    const_iterateur operator++(){return const_iterateur(++m_pointeur);}    //++i
    const_iterateur operator++(int){return const_iterateur(m_pointeur++);} //i++
    const_iterateur operator--(){return const_iterateur(--m_pointeur);}    //--i
    const_iterateur operator--(int){return const_iterateur(m_pointeur--);} //i--
    bool operator==(const const_iterateur& droite) const {return m_pointeur==droite.m_pointeur;}
    bool operator!=(const const_iterateur& droite) const {return m_pointeur!=droite.m_pointeur;}
};

////////////////////////////////////////////////////////////////
// constructeurs, affectateur et destructeur

template <typename T>
vecteur<T>::vecteur() : vecteur(0)
{}

template <typename T>
vecteur<T>::vecteur(size_t dim)
{
    if(dim>0)
	{
        m_debut=new T[dim];
	}
    else 
	{
        m_debut=nullptr;
	}
    
    m_finDim = m_finCap = m_debut + dim;
}

template <typename T>
vecteur<T>::vecteur(const vecteur& source) : vecteur(source.size())
{
    for(size_t i=0;i<source.size();++i)
	{
        m_debut[i]=source[i];
	}
}

template <typename T>
vecteur<T>& vecteur<T>::operator=(const vecteur& source)
{
	vecteur copie(source);
	swap(copie);
    return *this;
}

template <typename T>
vecteur<T>::~vecteur()
{
    clear();
}

////////////////////////////////////////////////////////////////
// selecteurs et mutateurs

template <typename T>
size_t vecteur<T>::size()const
{
    return m_finDim - m_debut;
}

template <typename T>
bool vecteur<T>::empty()const
{
    return m_debut==m_finDim;
}

template <typename T>
void vecteur<T>::swap(vecteur<T>& v)
{
    std::swap(m_debut,v.m_debut);
    std::swap(m_finDim,v.m_finDim);
    std::swap(m_finCap,v.m_finCap);
}

template <typename T>
T& vecteur<T>::back()
{
    return *(m_finDim-1);
}

template <typename T>
const T& vecteur<T>::back()const
{
    return *(m_finDim-1);
}

template <typename T>
T& vecteur<T>::front()
{
    return *m_debut;
}

template <typename T>
const T& vecteur<T>::front()const
{
    return *m_debut;
}



////////////////////////////////////////////////////////////////
// code de test

// Attention! cette fonction d'affichage ne fonctionne qu'avec
// des elements qui possedent l'operateur << des ostreams.

template <typename T>
void vecteur<T>::afficher(std::ostream& out) const
{
    size_t i;
    size_t dim (m_finDim-m_debut);
    size_t vide {dim};

    out<<"\n"<<"Etat du vecteur a l'adresse: "<<this<<"\n";

	out<<" m_debut:   "<<m_debut<<"\n";
	out<<" m_finDim: "<<m_finDim<<" (+"<<dim<<")\n";
	out<<" m_finCap: "<<m_finCap<<" (+"<<(m_finCap-m_debut)<<")\n";
    
    
    if(vide>11)
        vide=dim-11;
    else 
        vide=0;
    size_t cap=m_finCap-m_debut;
	for(i=0;i<dim;++i)
		if(i<10 || i>vide)
            out<<" "<<i<<": "<<m_debut[i]<<"\n";
        else
        {
            out<<" ..."<<"\n";
			i=vide;
        }
    
    if(cap>dim)
    {
        out<<" "<<i;
        if(cap-dim>1)
            out<<" a "<<cap-1;
        out<<": (--en reserve--)\n";
    }
}

// surcharge de l'opérateur<<

template <typename T>
std::ostream& operator<<(std::ostream& out,const vecteur<T>& v)
{
    char delim='[';
    size_t s=v.size();
    if (s==0)
        out<<delim;
    if (s>40)
        s=40;
    
    for (auto it = v.begin(); it != v.end(); it++)
    {
        out<<delim<<*it;
        delim=',';
    }
       
    out<<"]";
    return out;
}

///////////////////////////////////////////////////
//inclusion ici du fichier du code à ajouter
#include "VecteurIpl.h"

#endif
