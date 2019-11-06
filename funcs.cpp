#include "pch.h"
#include <vector>
#include "funcs.h"
//#include "Area.h"

double norm_2(std::vector<double> x) {
	double ans{};
	for (int i = 0; i < x.size(); ++i)
		ans += x[i] * x[i];
	return ans;
}

//std::vector<double> Set_x0(int dim, Area * area) {
//	std::vector<double> x(dim);
//	std::cout << std::endl << "Enter " << dim << " values for initial point: ";
//	for (int i = 0; i < dim; ++i)
//		std::cin >> x[i];
//	while (!area->IsInArea(x)) {
//		std::cout << "Enter values within the selected interval!" << std::endl;
//		for (int i = 0; i < dim; ++i)
//			std::cin >> x[i];
//	}
//	return x;
//}