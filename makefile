PROYECTO := programa
CXX := c++
LIB := -lftxui-screen -lftxui-dom -lftxui-component
INCLUDE := -Iinclude
EXE := bin/$(PROYECTO)

.PHONY: all run Nave archivos clean AsteroidsB

all: $(EXE)

$(EXE): src/main.cpp | bin
	$(CXX) $< -o $@ $(LIB) $(INCLUDE) -std=c++17

	run: bin/AsteroidsB
	./bin/AsteroidsB

archivos: bin/archivos
	./bin/archivos

bin/archivos: src/archivos.cpp | bin
	$(CXX) $< -o $@ -std=c++17

clean:
	del /Q bin\*.exe

AsteroidsB: bin/AsteroidsB
	./bin/AsteroidsB

bin/AsteroidsB: src/AsteroidsB.cpp | bin
	$(CXX) $< -o $@ -std=c++17

bin:
	mkdir bin