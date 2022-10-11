#ifndef SRC_CALCULATE_HPP_
#define SRC_CALCULATE_HPP_

#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <cmath>
#include <sstream>
const std::unordered_map<std::string, int> priorities = { {"+", 2}, {"-", 2}, {"*", 3}, {"/", 3}, {"(", 1},
               {")", 5}, {"sin", 4}, {"cos", 4}, {"tan", 4}, {"ln", 4},
                                                  {"sqrt", 4}, {"ctg", 4}, {"tg", 4}
                                                };

const std::string avalible_functions[] = {"sin", "sqrt", "cos", "ctg", "tan", "ln", "tg"};

double calculate(std::vector<std::string> elements, double x);
double func_two_args(std::string op, double a, double b);
double func_one_arg(std::string op, double a);
int get_priority(std::string in);
#endif  // SRC_CALCULATE_HPP
