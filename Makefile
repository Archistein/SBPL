all: main helper preproc lexer data vm error_handler build

main: src/main.cpp
	g++ -c src/main.cpp -o obj/main.o

helper: src/helper.cpp
	g++ -c src/helper.cpp -o obj/helper.o

preproc: src/preprocessor.cpp
	g++ -c src/preprocessor.cpp -o obj/preprocessor.o

lexer: src/lexer.cpp
	g++ -c src/lexer.cpp -o obj/lexer.o

data: src/data.cpp
	g++ -c src/data.cpp -o obj/data.o

vm: src/vm.cpp
	g++ -c src/vm.cpp -o obj/vm.o

error_handler: src/error_handler.cpp
	g++ -c src/error_handler.cpp -o obj/error_handler.o

build: obj/*.o
	g++ obj/*.o -o build/vm.out

run:
	./build/vm.out