#include <stdexcept>

namespace structures {


template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();

    ~LinkedQueue();

    void clear();  // limpar

    void enqueue(const T& data);  // enfilerar

    T dequeue();  // desenfilerar

    T& front() const;  // primeiro dado

    T& back() const;  // último dado

    bool empty() const;  // fila vazia

    std::size_t size() const;  // tamanho

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
    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

}  // namespace structures

template<typename T>
structures::LinkedQueue<T>::Node::Node(const T& data) {
    data_ = data;
    next_ = nullptr;
}

template<typename T>
structures::LinkedQueue<T>::Node::Node(const T& data, Node* next) {
    data_ = data;
    next_ = next;
}

template<typename T>
T& structures::LinkedQueue<T>::Node::data() {
    return this->data_;
}

template<typename T>
const T& structures::LinkedQueue<T>::Node::data() const {
    return this->data_;
}

template<typename T>
typename structures::LinkedQueue<T>::Node*
structures::LinkedQueue<T>::Node::next() {
    return this->next_;
}

template<typename T>
const typename structures::LinkedQueue<T>::Node*
structures::LinkedQueue<T>::Node::next() const {
    return this->next_;
}

template<typename T>
void structures::LinkedQueue<T>::Node::next(Node* next) {
    this->next_ = next;
}

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    this->head = nullptr;
    this->tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    this->clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (!empty()) {
        this->dequeue();
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node* new_node = new Node(data, nullptr);

    if (empty()) {
        tail = new_node;
        head = new_node;
    } else {
        tail->next(new_node);
        tail = new_node;
    }
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Fila vazia!");
    }

    T dequeued_data = head->data();
    Node* old_head = head;

    if (size() == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->next();
    }
    delete old_head;
    size_--;

    return dequeued_data;
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Fila vazia!");
    }
    return head->data();
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Fila vaiza!");
    }
    return tail->data();
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}
