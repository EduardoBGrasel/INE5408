#include <cstdint>
#include <stdexcept>  // C++ exceptions
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
        explicit Node(const T& data_) {
            data = data_;
            left = nullptr;
            right = nullptr;
        }

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            if (data_ < data) {
                if (left != nullptr) {
                    left->insert(data_);
                } else {
                    left = new Node(data_);
                }
            } else {
                if (right != nullptr) {
                    right->insert(data_);
                } else {
                    right = new Node(data_);
                }
            }
        }

        bool remove(const T& data_) {
            // caso 1
            if (data_ > data) {
                if (right != nullptr) {
                    if (right->data == data_) {
                        delete right;
                        right = nullptr;
                        return true;
                    } else {
                        return right->remove(data_);
                    }
                } else if (left != nullptr) {
                    return left->remove(data_);
                } else {
                    return false;
                }
            // caso 2
            } else if (data_ < data) {
                if (left != nullptr) {
                    if (left->data == data_) {
                        delete left;
                        left = nullptr;
                        return true;
                    } else {
                        return left->remove(data_);
                    }
                } else if (right != nullptr) {
                    return right->remove(data_);
                } else {
                    return false;
                }
            // caso 3
            } else {
                if (left != nullptr && right != nullptr) {
                    Node* aux = right;
                    while (aux->left != nullptr) {
                        aux = aux->left;
                    }
                    data = aux->data;
                    return right->remove(data);
                } else if (left != nullptr) {
                    data = left->data;
                    delete left;
                    left = nullptr;
                    return true;
                } else if (right != nullptr) {
                    data = right->data;
                    delete right;
                    right = nullptr;
                    return true;
                } else {
                    return false;
                }
            }
        }

        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data) {
                if (left != nullptr) {
                    return left->contains(data_);
                } else {
                    return false;
                }
            } else {  // data_ > data
                if (right != nullptr) {
                    return right->contains(data_);
                } else {
                    return false;
                }
            }
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures

//-------------------------------------

template<typename T>
structures::BinaryTree<T>::BinaryTree() {
    root = nullptr;
    size_ = 0;
}

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    delete root;
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (root != nullptr) {
        root->insert(data);
    } else {
        root = new Node(data);
    }
    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (root != nullptr) {
        root->remove(data);
        size_--;
    }
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (root != nullptr) {
        return root->contains(data);
    } else {
        return false;
    }
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> List;
	if (root != nullptr) {
		root->pre_order(List);
	}
	return List;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    ArrayList<T> List;
    if (root != nullptr) {
        root->in_order(List);
    }
    return List;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    ArrayList<T> List;
    if (root != nullptr) {
        root->post_order(List);
    }
    return List;
}
