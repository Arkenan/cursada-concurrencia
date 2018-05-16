all: main child

main: main.cpp
	g++ main.cpp -o main

child: child.cpp
	g++ child.cpp -o child

.PHONY: go

go: main
	./main
