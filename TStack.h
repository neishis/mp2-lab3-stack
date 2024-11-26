#pragma once
#include <iostream>
#include <string>

using namespace std;

const int MAX_STACK_SIZE = 10000;


template <class T>
class TStack {
    T* pMem;
    int MaxSize, Num;
public:
    TStack(int _MaxSize=10);
    ~TStack();
    TStack(const TStack& st);

    TStack& operator =(const TStack<T>& st);
    bool operator == (const TStack& st) const;
    bool operator != (const TStack& st) const;

    bool empty() const;
    bool full() const;
    int getNum();

    T pop();
    T top() const;
    void push(T val);
    void clear();
    bool checkThrow(string str);

    // Ввод элемента в стек
    friend istream& operator>>(istream& in, TStack& s)
    {
        T val;
        cout << "Введите элементы стека (введите 0 для завершения): ";
        while (in >> val && val != 0) {
            s.Push(val);
        }
        return in;
    }

    // Вывод элемента из стека
    friend ostream& operator<<(ostream& out, const TStack& s)
    {
        for (int i = 0; i <= s.Num; i++) {
            out << s.pMem[i] << " ";
        }
        return out;
    }
};


template <class T>
TStack<T>::TStack(int _MaxSize) {
    if (_MaxSize<0 || _MaxSize>MAX_STACK_SIZE) throw string("incorrect size");
    MaxSize = _MaxSize;
    Num = -1;
    pMem = new T[MaxSize];
}


template <class T>
TStack<T>::~TStack() {
    delete[] pMem;
}


template<class T>
TStack<T>::TStack(const TStack<T>& st) {
    if (st.MaxSize < 0 || st.MaxSize > MAX_STACK_SIZE || st.Num < -1 || st.Num >= st.MaxSize)
        throw - 1;

    MaxSize = st.MaxSize;
    Num = st.Num;
    pMem = new T[MaxSize];
    for (int i = 0; i < Num+1; i++) {
        pMem[i] = st.pMem[i];
    }
}


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
        for (int i = 0; i < Num + 1; i++) pMem[i] = st.pMem[i];
    }
    return *this;
}


template<class T>
bool TStack<T>::operator==( const TStack& st) const
{
    if (this == &st) return true;
    if (MaxSize != st.MaxSize || Num != st.Num) return false;
    for (int i = 0; i < Num + 1; i++) {
        if (pMem[i] != st.pMem[i]) return false;
    }
    return true;
}

template<class T>
bool TStack<T>::operator!=(const TStack& st) const
{
    return !(*this==st);
}


template<class T>
bool TStack<T>::full() const
{
    if (Num == ((MaxSize) - 1)) return true;
    return false;
}


template<class T>
bool TStack<T>::empty() const
{
    if (Num == -1) return true;
    return false;
}


template<class T>
T TStack<T>::pop() {
    if (empty()) {
        throw string("Stack is empty"); 
        
    }
    T tmp = pMem[Num];
    Num--;
    return tmp;
}

template<class T>
T TStack<T>::top() const
{
    if (empty()) {
        throw string("Stack is empty");
    }
    return pMem[Num];
}


template<class T>
void TStack<T>::push(T val) {
    if (full()) throw string("Stack is full");
    Num++;
    pMem[Num] = val;
}

template<class T>
 void TStack<T>::clear()
{
     Num = -1;
}

 template <class T>
 int TStack<T>::getNum()
 {
     return Num;
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

