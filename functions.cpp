#include "functions.hpp"

/*map functions*/

//int

int intPlusOne(const int& num) {
    return num + 1;
}

int intMinusTen(const int& num) {
    return num - 10;
}

//double

double doublePlusOne(const double& num) {
    return num + 1;
}

double doubleMinusTen(const double& num) {
    return num - 10;
}

//string

std::string stringChangeRegister(const std::string& str) {
    int i = 0;
    std::string u = str;
    while (u[i] != '\0') {
        if (isupper(u[i])) {
            u[i] = tolower(u[i]);
        }
        else if (isupper(u[i]) == 0) {
            u[i] = toupper(u[i]);
        }
        i++;
    }
    return u;
}

std::string stringMakeLoud(const std::string& str) {
    std::string u = str;
    u += '!';
    return u;
}

/*Where functions*/

//int

bool intIfEven(const int& num) {
    if (num % 2 == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool intIfOdd(const int& num) {
    if (num % 2 != 0) {
        return true;
    }
    else {
        return false;
    }
}

//double

bool doubleIfLargerThanTen(const double& num) {
    if (num > 10) {
        return true;
    }
    else {
        return false;
    }
}

bool doubleIfLesserThanFive(const double& num) {
    if (num < 5) {
        return true;
    }
    else {
        return false;
    }
}

//string

bool stringIfLargerThanEight(const std::string& str) {
    int i = 0;
    std::string u = str;
    while (u[i] != '\0') {
        i++;
    }
    if (i + 1 > 8) {
        return true;
    }
    else {
        return false;
    }
}

bool stringIfLesserThanSix(const std::string& str) {
    int i = 0;
    std::string u = str;
    while (u[i] != '\0') {
        i++;
    }
    if (i + 1 < 6) {
        return true;
    }
    else {
        return false;
    }
}
