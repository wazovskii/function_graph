#ifndef SRC_PARSER_HPP_
#define SRC_PARSER_HPP_


#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <cmath>

#define Pi 3.14
#define Width 80
#define Heigth 25

std::unordered_map<std::string, int> priorities = { {"+", 2}, {"-", 2}, {"*", 3}, {"/", 3}, {"(", 1},
                                                  {")", 5}, {"sin", 4}, {"cos", 4}, {"tan", 4}, {"ln", 4},
                                                  {"sqrt", 4}, {"ctg", 4}, {"tg", 4}
                                                };

std::string avalible_functions[] = {"sin", "sqrt", "cos", "ctg", "tan", "ln"};


void draw_graph(std::vector<std::string> elements);
int get_priority(std::string in);
void translate_to_polish(std::vector<std::string>& _elements);
double calculate(std::vector<std::string> elements, double x);
double func_two_args(std::string op, double a, double b);
double func_one_arg(std::string op, double a);
#endif    // SRC_PARSER_HPP_
