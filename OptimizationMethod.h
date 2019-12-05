/*!
	Данный класс содержит два метода оптимизации нахождения минимума заданной функции в заданной области:
	- Итерационный (здесь метод сопряженных градиентов Флетчера-Ривса)
	- Стохастический
*/

#pragma once
#include "Area.h"
#include "Function.h"
#include "StopCriterion.h"

class OptimizationMethod {
protected:
	std::vector<double> x0, y0, y1;
	int iter;
	double eps;
	int limit_iter;
public:
	OptimizationMethod(): iter(0) {};
	/*!
		Функция нахождения минимума функции и точки, в которой он достигается
		\param area Выбранная область, в которой будет находиться минимум
		\param func Функция, минимум которой будет находиться
		\param criterion Критерий остановки для выбранного метода
		\return Точку минимума функции в области
	*/
	virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) = 0;
	int Get_iter();
	void Set_x0y0y1(std::vector<double> x);
	void Set_eps(double epsil);
	void Set_limit_iter(int lim);
};

class FletcherReevesCG : public OptimizationMethod {
public:
	virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) override;
};

class Stochastic : public OptimizationMethod {
	///Вероятность попадания в окрестность текущей точки
	double prob;
public:
	virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) override;
	void Set_prob(double p);
};