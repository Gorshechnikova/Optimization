#pragma once
//#include "funcs.h"
#include "Area.h"
#include "Function.h"
#include "StopCriterion.h"

class OptimizationMethod {
protected:
	std::vector<double> x0, y0, y1;
	void Set_x0(int dim);
public:
	virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) = 0;
};

class FletcherReevesCG : public OptimizationMethod {
public:
	virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) override;
};

class Stochastic : public OptimizationMethod {
public:
	virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) override;
};