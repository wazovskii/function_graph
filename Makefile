CC = g++
ODIR = build
SDIR = src
INC = -Iinc
FLAGS = -std=c++17 -Wall -Werror -Wextra
OUT = graph

_OBJS = calculate.o parser.o polish_notation.o main.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.cpp 
	$(CC) -c $(INC) -o $@ $< $(FLAGS) 

$(OUT): $(OBJS) 
	$(CC) $^ -o $(OUT)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(OUT)