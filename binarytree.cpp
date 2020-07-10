#include <queue>
#include "binarytree.hpp"

//изменение данных в ноде
template <typename T>
void Tree<T>::Node::changeData(T newData) {
    data = newData;
}

//вставка элемента в дерево
template <typename T>
void Tree<T>::Node::push(Node *&root, T data) {
    //если нода пустая
    if (root == nullptr) {
        root = new Node;
        root->data = data;
        root->left = root->right = nullptr;
    }
    //если в ноде есть значения
    else if (data > root->data) {
        root->push(root->right, data);
    }
    else {
        root->push(root->left, data);
    }
}

//копирование нод
template <typename T>
void Tree<T>::Node::copyNode(Node *&target, Node *root) {
    if (root != nullptr) {
        target = new Node;
        target->data = root->data;
        target->left = target->right = nullptr;
        target->left->copyNode(target->left, root->left);
        target->right->copyNode(target->right, root->right);
    }
}

//получение строки в виде заданного обхода
template <typename T>
void Tree<T>::Node::setStringPLK(Node *&root, std::stringstream &buff) {
    if (root != nullptr) {
        root->setStringPLK(root->right, buff);
        root->setStringPLK(root->left, buff);
        buff << root->data << " ";
    }
}

template <typename T>
void Tree<T>::Node::setStringKLP(Node *&root, std::stringstream &buff) {
    if (root != nullptr) {
        buff << root->data << " ";
        root->setStringKLP(root->left, buff);
        root->setStringKLP(root->right, buff);
    }
}

//удаление поддерева
template <typename T>
void Tree<T>::Node::deleteNode(Node *&root, T key) {
    if (root != nullptr) {
        if  (root->data == key) {
            root->cleanMemory(root);
        }
        else {
            root->right->deleteNode(root->right, key);
            root->left->deleteNode(root->left, key);
        }
    }
}

//очистка памяти
template <typename T>
void Tree<T>::Node::cleanMemory(Node *&root) {
    if (root != nullptr) {
        root->right->cleanMemory(root->right);
        root->left->cleanMemory(root->left);
        delete root;
        root = nullptr;
    }
}

//получение поддерева
template <typename T>
typename Tree<T>::Node* Tree<T>::Node::getSubTree(Node *&root, T key) {
    Node *var = nullptr;
    var->assembleTree(var, root, key);
    return var;
}

//помощь в получении поддерева
template <typename T>
void Tree<T>::Node::assembleTree(Node *&var, Node *root, T key) {
    if (root != nullptr) {
        if (root->data == key) {
            var->copyNode(var, root);
        }
        else {
            var->assembleTree(var, root->right, key);
            var->assembleTree(var, root->left, key);
        }
    }
}

//проверка наличия элемента
template <typename T>
void Tree<T>::Node::checkPresence(Node *root, T key, bool &check) {
    if (root != nullptr) {
        if (root->data == key) {
            check = true;
        }
        else {
            root->right->checkPresence(root->right, key, check);
            root->left->checkPresence(root->left, key, check);
        }
    }
}

//сравнение деревьев
template <typename T>
void Tree<T>::Node::compareNodes(Node *root1, Node *root2, bool &check, bool &type) {
    if (root1 && root2) {
        if (root1->data == root2->data) {
            if (type == true)
                return;
            check = true;
            if ((root1->right && root2->right) || (!root1->right && !root2->right))
                root1->right->compareNodes(root1->right, root2->right, check, type);
            else {
                check = false;
                type = true;
                return;
            }
            if ((root1->left && root2->left) || (!root1->left && !root2->left))
                root1->left->compareNodes(root1->left, root2->left, check, type);
            else {
                check = false;
                type = false;
                return;
            }
        }
        else {
            check = false;
            type = true;
        }
    }
}

//проверка наличия поддерева
template <typename T>
void Tree<T>::Node::checkNodePresence(Node *root1, Node *root2, bool &check) {
    if (root2 != nullptr) {
        if (root1->data == root2->data) {
            bool type = false;
            root1->compareNodes(root1, root2, check, type);
        }
        root2->right->checkNodePresence(root1, root2->right, check);
        root2->left->checkNodePresence(root1, root2->left, check);
    }
}

