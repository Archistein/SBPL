all: main helper preproc lexer parser compiler data vm error_handler build

main: src/main.cpp
	g++ -c src/main.cpp -o build/obj/main.o

helper: src/helper.cpp
	g++ -c src/helper.cpp -o build/obj/helper.o

preproc: src/preprocessor.cpp
	g++ -c src/preprocessor.cpp -o build/obj/preprocessor.o

lexer: src/lexer.cpp
	g++ -c src/lexer.cpp -o build/obj/lexer.o

parser: src/parser.cpp
	g++ -c src/parser.cpp -o build/obj/parser.o

compiler: src/compiler.cpp
	g++ -c src/compiler.cpp -o build/obj/compiler.o

data: src/data.cpp
	g++ -c src/data.cpp -o build/obj/data.o

vm: src/vm.cpp
	g++ -c src/vm.cpp -o build/obj/vm.o

error_handler: src/error_handler.cpp
	g++ -c src/error_handler.cpp -o build/obj/error_handler.o

build: build/obj/*.o
	g++ build/obj/*.o -o build/sbpl

run:
	./build/sbpl