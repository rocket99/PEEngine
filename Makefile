#Makefile

main:main.o PEMatrix.o
	g++ -o main main.o PEMatrix.o

main.o:main.cpp
	g++ -c main.cpp
PEMatrix.o:PEMatrix.h PEMatrix.cpp
	g++ -c PEMatrix.cpp
clean:
	rm *.o
