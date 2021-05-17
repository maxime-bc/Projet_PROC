BIN= auto_svg

all: $(BIN).y $(BIN).l
	bison -dg $(BIN).y
	dot -Tpng $(BIN).dot -o $(BIN).png
	flex -vT $(BIN).l
	$(CC) -c lex.yy.c -o lex.yy.o
	$(CC) -c edge.c -o edge.o
	$(CC) -c node.c -o node.o
	$(CC) -c svg.c -o svg.o
	$(CC) -c $(BIN).tab.c -o $(BIN).tab.o
	$(CC) -o $(BIN).bin lex.yy.o $(BIN).tab.o edge.o node.o svg.o -ll -lm
	./$(BIN).bin

clean:
	rm -fv $(BIN).bin $(BIN).tab.h $(BIN).tab.c lex.yy.c lex.yy.o $(BIN).tab.o lex.backup $(BIN).dot $(BIN).png $(BIN).output node.o edge.o svg.o *~
