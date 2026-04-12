# Use g++ as the compiler
CXX = g++
# Enable all warnings and use C++17
CXXFLAGS = -Wall -std=c++17
# On Windows, executables end in .exe
TARGET = makefile_demo.exe

all: $(TARGET)

$(TARGET): makefile_demo.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) makefile_demo.cpp

# Windows uses 'del' instead of 'rm'
clean:
	del $(TARGET)
