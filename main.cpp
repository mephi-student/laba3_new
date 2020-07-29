#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "binarytree.hpp"
#include "binarytree.cpp"
#include "functions.cpp"
#include "functions.hpp"

#include <random>

double randDouble(double n1, double n2) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(n1, n2);
    return dist(mt);
}

int randInt(int n1, int n2) {
    return round(randDouble(n1, n2));
}

std::string randString(int n1, int n2) {
    int N = randInt(n1, n2);
    std::string buf = "abcdefghijklmnopqrstuvwxyz";
    std::string result = "";
    for (int i = 0; i < N; i++) {
        result += buf[randInt(0, sizeof(buf) - 1)];
    }
    return result;
}


TEST_CASE("Test binary tree random INT") {
    /* Тестируется создание древа через заполнение случайными числами */
    Tree<int> tree;

    for (int i = 0; i < 100; ++i) {
        tree.push(randInt(-100, 100));
    }

    SECTION("Test length") {
        CHECK(tree.getLength() == 100);
    }

    SECTION("Test push") {
        CHECK(tree.getLength() == 100);
        tree.push(randInt(-100, 100));
        CHECK(tree.getLength() == 101);
    }

    SECTION("Test delete") {
        int number = randInt(-100, 100);
        CHECK(tree.getLength() == 100);
        tree.push(number);
        CHECK(tree.getLength() == 101);
        tree.deleteNode(number);
        CHECK(tree.getLength() == 100);
    }

    SECTION("Test check") {
        CHECK(tree.getLength() == 100);
        tree.push(0);
        CHECK(tree.getLength() == 101);
        CHECK(tree.checkPresence(0) == true);
    }
}


TEST_CASE("Test binary tree random DOUBLE") {
    /* Тестируется создание древа через заполнение случайными числами */
    Tree<double> tree;

    for (double i = 0; i < 100; ++i) {
        tree.push(randDouble(-100, 100));
    }

    SECTION("Test length") {
        CHECK(tree.getLength() == 100);
    }

    SECTION("Test push") {
        CHECK(tree.getLength() == 100);
        tree.push(randDouble(-100, 100));
        CHECK(tree.getLength() == 101);
    }

    SECTION("Test delete") {
        double number = randDouble(-100, 100);
        CHECK(tree.getLength() == 100);
        tree.push(number);
        CHECK(tree.getLength() == 101);
        tree.deleteNode(number);
        CHECK(tree.getLength() == 100);
    }

    SECTION("Test check") {
        double number = randDouble(-100, 100);
        CHECK(tree.getLength() == 100);
        tree.push(number);
        CHECK(tree.getLength() == 101);
        CHECK(tree.checkPresence(number) == true);
    }
}


TEST_CASE("Test binary tree random STRING") {
    /* Тестируется создание древа через заполнение случайными числами */
    Tree<std::string> tree;

    for (int i = 0; i < 100; ++i) {
        tree.push(randString(10, 20));
    }

    SECTION("Test length") {
        CHECK(tree.getLength() == 100);
    }

    SECTION("Test push") {
        CHECK(tree.getLength() == 100);
        tree.push(randString(-100, 100));
        CHECK(tree.getLength() == 101);
    }

    SECTION("Test delete") {
        std::string str = randString(10, 20);
        CHECK(tree.getLength() == 100);
        tree.push(str);
        CHECK(tree.getLength() == 101);
        tree.deleteNode(str);
        CHECK(tree.getLength() == 100);
    }

    SECTION("Test check") {
        std::string str = randString(10, 20);
        CHECK(tree.getLength() == 100);
        tree.push(str);
        CHECK(tree.getLength() == 101);
        CHECK(tree.checkPresence(str) == true);
    }
}



