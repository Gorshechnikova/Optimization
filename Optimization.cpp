#include "pch.h"
//#include <iostream>
//#include <vector>
//#include "funcs.h"
#include "OptimizationMethod.h"
#include <typeinfo>

//const double step1 = 0.001;
//const double step2 = 0.0005;
//const double eps1 = 0.0001;
//const double eps2 = 0.00001;
//const int limit_iter1 = 1000;
//const int limit_iter2 = 5000;

int main()
{
	//int ind_func = 1;
	//int ind_area = 3;
	//int ind_stop = 2;
	//int ind_method = 1;
	double eps{}, step{}, limit_iter{}, prob{};
	int ind_func{}, ind_area{}, ind_stop{}, ind_method{}, n_hat{};
	while (ind_func < 1 || ind_func > 5) {
		std::cout << "Choose 1 function from 5:" << std::endl
			<< "1. f(x,y) = (x - 2)^4 + (x - 2*y)^2" << std::endl
			<< "2. f(x,y) = exp(sin(x/20 + y/20)) + y" << std::endl
			<< "3. f(x,y) = sin(x)*cos(y)" << std::endl
			<< "4. f(x,y,z) = x*y*z" << std::endl
			<< "5. f(x,y,z,w) = x+y+z+w" << std::endl;
		std::cin >> ind_func;
	}
	Function * function = nullptr;
	Area * area = nullptr;

	switch (ind_func) {
	case 1:
	case 2:
	case 3: {
		while (ind_area < 1 || ind_area > 3) {
			std::cout << std::endl << "Choose 1 area from 3:" << std::endl
				<< "1. [0,3]*[0,3]" << std::endl
				<< "2. [2,5]*[2,5]" << std::endl
				<< "3. [-5,5]*[-5,5]" << std::endl;
			std::cin >> ind_area;
		}
		switch (ind_area) {
		case 1: area = new Area11; break;
		case 2: area = new Area12; break;
		case 3: area = new Area13; break;
		}
		break;
	}
	case 4: { function = new function4;
		while (ind_area < 1 || ind_area > 3) {
			std::cout << std::endl << "Choose 1 area from 3:" << std::endl
				<< "1. [0,3]*[0,3]*[0,3]" << std::endl
				<< "2. [2,5]*[2,5]*[2,5]" << std::endl
				<< "3. [-5,5]*[-5,5]*[-5,5]" << std::endl;
			std::cin >> ind_area;
		}
		switch (ind_area) {
		case 1: area = new Area21; break;
		case 2: area = new Area22; break;
		case 3: area = new Area23; break;
		}
		break;
	}
	case 5: { function = new function5;
		while (ind_area < 1 || ind_area > 3) {
			std::cout << std::endl << "Choose 1 area from 3:" << std::endl
				<< "1. [0,3]*[0,3]*[0,3]*[0,3]" << std::endl
				<< "2. [2,5]*[2,5]*[2,5]*[2,5]" << std::endl
				<< "3. [-5,5]*[-5,5]*[-5,5]*[-5,5]" << std::endl;
			std::cin >> ind_area;
		}
		switch (ind_area) {
		case 1: area = new Area31; break;
		case 2: area = new Area32; break;
		case 3: area = new Area33; break;
		}
		break;
	}
	}
	switch (ind_func) {
	case 1: function = new function1; break;
	case 2: function = new function2; break;
	case 3: function = new function3; break;
	}

	StopCriterion * criterion = nullptr;

	/*while (ind_stop < 1 || ind_stop > 3) {
		std::cout << std::endl << "Choose 1 stop criterion from 3:" << std::endl
			<< "1. || grad(f(x_k)) || < eps" << std::endl
			<< "2. || x_k - x_k-1 || < eps" << std::endl
			<< "3. || (f(x_k) - f(x_k-1))/f(x_k) || < eps" << std::endl;
		std::cin >> ind_stop;
	}
	switch (ind_stop) {
	case 1: criterion = new nabla; break;
	case 2: criterion = new coord; break;
	case 3: criterion = new value; break;
	}*/

	while (limit_iter <= 0) {
		std::cout << std::endl << "Enter limit iteration: ";
		std::cin >> limit_iter;
	}
	/*method->Set_limit_iter(limit_iter);*/

	OptimizationMethod * method = nullptr;

	while (ind_method < 1 || ind_method > 2) {
		std::cout << std::endl << "Choose 1 method from 2:" << std::endl
			<< "1. Fletcher-Reeves CG" << std::endl
			<< "2. Stochastic method" << std::endl;
		std::cin >> ind_method;
	}
	if (ind_method == 1) {
		method = new FletcherReevesCG;
		while (step <= 0 || step >= 1) {
			std::cout << std::endl << "Enter step from 0 to 1 for that method: " << std::endl;
			std::cin >> step;
		}
		method->Set_step(step);
		while (ind_stop < 1 || ind_stop > 3) {
			std::cout << std::endl << "Choose 1 stop criterion from 3:" << std::endl
				<< "1. || grad(f(x_k)) || < eps" << std::endl
				<< "2. || x_k - x_k-1 || < eps" << std::endl
				<< "3. || (f(x_k) - f(x_k-1))/f(x_k) || < eps" << std::endl;
			std::cin >> ind_stop;
		}
		switch (ind_stop) {
		case 1: criterion = new nabla; break;
		case 2: criterion = new coord; break;
		case 3: criterion = new value; break;
		}
	}
	else {
		method = new Stochastic;
		std::cout << std::endl << "Enter the probability of getting into a neighborhood of a point from 0 to 1: ";
		while (prob <= 0 || prob >= 1)
			std::cin >> prob;
		dynamic_cast<Stochastic*>(method)->Set_prob(prob);
		while (ind_stop < 1 || ind_stop > 2) {
			std::cout << std::endl << "Choose 1 stop criterion from 1:" << std::endl
				<< "1. Reaching the iteration limit since last approach has improved" << std::endl
				<< "2. |f(x_k+j)-f(x_k)| < eps, j = min {m: f(x_k+m)<f(x_k)}" << std::endl;
			std::cin >> ind_stop;
		}
		switch (ind_stop) {
		case 1: {
			criterion = new n_iter;
			while (n_hat < 1) {
				std::cout << "Enter the limit of iterations from the last improvement: ";
				std::cin >> n_hat;
			}
			dynamic_cast<n_iter*>(criterion)->Set_n_hat(n_hat);
			break;
		}
		case 2:
			criterion = new last_improv; break;
		}
	}
	method->Set_limit_iter(limit_iter);

	if (typeid(*criterion) == typeid(last_improv) || typeid(*method) == typeid(FletcherReevesCG)) {
		while (eps <= 0 || eps >= 1) {
			std::cout << std::endl << "Enter eps error: ";
			std::cin >> eps;
		}
		function->Set_eps(eps);
		method->Set_eps(eps);
		criterion->Set_eps(eps);
	}


	//while (limit_iter != 1 && limit_iter != 2) {
	//	std::cout << std::endl << "Choose 1 limit iteration from 2: " << std::endl
	//		<< "1. limit_iter = 1000" << std::endl
	//		<< "2. limit_iter = 5000" << std::endl;
	//	std::cin >> limit_iter;
	//}
	//if (limit_iter == 1)
	//	method->Set_limit_iter(limit_iter1);
	//else method->Set_limit_iter(limit_iter2);

	int dimen = area->GetDimension();
	std::vector <double> x(dimen);
	std::cout << std::endl << "Enter " << dimen << " values for initial point: ";
	for (int i = 0; i < dimen; ++i)
		std::cin >> x[i];
	while (!area->IsInArea(x)) {
		std::cout << "Enter values within the selected interval!" << std::endl;
		for (int i = 0; i < dimen; ++i)
			std::cin >> x[i];
	}
	method->Set_x0y0y1(x);

	std::vector<double> answer = method->optimize(area, function, criterion);
	std::cout << std::endl << std::endl << "Sought point: (";
	for (unsigned int i = 0; i < answer.size() - 1; ++i)
		std::cout << answer[i] << ", ";
	std::cout << answer[answer.size() - 1];
	std::cout << ")" << std::endl
		<< "Min value: " << function->eval(answer) << std::endl
		<< "Number of iterations: " << method->Get_iter() << std::endl;
	return 0;
}