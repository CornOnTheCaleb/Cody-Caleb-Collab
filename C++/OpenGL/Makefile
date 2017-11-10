# Makefile
SOURCES_CPP = $(wildcard *.cpp)
SOURCES_C = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES_CPP:%.cpp=%.o) $(SOURCES_C:%.c=%.o)
CFLAGS = -Wall --pedantic-errors -O2
LFLAGS = -lglfw3 -lGL -lXrandr -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor
CPP = g++

%.o: %.c ${HEADERS}
	${CPP} ${CFLAGS} -c $< ${LFLAGS}

%.o: %.cpp ${HEADERS}
	${CPP} ${CFLAGS} -c $< ${LFLAGS}

program: ${OBJECTS}
	${CPP} ${CFLAGS} ${OBJECTS} -o program ${LFLAGS}

.PHONY: clean
clean:
	-@rm -f program
	-@rm -f ${OBJECTS}
