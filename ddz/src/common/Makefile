export CXX:=g++
pwd := $(shell pwd)
export CXX_FlAGS:=-g -O2 -Wall -std=c++17 -I$(pwd)
export LD_FLAGS:=
export RM:= rm -f

objects := $(patsubst %.cpp, %.o, $(srcs))

all: main clean

objects:
	mkdir -p objects

main: $(objects) 	
	$(CXX) $(LD_FlAGS) -o $@ objects/*
	@mv main ..

%.o: %.cpp objects
	$(CXX) $(CXX_FlAGS) -o objects/$(notdir $@) -c $<

clean: 
	$(RM) -r objects
