CXX := c++
EXE := bin/AsteroidsB

.PHONY: all clean AsteroidsB runAsteroidsB

all: $(EXE)

AsteroidsB: $(EXE)
	./$(EXE)

runAsteroidsB: $(EXE)
	./$(EXE)

$(EXE): src/AsteroidsB.cpp | bin
	$(CXX) $< -o $@ -std=c++17 -lsfml-audio -lsfml-system

bin:
	mkdir bin

clean:
	del /Q bin\*.exe

NAVE_EXE := bin/Nave

.PHONY: Nave runNave

Nave: $(NAVE_EXE)
	./$(NAVE_EXE)

runNave: $(NAVE_EXE)
	./$(NAVE_EXE)

$(NAVE_EXE): src/Nave.cpp | bin
	$(CXX) $< -o $@ -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system

CXX = g++
CXXFLAGS = -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC = src/Asteroids.cpp src/Ventana.cpp
OUT = runAsteroids

runAsteroids: src/Asteroids.cpp src/Ventana.cpp src/Nave.cpp src/Misil.cpp
	g++ -Iinclude -o runAsteroids src/Asteroids.cpp src/Ventana.cpp src/Nave.cpp src/Misil.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./$(OUT)
