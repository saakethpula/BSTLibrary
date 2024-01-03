
#include "BST.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

BST::BST() {
    root = NULL;
}

BST::BST(string title, string author, int yr, string pub, long long isbn, float rate) {
    root = new BSTNode(title, author, yr, pub, isbn, rate);
}


BST::~BST() {
    clearTree();
}

void BST::insert(string title, string author, int yr, string pub, long long isbn, float rate) {
    BSTNode *newNode = new BSTNode(title, author, yr, pub, isbn, rate);
    if (root == NULL) {
        root = newNode;
        return;
    } else {
        BSTNode *temp = root;
        bool set = false;
        while (!set) {
            if (*temp->book > *newNode->book) {
                if ( temp->left == NULL) {
                    temp->left = newNode;
                    newNode->parent = temp;
                    set = true;
                }else {
                    temp = temp->left;
                }
            }else if (*temp->book <= *newNode->book) {
                if (temp->right == NULL) {
                    temp->right = newNode;
                    newNode->parent = temp;
                    set = true;
                } else {
                    temp = temp->right;
                }
            }
        }
        setHeight(newNode);

    }
}

BSTNode *BST::find(string title, string author) {
    BSTNode *start = root;
    if (start == NULL) {
        return nullptr;
    }
    bool found = false;
    while (!found) {
        if (start == nullptr){
            return nullptr;
        } else if (start->book->title == title && start->book->author == author){
            found = true;
            return start;
        } else if (start->book->author >= author){
            start = start->left;
        } else if (start->book->author < author) {
            start = start->right;
        } else {
            return nullptr;
        }
    }
    return start;
}
BSTNode *BST::find(string title, string author, BSTNode *start) {
    bool found = false;
    while (!found) {
        if (start == nullptr){
            return nullptr;
        } else if (start->book->title == title && start->book->author == author){
            found = true;
            return start;
        } else if (start->book->author > author){
            start = start->left;
        } else if (start->book->author < author) {
            start = start->right;
        } else {
            return nullptr;
        }
    }
    return start;
}

void BST::printTreeIO() {
    if (root == NULL) {
        cout << "Empty Tree" << endl;
    }
    else {
        cout << endl << "Printing In-Order:" << endl;
        printTreeIO(root);
    }
}

void BST::printTreeIO(BSTNode *node) {
    if (node == NULL) {
        return;
    }
    printTreeIO(node->left);
    node->printNode(false);
    printTreeIO(node->right);
}


void BST::printTreePre() {
    if (root == NULL) {
        cout << "Empty Tree" << endl;
    }
    else {
        cout << endl << "Printing Pre-Order:" << endl;
        printTreePre(root);
    }
}

void BST::printTreePre(BSTNode *node) {
    if (node == nullptr){
        return;
    }
    node->printNode(false);
    printTreePre(node->left);
    printTreePre(node->right);
}

void BST::printTreePost() {
    if (root == NULL) {
        cout << "Empty Tree" << endl;
    }
    else {
        cout << endl<<"Printing Post-Order:" <<endl;
        printTreePost(root);
    }
}

void BST::printTreePost(BSTNode *node) {
    if (node == nullptr){
        return;
    }
    printTreePost(node->left);
    printTreePost(node->right);
    node->printNode(false);
}

void BST::clearTree() {
    if (root == NULL) {
        cout << "Tree already empty" << endl;
    }
    else {
        cout << endl << "Clearing Tree:" << endl;
        clearTree(root);
        root = NULL;
    }
}

void BST::clearTree(BSTNode *node) {
    if (node == NULL) {
        return;
    }
    else {
        clearTree(node->left);
        node->left = NULL;
        clearTree(node->right);
        node->right = NULL;
        node->printNode(true);
        delete node;
    }
}
bool BST::checkOut(string title, string author) {
    BSTNode *node = find(title, author);
    if (node == nullptr) {
        return false;
    }
    while (node != nullptr) {
        if (node->book->title == title && node->book->author == author && node->book->checked_out == false) {
            node->book->checked_out = true;
            return true;
        }

        if (node->book->title <= title && node->right != nullptr) {
            node = find(title, author, node->right);
        } else if (node->book->title >= title && node->left != nullptr) {
            node = find(title, author, node->left);
        } else {
            node = nullptr;
        }
    }

    return false;
}


bool BST::checkIn(string title, string author) {
    BSTNode *node = find(title, author);
    if (node == nullptr) {
        return false;
    }
    while (node != nullptr) {
        if (node->book->title == title && node->book->author == author && node->book->checked_out == true) {
            node->book->checked_out = false;
            return true;
        }

        if (node->book->title <= title && node->right != nullptr) {
            node = find(title, author, node->right);
        } else if (node->book->title >= title && node->left != nullptr) {
            node = find(title, author, node->left);
        } else {
            node = nullptr;
        }
    }

    return false;
}

