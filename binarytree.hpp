#ifndef binarytree_hpp
#define binarytree_hpp

#include <string>
#include <iostream>
#include <typeinfo>
#include <sstream>

template <typename T> // Tree class как оболочка над нодой
class Tree {
private:
    class Node { // инкапсулированный класс ноды
    public:
        T data;
        Node *left, *right;
        
        Node() {
            left = right = nullptr;
        };
    public:
        T getData() const {
            return data;
        }
        void changeData(T newData);
        void push(Node *&root, T data);
        void cleanMemory(Node *&root);
        void deleteNode(Node *&root, T key);
        Node* getSubTree(Node *&root, T key);
        void assembleTree(Node *&var, Node *root, T Key);
        void copyNode(Node *&target, Node *root);
        void setStringPLK(Node *&root, std::stringstream &buff);
        void setStringKLP(Node *&root, std::stringstream &buff);
        void checkPresence(Node *root, T key, bool &check);
        void compareNodes(Node *root1, Node *root2, bool &check, bool &type);
        void checkNodePresence(Node *root1, Node *root2, bool &check);
        void addNode(Node *&target, Node *root);
        void map(Node *&root, T (*f)(const T& data), Tree<T> &target);
        void where(Node *root, bool (*f)(const T& data), Tree<T> &target);
    };
private:
    Node *root;
    int length;
private:
    void deleteTree();
    Tree(Node *node);
public:
    Tree() { root = nullptr; length = 0; };
    void push(const T& data); // добавление элемента в дерево
    void addTree(const Tree<T>& tree); // слияние деревьев БЕЗ ПЕРЕБАЛАНСИРОВКИ, т.е. просто по корню
    Tree<T> map(T (*f)(const T& data)); // применить map-функцию
    Tree<T> where(bool (*f)(const T& data)); // применить where-функцию
    void deleteNode(T key); //удаление вершины
    std::string getStringPLK(); // получить строку обхода ПЛК
    std::string getStringKLP(); // получить строку обхода КЛП
    Node* getRoot(); // получить корневой элемент
    int getLength() const; // получить количество элементов
    Tree<T> getSubTree(const T& key); // получить поддерево
    bool checkPresence(const T& key) const; // проверить вхождение вершины в дерево
    bool compareTrees(const Tree<T>& tree) const; // сравнение деревьев поэлементно
    bool checkPresence(const Tree<T>& tree) const; // проверить вхождение дерева в дерево
    ~Tree();
};



#endif
