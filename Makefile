OBJ = main.o game.o io.o load.o myString.o room.o
FLAGS = -Wall -std=c99 -lncurses -Iinclude
EXE = run.out

all: $(EXE)
$(EXE): $(OBJ)
	gcc $(OBJ) -o $(EXE) $(FLAGS)
main.o: src/main.c
	gcc -c src/main.c $(FLAGS)
game.o: src/game.c
	gcc -c src/game.c $(FLAGS)
io.o: src/io.c
	gcc -c src/io.c $(FLAGS)
load.o: src/load.c
	gcc -c src/load.c $(FLAGS)
myString.o: src/myString.c
	gcc -c src/myString.c $(FLAGS)
room.o: src/room.c
	gcc -c src/room.c $(FLAGS)
run:
	./$(EXE) assets/map1.lvl
clean:
	rm $(OBJ) $(EXE)
debug: $(OBJ)
	gcc $(OBJ) -o $(EXE) $(FLAGS) -g
runVal:
	valgrind --track-origins=yes --show-reachable=yes  ./$(EXE) assets/map1.lvl
