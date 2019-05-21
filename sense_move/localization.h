#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include<iostream>
#include <string>
#include <vector>

typedef std::vector<double> double_v;
typedef std::vector<std::string> string_v;
typedef std::vector<int> int_v;

double_v sense(double_v p, std::string Z);
double_v move(double_v p, int U);
void print_probability();

#endif