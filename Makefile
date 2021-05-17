CC = g++
BIN= auto_svg

all: $(BIN).y $(BIN).l
	bison -dg $(BIN).y
	dot -Tpng $(BIN).dot -o $(BIN).png
	flex -vT $(BIN).l
	$(CC) lex.yy.c $(BIN).tab.c test.cpp -o $(BIN).bin
	./$(BIN).bin

clean:
	rm -fv $(BIN).bin $(BIN).tab.h $(BIN).tab.c lex.yy.c lex.yy.o $(BIN).tab.o lex.backup $(BIN).dot $(BIN).png $(BIN).output node.o edge.o svg.o *~
