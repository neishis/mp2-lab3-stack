#include "TStack.h"
#include "TCalc.h"
#include <iostream>
using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");
    TStack<int> st(5);
    st.push(2);
    st.push(3);
    st.push(4);

    cout << "Стек: ";
    cout << st << endl;
    cout << "////////////" << endl;


    TCalc c;


    c.SetInfix("(1 + 2 * (2 - 1 / 4) + 6)* (5 + 6 * 9 - (1 + 2))");
   
    cout << "Инфикс: " << c.GetInfix() << endl;
    c.ToPostfix();
    cout << "Постфикс: " << c.GetPostfix() << endl;
    double res = c.Calc();
    cout << "Результат: " << res << endl;
}
