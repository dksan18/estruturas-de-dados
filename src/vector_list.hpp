#include <iostream>  // Inclui a biblioteca para operações de entrada e saída (cout, cin)
#include <stdexcept> // Inclui a biblioteca para classes de exceção padrão (out_of_range, length_error)

#include "../include/vector_list.hpp" // Inclui o header da classe VectorList (declaração da classe)

// --- CONSTRUTOR PADRÃO (COM CAPACIDADE) ---
template <class T>
VectorList<T>::VectorList(size_t capacity) : _capacity(capacity), _size(0) {
  // 'template <class T>' indica que VectorList é um template, funcionando com vários tipos de dados.
  // 'VectorList<T>::VectorList(size_t capacity)' é o construtor, recebendo a capacidade inicial.
  // ': _capacity(capacity), _size(0)' é a lista de inicialização, que inicializa:
  //    - _capacity: com o valor do argumento 'capacity' (tamanho máximo do array interno).
  //    - _size: com 0 (lista inicialmente vazia).
  data = new T[capacity]; // Aloca dinamicamente um array de tamanho 'capacity' do tipo 'T'.
                            // 'data' é um ponteiro para o primeiro elemento do array alocado.
}

// --- DESTRUTOR ---
template <class T>
VectorList<T>::~VectorList() {
  // Este é o destrutor da classe.  É chamado automaticamente quando um objeto VectorList sai de escopo
  // ou é explicitamente deletado.
  delete[] data; // Libera a memória alocada para o array 'data' para evitar vazamentos de memória.
}

// --- CONSTRUTOR DE CÓPIA ---
template <class T>
VectorList<T>::VectorList(const VectorList &list)
    : _size(list._size), _capacity(list._capacity) {
  // Construtor de cópia: cria um novo VectorList como uma cópia de outro VectorList ('list').
  // 'const VectorList &list' recebe uma referência constante ao objeto a ser copiado.
  // ': _size(list._size), _capacity(list._capacity)' inicializa:
  //    - _size: com o tamanho do 'list'.
  //    - _capacity: com a capacidade do 'list'.
  data = new T[_capacity]; // Aloca um novo array com a mesma capacidade do 'list'.
  for (size_t i = 0; i < _size; ++i) {
    // Itera sobre os elementos do 'list' e copia cada elemento para o novo array 'data'.
    data[i] = list.data[i];
  }
}

// --- OPERADOR DE ATRIBUIÇÃO ---
template <class T>
VectorList<T> &VectorList<T>::operator=(const VectorList &list) {
  // Operador de atribuição: permite atribuir um VectorList a outro (e.g., list1 = list2).
  // 'const VectorList &list' recebe uma referência constante ao objeto a ser atribuído.
  if (this != &list) {
    // Verifica se a atribuição não é para o próprio objeto (auto-atribuição).  Isso evita problemas
    // ao liberar a memória do objeto antes de copiá-la.
    delete[] data;    // Libera a memória do array atual antes de copiar.
    _size = list._size;  // Copia o tamanho do 'list'.
    _capacity = list._capacity; // Copia a capacidade do 'list'.
    data = new T[_capacity]; // Aloca um novo array com a capacidade correta.
    for (size_t i = 0; i < _size; ++i) {
      // Copia os elementos do 'list' para o novo array.
      data[i] = list.data[i];
    }
  }
  return *this; // Retorna uma referência ao objeto atual (*this) para permitir encadeamento
                   // de atribuições (e.g., list1 = list2 = list3).
}

// --- MÉTODO SIZE ---
template <class T>
size_t VectorList<T>::size() const {
  // Retorna o número de elementos atualmente armazenados na lista.
  return _size; // Retorna o valor do membro '_size'.
}

// --- MÉTODO EMPTY ---
template <class T>
bool VectorList<T>::empty() const {
  // Retorna 'true' se a lista estiver vazia (size == 0), 'false' caso contrário.
  return _size == 0; // Retorna o resultado da comparação '_size == 0'.
}

// --- MÉTODO CAPACITY ---
template <class T>
size_t VectorList<T>::capacity() const {
  // Retorna a capacidade máxima da lista (o tamanho do array interno).
  return _capacity; // Retorna o valor do membro '_capacity'.
}

// --- MÉTODO PUSH_BACK ---
template <class T>
void VectorList<T>::push_back(const T &value) {
  // Adiciona um novo elemento ('value') ao final da lista.
  if (_size == _capacity) {
    // Verifica se a lista está cheia (tamanho igual à capacidade).
    throw std::length_error("push_back on full VectorList"); // Lança uma exceção se a lista estiver cheia.
  }
  data[_size] = value; // Adiciona o 'value' na próxima posição disponível no array.
  _size++;             // Incrementa o tamanho da lista.
}

