#include "TCalc.h"
#include <iostream>
#include "TStack.h"
int TCalc::GetPriority(char op)
{
	if (op == '+' || op == '-')
	{
		return 1;
	}
	if (op == '*' || op == '/')
	{
		return 2;
	}
	if (op == '^')
	{
		return 3;
	}
	return 0;
}



double TCalc::CalcPostfix()
{
	StNum.clear();
	string number = "";

	for (int i = 0; i < postfix.size(); i++)
	{
		char sim = postfix[i];

		if (isdigit(sim) || sim == '.')
		{
			number += sim;		// собираем число
		}
		else if (sim == ' ' && !number.empty())
		{
			double num = stod(number);
			StNum.push(num);
			//cout << "Добавлено число в стек: " << num << endl; // Для отладки
			number = "";
		}
		else if (sim == '+' || sim == '-' || sim == '*' || sim == '/' || sim == '^' || sim == '~')
		{
			if (StNum.getNum() < 1)
			{
				throw - 1;
			}
			double secondNum = StNum.pop();
			double firstNum = StNum.pop();
			double result = PerformOperation(firstNum, secondNum, postfix[i]);
			StNum.push(result);
		}
	}

	if (!number.empty()) {
		double val = stod(number);
		StNum.push(val);
	}
	if (StNum.getNum() != 0)
	{
		throw "Ошибка: неверное количество операндов в выражении";
	}
	double result = StNum.pop();
	return result;
}	



void TCalc::ToPostfix()
{
	postfix = "";
	StChar.clear();
	string number = "";

	for (int i = 0; i < infix.size(); i++)
	{
		char sim = infix[i];
		if (isdigit(sim) || sim == '.')
		{
			number += sim;  // собираем число (включая десятичную точку)
			if (i == infix.size() - 1 || (!isdigit(infix[i + 1]) && infix[i + 1] != '.'))		// проверка, что после числа идет пробел или символ операции
			{
				postfix += number + " ";
				number = "";
			}
		}
		else if (sim == '(')
		{
			StChar.push(sim);
		}
		else if (sim == ')')
		{
			while (!StChar.empty() && StChar.top() != '(')
			{
				postfix += StChar.pop();
				postfix += " ";
			}
			StChar.pop();
		}
		else if (sim == '+' || sim == '-' || sim == '*' || sim == '/' || sim == '^')
		{
			while (!StChar.empty() && GetPriority(StChar.top()) >= GetPriority(sim))
			{
				postfix += StChar.pop();
				postfix += " ";
			}
			StChar.push(sim);
		}
	}
	while (!StChar.empty())		// перемещаем оставшиеся операторы из стека в постфиксное выражение
	{
		postfix += StChar.pop();
		postfix += " ";
	}
}




double TCalc::Calc()
{
	string str = "(" + infix + ")";
	StNum.clear();
	StChar.clear();

	if (!StChar.checkThrow(infix))			// проверяем корректность скобок на парность
	{
		throw "ошибка: некорректное выражение (непарные скобки)!";
	}

	for (int i = 0; i < str.size(); ++i)
	{
		char tmp = str[i];

		if (tmp == '(')
		{
			StChar.push(tmp);		// помещаем в стек операторов
		}
		else if (tmp == '-')
		{
			if (i == 0 || str[i - 1] == '(')		// проверка на унарный минус
			{
				str[i] = '_';		// обозначаем унарный минус как отдельный символ
			}
			else					// это бинарный минус
			{
				while (!StChar.empty() && GetPriority(StChar.top()) >= GetPriority(tmp))		// выполняем все операции из стека >= по приоритету
				{
					char op = StChar.pop();
					double secondNum = StNum.pop();
					double firstNum = StNum.pop();
					StNum.push(PerformOperation(firstNum, secondNum, op));
				}
				StChar.push(tmp);			// кладем минус в стек операторов
			}
		}
		else if (isdigit(tmp) || tmp == '.')		// цифра или точка
		{
			size_t idx;
			double num = stod(str.substr(i), &idx);		// преобразование строки в число
			StNum.push(num);							// кладем в стек чисел
			i += idx - 1;
		}
		else if (tmp == ')')
		{
			while (!StChar.empty() && StChar.top() != '(')		// вычисляем все операции в текущих скобках 
			{
				char op = StChar.pop();
				double num2 = StNum.pop();
				double num1 = StNum.pop();
				StNum.push(PerformOperation(num1, num2, op));
			}
			StChar.pop();				// убираем открывающую скобку
		}
		else if (tmp == '+' || tmp == '*' || tmp == '/' || tmp == '^')
		{			// выполняем все операции с приоритетом >= текущей
			while (!StChar.empty() && GetPriority(StChar.top()) >= GetPriority(tmp)) {
				char op = StChar.pop();
				double num2 = StNum.pop();
				double num1 = StNum.pop();
				StNum.push(PerformOperation(num1, num2, op));
			}
			StChar.push(tmp);
		}
		else if (tmp == '_')		// преобразуем в отрицательное число 
		{
			size_t idx;
			double num = stod(str.substr(i + 1), &idx);
			//double num = atof(&str[i + 1]);			// *** - пример работы - внизу кода
			//StNum.push(-num);
			i += idx;
		}
	}
	if (StNum.getNum() != 0) {
		throw "Ошибка: неверное количество операндов в выражении!";
	}
	return StNum.pop();
}



double TCalc::PerformOperation(double num1, double num2, char op) {
	switch (op) {
	case '+': return num1 + num2;
	case '-': return num1 - num2;
	case '*': return num1 * num2;
	case '/':
		if (num2 == 0) throw "Ошибка: деление на ноль!";
		return num1 / num2;
	case '^': return pow(num1, num2);
	default: throw "Ошибка: неизвестная операция!";
	}
}