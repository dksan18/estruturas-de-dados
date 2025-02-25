#include "../include/vector_list.hpp"
#include <iostream>

int main(int argc, char const* argv[]) {
  // Exemplo de uso:
  VectorList<int> lista(5);

  lista.push_back(10);
  lista.push_back(20);
  lista.push_back(30);

  std::cout << "Tamanho da lista: " << lista.size() << std::endl;
  std::cout << "Capacidade da lista: " << lista.capacity() << std::endl;

  std::cout << "Elementos da lista: ";
  lista.print();

  std::cout << "Elemento no índice 1: " << lista[1] << std::endl;

  lista.insert(1, 15);
  std::cout << "Lista após inserção: ";
  lista.print();

  lista.remove(2);
  std::cout << "Lista após remoção: ";
  lista.print();

  lista.pop_back();
  std::cout << "Lista após pop_back: ";
  lista.print();

  std::cout << "A lista contem o valor 15? " << lista.contains(15) << std::endl;

  try {
        std::cout << "Buscando o valor 15: " << lista.find(15) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Erro ao buscar: " << e.what() << std::endl;
    }

  lista.clear();
  std::cout << "Lista após clear: ";
  lista.print();

  return 0;
}