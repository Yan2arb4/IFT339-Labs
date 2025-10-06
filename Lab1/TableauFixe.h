#pragma once
#include <cstddef>
#include <stdexcept>

template<typename T, size_t N>
class TableauFixe {
public:
    TableauFixe();
    TableauFixe(const TableauFixe& tableau_fixe);
    TableauFixe(TableauFixe&& tableau_fixe) noexcept;
    ~TableauFixe();

    TableauFixe& operator=(const TableauFixe& other);
    TableauFixe& operator=(TableauFixe&& other) noexcept;

    size_t taille() const;
    bool estVide() const;

    T& operator[](int index);
    const T& operator[](int index) const;

    T& element(int n);
    const T& element(int n) const;

    T& premier();
    const T& premier() const;

    T& dernier();
    const T& dernier() const;

    void remplis(const T& value);
    void echange(TableauFixe& tableau_fixe);

    template<size_t M>
    TableauFixe<T, N + M> fusion(const TableauFixe<T, M>& autre) const;

    template<size_t M>
    TableauFixe<T, M> sousEnsemble(int debut) const;

private:
    T* ptr;
};

// Constructor
template<typename T, size_t N>
TableauFixe<T, N>::TableauFixe() {
    ptr = new T[N];
}

// Copy constructor
template<typename T, size_t N>
TableauFixe<T, N>::TableauFixe(const TableauFixe& tableau_fixe) {
    ptr = new T[N];
    for (size_t i = 0; i < N; ++i) ptr[i] = tableau_fixe.ptr[i];
}

// Move constructor
template<typename T, size_t N>
TableauFixe<T, N>::TableauFixe(TableauFixe&& tableau_fixe) noexcept : ptr(tableau_fixe.ptr) {
    tableau_fixe.ptr = nullptr;
}

// Destructor
template<typename T, size_t N>
TableauFixe<T, N>::~TableauFixe() {
    delete[] ptr;
}

// operator=
template<typename T, size_t N>
TableauFixe<T, N>& TableauFixe<T, N>::operator=(const TableauFixe& other) {
    if (this == &other) return *this;
    T* newptr = new T[N];
    for (size_t i = 0; i < N; ++i) newptr[i] = other.ptr[i];
    delete[] ptr;
    ptr = newptr;
    return *this;
}

template<typename T, size_t N>
TableauFixe<T, N>& TableauFixe<T, N>::operator=(TableauFixe&& other) noexcept {
    if (this == &other) return *this;
    delete[] ptr;
    ptr = other.ptr;
    other.ptr = nullptr;
    return *this;
}

// Taille
template<typename T, size_t N>
size_t TableauFixe<T, N>::taille() const {
    return N;
}

// Est vide
template<typename T, size_t N>
bool TableauFixe<T, N>::estVide() const {
    return N == 0;
}

// operator[]
template<typename T, size_t N>
T& TableauFixe<T, N>::operator[](int index) {
    return ptr[index];
}

template<typename T, size_t N>
const T& TableauFixe<T, N>::operator[](int index) const {
    return ptr[index];
}

// element
template<typename T, size_t N>
T& TableauFixe<T, N>::element(int n) {
    if (n < 0 || n >= static_cast<int>(N)) throw std::out_of_range("L'element demandé est hors de portée");
    return ptr[n];
}

template<typename T, size_t N>
const T& TableauFixe<T, N>::element(int n) const {
    if (n < 0 || n >= static_cast<int>(N)) throw std::out_of_range("L'element demandé est hors de portée");
    return ptr[n];
}

// premier / dernier
template<typename T, size_t N>
T& TableauFixe<T, N>::premier() { return ptr[0]; }

template<typename T, size_t N>
const T& TableauFixe<T, N>::premier() const { return ptr[0]; }

template<typename T, size_t N>
T& TableauFixe<T, N>::dernier() { return ptr[N - 1]; }

template<typename T, size_t N>
const T& TableauFixe<T, N>::dernier() const { return ptr[N - 1]; }

// remplis
template<typename T, size_t N>
void TableauFixe<T, N>::remplis(const T& value) {
    for (size_t i = 0; i < N; i++) {
        ptr[i] = value;
    }
}

// echange
template<typename T, size_t N>
void TableauFixe<T, N>::echange(TableauFixe& tableau_fixe) {
    T* ptrTemp = ptr;
    ptr = tableau_fixe.ptr;
    tableau_fixe.ptr = ptrTemp;
}

// fusion
template<typename T, size_t N>
template<size_t M>
TableauFixe<T, N + M> TableauFixe<T, N>::fusion(const TableauFixe<T, M>& autre) const {
    TableauFixe<T, N + M> tableau_fixeFusion;
    for (size_t i = 0; i < N; i++) {
        tableau_fixeFusion[i] = ptr[i];
    }
    for (size_t i = 0; i < M; i++) {
        tableau_fixeFusion[N + i] = autre[i];
    }
    return tableau_fixeFusion;
}

// sousEnsemble
template<typename T, size_t N>
template<size_t M>
TableauFixe<T, M> TableauFixe<T, N>::sousEnsemble(int debut) const {
    if (debut < 0 || debut + M > static_cast<int>(N))
        throw std::out_of_range("Sous-ensemble hors de portée");

    TableauFixe<T, M> sousEnsemble;
    for (size_t i = 0; i < M; i++) {
        sousEnsemble[i] = ptr[debut + i];
    }
    return sousEnsemble;
}
