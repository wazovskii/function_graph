#include "parser.hpp"

bool parser::check_for_errors() {
    return check_brackets() && check_func_names();
}

bool parser::check_brackets() {
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

void parser::prepare_buffer() {
    parse_unary_minus();
    parse_mul();
    tokenize_string();
}

void parser::parse_unary_minus() {
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

void parser::parse_mul() {
    int j = 0;
    int last = 0;
    for (size_t i = 0; i < input.size(); i++) {
        if (last && input[i] == 'x') {
            input.insert(i, 1, '*');
        }
        last = isdigit(input[i]);
    }
}

bool parser::check_func_names() {
    std::string input_copy = input;
    for (auto &it : avalible_functions) {
        size_t pos = input_copy.find(it + "(");
        while (pos != std::string::npos) {
            input_copy.erase(pos, it.size());
            pos = input_copy.find(it + "(");
        }
    }

    for (int i = 0; i < input_copy.size(); i++) {
        if (isalpha(input_copy[i]) && (input_copy[i] != 'x')) {
            return false;
        }
    }
    return true;
}

void parser::tokenize_string() {
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

int parser::get_last_type(char in) {
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

parser::parser(std::string input_) : input(input_) {}

std::vector<std::string> parser::run() {
    std::string buffer;
    int error = 0;
    if (check_for_errors()) {
        prepare_buffer();
    } else {
        printf("Error\n");
        exit(0);
    }
    return elements;
}

std::vector<std::string> parser::get_tokens() {
    return elements;
}
