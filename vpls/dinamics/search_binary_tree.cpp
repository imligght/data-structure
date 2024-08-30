//!  Copyright [2020] <Autor>

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include "./array_list.h"

namespace structures {

//! Classe Árvore binária
template<typename T>
class BinaryTree {
 public:
    //! ...
    BinaryTree();
    //! ...
    ~BinaryTree();
    //! ...
    void insert(const T& data);
    //! ...
    void remove(const T& data);
    //! ...
    bool contains(const T& data) const;
    //! ...
    bool empty() const;
    //! ...
    std::size_t size() const;
    //! ...
    ArrayList<T> pre_order() const;
    //! ...
    ArrayList<T> in_order() const;
    //! ...
    ArrayList<T> post_order() const;

    //******************************************************************
    // Prova prática - implementações necessárias:

    // (1) determinação da altura da árvore:
    int height();

    // (2) contagem do número de folhas:
    int leaves();

    // (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
    //     valor da árvore:
    ArrayList<T> limits();

    // (4) criação de uma duplicação, em memória, da árvore:
    BinaryTree<T> clone();

    // (5) remove nós pelo número de seus filhos:
    void filter(int n_child);

    // (6) criação de um nova árvore que tenha todos os valores e a
    //     menor altura possível, ou seja, balanceada com base apenas
    //     no estabelecimento de uma nova ordem de inserção:
    BinaryTree<T> balance();

    //******************************************************************

 private:
    struct Node {
        //! Construtor
        explicit Node(const T& data) :
        data_{data}
        {}

        //! Destrutor
        ~Node() {
            delete left_;
            delete right_;
        }

        T data_;
        Node* left_{nullptr};
        Node* right_{nullptr};

        //! Inserção
        void insert(const T& data) {
            if (data < data_) {
                if (left_ == nullptr) {
                    left_ = new Node(data);
                    if (left_ == nullptr)
                        throw std::out_of_range("Full tree!");
                } else {
                    left_->insert(data);
                }
            } else {
                if (right_ == nullptr) {
                    right_ = new Node(data);
                    if (right_ == nullptr)
                        throw std::out_of_range("Full tree!");
                } else {
                    right_->insert(data);
                }
            }
        }

        //! Remoção
        Node* remove(const T& data) {
            if (data < data_ && left_ != nullptr) {
                left_ = remove(data, left_);
            } else if (data > data_ && right_ != nullptr) {
                right_ = remove(data, right_);
            } else {
                if (right_ != nullptr && left_ != nullptr) {
                    Node* temp = right_->minimum();
                    data_ = temp->data_;
                    right_ = remove(temp->data_, right_);
                } else if (right_ != nullptr) {
                    Node* temp = right_;
                    data_ = temp->data_;
                    right_ = temp->right_;
                    left_ = temp->left_;
                    temp->right_ = temp->left_ = nullptr;
                    delete temp;
                } else if (left_ != nullptr) {
                    Node* temp = left_;
                    data_ = temp->data_;
                    right_ = temp->right_;
                    left_ = temp->left_;
                    temp->right_ = temp->left_ = nullptr;
                    delete temp;
                } else {
                    delete this;
                    return nullptr;
                }
            }
            return this;
        }

        //! Contém
        bool contains(const T& data) const {
            if (data < data_)
                return left_ == nullptr? false : left_->contains(data);
            else if (data > data_)
                return right_ == nullptr? false : right_->contains(data);
            else
                return true;
        }

        //! Pré ordem
        void pre_order(ArrayList<T>* v) const {
            v->push_back(data_);
            if (left_ != nullptr)
                left_->pre_order(v);
            if (right_ != nullptr)
                right_->pre_order(v);
        }

        //! Em ordem
        void in_order(ArrayList<T>* v) const {
            if (left_ != nullptr)
                left_->in_order(v);
            v->push_back(data_);
            if (right_ != nullptr)
                right_->in_order(v);
        }

        //! Pós ordem
        void post_order(ArrayList<T>* v) const {
            if (left_ != nullptr)
                left_->post_order(v);
            if (right_ != nullptr)
                right_->post_order(v);
            v->push_back(data_);
        }

        //! Determinação da altura
        int height() const {
            int left_height = (left_ == nullptr) ? 0 : left_->height();
            int right_height = (right_ == nullptr) ? 0 : right_->height();
            return std::max(left_height, right_height);
        }

        //! Contagem das folhas
        int leaves() const {
            if (left_ == nullptr && right_ == nullptr)
                return 1;
            int left_leaves = (left_ == nullptr) ? 0 : left_->leaves();
            int right_leaves = (right_ == nullptr) ? 0 : right_->leaves();
            return left_leaves + right_leaves;
        }

        //! Mínimo valor
        Node* minimum() const {
            return (left_ == nullptr) ?
            const_cast<Node*>(this) : left_->minimum();
        }

        //! Máximo valor
        Node* maximum() const {
            return (right_ == nullptr) ?
            const_cast<Node*>(this) : right_->maximum();
        }

        //! Clonar
        Node* clone() const {
            Node* new_node = new Node(data_);
            if (left_ != nullptr)
                new_node->left_ = left_->clone();
            if (right_ != nullptr)
                new_node->right_ = right_->clone();
            return new_node;
        }

