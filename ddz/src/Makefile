CXX:=g++
CXX_FLAGS:=$(CXX_FLAGS) -g -O2
LD_FLAGS:=$(LD_FLAGS)
RM:=rm -rf
MKDIR:=mkdir -p

srcs:=$(wildcard *.cpp)
objects:=$(patsubst %.cpp, %.o, $(srcs))

all: main clean

main: $(objects)
	$(CXX) $(LD_FLAGS) -o main $(objects)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXX_FLAGS)

clean:
	$(RM) *.o

.PHONY: all 
