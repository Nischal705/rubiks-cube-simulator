CXX = g++
CXXFLAGS = -g -w -std=c++17
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CPP_FILES = main.cpp
TARGET = main

all: $(TARGET)

$(TARGET) : $(CPP_FILES)
	$(CXX) $(CPP_FILES) $(CXXFLAGS) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
