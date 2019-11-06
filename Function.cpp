#include "pch.h"
#include "Function.h"
#include <vector>
const double eps = 1e-5;

std::vector<double> Function::minus_eval_grad(std::vector<double> x) {
	std::vector<double> ans(x.size()), coordplush(x.size());
	for (int i = 0; i < x.size(); ++i) {
		coordplush = x;
		coordplush[i] += eps;
		ans[i] = -(eval(coordplush) - eval(x)) / eps;
	}
	return ans;
};