// --- MÉTODO INSERT ---
template <class T>
void VectorList<T>::insert(size_t index, const T &value) {
  // Insere um novo elemento ('value') na posição 'index'.
  if (index > _size) { // Permite inserção no final, mas não além
    throw std::out_of_range("Index out of range for insert"); // Lança exceção se o índice estiver fora dos limites válidos.
  }
  if (_size == _capacity) {
    // Verifica se a lista está cheia.
    throw std::length_error("insert on full VectorList"); // Lança uma exceção se a lista estiver cheia.
  }

  // Desloca os elementos para a direita a partir do índice para abrir espaço para o novo elemento.
  for (size_t i = _size; i > index; --i) {
    data[i] = data[i - 1]; // Move o elemento da posição 'i-1' para a posição 'i'.
  }

  data[index] = value; // Insere o 'value' na posição 'index'.
  _size++;             // Incrementa o tamanho da lista.
}

// --- MÉTODO POP_BACK ---
template <class T>
void VectorList<T>::pop_back() {
  // Remove o último elemento da lista.
  if (_size == 0) {
    // Verifica se a lista está vazia.
    throw std::out_of_range("pop_back on empty VectorList"); // Lança uma exceção se a lista estiver vazia.
  }
  _size--; // Decrementa o tamanho da lista.  O último elemento é "removido" simplesmente diminuindo
          // o valor de '_size'. O valor antigo permanece no array, mas não é mais acessível.
}

// --- MÉTODO REMOVE ---
template <class T>
void VectorList<T>::remove(size_t index) {
  // Remove o elemento na posição 'index'.
  if (index >= _size) {
    // Verifica se o índice está dentro dos limites válidos.
    throw std::out_of_range("Index out of range for remove"); // Lança uma exceção se o índice for inválido.
  }

  // Desloca os elementos para a esquerda a partir do índice para preencher o espaço do elemento removido.
  for (size_t i = index; i < _size - 1; ++i) {
    data[i] = data[i + 1]; // Move o elemento da posição 'i+1' para a posição 'i'.
  }
  _size--; // Decrementa o tamanho da lista.
}

// --- MÉTODO CLEAR ---
template <class T>
void VectorList<T>::clear() {
  // Remove todos os elementos da lista.
  _size = 0; // Define o tamanho da lista como 0.  Os elementos antigos permanecem no array,
             // mas não são mais acessíveis.
}

// --- MÉTODO FIND (MODIFICÁVEL) ---
template <class T>
T &VectorList<T>::find(const T &item) {
  // Procura um elemento igual a 'item' e retorna uma referência para ele.
  // Permite modificar o elemento encontrado.
  for (size_t i = 0; i < _size; ++i) {
    // Itera sobre os elementos da lista.
    if (data[i] == item) {
      // Se o elemento atual for igual a 'item', retorna uma referência para ele.
      return data[i];
    }
  }
  throw std::out_of_range("Item not found"); // Lança uma exceção se o item não for encontrado.
}

// --- MÉTODO FIND (CONSTANTE) ---
template <class T>
const T &VectorList<T>::find(const T &item) const {
  // Procura um elemento igual a 'item' e retorna uma referência constante para ele.
  // Não permite modificar o elemento encontrado.
  for (size_t i = 0; i < _size; ++i) {
    // Itera sobre os elementos da lista.
    if (data[i] == item) {
      // Se o elemento atual for igual a 'item', retorna uma referência constante para ele.
      return data[i];
    }
  }
  throw std::out_of_range("Item not found"); // Lança uma exceção se o item não for encontrado.
}

// --- MÉTODO CONTAINS ---
template <class T>
bool VectorList<T>::contains(const T &item) const {
  // Verifica se a lista contém um elemento igual a 'item'.
  for (size_t i = 0; i < _size; ++i) {
    // Itera sobre os elementos da lista.
    if (data[i] == item) {
      // Se o elemento atual for igual a 'item', retorna 'true'.
      return true;
    }
  }
  return false; // Retorna 'false' se o item não for encontrado.
}

// --- OPERADOR [] (MODIFICÁVEL) ---
template <class T>
T &VectorList<T>::operator[](size_t index) {
  // Permite acessar um elemento da lista usando a sintaxe de array (e.g., list[0]).
  // Retorna uma referência para o elemento, permitindo modificá-lo.
  if (index >= _size) {
    // Verifica se o índice está dentro dos limites válidos.
    throw std::out_of_range("Index out of range"); // Lança uma exceção se o índice for inválido.
  }
  return data[index]; // Retorna uma referência para o elemento na posição 'index'.
}

// --- OPERADOR [] (CONSTANTE) ---
template <class T>
const T &VectorList<T>::operator[](size_t index) const {
  // Permite acessar um elemento da lista usando a sintaxe de array (e.g., list[0]).
  // Retorna uma referência constante para o elemento, não permitindo modificá-lo.
  if (index >= _size) {
    // Verifica se o índice está dentro dos limites válidos.
    throw std::out_of_range("Index out of range"); // Lança uma exceção se o índice for inválido.
  }
  return data[index]; // Retorna uma referência constante para o elemento na posição 'index'.
}

// --- MÉTODO PRINT ---
template <class T>
void VectorList<T>::print() const {
  // Imprime os elementos da lista no console.
  for (size_t i = 0; i < _size; ++i) {
    // Itera sobre os elementos da lista.
    std::cout << data[i]; // Imprime o elemento atual.
    if (i < _size - 1) {
      // Se não for o último elemento, imprime uma vírgula e um espaço.
      std::cout << ", ";
    }
  }
  std::cout << std::endl; // Imprime uma nova linha no final.
}