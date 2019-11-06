#include "pch.h"
#include <vector>
#include "funcs.h"

double norm_2(std::vector<double> x) {
	double ans{};
	for (int i = 0; i < x.size(); ++i)
		ans += x[i] * x[i];
	return ans;
}