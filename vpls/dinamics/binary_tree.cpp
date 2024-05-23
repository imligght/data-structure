// Copyright [2024] <Caio César Rodrigues de Aquino>
#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();

    void insert(const T& data);
    void remove(const T& data);
    bool contains(const T& data) const;
    bool empty() const;
    std::size_t size() const;

    ArrayList<T> pre_order() const;
    ArrayList<T> in_order() const;
    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data);

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_);
        Node* remove(const T& data_, Node** root);
        bool contains(const T& data_) const;
        void pre_order(ArrayList<T>& v) const;
        void in_order(ArrayList<T>& v) const;
        void post_order(ArrayList<T>& v) const;

        void recursive_destroyer(Node* root);
    };

    Node* root;
    std::size_t size_;
};

template<typename T>
BinaryTree<T>::BinaryTree() : root(nullptr), size_(0) {}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    if (root != nullptr) {
        root->recursive_destroyer(root);
    }
}

template<typename T>
void BinaryTree<T>::insert(const T& data) {
    if (root == nullptr) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    ++size_;
}

template<typename T>
void BinaryTree<T>::remove(const T& data) {
    if (empty() || root == nullptr) {
        throw std::out_of_range("Impossível remover de uma árvore vazia!");
    }

    root = root->remove(data, &root);
    if (root != nullptr) {
        --size_;
    }
}

template<typename T>
bool BinaryTree<T>::contains(const T& data) const {
    if (root == nullptr) {
        return false;
    } else {
        return root->contains(data);
    }
}

template<typename T>
bool BinaryTree<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> result;
    if (root != nullptr) {
        root->pre_order(result);
    }
    return result;
}

template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> result;
    if (root != nullptr) {
        root->in_order(result);
    }
    return result;
}

template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> result;
    if (root != nullptr) {
        root->post_order(result);
    }
    return result;
}

template<typename T>
BinaryTree<T>::Node::Node(const T& data_) :
data(data_), left(nullptr), right(nullptr) {}

template<typename T>
void BinaryTree<T>::Node::insert(const T& data_) {
    if (data_ < data) {
        if (left == nullptr) {
            left = new Node(data_);
        } else {
            left->insert(data_);
        }
    } else if (data_ > data) {
        if (right == nullptr) {
            right = new Node(data_);
        } else {
            right->insert(data_);
        }
    }
}

template<typename T>
typename BinaryTree<T>::Node*
BinaryTree<T>::Node::remove(const T& data_, Node** root) {
    if (data_ < data) {
        if (left != nullptr) {
            left = left->remove(data_, root);
        }
    } else if (data_ > data) {
        if (right != nullptr) {
            right = right->remove(data_, root);
        }
    } else {
        if (left != nullptr && right != nullptr) {
            Node* min_node = right;
            while (min_node->left != nullptr) {
                min_node = min_node->left;
            }
            data = min_node->data;
            right = right->remove(data, root);
        } else {
            Node* child = (left != nullptr) ? left : right;
            if (this == *root) {
                *root = child;
            }
            delete this;
            return child;
        }
    }
    return this;
}

template<typename T>
bool BinaryTree<T>::Node::contains(const T& data_) const {
    if (data_ == data) {
        return true;
    } else if (data_ < data) {
        return left != nullptr && left->contains(data_);
    } else {
        return right != nullptr && right->contains(data_);
    }
}

template<typename T>
void BinaryTree<T>::Node::pre_order(ArrayList<T>& v) const {
    v.push_back(data);
    if (left != nullptr) {
        left->pre_order(v);
    }
    if (right != nullptr) {
        right->pre_order(v);
    }
}

template<typename T>
void BinaryTree<T>::Node::in_order(ArrayList<T>& v) const {
    if (left != nullptr) {
        left->in_order(v);
    }
    v.push_back(data);
    if (right != nullptr) {
        right->in_order(v);
    }
}

template<typename T>
void BinaryTree<T>::Node::post_order(ArrayList<T>& v) const {
    if (left != nullptr) {
        left->post_order(v);
    }
    if (right != nullptr) {
        right->post_order(v);
    }
    v.push_back(data);
}

template<typename T>
void BinaryTree<T>::Node::recursive_destroyer(Node* root) {
    if (root == nullptr) {
        return;
    }
    recursive_destroyer(root->left);
    recursive_destroyer(root->right);
    delete root;
}

}  // namespace structures
