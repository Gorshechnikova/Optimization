#pragma once
//#include "funcs.h"
#include "Area.h"
#include "Function.h"
#include "StopCriterion.h"

class OptimizationMethod {
protected:
	std::vector<double> x0, y0, y1;
	int iter;
	//void Set_x0(int dim);
	double step;
	double eps;
	int limit_iter;
public:
	OptimizationMethod(): iter(0) {};

	virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) = 0;
	int Get_iter() {
		return iter;
	}
	void Set_x0y0y1(std::vector<double> x);
	void Set_step(double st);
	void Set_eps(double epsil);
	void Set_limit_iter(int lim) {
		limit_iter = lim;
	}
};

class FletcherReevesCG : public OptimizationMethod {
public:
	virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) override;
};

class Stochastic : public OptimizationMethod {
public:
	virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) override;
};