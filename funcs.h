#pragma once

#include "pch.h"
#include <vector>
#include <iostream>
#include <random>

const double phi = 0.5 * (1.0 + sqrt(5.0));

double norm_2(std::vector<double> x);

double intersection(std::vector<double> x, std::vector<double> grad, std::vector<double> border);

std::vector<double> operator+(const std::vector<double>&a, const std::vector<double>&b);

std::vector<double> operator-(const std::vector<double>&a, const std::vector<double>&b);

std::vector<double> operator/(const std::vector<double>&a, const double &b);

std::vector<double> operator*(const double &b, const std::vector<double>&a);