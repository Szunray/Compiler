comp: main.o generate.o parser.o scanner.o stack.o traverse.o treePrint.o node_t.h token.h
	g++ -o comp main.o generate.o parser.o scanner.o stack.o traverse.o treePrint.o node_t.h token.h

main.o: main.cpp 
	g++ -c main.cpp

generate.o: generate.cpp
	g++ -c generate.cpp

parser.o: parser.cpp
	g++ -c parser.cpp

scanner.o: scanner.cpp
	g++ -c scanner.cpp

stack.o: stack.cpp
	g++ -c stack.cpp

traverse.o: traverse.cpp
	g++ -c traverse.cpp

treePrint.o: treePrint.cpp
	g++ -c treePrint.cpp
