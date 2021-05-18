CC = g++
BIN= auto_svg

all: $(BIN).y $(BIN).l
	bison -dg $(BIN).y
	dot -Tpng $(BIN).dot -o $(BIN).png
	flex -vT $(BIN).l
	$(CC) lex.yy.c $(BIN).tab.c node.cpp edge.cpp svg.cpp -o $(BIN).bin
	./$(BIN).bin

clean:
	rm -fv $(BIN).bin $(BIN).tab.h $(BIN).tab.c lex.yy.c $(BIN).dot $(BIN).png *~
