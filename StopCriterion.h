#pragma once
#include "funcs.h"

class StopCriterion {
protected:
	virtual ~StopCriterion() {};
public:
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) = 0;
};

class nabla : public StopCriterion {
public:
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) override;
};

class coord : public StopCriterion {
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) override;
	//bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad);
};

class value : public StopCriterion {
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) override;
};