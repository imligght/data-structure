#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class LinkedStack {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();  // limpa pilha

    void push(const T& data);  // empilha

    T pop();  // desempilha

    T& top() const;  // dado no topo

    bool empty() const;  // pilha vazia

    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data);
        Node(const T& data, Node* next);

        T& data();  // getter: info
        const T& data() const;  // getter-constante: info

        Node* next();  // getter: próximo
        const Node* next() const;  // getter-constante: próximo

        void next(Node* next);  // setter: próximo
     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures

template<typename T>
structures::LinkedStack<T>::Node::Node(const T& data) {
    this->data_ = data;
    this->next_ = nullptr;
}

template<typename T>
structures::LinkedStack<T>::Node::Node(const T& data, Node* next) {
    this->data_ = data;
    this->next_ = next;
}

template<typename T>
T& structures::LinkedStack<T>::Node::data() {
    return data_;
}

template<typename T>
const T& structures::LinkedStack<T>::Node::data() const {
    return data_;
}

template<typename T>
typename structures::LinkedStack<T>::Node*
structures::LinkedStack<T>::Node::next() {
    return next_;
}

template<typename T>
const typename structures::LinkedStack<T>::Node*
structures::LinkedStack<T>::Node::next() const {
    return next_;
}

template<typename T>
void structures::LinkedStack<T>::Node::next(Node* next) {
    this->next_ = next;
}

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node* new_node = new Node(data);

    if (empty()) {
        top_ = new_node;
        new_node->next(nullptr);
    } else {
        new_node->next(top_);
        top_ = new_node;
    }
    size_++;
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }

    Node* new_top = top_->next();
    T old_top_data = top_->data();
    delete top_;
    top_ = new_top;
    size_--;

    return old_top_data;
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    }
    return top_->data();
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
