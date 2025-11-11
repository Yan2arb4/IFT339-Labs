//
//  ensembleIpl.h
//  
//  Jean Goulet 2017
//
//  Devoir fait par
//     Coéquipier 1 : Yanéric Roussy
//     Coéquipier 2 : Alexis Kadar
//

/////////////////////////////////////////////////////////////////
// copieur et destructeur de liste

template <typename TYPEContenu>
ensemble<TYPEContenu>::ensemble(const ensemble<TYPEContenu>& src)
    : ensemble()
{
    for(iterateur it = src.begin(); it != src.end(); it++)
    {
        ajoute(*it);
    }
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
	//cellule* celluleTrouve = borneInf(x);
	iterateur it = borneInf(x);

	if (it.m_pointeur == m_avant->m_prec[0])    //Si on est à la fin, retourne fin
		return end();
	if (*(it.m_pointeur->m_contenu) != x)    //Si l'élément n'est pas égal à x, retourne fin
		return end();

	return it;
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
	iterateur it = trouve(val);

    if(it.m_pointeur == m_avant->m_prec[0])
		return 0;

	enleve(it);
}

// elimine de l'ensemble l'element en position it

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::enleve(iterateur it)
  {
   	cellule* c = it.m_pointeur;

    if (c == m_avant || c == m_avant->m_prec[0])
        return it;    

    cellule* apres = c->m_suiv[0];

	//On veut l'hauteur de la cellule à enlever
	size_t hauteur = c->m_suiv.size();

	//On reconnecte les pointeurs des cellules précédentes et suivantes
    for (size_t i = 0; i < hauteur; i++) {
		c->m_prec[i]->m_suiv[i] = c->m_suiv[i];
		c->m_suiv[i]->m_prec[i] = c->m_prec[i];
    }

    delete c;
	c = nullptr;
	--m_taille;

	//On enlève les niveaux vides s'il y a lieu
    while (m_avant->m_suiv.size() > 1 && 
		m_avant->m_suiv.back() == m_avant->m_prec[0]) //si la dernière couche est vide
    {
		m_avant->m_suiv.pop_back();
		m_avant->m_prec[0]->m_prec.pop_back();
    }

	return iterateur(apres);
}
