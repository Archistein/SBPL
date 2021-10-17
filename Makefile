all: main preproc data vm error_handler build

main: src/main.cpp
	g++ -c src/main.cpp -o obj/main.o

preproc: src/preprocessor.cpp
	g++ -c src/preprocessor.cpp -o obj/preprocessor.o

data: src/data.cpp
	g++ -c src/data.cpp -o obj/data.o

vm: src/vm.cpp
	g++ -c src/vm.cpp -o obj/vm.o

error_handler: src/error_handler.cpp
	g++ -c src/error_handler.cpp -o obj/error_handler.o

build: obj/main.o obj/data.o obj/vm.o obj/error_handler.o obj/preprocessor.o
	g++ obj/main.o obj/data.o obj/vm.o obj/error_handler.o obj/preprocessor.o -o build/vm.out

run:
	./build/vm.out