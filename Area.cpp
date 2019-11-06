#include "pch.h"
#include "Area.h"
#include <vector>
const double eps = 1e-5;

bool Area::IsInArea(std::vector<double> x) {
	for (int i = 0; i < dimension; ++i)
		if ((border[2 * i] - eps > x[i]) || (border[2 * i + 1] + eps < x[i]))
			return false;
	return true;
}

//void Area::border_crossing(std::vector<double> x, std::vector<double> y, std::vector<double> & ans)
//{
//	int cross_coord{};
//	for (int i = 0; i < ans.size(); ++i) {
//		if (border[2 * i] - eps > y[i]) {
//			cross_coord = i;
//			ans[i] = border[2 * i];
//		}
//		else if (border[2 * i + 1] + eps < y[i]) {
//			cross_coord = i;
//			ans[i] = border[2 * i + 1];
//		}
//	}
//}