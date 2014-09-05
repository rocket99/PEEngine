#Makefile

CC = g++ -std=c++11
all:PEDataType.o PEMatrix.o PEVector.o PECamera.o

PEDataType.o:PEDataType.cpp PEDataType.h
	$(CC) -c PEDataType.cpp && cp PEDataType.o ..
PEMatrix.o:PEMatrix.cpp PEMatrix.h
	$(CC) -c PEMatrix.cpp && cp PEMatrix.o ..
PEVector.o:PEVector.cpp PEVector.h
	$(CC) -c PEVector.cpp && cp PEVector.o ..
PECamera.o:PECamera.cpp PECamera.h
	$(CC) -c PECamera.cpp && cp PECamera.o ..
clean:
	rm *.o