TEST_CASE("Test binary tree fixed INT") {
    std::vector<int> data = {4, 10, 1, 13, 43, 19, 12, 3};

    Tree<int> tree;

    for (auto i : data) {
        tree.push(i);
    }

    SECTION("Test getLength") {
        CHECK(tree.getLength() == 8);
    }

    SECTION("Test traverse") {
        CHECK(tree.getStringPLK() == "19 43 12 13 10 3 1 4 ");
        CHECK(tree.getStringKLP() == "4 1 3 10 13 12 43 19 ");
    }

    SECTION("Test checkPresence key") {
        for (auto i : data) {
            CHECK(tree.checkPresence(i) == true);
        }
        CHECK(tree.checkPresence(-42342) == false);
    }

    SECTION("Test checkPresence tree") {
        std::vector<int> newData = {13, 12, 43, 19};
        Tree<int> newTree;
        for (auto i : newData) {
            newTree.push(i);
        }
        CHECK(tree.checkPresence(newTree) == true);
        newTree.push(342);
        CHECK(tree.checkPresence(newTree) == false);
    }

    SECTION("Test getSubtree") {
        Tree<int> subtree = tree.getSubTree(10);
        CHECK(subtree.getStringPLK() == "19 43 12 13 10 ");
        CHECK(subtree.getStringKLP() == "10 13 12 43 19 ");
        CHECK(subtree.getLength() == 5);
    }

    SECTION("Test map 1") {
        Tree<int> mapped = tree.map(intPlusOne);
        CHECK(mapped.getStringPLK() == "20 44 13 14 11 4 2 5 ");
        CHECK(mapped.getStringKLP() == "5 2 4 11 14 13 44 20 ");
    }

    SECTION("Test map 2") {
        Tree<int> mapped = tree.map(intMinusTen);
        CHECK(mapped.getStringPLK() == "9 33 2 3 0 -7 -9 -6 ");
        CHECK(mapped.getStringKLP() == "-6 -9 -7 0 3 2 33 9 ");
    }

    SECTION("Test where 1") {
        Tree<int> whered = tree.where(intIfEven);
        CHECK(whered.getStringPLK() == "12 10 4 ");
        CHECK(whered.getStringKLP() == "4 10 12 ");
        CHECK(whered.getLength() == 3);
    }

    SECTION("Test where 2") {
        Tree<int> whered = tree.where(intIfOdd);
        CHECK(whered.getStringPLK() == "19 43 13 3 1 ");
        CHECK(whered.getStringKLP() == "1 3 13 43 19 ");
        CHECK(whered.getLength() == 5);
    }

    SECTION("Test compareTrees") {
        Tree<int> newTree;
        for (auto i : data) {
            newTree.push(i);
        }
        CHECK(tree.compareTrees(newTree) == true);

        newTree.deleteNode(10);
        CHECK(tree.compareTrees(newTree) == false);
    }
}


TEST_CASE("Test binary tree fixed DOUBLE") {
    std::vector<double> data = {4.2, 10.4, 1.5, 13.1, 43.8, 19.6, 12.9, 3.3};

    Tree<double> tree;

    for (auto i : data) {
        tree.push(i);
    }

    SECTION("Test getLength") {
        CHECK(tree.getLength() == 8);
    }

    SECTION("Test traverse") {
        CHECK(tree.getStringPLK() == "19.6 43.8 12.9 13.1 10.4 3.3 1.5 4.2 ");
        CHECK(tree.getStringKLP() == "4.2 1.5 3.3 10.4 13.1 12.9 43.8 19.6 ");
    }

    SECTION("Test checkPresence key") {
        for (auto i : data) {
            CHECK(tree.checkPresence(i) == true);
        }
        CHECK(tree.checkPresence(-423.42) == false);
    }

    SECTION("Test checkPresence tree") {
        std::vector<double> newData = {13.1, 12.9, 43.8, 19.6};
        Tree<double> newTree;
        for (auto i : newData) {
            newTree.push(i);
        }
        CHECK(tree.checkPresence(newTree) == true);
        newTree.push(342.2);
        CHECK(tree.checkPresence(newTree) == false);
    }

    SECTION("Test getSubtree") {
        Tree<double> subtree = tree.getSubTree(10.4);
        CHECK(subtree.getStringPLK() == "19.6 43.8 12.9 13.1 10.4 ");
        CHECK(subtree.getStringKLP() == "10.4 13.1 12.9 43.8 19.6 ");
        CHECK(subtree.getLength() == 5);
    }

    SECTION("Test map 1") {
        Tree<double> mapped = tree.map(doublePlusOne);
        CHECK(mapped.getStringPLK() == "20.6 44.8 13.9 14.1 11.4 4.3 2.5 5.2 ");
        CHECK(mapped.getStringKLP() == "5.2 2.5 4.3 11.4 14.1 13.9 44.8 20.6 ");
    }

    SECTION("Test map 2") {
        Tree<double> mapped = tree.map(doubleMinusTen);
        CHECK(mapped.getStringPLK() == "9.6 33.8 2.9 3.1 0.4 -6.7 -8.5 -5.8 ");
        CHECK(mapped.getStringKLP() == "-5.8 -8.5 -6.7 0.4 3.1 2.9 33.8 9.6 ");
    }

    SECTION("Test where 1") {
        Tree<double> whered = tree.where(doubleIfLargerThanTen);
        CHECK(whered.getStringPLK() == "19.6 43.8 12.9 13.1 10.4 ");
        CHECK(whered.getStringKLP() == "10.4 13.1 12.9 43.8 19.6 ");
        CHECK(whered.getLength() == 5);
    }

    SECTION("Test where 2") {
        Tree<double> whered = tree.where(doubleIfLesserThanFive);
        CHECK(whered.getStringPLK() == "3.3 1.5 4.2 ");
        CHECK(whered.getStringKLP() == "4.2 1.5 3.3 ");
        CHECK(whered.getLength() == 3);
    }

    SECTION("Test compareTrees") {
        Tree<double> newTree;
        for (auto i : data) {
            newTree.push(i);
        }
        CHECK(tree.compareTrees(newTree) == true);

        newTree.deleteNode(10.4);
        CHECK(tree.compareTrees(newTree) == false);
    }
}


