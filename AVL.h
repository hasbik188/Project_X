#ifndef INC_1_2_AVL_H
#define INC_1_2_AVL_H

#include <iostream>
#include <stack>
#include "List.h"

template<typename T>
class TNode {
public:
    int height;
    List<T>* list;
    TNode<T>* left;
    TNode<T>* right;
    int balance;

    TNode() : list(nullptr), left(nullptr), right(nullptr), height(1), balance(0) {}

    TNode(T num) : left(nullptr), right(nullptr), height(1), balance(0) {
        list = new List<T>(num);
    }

    ~TNode() {
        delete list;
    }
};
template<typename T>
class BST {
private:
    TNode<T>* root;
    bool h;

public:
    BST() : root(nullptr), h(true) {}

    ~BST() {
        deleteTree(root);
    }

    void insert(T num) {
        insertInTree(root, num, h);
    }

    void remove(T num) {
        deleteFromTree(root, num, h);
    }

    void printSideways() {
        printOnSide(0, root);
        std::cout << std::endl;
    }

    bool isEqual(BST& other) {
        return areEqual(root, other.root);
    }

private:
    int nodeNumber(List<T>* node) {
        int number = 1;
        if (node->next == nullptr)
            return number;
        List<T>* current = node->next;
        while (current != nullptr) {
            number++;
            current = current->next;
        }
        return number;
    }

    void deleteFromList(TNode<T>* node) {
        List<T>* listnode = node->list;
        List<T>* temp = listnode->next;
        listnode->next = temp->next;
        if (temp->next != nullptr)
            temp->next->prev = listnode;
        delete temp;
    }

    void addToList(List<T>*& node, T num) {
        ToList(node,num);
//
//        List<T>* newone = new List<T>(num);
//        if (node != nullptr) {
//            node->prev = newone;
//            newone->next = node;
//        }
//        node = newone;
    }

    T getNodeValue(TNode<T>* p) {
        return p->list->data;
    }

    TNode<T>* findNode(TNode<T>* root, T num) {
        if (root == nullptr) {
            std::cout << "The tree is empty.\n";
            return nullptr;
        }
        TNode<T>* current = root;
        while ((current != nullptr) && (getNodeValue(current) != num)) {
            if (getNodeValue(current) < num)
                current = current->left;
            else if (getNodeValue(current) > num)
                current = current->right;
        }
        if (current == nullptr) {
            std::cout << "Element not found.\n";
            return nullptr;
        }
        else {
            std::cout << "Element found.\n";
            return current;
        }
    }

    void insertInTree(TNode<T>*& root, T num, bool& h) {
        if ((root == nullptr) || (root->list == nullptr)) {
            root = new TNode<T>(num);
            root->height = 1;
            root->left = nullptr;
            root->right = nullptr;
            h = true;
        }
        else if (getNodeValue(root) > num) {
            insertInTree(root->left, num, h);
            if (h == true) {
                if (root->balance == 1) {
                    root->balance = 0;
                    h = false;
                }
                else if (root->balance == 0) {
                    root->balance = -1;
                }
                else if (root->balance == -1) {
                    TNode<T>* node = root->left;
                    if (node->balance == -1) {
                        root->left = node->right;
                        node->right = root;
                        root->balance = 0;
                        root = node;
                    }
                    else {
                        TNode<T>* node1 = node->right;
                        node->right = node1->left;
                        node1->left = node;
                        root->left = node1->right;
                        node1->right = root;
                        if (node1->balance == -1)
                            root->balance = 1;
                        else
                            root->balance = 0;
                        if (node1->balance == 1)
                            node1->balance = -1;
                        else
                            node->balance = 0;
                        root = node1;
                    }
                    root->balance = 0;
                    h = false;
                }
            }
        }
        else if (getNodeValue(root) < num) {
            insertInTree(root->right, num, h);
            if (h == true) {
                if (root->balance == -1) {
                    root->balance = 0;
                    h = false;
                }
                else if (root->balance == 0) {
                    root->balance = 1;
                }
                else if (root->balance == 1) {
                    TNode<T>* node = root->right;
                    if (node->balance == 1) {
                        root->right = node->left;
                        node->left = root;
                        root->balance = 0;
                        root = node;
                    }
                    else {
                        TNode<T>* node1 = node->left;
                        node->left = node1->right;
                        node1->right = node;
                        root->right = node1->left;
                        node1->left = root;
                        if (node1->balance == 1)
                            root->balance = -1;
                        else
                            root->balance = 0;
                        if (node1->balance == -1)
                            node->balance = 1;
                        else
                            node->balance = 0;
                        root = node1;
                    }
                    root->balance = 0;
                    h = false;
                }
            }
        }
        else
            addToList(root->list, num);
    }

