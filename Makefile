GLAD_DIR = ./GLAD
SRC_DIR  = ./src
INCLUDE = -I$(GLAD_DIR)/include -I./include/

main: *.c
	cc main.c $(SRC_DIR)/*.c -o main -lSDL2 $(INCLUDE) $(GLAD_DIR)/src/glad.c -ggdb2 -ldl