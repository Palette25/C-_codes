CC := g++
FLAGS := -std=c++11 -w

DIR_BIN = ./bin
DIR_OBJ = ./bulid
DIR_INC = ./include
DIR_SRC = ./src

SRC = $(wildcard ${DIR_SRC}/*.c)
OBJ = $(patsubst ${DIR_OBJ}/*.c, $(notdir ${SRC}))

TARGET = main
BIN_TAEGET = ${DIR_BIN}/${TARGET}

${BIN_TAEGET}:${OBJ}
  $(CC) $(OBJ) -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf()

