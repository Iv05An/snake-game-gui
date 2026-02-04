# # Простейший Makefile для змейки
# all:
# 	g++ main.cpp Food.cpp Snake.cpp -o main -std=c++11

# run:
# 	g++ main.cpp Game.cpp Food.cpp Snake.cpp Record.cpp Menu.cpp Utils.cpp -o main -std=c++11
# 	./main

# clean:
# 	del main.exe main 2>nul || rm -f main


CXX = g++
CXXFLAGS = -std=c++17 -I./include -I"C:/SFML-2.5.0/include"
LDFLAGS = -L"C:/SFML-2.5.0/lib"
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = src
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/GameWindow.cpp $(SRC_DIR)/Food.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = snake-gui.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

copy-dll:
	cp "C:/SFML-2.5.0/bin/"*.dll .

run: all copy-dll
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) *.dll

.PHONY: all clean run copy-dll