//слияние деревьев
template <typename T>
void Tree<T>::Node::addNode(Node *&target, Node *root) {
    if (target == nullptr) {
        target->copyNode(target, root);
    }
    else if (root->data > target->data) {
        target->right->addNode(target->right, root);
    }
    else {
        target->left->addNode(target->left, root);
    }
}

//map
template <typename T>
void Tree<T>::Node::map(Node *&root, T (*f)(const T& data), Tree<T> &target) {
    Node* ptr = root;
    std::queue<Node*> queue;
    queue.push(ptr);
    while (queue.size() != 0) {
        Node* next = queue.front();
        target.push(f(next->getData()));
        queue.pop();
        if (next->left) {
            queue.push(next->left);
        }
        if (next->right) {
            queue.push(next->right);
        }
    }
}

//where
template <typename T>
void Tree<T>::Node::where(Node *root, bool (*f)(const T& data), Tree<T> &target) {
    Node* ptr = root;
    std::queue<Node*> queue;
    queue.push(ptr);
    while (queue.size() != 0) {
        Node* next = queue.front();
        if (f(next->getData()))
            target.push(next->getData());
        queue.pop();
        if (next->left) {
            queue.push(next->left);
        }
        if (next->right) {
            queue.push(next->right);
        }
    }
}




template <typename T>
Tree<T>::Tree(Tree<T>::Node *node) {
    this->root = nullptr;
    this->length = 0;
    Node* ptr = node;
    std::queue<Node*> queue;
    queue.push(ptr);
    while (queue.size() != 0) {
        Node* next = queue.front();
        this->push(next->getData());
        queue.pop();
        if (next->left) {
            queue.push(next->left);
        }
        if (next->right) {
            queue.push(next->right);
        }
    }
}

//методы для деревьев
template <typename T>
void Tree<T>::push(const T& data) {
    this->length++;
    root->push(root, data);
}

template <typename T>
void Tree<T>::addTree(const Tree<T>& tree) {
    root->addNode(root, tree.root);
}

template <typename T>
typename Tree<T>::Node* Tree<T>::getRoot() {
    return root;
}

template <typename T>
int Tree<T>::getLength() const {
    return this->length;
}

template <typename T>
Tree<T> Tree<T>::map(T (*f)(const T& data)) {
    Tree<T> target;
    root->map(root, f, target);
    return target;
}

template <typename T>
Tree<T> Tree<T>::where(bool (*f)(const T& data)) {
    Tree<T> target;
    root->where(root, f, target);
    return target;
}

template <typename T>
void Tree<T>::deleteNode(T key) {
    this->length--;
    root->deleteNode(root, key);
}

template <typename T>
std::string Tree<T>::getStringPLK() {
    std::stringstream buff;
    root->setStringPLK(root, buff);
    return buff.str();
}

template <typename T>
std::string Tree<T>::getStringKLP() {
    std::stringstream buff;
    root->setStringKLP(root, buff);
    return buff.str();
}

template <typename T>
Tree<T> Tree<T>::getSubTree(const T& key) {
    return Tree<T>(this->root->getSubTree(this->root, key));
}

template <typename T>
void Tree<T>::deleteTree() {
    root->cleanMemory(root);
}

template <typename T>
bool Tree<T>::checkPresence(const T& key) const {
    bool check = false;
    root->checkPresence(root, key, check);
    return check;
}

template <typename T>
bool Tree<T>::compareTrees(const Tree<T>& tree) const {
    bool check = false;
    bool type = false;
    root->compareNodes(root, tree.root, check, type);
    return check;
}

template <typename T>
bool Tree<T>::checkPresence(const Tree<T>& tree) const {
    bool check = false;
    root->checkNodePresence(tree.root, root, check);
    return check;
}

template <typename T>
Tree<T>::~Tree() {
    root->cleanMemory(root);
}
