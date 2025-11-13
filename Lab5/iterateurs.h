//
//  iterateurs.h
//  par un AVL
//
//  Jean Goulet 17-03-17.
//  Copyleft 2017 UdeS
//
// Modifications 2025 : MFAF

//////////////////////////////////////////////////////////////////////////
// classes d'iterateurs

template <typename T_CLE, typename T_CONTENU>
class fonction<T_CLE,T_CONTENU>::iterateur
{
private:
    noeud* m_courant = nullptr;

    friend class fonction<T_CLE, T_CONTENU>;

    explicit iterateur() = default;

    explicit iterateur(noeud* p) : m_courant(p) {}
    
public:
    iterateur(const iterateur&) = default;
    iterateur& operator=(const iterateur&) = default;
    
    T_paire& operator*() {
        return *(m_courant->m_contenu);
    }
    
    T_paire* operator->(){
        return m_courant->m_contenu;
    }
    iterateur& operator++() //++i
    {
        fonction<T_CLE, T_CONTENU>::avance(m_courant); 
        return *this;
    }
    
    iterateur operator++(int) //i++
    {
        iterateur copie(*this);
        fonction<T_CLE, T_CONTENU>::avance(m_courant);
        return copie;
    }
    
    iterateur& operator--() //--i
    {
        fonction<T_CLE, T_CONTENU>::recule(m_courant);
        return *this;
    }
    iterateur operator--(int) //i--
    {
        iterateur copie(*this);
        fonction<T_CLE, T_CONTENU>::recule(m_courant);
        return copie;
    }
    
    bool operator==(const iterateur& e_it) const
    {
        return m_courant == e_it.m_courant;
    }
    bool operator!=(const iterateur& dr) const 
    {
        return !(*this == dr);
    }
};

template <typename T_CLE, typename T_CONTENU>
class fonction<T_CLE, T_CONTENU>::iterateurVersConst
{
private:
    noeud* m_courant = nullptr;
    friend class fonction<T_CLE, T_CONTENU>;

    explicit iterateurVersConst() = default;

    explicit iterateurVersConst(noeud* p) : m_courant(p) { };
    
public:
    iterateurVersConst(const iterateurVersConst&) = default;
    iterateurVersConst& operator=(const iterateurVersConst&) = default;
    
    // retourne l'adresse d'une paire
    const T_paire& operator*() const
    {
        return *(m_courant->m_contenu);
    }
    
    // retourne une paire
    const T_paire* operator->() const
    {
        return m_courant->m_contenu;
    }
    iterateurVersConst& operator++() //++i
    {
        fonction<T_CLE, T_CONTENU>::avance(m_courant);
        return *this;
    }
    iterateurVersConst operator++(int) //i++
    {
        iterateurVersConst copie(*this);
        fonction<T_CLE, T_CONTENU>::avance(m_courant);
        return copie;
    }
    iterateurVersConst& operator--() //--i
    {
        fonction<T_CLE, T_CONTENU>::recule(m_courant);
        return *this;
    }
    iterateurVersConst operator--(int) //i--
    {
        iterateurVersConst copie(*this);
        fonction<T_CLE, T_CONTENU>::recule(m_courant);
        return copie;
    }
    bool operator==(const iterateurVersConst& dr) const 
    {
        return m_courant == dr.m_courant;
    }
    bool operator!=(const iterateurVersConst& dr) const 
    {
        return !(*this == dr);
    }
};

