CC = g++
GLAD = ./GLAD
GLM = ./GLM
HEADERS = ./include 

INCLUDE = -I$(HEADERS) -I$(GLAD)/include 
SRC     = ./src/*.cpp $(GLAD)/src/glad.c
LIB     = -lSDL2 -ldl

TRIANGLE = ./TRIANGLE
CUBE     = ./CUBE


all: triangle cube

triangle: $(TRIANGLE)/triangle.cpp 
	$(CC) $(TRIANGLE)/triangle.cpp -o $(TRIANGLE)/triangle $(LIB) $(INCLUDE) $(SRC) -ggdb2

cube: $(CUBE)/cube.cpp	
	$(CC) $(CUBE)/cube.cpp -o $(CUBE)/cube $(LIB) $(INCLUDE) $(SRC) -ggdb2 -I$(GLM)  ./CUBE/CAMERA/camera.cpp 

