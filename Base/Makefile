#Makefile

CC=g++ --std=c++11 

all:PEObject.o PENode.o PERealNode.o PELayer3D.o PEPolygon.o PERect.o PESphere.o PEPolarSurface.o PEMeshSurface.o PELight.o PEBox.o PECylinder.o

PEObject.o:PEObject.cpp PEObject.h
	$(CC) -c PEObject.cpp
PENode.o:PENode.cpp PENode.h
	$(CC) -c PENode.cpp
PERealNode.o:PERealNode.cpp PERealNode.h PELayer3D.h
	$(CC) -c PENode.cpp
PELayer3D.o:PELayer3D.cpp PELayer3D.h
	$(CC) -c PELayer3D.cpp
PEPolygon.o:PEPolygon.cpp PEPolygon.h
	$(CC) -c PEPolygon.cpp
PERect.o:PERect.cpp PERect.h
	$(CC) -c PERect.cpp
PEMeshSurface.o:PEMeshSurface.cpp PEMeshSurface.h
	$(CC) - c PEMeshSurface.cpp
PESphere.o:PESphere.cpp PESphere.h
	$(CC) -c PESphere.cpp
PEPolarSurface.o:PEPolarSurface.cpp PEPolarSurface.h
	$(CC) -c PEPolarSurface.cpp
PELight.o:PELight.cpp PELight.h
	$(CC) -C PELight.cpp
PEBox.o:PEBox.cpp PEBox.h
	$(CC) -c PEBox.cpp
PECylinder.o:PECylinder.cpp PECylinder.h
	$(CC) -c PECylinder.cpp

clean:
	rm *.o
