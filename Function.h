#pragma once
#include "funcs.h"

class Function {
protected:
	double eps;
public:
	virtual double eval(std::vector<double> x) = 0;
	std::vector<double> minus_eval_grad(std::vector<double> x);
	void Set_eps(double epsil);
};

class function1 : public Function {
protected:
public:
	virtual double eval(std::vector<double> x) override;
};

class function2 : public Function {
protected:
public:
	virtual double eval(std::vector<double> x) override;
};

class function3 : public Function {
protected:
	double x1, x2, x3, x4;
public:
	virtual double eval(std::vector<double> x) override;
};

class function4 : public Function {
public:
	virtual double eval(std::vector<double> x) override;
};

class function5 : public Function {
public:
	virtual double eval(std::vector<double> x) override;
};

std::vector<double> Golden_ratio(std::vector<double> a, std::vector<double> b, double eps_2, Function * func);