void BST::updateRating(string title, string author, float newRating) {
    BSTNode *node = find(title, author);
    while (node != nullptr) {
        if (node->book->title == title && node->book->author == author) {
            node->book->rating = newRating;
        }
        if (node->book->title <= title && node->right != nullptr) {
            node = find(title, author, node->right);
        } else if (node->book->title >= title && node->left != nullptr) {
            node = find(title, author, node->left);
        } else {
            node = nullptr;
        }
    }
}


BSTNode *BST::removeNoKids(BSTNode *node) {
    if (node->left == NULL && node->right == NULL) {
        if (node->parent->left == node){
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
    }
    return node;
}



BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag) {
    BSTNode *newChild;
    if (leftFlag) {
        newChild = node->left;
    } else {
        newChild = node->right;
    }
    BSTNode *parent = node->parent;
    if (node == parent->left) {
        parent->left = newChild;
    } else {
        parent->right = newChild;
    }
    newChild->parent = parent;
    return parent;
}


BSTNode *BST::remove(string title, string author) {
    BSTNode *node = find(title, author);
    if (node == nullptr) {
        return nullptr;
    }
    BSTNode *temp = node;
    if (node == root) {
        if (node->left == nullptr && node->right == nullptr) {
            root = nullptr;  // The tree becomes empty
            return node;
        } else if (node->left != nullptr && node->right == nullptr) {
            root = node->left;
            node->left->parent = nullptr;
            return node;
        } else if (node->left == nullptr && node->right != nullptr) {
            root = node->right;
            node->right->parent = nullptr;
            return node;
        }
    }
    if (node->left == NULL && node->right == NULL) {
        if (node->parent->left == node && node->parent->right == NULL) {
            while (temp->parent != NULL) {
                if (node->parent->left == node && node->parent->right == NULL) {
                    temp->parent->height--;
                    temp = temp->parent;
                }
            }
            removeNoKids(node);
        } else if (node->parent->right == node && node->parent->left == NULL) {
            while (temp->parent != NULL) {
                if (node->parent->right == node && node->parent->left == NULL) {
                    temp->parent->height--;
                    temp = temp->parent;
                }
            }
            removeNoKids(node);
        } else {
            removeNoKids(node);
        }
    } else if (node->left != NULL && node->right == NULL) {
        setHeight(removeOneKid(node, true));
    } else if (node->left == NULL && node->right != NULL) {
        setHeight(removeOneKid(node, false));
    } else if (node->left != NULL && node->right != NULL) {
        if (node->parent != nullptr) {
            BSTNode* replacement = node->right;
            while (replacement->left != nullptr) {
                replacement = replacement->left;
            }
            if (replacement->parent->left == replacement) {
                replacement->parent->left = replacement->right;
            } else {
                replacement->parent->right = replacement->right;
            }
            if (replacement->right != nullptr) {
                replacement->right->parent = replacement->parent;
            }
            if (node->parent->left == node) {
                node->parent->left = replacement;
            } else {
                node->parent->right = replacement;
            }
            return node;
        } else if (node == root) {
            BSTNode *replacement = node->right;
            while (replacement->left != NULL) {
                replacement = replacement->left;
            }
            replacement->height = root->height;
            if (node->left == nullptr && node->right == nullptr) {
                root = nullptr;  // The tree becomes empty
                return node;
            } else if (node->left != nullptr && node->right == nullptr) {
                root = node->left;
                node->left->parent = nullptr;
                return node;
            } else if (node->left == nullptr && node->right != nullptr) {
                root = node->right;
                node->right->parent = nullptr;
                return node;
            } else {
                BSTNode *replacement = node->right;
                while (replacement->left != nullptr) {
                    replacement = replacement->left;
                }
                if (replacement != node->right) {
                    replacement->parent->left = replacement->right;
                    if (replacement->right != nullptr) {
                        replacement->right->parent = replacement->parent;
                    }
                    replacement->right = node->right;
                    node->right->parent = replacement;
                }
                replacement->left = node->left;
                node->left->parent = replacement;
                root = replacement;
                replacement->parent = nullptr;
            }
        }
    }
    return node;
}
void BST::setHeight(BSTNode *node) {
    bool done = false;
    while (!done) {
        int lefth = 0;
        int righth = 0;
        if (node->left != NULL) {
            lefth = node->left->height;
        }
        if (node->right != NULL) {
            righth = node->right->height;
        }
        int temp;
        if (lefth > righth) {
            temp = lefth;
        } else {
            temp = righth;
        }
        node->height = temp + 1;
        if (node == root) {
            done = true;
        }
        node = node->parent;
    }
}