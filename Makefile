CC=g++
CCFLAGS=-Wall -std=c++20
CCLIB=-lsqlite3
TARGET=teste.x
FORMAT=@clang-format -style=Chromium -i

all: $(TARGET)

HEADERS=$(wildcard src/*.hpp)
OBJECTS=$(HEADERS:.hpp=.o)

VPATH = src

%.o: %.cpp %.hpp
	$(FORMAT) $^
	$(CC) $(CCFLAGS) $(DEBUG) -c $< -o $@

main.o: main.cpp
	$(FORMAT) $^
	$(CC) $(CCFLAGS) $(DEBUG) -c  $^ -o $@

$(TARGET): main.o $(OBJECTS)
	$(CC) $^ $(DEBUG) $(CCLIB) -o $@

test: $(TARGET)
	./$(TARGET)

memcheck: $(TARGET)
	valgrind ./$(TARGET)

format: main.cpp
	@$(FORMAT) $^

clean:
	@rm -v main.o $(TARGET) $(OBJECTS)

teste:
	@echo  $(HEADERS) $(OBJECTS)
