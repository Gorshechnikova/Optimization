#pragma once
#include "funcs.h"

class Function {
protected:
public:
	virtual double eval(std::vector<double> x) = 0;
	std::vector<double> minus_eval_grad(std::vector<double> x);
};

class function1 : public Function {
protected:
public:
	virtual double eval(std::vector<double> x) override {
		return (x[0] - 2)*(x[0] - 2)*(x[0] - 2)*(x[0] - 2) + (x[0] - 2 * x[1])*(x[0] - 2 * x[1]);
	};
};

class function2 : public Function {
protected:
public:
	virtual double eval(std::vector<double> x) override {
		return(exp(sin(x[0] / 20 + x[1] / 20)) + x[1]);
	};
};

class function3 : public Function {
protected:
	double x1, x2, x3, x4;
public:
	virtual double eval(std::vector<double> x) override {
		return(sin(x[0])*cos(x[1]));
	};
};

class function4 : public Function {
protected:
	double x1, x2, x3, x4, x5, x6;
public:
	virtual double eval(std::vector<double> x) override {
		return (x[0] * x[1] * x[2]);
	};
};

class function5 : public Function {
protected:
	double x1, x2, x3, x4, x5, x6, x7, x8;
public:
	virtual double eval(std::vector<double> x) override {
		return (x[0] + x[1] + x[2] + x[3]);
	};
};