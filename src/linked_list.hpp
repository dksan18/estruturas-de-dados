#include "../include/linked_list.hpp"
#include <iostream>

int main() {
    LinkedList<int> minhaLista;

    minhaLista.push_front(10);
    minhaLista.push_front(20);
    minhaLista.push_front(30);

    std::cout << "Lista original: ";
    minhaLista.print();


    std::cout << "Elemento no índice 1: " << minhaLista[1] << std::endl;

    minhaLista[1] = 50;
    std::cout << "Lista após modificação: ";
    minhaLista.print();


    try {
        std::cout << "Elemento no índice 5: " << minhaLista[5] << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Exceção ao acessar índice inválido: " << e.what() << std::endl;
    }

    const LinkedList<int> constLista = minhaLista;
    std::cout << "Elemento no indice 0 da lista const: " << constLista[0] << std::endl;


    try {
        int& valorEncontrado = minhaLista.find(50);
        std::cout << "Valor encontrado com find (não const): " << valorEncontrado << std::endl;
        valorEncontrado = 75;
        std::cout << "Valor encontrado (e modificado) com find (não const): " << minhaLista[1] << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Exceção ao usar find (não const): " << e.what() << std::endl;
    }

    std::cout << "minhaLista antes da busca const: ";
    minhaLista.print();
    std::cout << "constLista antes da busca const: ";
    constLista.print();

    return 0;
}