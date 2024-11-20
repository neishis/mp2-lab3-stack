#pragma once
#include <iostream>
#include <string>
//          ЧТО С ПОМОЩЬЮ ТАКОГО СТЕКА МОЖНО СДЕЛАТЬ?
/*
Проверить в (2+2)*2 правильность расстановки скобок
bool Check(string st2){
TStack<char> s;
bool res=true;
for(int i=0;i<st2.size)+();i++){
if (st2[i]=='(')s.push'(');
if(st2[i]==')'){
if(s.epmty())return false; s.pop();
}
}
if(!s.empty()) return false;
return true;
}




*/
using namespace std;

const int MAX_STACK_SIZE = 10000;
//+-*^/ как доп задание-функции, могут быть скобки, вычислить выражение заданной строки

template <class T>
class TStack {
    T* pMem;
    int MaxSize, Num;
public:
    TStack(int _MaxSize=10);
    ~TStack();
    TStack(const TStack& st);

    TStack& operator =(const TStack<T>& st);
    bool operator == (TStack<T>& st);
    bool operator != (TStack<T>& st);

    bool empty() const;
    bool full() const;
    T getNum();

    T pop();
    T top() const;
    void push(T val);
    void clear();
    bool checkThrow(string str);
};

//Конструктор
template <class T>
TStack<T>::TStack(int _MaxSize) {
    if (_MaxSize<0 || _MaxSize>MAX_STACK_SIZE) throw string("incorrect size");
    MaxSize = _MaxSize;
    Num = -1;
    pMem = new T[MaxSize];
}

//Деструктор
template <class T>
TStack<T>::~TStack() {
    delete[] pMem;
}

//Конструктор копирования
template<class T>
TStack<T>::TStack(const TStack<T>& st) {
    MaxSize = st.MaxSize;
    Num = st.Num;
    pMem = new T[MaxSize];
    for (int i = 0; i < Num; i++) {
        pMem[i] = st.pMem[i];
    }
}

//Оператор присваивания
template<class T>
TStack<T>& TStack<T>::operator =(const TStack<T>& st)
{
    if (this != &st) {
        if (MaxSize != st.MaxSize) {
            MaxSize = st.MaxSize;
            delete[] pMem;
            pMem = new T[MaxSize];
        }
        Num = st.Num;
        for (int i = 0; i < Num; i++) pMem[i] = st.pMem[i];
    }
    return *this;
}

//Операторы сравнения
template<class T>
bool TStack<T>::operator==(TStack<T>& st)
{
    if (this == &st) return true;
    if (MaxSize != st.MaxSize || Num != st.Num) return false;
    for (int i = 0; i < Num; i++) {
        if (pMem[i] != st.pMem[i]) return false;
    }
    return true;
}

template<class T>
bool TStack<T>::operator!=(TStack<T>& st)
{
    return !(*this==st);
}

//Проверка на полноту
template<class T>
bool TStack<T>::full() const
{
    if (Num == ((MaxSize) - 1)) return true;
    return false;
}

//Проверка на пустоту
template<class T>
bool TStack<T>::empty() const
{
    if (Num == -1) return true;
    return false;
}

//Удаление последнего элемента из стека
template<class T>
T TStack<T>::pop() {
    if (this->empty()) throw string ("Stack is empty");
    T tmp = pMem[Num];
    Num--;
    return tmp;
}

template<class T>
T TStack<T>::top() const
{
    return pMem[Num];
}

//Добавление элемента в стек
template<class T>
void TStack<T>::push(T val) {
    if (this->full()) throw string("Stack is full");
    Num++;
    pMem[Num] = val;
}

template<class T>
 void TStack<T>::clear()
{
     Num = -1;
}

 template <class T>
 T TStack<T>::getNum()
 {
     return pMem[Num];
 }

 template <class T>
 bool TStack<T>::checkThrow(string str)
 {
     TStack<char> s;
     for (char ch : str)
     {
         if (ch == '(')
             s.push('(');
         else if (ch == ')')
         {
             if (s.empty())
                 return false;
             s.pop();
         }
     }
     return s.empty();
 }

