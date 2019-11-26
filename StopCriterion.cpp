#include "pch.h"
#include "StopCriterion.h"
#include <vector>
#include "funcs.h"

//��� ������������� ������

bool nabla::stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) {
	if (norm_2(grad) < eps_2)
		return true;
	return false;
};

bool coord::stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) {
	std::vector<double> x(x0.size());
	for (unsigned int i = 0; i < x.size(); ++i)
		x[i] = x1[i] - x0[i];
	if (norm_2(x) < eps_2)
		return true;
	return false;
};

bool value::stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) {
	if (abs((f1 - f0)/f1) < eps)
		return true;
	return false;
};

//��� ��������������� ������

//��� ����������� � ����� �������� � ���������� ���������:
//���������� 0, ���� ��������� ��������� (+ ������� ����� ����� ����� ��������)
//���������� 1, ���� ��������� �� ���� (��������� 1 � ����� ����� ��������)
bool n_iter::stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) {
	if (f1 < f0)
		return false;
	return true;
}

bool last_improv::stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) {
	if (abs(f1-f0) < eps)
		return true;
	return false;
}