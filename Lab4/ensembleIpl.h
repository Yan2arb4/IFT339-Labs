//
//  ensembleIpl.h
//  
//  Jean Goulet 2017
//
//  Devoir fait par
//     Coéquipier 1 : Yanéric Roussy
//     Coéquipier 2 : Alexis Kaddar
//

/////////////////////////////////////////////////////////////////
// copieur et destructeur de liste

template <typename TYPEContenu>
ensemble<TYPEContenu>::ensemble(const ensemble<TYPEContenu>& src)
    : ensemble()
{
    // a completer
}

template <typename TYPEContenu>
ensemble<TYPEContenu>::~ensemble()
{
    // a completer
}

/////////////////////////////////////////////////////////////////
// localise un element, retourne la fin si absent

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::trouve(const TYPEContenu& x) const
{
    // a completer
}

// localise la premiere position ou l'element n'est
// pas plus petit que celui recu en parametre

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::borneInf(const TYPEContenu& t) const
{

    // code fonctionnel mais non optimal. a remplacer

    cellule *c = m_avant;
    cellule *apres = m_avant->m_prec[0];
    while (c->m_suiv[0] != apres)
        if (*c->m_suiv[0]->m_contenu < t)
            c = c->m_suiv[0];
        else
            break;
    return iterateur(c->m_suiv[0]);
    
}

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::borneSup(const TYPEContenu& x) const
{
    // a completer
}

/////////////////////////////////////////////////////////////////
// elimine val de l'ensemble, si present

template <typename TYPEContenu>
size_t ensemble<TYPEContenu>::retire(const TYPEContenu& val)
{
    // a completer
}

// elimine de l'ensemble l'element en position it

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::enleve(iterateur it)
{
    // a completer
}
