#include "pch.h"
#include "Function.h"
#include <vector>

std::vector<double> Function::minus_eval_grad(std::vector<double> x) {
	std::vector<double> ans(x.size()), coordplush(x.size());
	for (int i = 0; i < x.size(); ++i) {
		coordplush = x;
		coordplush[i] += eps*eps;
		ans[i] = -(eval(coordplush) - eval(x)) / (eps*eps);
	}
	return ans;
};

std::vector<double> Golden_ratio(std::vector<double> a, std::vector<double> b, double eps_2, Function * func) {
	while (norm_2(b - a) > eps_2) {
		std::vector<double> t = (b - a) / phi;
		std::vector<double> x1 = b - t;
		std::vector<double> x2 = a + t;
		if (func->eval(x1) > func->eval(x2))
			a = x1;
		else b = x2;
	}
	return ((a + b) / 2);
};