CC = g++
GLAD = ./GLAD
HEADERS = ./include

INCLUDE = -I$(HEADERS) -I$(GLAD)/include
SRC     = ./src/*.cpp $(GLAD)/src/glad.c
LIB     = -lSDL2 -ldl

main: main.cpp 
	$(CC) main.cpp -o main $(LIB) $(INCLUDE) $(SRC) -ggdb2