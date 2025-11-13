//
//  ensembleIpl.h
//  
//  Jean Goulet 2017
//
//  Devoir fait par
//     Coéquipier 1 : Yanéric Roussy
//     Coéquipier 2 : Alexis Kadar
//
/*  Explications des 4 cas prévus dans la fonction insere

    Cas #1 :
        L'itérateur évalué ne se trouve pas à la bonne place. La valeur doit être insérée
        plus loin dans l'ensemble.

    Cas #2 :
        L'insertion se fait au début de l'ensemble (aucun éléments présents).

    Cas #3 :
        L'insertion se fait entre deux cellules existantes. Donc la valeur se situe entre
        celle du précédent et celle du suivant.

    Cas #4 :
        L'insertion se fait à la fin de l'ensemble (aucune cellule mise à part la fin).
*/

/////////////////////////////////////////////////////////////////
// copieur et destructeur de liste

template <typename TYPEContenu>
ensemble<TYPEContenu>::ensemble(const ensemble<TYPEContenu>& src)
    : ensemble()
{
    for(iterateur it = src.begin(); it != src.end(); it++)
    {
        ajoute(*it.m_pointeur->m_contenu);
    }
}

template <typename TYPEContenu>
ensemble<TYPEContenu>::~ensemble()
{
    cellule* c = m_avant;
    while (c != nullptr)
    {
        cellule* apres = nullptr;       
        if (!c->m_suiv.empty())         //On garde le prochain noeud s'il y en a un
            apres = c->m_suiv[0];
        delete c;
        c = apres;
    }
    m_avant = nullptr;
    m_taille = 0;
}

/////////////////////////////////////////////////////////////////
// localise un element, retourne la fin si absent

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::trouve(const TYPEContenu& x) const
{
	iterateur it = borneInf(x);

	if (it.m_pointeur == m_avant->m_prec[0])    //Si on est à la fin, retourne fin
		return end();
    if (*(it.m_pointeur->m_contenu) < x || x < *(it.m_pointeur->m_contenu))
        return end();

	return it;
}

// localise la premiere position ou l'element n'est
// pas plus petit que celui recu en parametre

template <typename TYPEContenu>  
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::borneInf(const TYPEContenu& t) const  
{  
   cellule* c = m_avant;  
   size_t h = m_avant->m_suiv.size();  

   for (size_t i = h; i > 0; i--) {  
       while (c->m_suiv[i - 1] != m_avant->m_prec[0] && 
                *(c->m_suiv[i - 1]->m_contenu) < t) 
       {  
           c = c->m_suiv[i - 1];  
       }  
   }

   if (c->m_suiv[0] == m_avant->m_prec[0])
       return end();

   return iterateur(c->m_suiv[0]);
}

template <typename TYPEContenu>
typename ensemble<TYPEContenu>::iterateur ensemble<TYPEContenu>::borneSup(const TYPEContenu& x) const
{
    //En ce moment c est le candidat >= t
    cellule* c = borneInf(x).m_pointeur;

    if (x < *(c->m_contenu))    //Si c est déjà plus grand que t
        return iterateur(c);

    c = c->m_suiv[0];

    if (c == m_avant->m_prec[0])//Si le prochain est la fin, retourne fin.
        return end();

    return iterateur(c);
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
    return 1;
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
