#include "pch.h"
#include "OptimizationMethod.h"
#include <vector>
#include <iostream>
#include <random>
#include "funcs.h"
#include <typeinfo>
//const double eps = 1e-5;
//const double eps_2 = 1e-10;
const double min_fun = 9999;
//const double step = 0.001;
double delta = 0.1;


std::vector<double> FletcherReevesCG::optimize(Area * area, Function * func, StopCriterion * criterion) {
	double eps_2 = eps * eps;
	int dim = area->GetDimension();
	std::vector<double> d0 = func->minus_eval_grad(y0), d1(dim), ans(dim);
	int j = 0;
	double lambda{}, opt_lambda{};

	//starting point optimality check
	double norm0 = norm_2(d0), norm1{};
	if (norm0 < eps_2)
		return y0;

	while ((iter < limit_iter)) {
		std::vector<double> dot(dim);
		double curr_eval_fanc{}, min_func = min_fun;
		lambda = 0;
		d0 = func->minus_eval_grad(y0);
		while (true) {
			for (int i = 0; i < dim; ++i) {
				dot[i] = y0[i] + lambda * d0[i];
			}
			if (!area->IsInArea(dot)) {
				break;
			}
			curr_eval_fanc = func->eval(dot);
			if ((min_func - curr_eval_fanc) > step) {
				opt_lambda = lambda;
				min_func = curr_eval_fanc;
			}
			lambda += step;
		};

		for (int i = 0; i < dim; ++i)
			y1[i] = y0[i] + opt_lambda * d0[i];
		norm0 = norm_2(d0);
		std::vector<double> d = func->minus_eval_grad(y1);
		norm1 = norm_2(d);

		if (j < dim - 1) {
			double alpha = norm1 / norm0;
			for (int i = 0; i < dim; ++i) {
				d1[i] = func->minus_eval_grad(y1)[i] + alpha * d0[i];
				y0[i] = y1[i];
			}
			++j;
		}
		else {
			if (criterion->stop(x0, y1, func->eval(x0), func->eval(y1), func->minus_eval_grad(y1))) {
				return y1;
			}

			y0 = y1;
			x0 = y1;
			//d0 = func->minus_eval_grad(y0);
			j = 0;
			++iter;
		}

	}
	return y0;
}

void OptimizationMethod::Set_step(double st) {
	step = st;
}

void OptimizationMethod::Set_eps(double epsil) {
	eps = epsil;
}

std::vector<double> Stochastic::optimize(Area * area, Function * func, StopCriterion * criterion) {
	std::random_device rd;
	std::mt19937 gen(rd());
	//std::mt19937 gen(5);
	int dim = area->GetDimension();
	std::vector<double> border = area->GetBorder(), grad;
	std::uniform_real_distribution<> dis(0, 1);
	//std::vector<double> rand(dim);
	int n_h{};
	int n_hat = 1;
	if (typeid(*criterion) == typeid(n_iter))
		n_hat = dynamic_cast<n_iter*>(criterion)->Get_n_hat();
	double rand{};
	double curr_eval = func->eval(y0), new_eval{};
	while (iter < limit_iter && n_h < n_hat) {
		rand = dis(gen);         //этот rand для сравнения с вероятностью prob для выбора области
		if (rand > prob) {       //в качестве области выбирается вся область
			for (int i = 0; i < dim; ++i) {
				rand = dis(gen);     //этот rand для выбора рандомной точки в выбранной области для каждой координаты
				y1[i] = border[2 * i] + rand * (border[2 * i + 1] - border[2 * i]);
			}
		}
		else {                   //в качестве области выбирается куб "радиусом" delta
			for (int i = 0; i < dim; ++i) {
				rand = dis(gen);     //этот rand для выбора рандомной точки в выбранной области для каждой координаты
				if (y0[i] - delta < border[i * 2])
					y1[i] = border[2 * i] + rand * (y0[i] + delta - border[2 * i]);
				else if (y0[i] + delta > border[i * 2 + 1])
					y1[i] = y0[i] - delta + rand * (border[2 * i + 1] - y0[i] + delta);
				else
					y1[i] = y0[i] - delta + rand * 2 * delta;
			}
		}
		++iter;
		new_eval = func->eval(y1);
		if (typeid(*criterion) == typeid(n_iter)) {
			if (criterion->stop(y0, y1, curr_eval, new_eval, grad))      //пояснения работы в StopCriterion.cpp
				++n_h;
			else {
				n_h = 0;
				/*	y0 = y1;
					curr_eval = new_eval;*/
				delta /= 2;
			}
		}
		else
		{
			if (criterion->stop(y0, y1, curr_eval, new_eval, grad))
				return y0;
		}
		if (new_eval < curr_eval) {
			y0 = y1;
			curr_eval = new_eval;
		}
	}
	return y0;
};

void OptimizationMethod::Set_x0y0y1(std::vector<double> x) {
	x0.resize(x.size());
	y0.resize(x.size());
	y1.resize(x.size());
	x0 = x;
	y0 = x;
}
