// Esta implementação está errada!

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <stdexcept>
#include <cstdint>

namespace structures {

template<typename T>
class CircularList {
public:
    CircularList();
    ~CircularList();

    void clear(); // limpar lista

    void push_back(const T& data); // inserir no fim
    void push_front(const T& data); // inserir no início
    void insert(const T& data, std::size_t index); // inserir na posição
    void insert_sorted(const T& data); // inserir em ordem

    T& at(std::size_t index); // acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const; // versão const do acesso ao indice

    T pop(std::size_t index); // retirar da posição
    T pop_back(); // retirar do fim
    T pop_front(); // retirar do início
    void remove(const T& data); // remover dado específico

    bool empty() const; // lista vazia
    bool contains(const T& data) const; // lista contém determinado dado?
    std::size_t find(const T& data) const; // posição de um item na lista

    std::size_t size() const; // tamanho da lista
 private:
    class Node {  // Elemento (implementação pronta)
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* before_index(std::size_t index) {  // nó anterior ao 'index'
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};
};

#endif

template<typename T>
structures::CircularList<T>::CircularList() {
    Node* sentinel = new Node(0);
    head = sentinel;
    tail = sentinel;
    size_ = 0;
}

template<typename T>
structures::CircularList<T>::~CircularList() {
    clear();
}

template<typename T>
void structures::CircularList<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
    Node* new_node = new Node(data);
    Node* old_tail = tail;

    old_tail->next(new_node);
    new_node->next(head);
    tail = new_node;
    size_++;
}

template<typename T>
void structures::CircularList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    Node* old_first = head->next();

    head->next(new_node);
    new_node->next(old_first);
    size_++;
}

template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    if (index < 0 || index >= size()) {
        throw std::out_of_range("Index inválido!");
    }
    if (index == 0) {
        push_back(data);
        return;
    }
    Node* new_node = new Node(data);
    Node* current = head->next();
    Node* before_current = head;

    for (std::size_t i = 0; i < index; i++) {
        current = current->next();
        before_current = before_current->next();
    }
    before_current->next(new_node);
    new_node->next(current);
    size_++;
}

template<typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    if (size() == 0) {
        push_back(data);
        return;
    }
    Node* current = head->next();

    for (std::size_t i = 0; i < size(); i++) {
        if (current->data() >= data) {
            insert(data, i);
            return;
        }
        current = current->next();
    }
    push_back(data);
}

template<typename T>
T& structures::CircularList<T>::at(std::size_t index) {
    return at(index);
}

template<typename T>
const T& structures::CircularList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }
    if (index < 0 || index >= size()) {
        throw std::out_of_range("Index inválido!");
    }
    Node* current = head->next();
    for (std::size_t i = 0; i < index; i++) {
        current = current->next();
    }
    T& current_data = current->data();
    return current_data;
}

template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }
    if (index < 0 || index >= size()) {
        throw std::out_of_range("Index inválido!");
    }
    Node* current = head->next();
    Node* before_index = head;

    for (std::size_t i = 0; i < index; i++) {
        current = current->next();
        before_index = before_index->next();
    }
    Node* current_next = current->next();
    T current_data = current->data();

    before_index->next(current_next);

    delete current;
    size_--;
    return current_data;
}

template<typename T>
T structures::CircularList<T>::pop_back() {
    return pop(size() - 1);
}

template<typename T>
T structures::CircularList<T>::pop_front() {
    return pop(0);
}

template<typename T>
void structures::CircularList<T>::remove(const T& data) {
    std::size_t data_index = find(data);
    pop(data_index);
}

template<typename T>
bool structures::CircularList<T>::empty() const {
    return size() == 0;
}

template<typename T>
bool structures::CircularList<T>::contains(const T& data) const {
    std::size_t data_index = find(data);
    if (data_index != size()) {
        return true;
    }
    return false;
}

template<typename T>
std::size_t structures::CircularList<T>::find(const T& data) const {
    Node* current = head->next();

    for (std::size_t i = 0; i < size(); i++) {
        if (current->data() == data) {
            return i;
        }
        current = current->next();
    }
    return size();
}

template<typename T>
std::size_t structures::CircularList<T>::size() const {
    return size_;
}
