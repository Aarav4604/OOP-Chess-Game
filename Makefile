CC=g++ 
CFLAGS=-g -std=c++17 -Wall
LDFLAGS=
SRC_FILES=$(filter-out main.cc, $(wildcard *.cc))
OBJ_FILES=$(SRC_FILES:.cc=.o)
APP=chess

all: $(APP)

$(APP): $(OBJ_FILES) main.o
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(APP)

valgrind:
	valgrind --leak-check=full ./$(APP)
