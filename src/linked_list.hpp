#include "../include/linked_list.hpp"

int main() {
    LinkedList<int> minhaLista;

    // Adiciona alguns elementos à lista
    minhaLista.push_front(10);
    minhaLista.push_front(20);
    minhaLista.push_front(30);

    std::cout << "Lista original: ";
    minhaLista.print();

    // Acessa um elemento usando o operador[] e imprime seu valor
    std::cout << "Elemento no índice 1: " << minhaLista[1] << std::endl;

    // Modifica um elemento usando o operador[]
    minhaLista[1] = 50;
    std::cout << "Lista após modificação: ";
    minhaLista.print();

    // Tenta acessar um índice inválido e captura a exceção
    try {
        std::cout << "Elemento no índice 5: " << minhaLista[5] << std::endl; // Isso lançará uma exceção
    } catch (const std::out_of_range& e) {
        std::cerr << "Exceção ao acessar índice inválido: " << e.what() << std::endl;
    }

    //Demonstração do uso da versão const do operador[]
    const LinkedList<int> constLista = minhaLista;
    std::cout << "Elemento no indice 0 da lista const: " << constLista[0] << std::endl;

    //Demonstração do uso da função find não const
    try {
        int& valorEncontrado = minhaLista.find(50);
        std::cout << "Valor encontrado com find (não const): " << valorEncontrado << std::endl;
        valorEncontrado = 75;
        std::cout << "Valor encontrado (e modificado) com find (não const): " << minhaLista[1] << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Exceção ao usar find (não const): " << e.what() << std::endl;
    }

   // Imprima as listas para diagnóstico
    std::cout << "minhaLista antes da busca const: ";
    minhaLista.print();
    std::cout << "constLista antes da busca const: ";
    constLista.print();

    return 0;
}