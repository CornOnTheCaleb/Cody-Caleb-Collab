CXX = g++
CXXFLAGS = -Wpedantic -Wall -Wextra -Wfloat-conversion -Werror

OBJECTS =   main.o	\
			position.o	\
			actor.o		\

.SUFFIXES: .cpp

.cpp.o: $<
	${CXX} -c ${CXXFLAGS} $< -o $@

default: all

all: program

program: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o $@

clean:
	-@del program.exe
	-@del ${OBJECTS}

# Dependency lists
actor.o: actor.cpp
main.o: main.cpp position.hpp
position.o: position.cpp position.hpp