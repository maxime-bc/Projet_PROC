CC = c++
BIN= auto_svg

all: $(BIN).y $(BIN).l
	bison -dg $(BIN).y
	dot -Tpng $(BIN).dot -o $(BIN).png
	flex -vT $(BIN).l
	$(CC) -std=c++17 -Werror lex.yy.c $(BIN).tab.c node.cpp edge.cpp svg.cpp automaton.cpp -o $(BIN).bin
	./$(BIN).bin

clean:
	rm -fv $(BIN).bin $(BIN).tab.h $(BIN).tab.c lex.yy.c $(BIN).dot $(BIN).png *~
