#ifndef functions_hpp
#define functions_hpp

#include <iostream>
#include "binarytree.hpp"

// map

int intPlusOne(const int& num);
int intMinusTen(const int& num);

double doublePlusOne(const double& num);
double doubleMinusTen(const double& num);

std::string stringChangeRegister(const std::string& str);
std::string stringMakeLoud(const std::string& str);

// where

bool intIfEven(const int& num);
bool intIfOdd(const int& num);

bool doubleIfLargerThanTen(const double& num);
bool doubleIfLesserThanFive(const double& num);

bool stringIfLargerThanEight(const std::string& str);
bool stringIfLesserThanSix(const std::string& str);

#endif
