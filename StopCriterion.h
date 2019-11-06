#pragma once
#include "funcs.h"

class StopCriterion {
protected:
	double eps;
	double eps_2;
	virtual ~StopCriterion() {};
public:
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) = 0;
	void Set_eps(double epsil) {
		eps = epsil;
		eps_2 = eps * eps;
	}
};

class nabla : public StopCriterion {
public:
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) override;
};

class coord : public StopCriterion {
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) override;
};

class value : public StopCriterion {
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) override;
};