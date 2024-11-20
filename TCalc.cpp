#include "TCalc.h"
#include <iostream>
#include "TStack.h"

int TCalc::prior(char a)
{
    if (a == '^')
        return 3;
    else if (a == '*' || a == '/')
        return 2;
    else if (a == '+' || a == '-')
        return 1;
    return 0;
}

TCalc::TCalc()
{
    TStack<double> StNum;
    TStack<char> StOwn;
}

void TCalc::ToPostfix()
{
    postfix = "";
    StOwn.clear();

    string str = "(" + infix + ")";
    if (!StOwn.checkThrow(infix)) {
        throw - 1;
    }
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            StOwn.push('(');
        }

        else if (str[i - 1] == '(' && str[i] == '-') {
            postfix += '_';
        }
        else if (isdigit(str[i]) || str[i] == '.') {
            postfix += str[i];
        }

        else if (str[i] == ')') {
            char a = StOwn.pop();
            while (a != '(') {
                postfix += a;
                postfix += ' ';
                a = StOwn.pop();
            }
        }

        else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^')
        {
            while (prior(StOwn.top()) >= prior(str[i]))
                postfix += StOwn.pop();
            StOwn.push(str[i]);
        }
        else
            throw - 1;
    }
    if (StOwn.empty() == 0)
        throw - 1;
}

double TCalc::Calculate() {
    string str = "(" + infix + ")";
    StNum.clear();
    StOwn.clear();
    if (!StOwn.checkThrow(infix)) {
        throw - 1;
    }
    for (int i = 0; i < str.size(); i++) {
        char tmp = str[i];
        if (tmp == '(') {
            StOwn.push(tmp);
        }
        else if (str[i - 1] == '(' && tmp == '-') {
            str[i] = '_';
        }
        else if (i > 0 && tmp >= '0' && tmp <= '9' && str[i - 1] == '_')
        {
            size_t idx;
            double num = stod(&tmp, &idx);
            StNum.push(num * (-1.0));
            i += idx - 1;
        }
        else if (tmp >= '0' && tmp <= '9' || tmp == '.') {
            size_t idx;
            double num = stod(&tmp, &idx);
            StNum.push(num);
            i += idx - 1;
        }
        if (tmp == ')') {
            char a = StOwn.pop();
            while (a != '(') {
                double secondNum = StNum.pop();
                double firstNum = StNum.pop();
                if (a == '+') StNum.push(firstNum+secondNum);
                if (a == '-') StNum.push(firstNum - secondNum);
                if (a == '*') StNum.push(firstNum * secondNum);
                if (a == '/') {
                    if (secondNum == 0) {
                        throw string("division by 0");
                    }
                    StNum.push(firstNum / secondNum);
                }
                if (a == '^') {
                    double res = 1;
                    for (int i = 0; i < secondNum; i++) {
                        res = res * firstNum;
                    }
                    StNum.push(res);
                }
                a = StOwn.pop();
            }
        }
        if (tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/' || tmp == '^') {
            while (prior(StOwn.top()) >= prior(tmp)) {
                double secondNum = StNum.pop();
                double firstNum = StNum.pop();
                char a = StOwn.pop();
                if (a == '+') StNum.push(firstNum + secondNum); 
                if (a == '-') StNum.push(firstNum - secondNum);
                if (a == '*') StNum.push(firstNum * secondNum);
                if (a == '/') {
                    if (secondNum == 0) {
                        throw string("division by 0");
                    }
                    StNum.push(firstNum / secondNum);
                }
                if (a == '^') {
                    double res = 1;
                    for (int i = 0; i < secondNum; i++) {
                        res = res * firstNum;
                    }
                    StNum.push(res);
                }
            }
            StOwn.push(tmp);
        }
    }
    if (StNum.empty() == 0)
        throw - 1;
    return (StNum.pop());
}

double TCalc::CalcPostfix()
{
    StNum.clear();
    for (int i = 0; i < postfix.size(); i++) {
        if (i > 0 && postfix[i] >= '0' && postfix[i] <= '9' && postfix[i - 1] == '_')
            StNum.push((postfix[i] - '0') * (-1));
        else if (postfix[i] >= '0' && postfix[i] <= '9') {
            StNum.push(postfix[i] - '0');
        }
        else {
            double secondNum = StNum.pop();
            double firstNum = StNum.pop();
            switch (postfix[i]) {
            case '+':
                StNum.push(firstNum + secondNum);
                break;
            case '-':
                StNum.push(firstNum - secondNum);
                break;
            case '*':
                StNum.push(firstNum * secondNum);
                break;
            case '/':
                StNum.push(firstNum / secondNum);
                break;
            case '^':
                double res = 1;
                for (int i = 0; i < secondNum; i++) {
                    res = res * firstNum;
                }
                StNum.push(res);
                break;
            }
        }
    }
    if (!(StNum.empty())) {
        throw string ("Stack isn't empty");
    }
    return StNum.pop();
    
}