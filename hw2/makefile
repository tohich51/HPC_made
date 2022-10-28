CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp matmul.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=matmul

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@