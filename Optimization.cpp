#include "pch.h"
//#include <iostream>
//#include <vector>
//#include "funcs.h"
#include "OptimizationMethod.h"

int main()
{
	//int ind_func = 2;
	//int ind_area = 3;
	//int ind_stop = 1;
	//int ind_method = 2;
	int ind_func{}, ind_area{}, ind_stop{}, ind_method{};
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

	while (ind_stop < 1 || ind_stop > 3) {
		std::cout << std::endl << "Choose 1 stop criterion from 3:" << std::endl
			<< "1. nabla" << std::endl
			<< "2. coord" << std::endl
			<< "3. value" << std::endl;
		std::cin >> ind_stop;
	}
	switch (ind_stop) {
	case 1: criterion = new nabla; break;
	case 2: criterion = new coord; break;
	case 3: criterion = new value; break;
	}

	OptimizationMethod * method = nullptr;

	while (ind_method < 1 || ind_method > 2) {
		std::cout << std::endl << "Choose 1 method from 2:" << std::endl
			<< "1. Fletcher-Reeves CG" << std::endl
			<< "2. Stochastic method" << std::endl;
		std::cin >> ind_method;
	}
	if (ind_method == 1)
		method = new FletcherReevesCG;
	else method = new Stochastic;

	std::vector<double> answer = method->optimize(area, function, criterion);
	std::cout << std::endl << std::endl << "(";
	for (unsigned int i = 0; i < answer.size() - 1; ++i)
		std::cout << answer[i] << ", ";
	std::cout << answer[answer.size() - 1];
	std::cout << ")";

	return 0;
}