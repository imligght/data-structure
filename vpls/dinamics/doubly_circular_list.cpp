// Copyright 2024 Caio Cesar Rodrigues de Aquino

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data);
        Node(const T& data, Node* next);
        Node(const T& data, Node* prev, Node* next);

        T& data();
        const T& data() const;

        Node* prev();
        const Node* prev() const;

        void prev(Node* node);

        Node* next();
        const Node* next() const;

        void next(Node* node);

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyCircularList<T>::Node::Node(const T& data):
    data_(data)
    {}

template<typename T>
structures::DoublyCircularList<T>::Node::Node(const T& data, Node* next):
    data_(data),
    next_(next)
    {}

template<typename T>
structures::DoublyCircularList<T>::Node::Node(const T& data,
                                              Node* prev,
                                              Node* next):
    data_(data),
    prev_(prev),
    next_(next)
    {}

template<typename T>
T& structures::DoublyCircularList<T>::Node::data() {
    return data_;
}

template<typename T>
const T& structures::DoublyCircularList<T>::Node::data() const {
    return data_;
}

template<typename T>
typename structures::DoublyCircularList<T>::Node*
structures::DoublyCircularList<T>::Node::prev() {
    return prev_;
}

template<typename T>
const typename structures::DoublyCircularList<T>::Node*
structures::DoublyCircularList<T>::Node::prev() const {
    return prev_;
}

template<typename T>
void structures::DoublyCircularList<T>::Node::prev(Node* node) {
    prev_ = node;
}

template<typename T>
typename structures::DoublyCircularList<T>::Node*
structures::DoublyCircularList<T>::Node::next() {
    return next_;
}

template<typename T>
const typename structures::DoublyCircularList<T>::Node*
structures::DoublyCircularList<T>::Node::next() const {
    return next_;
}

template<typename T>
void structures::DoublyCircularList<T>::Node::next(Node* node) {
    next_ = node;
}

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    Node* sentinel = new Node(0);
    sentinel->next(sentinel);
    sentinel->prev(sentinel);

    head = sentinel;
    size_ = 0;
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    Node* new_node = new Node(data);  // nó a ser inserido
    Node* tail = head->prev();  // último nó da lista

    tail->next(new_node);
    new_node->prev(tail);
    new_node->next(head);
    head->prev(new_node);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);  // nó a ser inserido
    Node* old_first = head->next();  // primeiro nó da lista
                                     // (que não seja o sentinela)

    head->next(new_node);
    new_node->prev(head);
    new_node->next(old_first);
    old_first->prev(new_node);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data,
                                               std::size_t index) {
    if (index < 0 || index > size()) {
        throw std::out_of_range("Index inválido!");
    }
    if (index == 0) {
        push_front(data);
        return;
    }
    Node* new_node = new Node(data);

    Node* index_node = head->next();
    for (std::size_t i = 0; i < index; i++) {
        index_node = index_node->next();
    }
    Node* before_index = index_node->prev();

    new_node->next(index_node);
    new_node->prev(before_index);
    index_node->prev(new_node);
    before_index->next(new_node);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (size() == 0) {
        push_back(data);
        return;
    }
    for (std::size_t i = 0; i < size(); i++) {
        if (at(i) >= data) {
            insert(data, i);
            return;
        }
    }
    push_back(data);
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }
    if (index < 0 || index >= size()) {
        throw std::out_of_range("Index inválido!");
    }
    if (index == 0) {
        return pop_front();
    }
    Node* current = head->next();
    for (std::size_t i = 0; i < index; i++) {
        current = current->next();
    }
    T current_data = current->data();
    Node* current_next = current->next();
    Node* current_prev = current->prev();

    current_prev->next(current_next);
    current_next->prev(current_prev);

    delete current;
    size_--;
    return current_data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }
    Node* old_last = head->prev();
    Node* new_last = old_last->prev();
    T old_last_data = old_last->data();

    head->prev(new_last);
    new_last->next(head);

    delete old_last;
    size_--;
    return old_last_data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }
    Node* old_first = head->next();
    Node* new_first = old_first->next();
    T old_first_data = old_first->data();

    head->next(new_first);
    new_first->prev(head);

    delete old_first;
    size_--;
    return old_first_data;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }
    Node* current = head->next();
    for (std::size_t i = 0; i < size(); i++) {
        if (at(i) == data) {
            pop(i);
            return;
        }
        current = current->next();
    }
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return size() == 0;
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    if (empty()) {
        return false;
    }
    Node* current = head->next();
    for (std::size_t i = 0; i < size(); i++) {
        if (current->data() == data) {
            return true;
        }
        current = current->next();
    }
    return false;
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
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
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    const T& data = at(index);
    return data;
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }
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
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}