TEST_CASE("Test binary tree fixed STRING") {
    std::vector<std::string> data = {"father", "MOTHER", "sister", "BROTHER", "book", "ham", "priEST", "government"};

    Tree<std::string> tree;

    for (auto i : data) {
        tree.push(i);
    }

    SECTION("Test getLength") {
        CHECK(tree.getLength() == 8);
    }

    SECTION("Test traverse") {
        CHECK(tree.getStringPLK() == "priEST government ham sister book BROTHER MOTHER father ");
        CHECK(tree.getStringKLP() == "father MOTHER BROTHER book sister ham government priEST ");
    }

    SECTION("Test checkPresence key") {
        for (auto i : data) {
            CHECK(tree.checkPresence(i) == true);
        }
        CHECK(tree.checkPresence("severity") == false);
    }

    SECTION("Test checkPresence tree") {
        std::vector<std::string> newData = {"ham", "priEST", "government"};
        Tree<std::string> newTree;
        for (auto i : newData) {
            newTree.push(i);
        }
        CHECK(tree.checkPresence(newTree) == true);
        newTree.push("chak chak");
        CHECK(tree.checkPresence(newTree) == false);
    }

    SECTION("Test getSubtree") {
        Tree<std::string> subtree = tree.getSubTree("sister");
        CHECK(subtree.getStringPLK() == "priEST government ham sister ");
        CHECK(subtree.getStringKLP() == "sister ham government priEST ");
        CHECK(subtree.getLength() == 4);
    }

    SECTION("Test map 1") {
        Tree<std::string> mapped = tree.map(stringChangeRegister);
        CHECK(mapped.getStringPLK() == "brother PRIest GOVERNMENT HAM SISTER mother BOOK FATHER ");
        CHECK(mapped.getStringKLP() == "FATHER BOOK mother SISTER HAM GOVERNMENT PRIest brother ");
    }

    SECTION("Test map 2") {
        Tree<std::string> mapped = tree.map(stringMakeLoud);
        CHECK(mapped.getStringPLK() == "priEST! government! ham! sister! book! BROTHER! MOTHER! father! ");
        CHECK(mapped.getStringKLP() == "father! MOTHER! BROTHER! book! sister! ham! government! priEST! ");
    }

    SECTION("Test where 1") {
        Tree<std::string> whered = tree.where(stringIfLargerThanEight);
        CHECK(whered.getStringPLK() == "government ");
        CHECK(whered.getStringKLP() == "government ");
        CHECK(whered.getLength() == 1);
    }

    SECTION("Test where 2") {
        Tree<std::string> whered = tree.where(stringIfLesserThanSix);
        CHECK(whered.getStringPLK() == "ham book ");
        CHECK(whered.getStringKLP() == "book ham ");
        CHECK(whered.getLength() == 2);
    }

    SECTION("Test compareTrees") {
        Tree<std::string> newTree;
        for (auto i : data) {
            newTree.push(i);
        }
        CHECK(tree.compareTrees(newTree) == true);

        newTree.deleteNode("book");
        CHECK(tree.compareTrees(newTree) == false);
    }
}
