#include "parser.hpp"
#include "polish_notation.hpp"

#define Pi 3.14
#define Width 160
#define Heigth 25

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

int main() {
    std::string input;
    getline(std::cin, input);
    parser *parse = new parser(input);
    parse->run();
    std::vector<std::string> tokens = parse->get_tokens();
    if (tokens.size() > 1) {
        translate_to_polish(tokens);
        draw_graph(tokens);
    }
    return 0;
}