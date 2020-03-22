CC= g++
PROG_NAME =  CuatroEnLinea
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt
SRC = *.cpp
FLAG = -Wall -ggdb3

run: compile
	./$(PROG_NAME)
compile:
	$(CC) $(FLAG) $(SRC) -o $(PROG_NAME)
valgrind:
	$(VALGRIND) ./$(PROG_NAME)
