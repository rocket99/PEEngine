#Makefile

CC = g++ -std=c++11
all:PEDataType.o PEMatrix.o PEVector.o PELine.o PEPlane.o PEPolygon.o PESphere.o

PEDataType.o:PEDataType.cpp PEDataType.h
	$(CC) -c PEDataType.cpp
PEMatrix.o:PEMatrix.cpp PEMatrix.h
	$(CC) -c PEMatrix.cpp 
PEVector.o:PEVector.cpp PEVector.h
	$(CC) -c PEVector.cpp  
PELine.o:PELine.cpp PELine.h
	$(CC) -c PELine.cpp
PEPlane.o:PEPlane.cpp PEPlane.h
	$(CC) -c PEPlane.cpp
PEPolygon.o:PEPolygon.cpp PEPolygon.h PEDataType.h
	$(CC) -c PEPolygon.cpp
PESphere.o:PESphere.cpp PESphere.h
	$(CC) -c PESphere.cpp
clean:
	rm *.o
