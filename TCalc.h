#pragma once
#include <iostream>
#include <string>
#include "TStack.h"

class TCalc
{
	string infix, postfix;
	TStack <double> StNum;
	TStack <char> StChar;

public:
	void ToPostfix();			// преобразовать из infix в postfix
	double CalcPostfix();		// перевод в постфиксную форму
	double Calc();				// вычисления по постфиксной записи

	double PerformOperation(double firstNum, double secondNum, char op);		// алгоритм обратной польской нотации

	int GetPriority(char op);	// выдача приоритета для операций

	void SetInfix(const string& stroka)
	{
		infix = stroka;
	}
	string GetPostfix() const
	{
		return postfix;
	}
	string GetInfix() const
	{
		return infix;
	}
};



