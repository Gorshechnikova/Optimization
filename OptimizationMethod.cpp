#include "pch.h"
#include "OptimizationMethod.h"
#include <vector>
#include <iostream>
#include <random>
#include "funcs.h"
const double eps = 1e-5;
const double eps_2 = 1e-10;

void OptimizationMethod::Set_x0(int dim) {
	std::cout << std::endl << "Enter " << dim << " values for initial point: ";
	x0.resize(dim);
	y0.resize(dim);
	y1.resize(dim);
	for (int i = 0; i < dim; ++i) {
		std::cin >> x0[i];
		y0[i] = x0[i];
	}
}

std::vector<double> FletcherReevesCG::optimize(Area * area, Function * func, StopCriterion * criterion) {
	int dim = area->GetDimension();
	Set_x0(dim);
	while (!area->IsInArea(x0)) {
		std::cout << "Enter values within the selected interval!" << std::endl;
		Set_x0(dim);
	}
	std::vector<double> d0 = func->minus_eval_grad(y0), d1(dim), ans(dim)/*, d0_reserve{}*/;
	int k = 1, j = 0;
	double lambda{}, opt_lambda{};

	//starting point optimality check
	double norm0 = norm_2(d0), norm1{};
	if (norm0 < eps_2)
		return y0;

	while ((k < limit_iter)) {
		std::vector<double> dot(dim);
		double min_func = 9999, step = 0.001;
		double curr_eval_fanc{};
		lambda = 0;
		while (true) {
			for (int i = 0; i < dim; ++i) {
				dot[i] = y0[i] + lambda * d0[i];
			}
			if (!area->IsInArea(dot)) {
				opt_lambda = lambda;
				break;
			}
			curr_eval_fanc = func->eval(dot);
			if ((min_func - curr_eval_fanc) < eps) {
				opt_lambda = lambda;
				break;
			}
			min_func = curr_eval_fanc;
			lambda += step;
		};

		for (int i = 0; i < dim; ++i)
			y1[i] = y0[i] + opt_lambda * d0[i];
		//d0_reserve = d0;

		std::vector<double> d = func->minus_eval_grad(y1);
		norm1 = norm_2(d);

		if (j < dim - 1) {
			double alpha = norm0 / norm1;
			for (int i = 0; i < dim; ++i) {
				d1[i] = func->minus_eval_grad(y1)[i] + alpha * d0[i];
				y0[i] = y1[i];
			}
			++j;
		}
		else {
			if (criterion->stop(x0, y1, func->eval(x0), func->eval(y1), func->minus_eval_grad(y1))) {
				//area->border_crossing(x0, y1, ans);
				if (!area->IsInArea(y1))
					return x0;
				else return y1;
			}

			for (int i = 0; i < dim; ++i) {
				y0[i] = y1[i];
				x0[i] = y1[i];
				d0[i] = func->minus_eval_grad(y0)[i];
			}
			j = 1;
			++k;
		}
	}
	//if (area->IsInArea(y0))
		return y0;
	//else {
	//	for (int i = 0; i < dim; ++i)
	//		ans[i] = y0[i] - opt_lambda * d0_reserve[i];
	//	return ans;
	//}
};

std::vector<double> Stochastic::optimize(Area * area, Function * func, StopCriterion * criterion) {
	std::random_device rd;
	std::mt19937 gen(rd());
	//std::mt19937 gen(5);
	int dim = area->GetDimension();
	std::vector<double> init_dis = area->GetBorder();
	std::uniform_real_distribution<> dis(init_dis[0], init_dis[1]);
	Set_x0(dim);
	while (!area->IsInArea(x0)) {
		std::cout << "Enter values within the selected interval!" << std::endl;
		Set_x0(dim);
	}
	int k = 0;
	double curr_eval = func->eval(y0), new_eval{};
	while (k < limit_iter) {
		for (int i = 0; i < dim; ++i)
			y1[i] = dis(gen);
		++k;
		new_eval = func->eval(y1);
		if (new_eval < curr_eval) {
			y0 = y1;
			curr_eval = new_eval;
		}
	}
	return y0;
};