        //! Filtrar
        Node* filter(int n_child, std::size_t& size) {
            if (left_ != nullptr)
                left_ = left_->filter(n_child, size);
            if (right_ != nullptr)
                right_ = right_->filter(n_child, size);

            int num_children = (left_ != nullptr) + (right_ != nullptr);
            if (num_children == n_child) {
                if (left_ != nullptr && right_ != nullptr) {
                    Node* temp = right_->minimum();
                    data_ = temp->data_;
                    right_ = right_->remove(temp->data_);
                } else {
                    Node* temp = (left_ != nullptr) ? left_ : right_;
                    left_ = right_ = nullptr;
                    delete this;
                    --size;
                    return temp;
                }
            }
            return this;
        }

     private:
        //! Complemento da funcão de remoção
        Node* remove(const T& data, Node* arv) {
            if (arv == nullptr)
                return arv;
            if (data < arv->data_) {
                arv->left_ = remove(data, arv->left_);
                return arv;
            }
            if (data > arv->data_) {
                arv->right_ = remove(data, arv->right_);
                return arv;
            }
            // dois filhos
            if (arv->right_ != nullptr && arv->left_ != nullptr) {
                Node* temp = arv->right_->minimum();
                arv->data_ = temp->data_;
                arv->right_ = remove(temp->data_, arv->right_);
                return arv;
            }
            // um filho ou folha
            Node* temp = nullptr;
            if (arv->right_ != nullptr)
                temp = arv->right_;
            else
                temp = arv->left_;

            arv->right_ = arv->left_ = nullptr;
            delete arv;
            return temp;
        }
    };

    Node* root_{nullptr};
    std::size_t size_{0};

    //! Encontra o menor valor da árvore
    Node* minimum() const {
        if (root_ == nullptr)
            throw std::out_of_range("Empty tree");
        return root_->minimum();
    }

    //! Encontra o maior valor da árvore
    Node* maximum() const {
        if (root_ == nullptr)
            throw std::out_of_range("Empty tree");
        return root_->maximum();
    }
};

//******************************************************************
// Prova prática - implementações necessárias:

//! (1) determinação da altura da árvore:
template<typename T>
int BinaryTree<T>::height() {
    return (root_ == nullptr) ? 0 : root_->height();
}

//! (2) contagem do número de folhas:
template<typename T>
int BinaryTree<T>::leaves() {
    return (root_ == nullptr) ? 0 : root_->leaves();
}

//! (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
//!     valor da árvore:
template<typename T>
ArrayList<T> BinaryTree<T>::limits() {
    ArrayList<T> L(2);
    if (root_ != nullptr) {
        L.push_back(minimum()->data_);
        L.push_back(maximum()->data_);
    }
    return L;
}

//! (4) criação de uma duplicação, em memória, da árvore:
template<typename T>
BinaryTree<T> BinaryTree<T>::clone() {
    BinaryTree<T> C;
    if (root_ != nullptr)
        C.root_ = root_->clone();
    C.size_ = size_;
    return C;
}

//! (5) remove nós pelo número de seus filhos:
template<typename T>
void BinaryTree<T>::filter(int n_child) {
    if (root_ != nullptr)
        root_ = root_->filter(n_child, size_);
}

//! (6) criação de um nova árvore que tenha todos os valores e a
//!     menor altura possível, ou seja, balanceada com base apenas
//!     no estabelecimento de uma nova ordem de inserção:
template<typename T>
BinaryTree<T> BinaryTree<T>::balance() {
    ArrayList<T> sorted_values = in_order();
    BinaryTree<T> B;

    std::function<void(BinaryTree<T>&, ArrayList<T>&, int, int)> build_balanced;
    build_balanced = [&](BinaryTree<T>& tree, ArrayList<T>& values, int start, int end) {
        if (start <= end) {
            int mid = (start + end) / 2;
            tree.insert(values[mid]);
            build_balanced(tree, values, start, mid - 1);
            build_balanced(tree, values, mid + 1, end);
        }
    };

    build_balanced(B, sorted_values, 0, sorted_values.size() - 1);
    return B;
}

//******************************************************************

//! Construtor
template<typename T>
BinaryTree<T>::BinaryTree()
{}

//! Destrutor
template<typename T>
BinaryTree<T>::~BinaryTree() {
    delete root_;
}

//! Inserção
template<typename T>
void BinaryTree<T>::insert(const T& data) {
    if (empty()) {
        root_ = new Node(data);
        if (root_ == nullptr)
            throw std::out_of_range("Full tree!");
    } else {
        root_->insert(data);
    }
    ++size_;
}

// Remoção
template<typename T>
void BinaryTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Empty tree");

    if (size() != 1u) {
        root_ = root_->remove(data);
        --size_;
    } else {
        if (root_->data_ == data) {
            delete root_;
            root_ = nullptr;
            --size_;
        }
    }
}

//! Contém
template<typename T>
bool BinaryTree<T>::contains(const T& data) const {
    if (empty())
        return false;
    return root_->contains(data);
}

//! Vazio
template<typename T>
bool BinaryTree<T>::empty() const {
    return size() == 0;
}

//! Tamanho
template<typename T>
std::size_t BinaryTree<T>::size() const {
    return size_;
}

//! Pré ordem
template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->pre_order(&v);
    return v;
}

//! Em ordem
template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->in_order(&v);
    return v;
}

//! Pós ordem
template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(&v);
    return v;
}

}  // namespace structures

#endif
