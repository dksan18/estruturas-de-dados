#include "../include/doubly_linked_list.hpp"
#include <iostream>

int main() {
    DoublyLinkedList<int> myList;

    // Teste de push_back
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    std::cout << "Lista após push_back: ";
    myList.print(); // Saída: 10 20 30

    // Teste de push_front
    myList.push_front(5);
    std::cout << "Lista após push_front: ";
    myList.print(); // Saída: 5 10 20 30

    // Teste de insert
    auto it = myList.begin();
    ++it; // Aponta para o segundo elemento (10)
    myList.insert(it, 15);
    std::cout << "Lista após insert: ";
    myList.print(); // Saída: 5 15 10 20 30

    // Teste de find
    auto findIt = myList.find(20);
    if (findIt != myList.end()) {
        std::cout << "Elemento encontrado: " << *findIt << std::endl; // Saída: Elemento encontrado: 20
    } else {
        std::cout << "Elemento não encontrado" << std::endl;
    }

    // Teste de contains
    if (myList.contains(10)) {
        std::cout << "A lista contém o elemento 10" << std::endl;
    } else {
        std::cout << "A lista não contém o elemento 10" << std::endl;
    }

    // Teste de operator[]
    std::cout << "Elemento no índice 2: " << myList[2] << std::endl; // Saída: Elemento no índice 2: 10

    // Teste de pop_back
    myList.pop_back();
    std::cout << "Lista após pop_back: ";
    myList.print(); // Saída: 5 15 10 20

    // Teste de pop_front
    myList.pop_front();
    std::cout << "Lista após pop_front: ";
    myList.print(); // Saída: 15 10 20

    // Teste de erase
    auto eraseIt1 = myList.begin();
    ++eraseIt1; // Aponta para 10
    auto eraseIt2 = myList.end();
    myList.erase(eraseIt1, eraseIt2);
    std::cout << "Lista após erase: ";
    myList.print(); // Saída: 15

    // Teste de clear
    myList.clear();
    std::cout << "Lista após clear: ";
    myList.print(); // (Saída não mostrará nada porque a lista está vazia)

    std::cout << "Tamanho da lista: " << myList.size() << std::endl; // Saída: Tamanho da lista: 0

    return 0;
}