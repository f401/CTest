CXX:=g++
CXX_FLAGS:=$(CXX_FLAGS) -g -O2
LINK_FLAGS:=$(LINK_FLAGS) -s
RM=rm -f

objects:=defines.o main.o

main: $(objects)
	$(CXX) -o $@ $^
clean: 
	$(RM) *.o

defines.o: defines.cpp

main.o: main.cpp

all: main clean

.PHONY: all
