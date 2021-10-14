all: main data vm build run

main: src/main.cpp
	g++ -c src/main.cpp -o obj/main.o

data: src/data.cpp
	g++ -c src/data.cpp -o obj/data.o

vm: src/vm.cpp
	g++ -c src/vm.cpp -o obj/vm.o

build: obj/main.o obj/data.o obj/vm.o
	g++ obj/main.o obj/data.o obj/vm.o -o build/vm.out

run:
	./build/vm.out