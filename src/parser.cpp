
#include "parser.hpp"

class parser {
private:
    std::string input;
    std::vector<std::string> elements;

    bool check_for_errors() {
        return check_brackets() && check_func_names();
    }

    bool check_brackets() {
        std::stack<char> brackets;
        for (int i = 0; i < input.size(); i++) {
            if (input[i] == '(') {
                brackets.push(input[i]);
                continue;
            }
            if (!brackets.empty()) {
                if ((input[i] == ')') && (brackets.top() == '('))
                    brackets.pop();
                else if ((input[i] == ')') && (brackets.top() != '('))
                    return false;
            } else if (input[i] == ')') {
                return false;
            }
        }
        if (brackets.empty())
            return true;
        else
            return false;
    }

    void prepare_buffer() {
        parse_unary_minus();
        parse_mul();
        tokenize_string();
    }

    void parse_unary_minus() {
        char last = 0;
        for (int i = 0; i < (int)input.size(); i++) {
            if ((input[i] == '-') && (last == '(')) {
                input[i] = '~';
            } else if ((input[i] == '-') && (!isdigit(last) && (get_priority(std::string(1, last) + ' ') < 3))) {
                input[i] = '~';
            }
            last = input[i];
        }
    }

    void parse_mul() {
        int j = 0;
        int last = 0;
        for (size_t i = 0; i < input.size(); i++) {
            if (last && input[i] == 'x') {
                input.insert(i, 1, '*');
            }
            last = isdigit(input[i]);
        }
    }

    bool check_func_names() {
        std::string input_copy = input;
        for (auto &it : avalible_functions) {
            size_t pos = 0;
            while (pos = input_copy.find(it + "(") != std::string::npos)
                input_copy.erase(pos - 1, it.size());
        }

        for (int i = 0; i < input_copy.size(); i++) {
            if (isalpha(input_copy[i]) && (input_copy[i] != 'x')) {
                return false;
            }
        }
        return true;
    }

    void tokenize_string() {
        std::string tmp;
        int last = get_last_type(input[0]);
        tmp.push_back(input[0]);
        for (int i = 1; i < (int)input.size(); i++) {
            if (last != get_last_type(input[i])) {
                elements.push_back(tmp);
                tmp = "";
            }
            tmp.push_back(input[i]);
            last = get_last_type(input[i]);
        }
        if (!tmp.empty())
            elements.push_back(tmp);
    }

    int get_last_type(char in) {
        int result;
        if (std::isalpha(in))
            result = 1;
        else if (std::isdigit(in))
            result = 2;
        else if (in == '.')
            result = 2;
        else if (in == '~')
            result = 2;
        else
            result = in - '0';
        return result;
    }

public:
    parser(std::string input_) : input(input_) {}

    std::vector<std::string> run() {
        std::string buffer;
        int error = 0;
        if (check_for_errors()) {
            prepare_buffer();
            if (elements.size() > 1) {
                translate_to_polish(elements);
            }
        } else {
            printf("Error\n");
        }
        return elements;
    }
    std::vector<std::string> get_tokens() {
        return elements;
    }
};

void draw_graph(std::vector<std::string> elements) {
    double y;
    double x;
    double eps = 4 * Pi / 200;
    for (double j = 1; j >= -1; j -= (double)2 / Heigth) {
        x = 0;
        for (int i = 0; i < Width; i++) {
            y = calculate(elements, x);
            if ((y < j + eps) && (y > j - eps))
                printf("*");
            else
                printf(".");
            x += 4 * Pi / Width;
        }
        printf("\n");
    }
}

int get_priority(std::string in) {
    return priorities[in] > 0 ? priorities[in] : 0;
}

void translate_to_polish(std::vector<std::string> &_elements) {
    std::stack<std::string> elements;
    std::vector<std::string> out;
    int j = 0;
    for (int i = 0; i < (int)_elements.size(); i++) {
        if (get_priority(_elements[i]) == 0) {
            out.push_back(_elements[i]);
        } else {
            if (elements.empty()) {
                elements.push(_elements[i]);
            } else if (_elements[i] == "(") {
                elements.push(_elements[i]);
            } else if (_elements[i] == ")") {
                while (elements.top() != "(") {
                    out.push_back(elements.top());
                    elements.pop();
                    j++;
                }
                elements.pop();
            } else if (get_priority(elements.top()) < get_priority(_elements[i])) {
                elements.push(_elements[i]);
            } else if (get_priority(elements.top()) >= get_priority(_elements[i])) {
                while ((!elements.empty()) && (get_priority(elements.top()) >= get_priority(_elements[i]))) {
                    out.push_back(elements.top());
                    elements.pop();
                    j++;
                }
                elements.push(_elements[i]);
            }
        }
    }
    while (!elements.empty()) {
        out.push_back(elements.top());
        elements.pop();
    }
    _elements = out;
}

double calculate(std::vector<std::string> elements, double x) {
    int i = 0;
    std::stack<std::string> operation;
    for (int i = 0; i < elements.size(); i++) {
        std::string token = elements[i];
        if (token == "x")
            token = std::to_string(x);
        if (get_priority(token) == 0) {
            operation.push(token);
        } else if (get_priority(token) > 2) {
            double a = std::stod(operation.top());
            operation.pop();
            operation.push(std::to_string(func_one_arg(token, a)));
        } else if (get_priority(token) <= 2) {
            double a = std::stod(operation.top());
            operation.pop();
            double b = std::stod(operation.top());
            operation.pop();
            operation.push(std::to_string(func_two_args(token, a, b)));
        }
    }
    return std::stod(operation.top());
}

double func_two_args(std::string op, double a, double b) {
    double result;
    if (op == "+")
        result = a + b;
    if (op == "-")
        result = a - b;
    if (op == "/")
        result = a / b;
    if (op == "*")
        result = a * b;
    return result;
}

double func_one_arg(std::string op, double a) {
    double result;
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

int main() {
    std::string input;
    getline(std::cin, input);
    parser *parse = new parser(input);
    parse->run();
    draw_graph(parse->get_tokens());
    return 0;
}
