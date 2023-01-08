#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <Windows.h>

using xValue = double;
using yValue = double;

class IntegralMhetods
{
private:
	double h;
	double a;
	double b;
	size_t n;
	std::vector<std::pair<xValue, yValue>> valueTable;
	double (*func)(double);
public:
	IntegralMhetods(double a, double b, size_t n, double (*func)(double))
		: a(a), b(b), n(n + 1), h((b - a) / n), func(func)
	{
		std::cout << h << std::endl;
		valueTable.resize(this->n);
		std::cout << n << std::endl;

		for (size_t i = 0; i < valueTable.size(); i++)
		{
			valueTable[i].first = this->a + i * this->h;
			valueTable[i].second = this->func(valueTable[i].first);
		}
	}

	double LeftRectangle() const 
	{
		double result = 0;

		for (size_t i = 0; i < n - 1; i++)
		{
			result += valueTable[i].second;
		}

		return h * result;
	}

	double RightRectangle() const
	{
		double result = 0;

		for (size_t i = 1; i < n; i++)
		{
			result += valueTable[i].second;
		}

		return h * result;
	}

	double AvarageRectangle() const
	{
		auto newValueTable = valueTable;

		for (auto& ele : newValueTable)
		{
			ele.second = func(ele.first + h / 2.0);
		}

		double result = 0;

		for (size_t i = 1; i < n; i++)
		{
			result += newValueTable[i - 1].second;
		}

		return h * result;
	}

	double TrapezoidMhetod() const
	{
		double result = (valueTable[0].second + valueTable[n - 1].second) / 2.0;

		for (size_t i = 1; i < n - 1; i++)
		{
			result += valueTable[i].second;
		}

		return h * result;
	}

	double GeneralizedMhetod(double avarageIntegral, double trapezoidIntegral) const
	{
		return (1 / 3.0) * (2 * avarageIntegral + trapezoidIntegral);
	}

	double SimpsonMhetod() const
	{
		double result = valueTable[0].second + valueTable[n - 1].second;
		double h = this->h / 3.0;
		for (size_t i = 1; i < n - 1; i++)
		{
			if (i % 2 == 0)
			{
				result += 2 * valueTable[i].second;
			}
			else
			{
				result += 4 * valueTable[i].second;
			}
		}

		return h * result;
	}

	friend std::ostream& operator<<(std::ostream& out, const IntegralMhetods& object);
};

std::ostream& operator<<(std::ostream& out, const IntegralMhetods& object)
{
	for (const auto& ele : object.valueTable)
	{
		out << "X = " << ele.first << "\t\t\tY = " << ele.second << std::endl;
	}

	return out;
}

double Function(double value)
{
	
	//return 1 / value;
	return 1 / std::pow(4 * std::pow(value, 2) + 1.4, 1 / 2.0);
	//return std::pow(value, 2) * std::pow(1 + std::pow(value, 5), 1 / 2.0);
	//return 1.0 / std::pow(0.2 * std::pow(value, 2) + 1, 1 / 2.0);
	return 1 / (std::pow(value * value + 0.8, 1 / 2.0));
	return 1.0 / (std::pow(std::cos(value * 5), 2));
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);



	IntegralMhetods object(1.4, 2.2, 8, Function);

	std::cout << "Обчислення інтегралу методом лівих прямокутників:     " << object.LeftRectangle() << std::endl;
	std::cout << "Обчислення інтегралу методом правих прямокутників:    " << object.RightRectangle() << std::endl;
	std::cout << "Обчислення інтегралу методом середніх прямокутників:  " << object.AvarageRectangle() << std::endl;
	std::cout << "Обчислення інтегралу методом трапеції:                " << object.TrapezoidMhetod() << std::endl;
	std::cout << "Обчислення інтегралу методом Сімпсона:                " << object.SimpsonMhetod() << std::endl;
	std::cout << "Обчислення інтегралу узагальненою формулою:           " << object.GeneralizedMhetod(object.AvarageRectangle(), object.TrapezoidMhetod()) << std::endl;

	std::cout << std::endl << object << std::endl;

	return 0;
}