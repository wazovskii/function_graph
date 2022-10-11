CC = g++
ODIR = build
SDIR = src
INC = -Iinc
FLAGS = -std=c++17 -Wall -Werror -Wextra
OUT = graph

_OBJS = calculate.o parser.o polish_notation.o main.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))
dir_guard=@mkdir -p $(@D)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(dir_guard)
	$(CC) -c $(INC) -o $@ $< $(FLAGS) 

$(OUT): $(OBJS) 
	$(CC) $^ -o $(OUT)

test: $(OBJS)
	$(CC) -c tests/test.cpp $(FLAGS)
	$(CC) -lgtest build/calculate.o build/parser.o build/polish_notation.o test.o -o test

.PHONY: clean

clean:
	rm -rf $(ODIR) $(OUT) test test.o