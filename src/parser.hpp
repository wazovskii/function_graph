#ifndef SRC_PARSER_HPP_
#define SRC_PARSER_HPP_

#include "calculate.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <stack>

class parser {
    private:
        std::string input;
        std::vector<std::string> elements;

        bool check_for_errors();
        bool check_brackets();
        void prepare_buffer();
        void parse_unary_minus();
        void parse_mul();
        bool check_func_names();
        void tokenize_string();
        int get_last_type(char in);

    public:
        parser(std::string input_);
        std::vector<std::string> run();
        std::vector<std::string> get_tokens();
};
#endif    // SRC_PARSER_HPP_
