#include "calculate.hpp"

double calculate(std::vector<std::string> elements, double x) {
    std::stack<std::string> operation;
    
    for (size_t i = 0; i < elements.size(); i++) {
        std::string token = elements[i];
        if (get_priority(token) == 0) {
            operation.push(token);
        } else if (get_priority(token) > 3) {
            double a;
            if (operation.top() == "x")
                a = x;
            else
                a = std::stod(operation.top());
            operation.pop();
            std::ostringstream result_to_string;
            result_to_string << func_one_arg(token, a);
            operation.push(result_to_string.str());
            result_to_string.clear();
        } else if (get_priority(token) <= 3) {
            double a;
            if (operation.top() == "x")
                a = x;
            else
                a = std::stod(operation.top());
            operation.pop();
            double b;
            if (operation.top() == "x")
                b = x;
            else
                b = std::stod(operation.top());
            operation.pop();
            std::ostringstream result_to_string;
            result_to_string << func_two_args(token, b, a);
            operation.push(result_to_string.str());
            result_to_string.clear();
        }
    }
    return std::stod(operation.top());
}

double func_two_args(std::string op, double a, double b) {
    double result = 0;
    if (op == "+")
        result = a + b;
    else if (op == "-")
        result = a - b;
    else if (op == "/")
        result = a / b;
    else if (op == "*")
        result = a * b;
    return result;
}

double func_one_arg(std::string op, double a) {
    double result = 0.0;
    if (op == "sin")
        result = sin(a);
    else if (op == "cos")
        result = cos(a);
    else if (op == "tan")
        result = tan(a);
    else if (op == "ctg")
        result = pow(1. / tan(a), 2);
    else if (op == "sqrt")
        result = sqrt(a);
    return result;
}

int get_priority(std::string in) {
    return priorities.find(in) != priorities.end() ? priorities.find(in)->second : 0;
}
