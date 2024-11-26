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
	void ToPostfix();			// ������������� �� infix � postfix
	double CalcPostfix();		// ������� � ����������� �����
	double Calc();				// ���������� �� ����������� ������

	double PerformOperation(double firstNum, double secondNum, char op);		// �������� �������� �������� �������

	int GetPriority(char op);	// ������ ���������� ��� ��������

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



