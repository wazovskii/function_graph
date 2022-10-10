FLAGS = -Wall -Werror -Wextra -std=c++17
COMPILER = g++

all: graph

graph: calculate.cpp parser.cpp polish_notation.cpp main.cpp
	$(COMPILER) $(FLAGS) $^ -o $@

clean:
	rm -rf *.o
	rm graph

