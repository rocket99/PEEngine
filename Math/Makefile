#Makefile

CC = g++ -std=c++11
all:PEDataType.o PEMatrix.o PEVector.o PELine.o

PEDataType.o:PEDataType.cpp PEDataType.h
	$(CC) -c PEDataType.cpp
PEMatrix.o:PEMatrix.cpp PEMatrix.h
	$(CC) -c PEMatrix.cpp 
PEVector.o:PEVector.cpp PEVector.h
	$(CC) -c PEVector.cpp  
PELine.o:PELine.cpp PELine.h
	$(CC) -c PELine.cpp
clean:
	rm *.o
