BIN= auto_svg

all: $(BIN).y $(BIN).l
	bison -dg $(BIN).y
	dot -Tpng $(BIN).dot -o $(BIN).png
	flex -vT $(BIN).l
	$(CC) -c lex.yy.c -o lex.yy.o
	$(CC) -c struct.c -o struct.o
	$(CC) -c $(BIN).tab.c -o $(BIN).tab.o
	$(CC) -o $(BIN).bin lex.yy.o $(BIN).tab.o struct.o -ll -lm
	./$(BIN).bin

clean:
	rm -fv $(BIN).bin $(BIN).tab.h $(BIN).tab.c lex.yy.c lex.yy.o $(BIN).tab.o lex.backup $(BIN).dot $(BIN).png $(BIN).output *~
