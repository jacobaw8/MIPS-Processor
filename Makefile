# Compiler to use
CXX=g++
# Compiler flags
CXXFLAGS=-std=c++11 -Wall
# Executable file name
EXECUTABLE=mips_monitor
# Command line arguments
FILE=in.bin
FLAG=

all: $(EXECUTABLE)

$(EXECUTABLE): Program.cpp
	$(CXX) $(CXXFLAGS) Program.cpp -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
	rm *.o

run:
	./$(EXECUTABLE) $(FILE) $(FLAG)