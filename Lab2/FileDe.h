//
//  Nom du fichier : FileDe.h
//  Description : file à double extrémité circulaire
//
//  Auteur : Jean Goulet
//  Date :   2016-12-27
//  Copyleft 2016 UdeS
//
//  Modifié par Vincent Ducharme, Septembre 2022
//  Modifié par MFAF, septembre 2024

#ifndef _fileDE_h
#define _fileDE_h

#include <ostream>
#include <utility>
#include <stdexcept>

template <typename T>
class fileDE
{
private:
    T**  m_debut;
    size_t m_cap, m_taille, m_zero;
    
    void reserve(size_t); //augmente la capacite
public:
    fileDE(size_t=0);
    ~fileDE();
    fileDE(const fileDE&);
    fileDE& operator=(const fileDE&);
    void swap(fileDE&);
    
    //selecteurs
    size_t size() const;
    bool empty() const;
    
    //gestion de la memoire
    void resize(size_t); //change la dimension
    void clear();        //vide la memoire
    
    //acces aux elements individuels
    T& operator[](size_t);
    T& at(size_t);
    const T& operator[](size_t) const;
    const T& at(size_t)const;
    
    void push_back(const T&);
    void pop_back();
    void push_front(const T&);
    void pop_front();
    
    //code de mise au point
    void afficher(std::ostream&) const;
};

template <typename T>
fileDE<T>::fileDE(size_t dim) : m_taille(dim), m_cap(dim), m_zero(0)
{
    if (dim>0)
        m_debut=new T*[m_cap];
    else 
        m_debut=nullptr;
    
    for(size_t i=0;i<dim;++i)
        m_debut[i]=new T();
}

template <typename T>
fileDE<T>::~fileDE()
{
    clear();
}

template <typename T>
fileDE<T>& fileDE<T>::operator=(const fileDE& source)
{
	fileDE copie(source);
    
    swap(copie);
    
    return *this;
}

template <typename T>
void fileDE<T>::swap(fileDE& source)
{
    std::swap(m_debut,source.m_debut);
    std::swap(m_cap,source.m_cap);
    std::swap(m_taille,source.m_taille);
    std::swap(m_zero,source.m_zero);
}

template <typename T>
size_t fileDE<T>::size() const
{
    return m_taille;
}

template <typename T>
bool fileDE<T>::empty() const
{
    return m_taille == 0;
}

template <typename T>
void fileDE<T>::clear()
{
    for(size_t i=0;i<m_taille;++i)
        delete m_debut[(i+m_zero)%m_cap];
    
    delete[] m_debut;
    
    m_debut=nullptr;
    m_zero=0;
    m_cap=m_taille=0;
}


/////////////////////////////////////////////////////////////////
//code de mise au point

template <typename T>
void fileDE<T>::afficher(std::ostream& out) const
{
    out<<"\n"<<"Etat de la fileDE a l'adresse: "<<this<<"\n";
    out<<"m_debut:"<<m_debut<<"\n";
    out<<"m_cap:  "<<m_cap<<"\n";
    out<<"m_size: "<<m_taille<<"\n";
    out<<"m_zero: "<<m_zero<<"\n";
    out<<"---------------------------\n";
    
    size_t i, j;
    
    for (i=0; i<m_cap;++i)
    {
        j = (m_cap+i-m_zero)%m_cap;
        if (j>=m_taille)
            out<<i<<"(-)"<<"\n";
        else 
            out<<i<<"("<<j<<"): "<<*m_debut[i]<<"\n";
    }
    if (m_cap>0)
        out<<"---------------------------\n";
}

template <typename T>
std::ostream& operator<<(std::ostream& out,const fileDE<T>& d)
{
    char delim='[';
    
    size_t s=d.size();
    
    if(s==0)
        out<<delim;
    if (s>40)
        s=40;
    
    for(size_t i=0;i<s;++i)
    {
        out<<delim<<d[i];
        delim=',';
    }
    
    out<<"]";
    
    return out;
}

//inclusion ici du fichier du code à ajouter
#include "FileDeIpl.h"


#endif // fileDE_h
