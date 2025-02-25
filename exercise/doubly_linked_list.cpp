#include "../include/doubly_linked_list.hpp"
#include <iostream>

int main() {
    DoublyLinkedList<int> myList;

    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    std::cout << "Lista após push_back: ";
    myList.print();

    myList.push_front(5);
    std::cout << "Lista após push_front: ";
    myList.print();

    auto it = myList.begin();
    ++it; // Aponta para o segundo elemento (10)
    myList.insert(it, 15);
    std::cout << "Lista após insert: ";
    myList.print(); // Saída: 5 15 10 20 30

    auto findIt = myList.find(20);
    if (findIt != myList.end()) {
        std::cout << "Elemento encontrado: " << *findIt << std::endl;
    } else {
        std::cout << "Elemento não encontrado" << std::endl;
    }

    if (myList.contains(10)) {
        std::cout << "A lista contém o elemento 10" << std::endl;
    } else {
        std::cout << "A lista não contém o elemento 10" << std::endl;
    }

    std::cout << "Elemento no índice 2: " << myList[2] << std::endl;


    myList.pop_back();
    std::cout << "Lista após pop_back: ";
    myList.print();

    myList.pop_front();
    std::cout << "Lista após pop_front: ";
    myList.print();


    auto eraseIt1 = myList.begin();
    ++eraseIt1; // Aponta para 10
    auto eraseIt2 = myList.end();
    myList.erase(eraseIt1, eraseIt2);
    std::cout << "Lista após erase: ";
    myList.print();


    myList.clear();
    std::cout << "Lista após clear: ";
    myList.print();

    std::cout << "Tamanho da lista: " << myList.size() << std::endl;

    return 0;
}