    void balanceL(TNode<T>*& root, bool& h) {
        if (root->balance == -1)
            root->balance = 0;
        else if (root->balance == 0) {
            root->balance = 1;
            h = false;
        }
        else {
            TNode<T>* node = root->right;
            if (node->balance >= 0) {
                root->right = node->left;
                node->left = root;
                if (node->balance == 0) {
                    root->balance = 1;
                    node->balance = -1;
                    h = false;
                }
                else {
                    root->balance = 0;
                    node->balance = 0;
                }
                root = node;
            }
            else {
                TNode<T>* node1 = node->left;
                node->left = node1->right;
                node1->right = node;
                root->right = node1->left;
                node1->left = root;
                if (node1->balance == -1)
                    root->balance = 1;
                else
                    root->balance = 0;
                if (node1->balance == 1)
                    node->balance = -1;
                else
                    node->balance = 0;
                root = node1;
                node1->balance = 0;
            }
        }
    }

    void balanceR(TNode<T>*& root, bool& h) {
        if (root->balance == 1)
            root->balance = 0;
        else if (root->balance == 0) {
            root->balance = -1;
            h = false;
        }
        else {
            TNode<T>* node = root->left;
            if (node->balance <= 0) {
                root->left = node->right;
                node->right = root;
                if (node->balance == 0) {
                    root->balance = -1;
                    node->balance = 1;
                    h = false;
                }
                else {
                    root->balance = 0;
                    node->balance = 0;
                }
                root = node;
            }
            else {
                TNode<T>* node1 = node->right;
                node->right = node1->left;
                node1->left = node;
                root->left = node1->right;
                node1->right = root;
                if (node1->balance == -1)
                    root->balance = 1;
                else
                    root->balance = 0;
                if (node1->balance == 1)
                    node->balance = -1;
                else
                    node->balance = 0;
                root = node1;
                node1->balance = 0;
            }
        }
    }
    TNode<T>* deleteFromTr(TNode<T>*& root, TNode<T>*& node, bool& h) {
        if (root->right != nullptr) {
            deleteFromTr(root->right, node, h);
            if (h)
                balanceR(root, h);
        }
        else {
            node->list = root->list;
            root = root->left;
            h = true;
        }
        return root;
    }

    TNode<T>* deleteFromTree(TNode<T>*& root, T num, bool& h) {
        if (root == nullptr)
            std::cout << "Tree is empty.";
        else if (getNodeValue(root) > num) {
            root->left = deleteFromTree(root->left, num, h);
            if (h)
                balanceL(root, h);
        }
        else if (getNodeValue(root) < num) {
            root->right = deleteFromTree(root->right, num, h);
            if (h)
                balanceR(root, h);
        }
        else if (nodeNumber(root->list) > 1) {
            deleteFromList(root);
            return root;
        }
        else {
            TNode<T>* node = root;
            if (node->right == nullptr) {
                root = node->left;
                h = true;
            }
            else if (node->left == nullptr) {
                root = node->right;
                h = true;
            }
            else {
                node->left = deleteFromTr(node->left, node, h);
                if (h)
                    balanceL(root, h);
            }
        }
        return root;
    }

    void deleteTree(TNode<T>*& node) {
        if (node != nullptr) {
            if (node->left)
                deleteTree(node->left);
            if (node->right)
                deleteTree(node->right);
            delete node;
        }
    }

    void printOnSide(int h, TNode<T>* node) {
        if (node != nullptr) {
            printOnSide(h + 8, node->right);
            for (int i = 0; i < h; ++i)
                std::cout << " ";
            std::cout << node->list->data << " " << nodeNumber(node->list) << std::endl;
            printOnSide(h + 8, node->left);
        }
    }

    void toStack(TNode<T>* a, std::stack<int>*& astack) {
        if (a != nullptr) {
            toStack(a->left, astack);
            astack->push(getNodeValue(a));
            toStack(a->right, astack);
        }
    }

    bool areEqual(TNode<T>* a, TNode<T>* b) {
        if (a == nullptr && b == nullptr)
            return true;
        if (a == nullptr ^ b == nullptr)
            return false;
        auto* astack = new std::stack<int>;
        auto* bstack = new std::stack<int>;
        toStack(a, astack);
        toStack(b, bstack);
        while (!astack->empty() && !bstack->empty()) {
            if (astack->top() != bstack->top())
                return false;
            astack->pop();
            bstack->pop();
        }
        return areEqual(a->left, b->left) && areEqual(a->right, b->right);
    }
};

#endif //INC_1_2_AVL_H