#include <iostream>
#include <stdexcept>

#include "../include/vector_list.hpp"

/*Construtor*/
template <class T>
VectorList<T>::VectorList(size_t capacity) : _capacity(capacity), _size(0) {
  data = new T[capacity]; 
}

/*Destrutor*/
template <class T>
VectorList<T>::~VectorList() {
  delete[] data;
}

/*Copia*/
template <class T>
VectorList<T>::VectorList(const VectorList &list)
    : _size(list._size), _capacity(list._capacity) {
  data = new T[_capacity];
  for (size_t i = 0; i < _size; ++i) {
    data[i] = list.data[i];
  }
}

/*Operador*/
template <class T>
VectorList<T> &VectorList<T>::operator=(const VectorList &list) {
  if (this != &list) {
    delete[] data;
    _size = list._size;
    _capacity = list._capacity;
    data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      data[i] = list.data[i];
    }
  }
  return *this;
}

/*Size*/
template <class T>
size_t VectorList<T>::size() const {
  return _size;
}

/*Vazio*/
template <class T>
bool VectorList<T>::empty() const {
  return _size == 0;
}

/*Capacidade*/
template <class T>
size_t VectorList<T>::capacity() const {
  return _capacity;
}

/*add final da lista*/
template <class T>
void VectorList<T>::push_back(const T &value) {
  if (_size == _capacity) {
    throw std::length_error("push_back on full VectorList");
  }
  data[_size] = value;
  _size++;
}

/*insere na pos*/
template <class T>
void VectorList<T>::insert(size_t index, const T &value) {
  if (index > _size) {
    throw std::out_of_range("Index out of range for insert");
  }
  if (_size == _capacity) {
    throw std::length_error("insert on full VectorList");
  }


  for (size_t i = _size; i > index; --i) {
    data[i] = data[i - 1];
  }

  data[index] = value;
  _size++;
}

/*retira último elemento da lista*/
template <class T>
void VectorList<T>::pop_back() {
  if (_size == 0) {
    throw std::out_of_range("pop_back on empty VectorList");
  }
  _size--;
}

/*remover de uma pos*/
template <class T>
void VectorList<T>::remove(size_t index) {
  if (index >= _size) {
    throw std::out_of_range("Index out of range for remove");
  }

  for (size_t i = index; i < _size - 1; ++i) {
    data[i] = data[i + 1];
  }
  _size--;
}

/*zerar lista*/
template <class T>
void VectorList<T>::clear() {
  _size = 0;
}

/*busca e altera*/
template <class T>
T &VectorList<T>::find(const T &item) {
  for (size_t i = 0; i < _size; ++i) {
    if (data[i] == item) {
      return data[i];
    }
  }
  throw std::out_of_range("Item not found");
}

/*busca referencia do item*/
template <class T>
const T &VectorList<T>::find(const T &item) const {
  for (size_t i = 0; i < _size; ++i) {
    if (data[i] == item) {
      return data[i];
    }
  }
  throw std::out_of_range("Item not found");
}

/*varrer a lista para item*/
template <class T>
bool VectorList<T>::contains(const T &item) const {
  for (size_t i = 0; i < _size; ++i) {
    if (data[i] == item) {
      return true;
    }
  }
  return false;
}

/*busca referencia por index*/
template <class T>
T &VectorList<T>::operator[](size_t index) {
  if (index >= _size) {
    throw std::out_of_range("Index out of range");
  }
  return data[index];
}

/*retorna referencia constante*/
template <class T>
const T &VectorList<T>::operator[](size_t index) const {
  if (index >= _size) {
    throw std::out_of_range("Index out of range");
  }
  return data[index];
}

/*cout*/
template <class T>
void VectorList<T>::print() const {
  for (size_t i = 0; i < _size; ++i) {
    std::cout << data[i];
    if (i < _size - 1) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;
}
#include "../include/linked_list.hpp"