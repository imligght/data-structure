// Copyright [2024] <Caio César Rodrigues de Aquino>

#include "array_list.h"


namespace structures {

template<typename T>
class AVLTree {
public:
    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
            height_ = 0;
            left = nullptr;
            right = nullptr;
        }

        T data;
        int height_;
        Node* left;
        Node* right;

        void insert(const T& data_, Node** parent);

        bool remove(const T& data_, Node** root);

        bool contains(const T& data_) const;
        
        void updateHeight();

        Node* simpleLeft();

        Node* simpleRight();

        Node* doubleLeft();
        
        Node* doubleRight();

        void pre_order(ArrayList<T>& v) const;

        void in_order(ArrayList<T>& v) const;

        void post_order(ArrayList<T>& v) const;

        int height() {
            return height_;
        }

        void balance(Node** parent);

        int leftHeight() const;

        int rightHeight() const;

        int balanceFactor() const;
    };

    Node* root;
    std::size_t size_;
};

}

// -----

template<typename T>
int structures::AVLTree<T>::Node::leftHeight() const {
    if (left != nullptr) {
        return left->height();
    } else {
        return -1;
    }
}

template<typename T>
int structures::AVLTree<T>::Node::rightHeight() const {
    if (right != nullptr) {
        return right->height();
    } else {
        return -1;
    }
}

template<typename T>
int structures::AVLTree<T>::Node::balanceFactor() const {
    return leftHeight() - rightHeight();
}

int max(int a, int b) {
    return a > b ? a : b;
}

template<typename T>
void structures::AVLTree<T>::Node::balance(Node** parent) {
    int current_balance_factor = balanceFactor();

    if (current_balance_factor > 1) {
        if (left->balanceFactor() > 0) {
            *parent = simpleRight();
        } else {
            *parent = doubleRight();
        }
    } else if (current_balance_factor < -1) {
        if (right->balanceFactor() < 0) {
            *parent = simpleLeft();
        } else {
            *parent = doubleLeft();
        }
    }
}

template<typename T>
void structures::AVLTree<T>::Node::updateHeight() {
    int leftHeight;
    int rightHeight;
    if (left != nullptr) {
        leftHeight = left->height();
    } else {
        leftHeight = -1;
    }

    if (right != nullptr) {
        rightHeight = right->height();
    } else {
        rightHeight = -1;
    }

    height_ = max(leftHeight, rightHeight) + 1;
}

template<typename T>
typename structures::AVLTree<T>::Node* structures::AVLTree<T>::Node::simpleLeft() {
    Node* new_root = right;
    right = new_root->left;
    new_root->left = this;
    updateHeight();
    new_root->updateHeight();
    return new_root;
}

template<typename T>
typename structures::AVLTree<T>::Node* structures::AVLTree<T>::Node::simpleRight() {
    Node* new_root = left;
    left = new_root->right;
    new_root->right = this;
    updateHeight();
    new_root->updateHeight();
    return new_root;
}

template<typename T>
typename structures::AVLTree<T>::Node* structures::AVLTree<T>::Node::doubleLeft() {
    right = right->simpleRight();
    return simpleLeft();
}

template<typename T>
typename structures::AVLTree<T>::Node* structures::AVLTree<T>::Node::doubleRight() {
    left = left->simpleLeft();
    return simpleRight();
}

template<typename T>
void structures::AVLTree<T>::Node::insert(const T& data_, Node** parent) {
    if (data_ < data) {
        if (left == nullptr) {
            left = new Node(data_);
        } else {
            left->insert(data_, &left);
        }
    } else if (data_ > data) {
        if (right == nullptr) {
            right = new Node(data_);
        } else {
            right->insert(data_, &right);
        }
    }
    updateHeight();
    balance(parent);
}

template<typename T>
bool structures::AVLTree<T>::Node::remove(const T& data_, Node** parent) {
            if (data_ < data) {
                if (left != nullptr) {
                    bool return_value{left->remove(data_, &left)};
                    updateHeight();
                    balance(parent);
                    return return_value;
                }

            } else if (data_ > data) {
                if (right != nullptr) {
                    bool return_value{right->remove(data_, &right)};
                    updateHeight();
                    balance(parent);
                    return return_value;
                }

            } else {
                if (left != nullptr && right == nullptr) {
                    if (parent != nullptr) {
                        *parent = left;
                    }
                    delete this;

                } else if (left == nullptr && right != nullptr) {
                    if (parent != nullptr) {
                        *parent = right;
                    }
                    delete this;

                } else if (left != nullptr && right != nullptr) {
                    Node* sucessor{right};
                    while (sucessor->left != nullptr) {
                        sucessor = sucessor->left;
                    }
                    T sucessorData = sucessor->data;
                    right->remove(sucessorData, &right);

                    data = sucessorData;

                } else {
                    *parent = nullptr;
                    delete this;
                }
                return true;
            }
            return false;
}


template<typename T>
bool structures::AVLTree<T>::Node::contains(const T& data_) const {
    if (data_ == data) {
        return true;
    }

    if (data_ < data) {
        if (left != nullptr) {
            return left->contains(data_);
        } else {
            return false;
        }
    } else if (data_ > data) {
        if (right != nullptr) {
            return right->contains(data_);
        } else {
            return false;
        }
    }
    return false;
}

template<typename T>
void structures::AVLTree<T>::Node::pre_order(ArrayList<T>& v) const {
    v.push_back(data);
    if (left) {
        left->pre_order(v);
    }
    if (right) {
        right->pre_order(v);
    }
}

template<typename T>
void structures::AVLTree<T>::Node::in_order(ArrayList<T>& v) const {
    if (left) {
        left->in_order(v);
    }
    v.push_back(data);
    if (right) {
        right->in_order(v);
    }
}

template<typename T>
void structures::AVLTree<T>::Node::post_order(ArrayList<T>& v) const {
    if (left) {
        left->post_order(v);
    }
    if (right) {
        right->post_order(v);
    }
    v.push_back(data);
}

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    delete root;
}

template<typename T>
void structures::AVLTree<T>::insert(const T& data_) {
    if (root == nullptr) {
        root = new Node(data_);
    } else {
        root->insert(data_, &root);
    }
    size_++;
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data_) {
    if (root == nullptr) {
        return;
    }

    root->remove(data_, &root);
    size_--;
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data_) const {
    if (root == nullptr) {
        return false;
    }

    return root->contains(data_);
}

template<typename T>
bool structures::AVLTree<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template<typename T>
int structures::AVLTree<T>::height() const {
    if (root == nullptr) {
        return -1;
    }
    return root->height();
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    ArrayList<T> v;
    if (root == nullptr) {
        return v;
    }
    root->pre_order(v);
    return v;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    ArrayList<T> v;
    if (root == nullptr) {
        return v;
    }
    root->in_order(v);
    return v;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    ArrayList<T> v;
    if (root == nullptr) {
        return v;
    }
    root->post_order(v);
    return v;
}   