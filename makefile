PROYECTO := programa
CXX := c++
LIB := -lftxui-screen -lftxui-dom -lftxui-component
INCLUDE := -Iinclude
EXE := bin/$(PROYECTO)

.PHONY: all run Nave archivos clean

all: $(EXE)

$(EXE): src/main.cpp
	$(CXX) $< -o $@ $(LIB) $(INCLUDE) -std=c++17

run: $(EXE)
	./$(EXE)

Nave: bin/Nave
	./bin/Nave

bin/Nave: src/Nave.cpp
	$(CXX) $< -o $@ -std=c++17

archivos: bin/archivos
	./bin/archivos

bin/archivos: src/archivos.cpp
	$(CXX) $< -o $@ -std=c++17

clean:
	del /Q bin\*.exe
