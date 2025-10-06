#include <iostream>
#include "TableauFixe.h"

#include <array>

typedef int Object; // vous devriez tester un type plus complexe...

template<typename T, size_t N>
void afficherArrayIndex(const TableauFixe<T, N>& a)
{
    std::cout << "======= Affichage d'un TableauFixe<T, N> avec un index (operator[]) ==========" << std::endl;
    for (size_t i = 0; i < N; ++i)
    {
        std::cout << "(" << i << ") - " << a[i] << std::endl;
    }
    std::cout << "======= Fin de l'affichage d'un TableauFixe<T, N> ==========" << std::endl;
}


void testArray()
{
    TableauFixe<Object, 5> aObj;

    aObj.remplis(Object(4));
    std::cout << "Affichage d'un TableauFixe<Object, 5> rempli par la methode remplis avec un Object(4) :" << std::endl;
    afficherArrayIndex(aObj);

    std::cout << "Changement de la valeur a la position 3 avec la methode element avec un Object(10) :" << std::endl;
    aObj.element(3) = Object(10);
    afficherArrayIndex(aObj);

    std::cout << "Changement de la valeur a la position 0 avec l'operator [] avec un Object(15) et changement de dernier() par premier() :" << std::endl;
    aObj[0] = Object(15);
    aObj.dernier() = aObj.premier();
    afficherArrayIndex(aObj);

    // Fusion
    std::cout << "Creation d'un TableauFixe<T, 14> rempli par des Object(2)" << std::endl;
    TableauFixe<Object, 14> bObj;
    bObj.remplis(Object(2));
    std::cout << "Creation d'un TableauFixe<T, 9> rempli par des Object(6)" << std::endl;
    TableauFixe<Object, 9> cObj;
    cObj.remplis(Object(6));
    afficherArrayIndex(bObj);
    afficherArrayIndex(cObj);
    std::cout << "Fusion du TableauFixe<T, 5> et du TableauFixe<T, 9> dans le TableauFixe<T, 14>" << std::endl;
    bObj = aObj.fusion(cObj);
    afficherArrayIndex(bObj);

    // Subset
    std::cout << "sous-ensemble d'un TableauFixe<T, 14> vers un TableauFixe<T, 5> a partir de la position 3" << std::endl;
    aObj = bObj.sousEnsemble<5>(3);
    afficherArrayIndex(aObj);
}


int main()
{
    std::cout << " ========= Debut du programmede test ========" << std::endl;

    testArray();

    std::cout << " ========= Fin du programme de test ========" << std::endl;

}