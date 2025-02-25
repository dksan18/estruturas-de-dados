#include <iostream>

#include "../include/doubly_linked_list.hpp"

template <class T>
DoublyLinkedList<T>::Node::Node(const T& value)
    : value{value}, next{nullptr}, prev{nullptr} {}

template <class T>
DoublyLinkedList<T>::Node::~Node() {}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
    : head{nullptr}, tail{nullptr}, _size(0) {}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& list)
    : head{nullptr}, tail{nullptr}, _size(0) {
  Node* current_other = list.head;
  while (current_other != nullptr) {
    push_back(current_other->value);
    current_other = current_other->next;
  }
}

template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(
    const DoublyLinkedList& list) {
  if (this != &list) {
    clear();
    Node* current_other = list.head;
    while (current_other != nullptr) {
      push_back(current_other->value);
      current_other = current_other->next;
    }
  }
  return *this;
}

template <class T>
size_t DoublyLinkedList<T>::size() const {
  return _size;
}

template <class T>
bool DoublyLinkedList<T>::empty() const {
  return _size == 0;
}

template <class T>
void DoublyLinkedList<T>::push_front(const T& value) {
  Node* new_node = new Node(value);
  if (empty()) {
    head = tail = new_node;
  } else {
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
  }
  _size++;
}

template <class T>
void DoublyLinkedList<T>::push_back(const T& value) {
  Node* new_node = new Node(value);
  if (empty()) {
    head = tail = new_node;
  } else {
    new_node->prev = tail;
    tail->next = new_node;
    tail = new_node;
  }
  _size++;
}

template <class T>
void DoublyLinkedList<T>::insert(typename DoublyLinkedList<T>::iterator pos,
                                 const T& value) {
  Node* new_node = new Node(value);

  if (empty()) {
    // Inserting into an empty list
    head = tail = new_node;
  } else if (pos == begin()) {
    // Inserting at the beginning
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
  } else if (pos.node == nullptr) {
    // Inserting at end(), which is past the end of the list.  This needs to be
    // handled like push_back
    new_node->prev = tail;
    tail->next = new_node;
    tail = new_node;
  } else {
    // Inserting in the middle
    Node* current = pos.node;
    new_node->next = current;
    new_node->prev = current->prev;
    current->prev->next = new_node;
    current->prev = new_node;
  }
  _size++;
}

template <class T>
void DoublyLinkedList<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("pop_front() called on empty list");
  }

  Node* old_head = head;
  head = head->next;

  if (head != nullptr) {
    head->prev = nullptr;
  } else {
    tail = nullptr;
  }

  delete old_head;
  _size--;
}

template <class T>
void DoublyLinkedList<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("pop_back() called on empty list");
  }

  Node* old_tail = tail;
  tail = tail->prev;

  if (tail != nullptr) {
    tail->next = nullptr;
  } else {
    head = nullptr;
  }

  delete old_tail;
  _size--;
}

template <class T>
void DoublyLinkedList<T>::erase(typename DoublyLinkedList<T>::iterator first,
                                typename DoublyLinkedList<T>::iterator last) {
  Node* current = first.node;
  while (current != last.node) {
    Node* next = current->next;

    if (current->prev) {
      current->prev->next = next;
    } else {
      head = next;
    }

    if (current->next) {
      current->next->prev = current->prev;
    } else {
      tail = current->prev;
    }

    delete current;
    current = next;
    _size--;
  }
}

template <class T>
void DoublyLinkedList<T>::clear() {
  Node* current = head;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  head = tail = nullptr;
  _size = 0;
}

template <class T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::find(
    const T& item) const {
  Node* current = head;
  while (current != nullptr) {
    if (current->value == item) {
      return const_iterator(current, false);
    }
    current = current->next;
  }
  return end();
}

template <class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::find(
    const T& item) {
  Node* current = head;
  while (current != nullptr) {
    if (current->value == item) {
      return iterator(current, false);
    }
    current = current->next;
  }
  return end();
}

