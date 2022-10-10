#include "polish_notation.hpp"

void translate_to_polish(std::vector<std::string> &_elements) {
    std::stack<std::string> elements;
    std::vector<std::string> out;
    int j = 0;
    for (size_t i = 0; i < _elements.size(); i++) {
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
