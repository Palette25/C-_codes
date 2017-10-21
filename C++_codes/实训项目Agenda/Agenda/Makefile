CC := g++
FLAGS := -std=c++11 -g

DIR_BIN = ./bin
DIR_OBJ = ./bulid
DIR_INC = ./include
DIR_SRC = ./src

SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRC}))

TARGET = ${DIR_BIN}/main

${TARGET}: ${OBJ}
	${CC} ${FLAGS} ${OBJ} -o $@


${DIR_OBJ}/%.o: ${DIR_SRC}/%.cpp
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -r ${TARGET} ${DIR_OBJ}/*.o