template <class T>
bool DoublyLinkedList<T>::contains(const T& item) const {
  return find(item) != end();
}

template <class T>
T& DoublyLinkedList<T>::operator[](size_t index) {
  if (index >= _size) {
    throw std::out_of_range("Index out of range");
  }
  Node* current = head;
  for (size_t i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->value;
}

template <class T>
const T& DoublyLinkedList<T>::operator[](size_t index) const {
  if (index >= _size) {
    throw std::out_of_range("Index out of range");
  }
  Node* current = head;
  for (size_t i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->value;
}

template <class T>
void DoublyLinkedList<T>::print() const {
  Node* current = head;
  while (current != nullptr) {
    std::cout << current->value << " ";
    current = current->next;
  }
  std::cout << std::endl;
}

template <class T>
template <class U>
DoublyLinkedList<T>::Iterator<U>::Iterator(U* ptr, bool end)
    : node(ptr), end(end) {}

template <class T>
template <class U>
auto& DoublyLinkedList<T>::Iterator<U>::operator*() const {
  if (node == nullptr) {
    throw std::out_of_range("Cannot dereference a null iterator.");
  }
  return node->value;
}

template <class T>
template <class U>
typename DoublyLinkedList<T>::Iterator<U>&
DoublyLinkedList<T>::Iterator<U>::operator++() {
  if (node != nullptr) {
    node = node->next;
  }
  end = (node == nullptr);
  return *this;
}

template <class T>
template <class U>
typename DoublyLinkedList<T>::Iterator<U>&
DoublyLinkedList<T>::Iterator<U>::operator--() {
  if (node == nullptr) {
    end = false;
    auto temp = this->node;
    if (temp->prev != nullptr) {
      this->node = temp->prev;
    }
  } else if (node->prev != nullptr) {
    node = node->prev;
    end = false;
  }
  
  return *this;
}

template <class T>
template <class U>
bool DoublyLinkedList<T>::Iterator<U>::operator==(
    const Iterator<U>& other) const {
  return node == other.node && end == other.end;
}

template <class T>
template <class U>
bool DoublyLinkedList<T>::Iterator<U>::operator!=(
    const Iterator<U>& other) const {
  return !(*this == other);
}

template <class T>
template <class U>
typename DoublyLinkedList<T>::Iterator<U>
DoublyLinkedList<T>::Iterator<U>::operator+(size_t offset) const {
  Iterator<U> temp = *this;
  for (size_t i = 0; i < offset; ++i) {
    if (temp.node == nullptr) break;
    ++temp;
  }
  return temp;
}

template <class T>
template <class U>
typename DoublyLinkedList<T>::Iterator<U>
DoublyLinkedList<T>::Iterator<U>::operator-(size_t offset) const {
  Iterator<U> temp = *this;
  for (size_t i = 0; i < offset; ++i) {
    if (temp.node == nullptr || temp.node->prev == nullptr)
      break;  // Stop if we reach the beginning
    --temp;
  }
  return temp;
}

template <class T>
template <class U>
size_t DoublyLinkedList<T>::Iterator<U>::operator-(
    const Iterator<U> other) const {
  if (this->end != other.end) {
    throw std::invalid_argument(
        "Cannot subtract iterators from different lists or one is end "
        "iterator.");
  }

  size_t distance = 0;
  Iterator<U> temp = other;

  while (temp.node != this->node && temp.node != nullptr) {
    ++temp;
    ++distance;
  }

  if (temp.node == nullptr && this->node != nullptr) {
    // The iterators are not in the same list.
    throw std::invalid_argument("Iterators are not in the same list.");
  }

  return distance;
}

template <class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::begin() {
  return iterator(head, false);
}

template <class T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::begin()
    const {
  return const_iterator(head, false);
}

template <class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::end() {
  return iterator(nullptr, true);
}

template <class T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::end() const {
  return const_iterator(nullptr, true);
}