#pragma once

template<typename T>
class VecteurIpl {
	void vecteur<T>::reserve(size_t n)
	{
		if (n > m_finCap)
			reserve(n);
	}

	void vecteur<T>::resize(size_t n) 
	{
		if (n > m_finCap)
			reserve(n);

		m_finDim = n;
	}

	void vecteur<T>::push_back(const T& value)
	{
		if (m_finDim == m_finCap)
			reserve(2 * m_finCap);	// On double la capacité pour éviter d'appeler à chaque fois.

		m_finDim++;
		m_debut[m_finDim - 1] = value;
	}

	void vecteur<T>::pop_back()
	{
		if (m_finDim > 0)
			m_finDim--;
	}

	//clear
	void vecteur<T>::clear() 
	{
		m_finDim = m_finCap = 0;
		delete[] m_debut;
		m_debut = nullptr;
	}
};