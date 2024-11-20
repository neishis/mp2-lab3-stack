#pragma once
#include <iostream>
#include <string>
#include "TStack.h"

class TCalc {

    string infix;
    string postfix;

    TStack<double> StNum;
    TStack<char> StOwn;

    int prior(char a);
public:

    void SetInfix(string inf) { infix = inf; };
    void SetPostfix(string post) { postfix = post; };
    string GetInfix() { return infix; };
    string GetPostfix() { return postfix; };

    TCalc();

    void ToPostfix();
    double CalcPostfix();
    double Calculate();
};



