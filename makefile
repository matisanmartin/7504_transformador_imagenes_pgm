all: tp1

tp1: main.o complejo.o cmdline.o operador.o
	g++ -Wall -pedantic -o tp1 main.o cmdline.o complejo.o operador.o

complejo.o: complejo.cpp complejo.hpp
	g++ -Wall -pedantic -c -o complejo.o complejo.cpp	

operador.o: operador.cpp operador.hpp
	g++ -Wall -pedantic -c -o operador.o operador.cpp

cmdline.o: cmdline.cpp cmdline.hpp
	g++ -Wall -pedantic -c -o cmdline.o cmdline.cpp

main.o: main.cpp common.hpp cmdline.hpp complejo.hpp operador.hpp pgm.hpp matriz.hpp procesamiento.hpp pila.hpp sy.hpp rpn_calc.hpp
	g++ -Wall -pedantic -c -o main.o main.cpp -std=c++0x
