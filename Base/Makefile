#Makefile

CC=g++ --std=c++11 
DGL= -DGL_GLEXT_PROTOTYPES

ALL:PEObject.o PENode.o PERealNode.o PELayer3D.o PEPolygon.o \
	PERect.o PESphere.o PEPolarSurface.o PEMeshSurface.o \
	PELight.o PEBox.o PECylinder.o

PEObject.o:PEObject.cpp PEObject.h
	$(CC) -c PEObject.cpp
PENode.o:PENode.cpp PENode.h
	$(CC) -c PENode.cpp		$(DGL)
PERealNode.o:PERealNode.cpp PERealNode.h PELayer3D.h ../PETextureManager.h
	$(CC) -c PERealNode.cpp $(DGL)
PELayer3D.o:PELayer3D.cpp PELayer3D.h
	$(CC) -c PELayer3D.cpp  $(DGL)
PEPolygon.o:PEPolygon.cpp PEPolygon.h
	$(CC) -c PEPolygon.cpp  $(DGL)
PERect.o:PERect.cpp PERect.h
	$(CC) -c PERect.cpp		$(DGL)
PEMeshSurface.o:PEMeshSurface.cpp PEMeshSurface.h 
	$(CC) -c PEMeshSurface.cpp  $(DGL)
PESphere.o:PESphere.cpp PESphere.h
	$(CC) -c PESphere.cpp	$(DGL)
PEPolarSurface.o:PEPolarSurface.cpp PEPolarSurface.h
	$(CC) -c PEPolarSurface.cpp	$(DGL)
PELight.o:PELight.cpp PELight.h 
	$(CC) -c PELight.cpp	$(DGL)
PEBox.o:PEBox.cpp PEBox.h
	$(CC) -c PEBox.cpp		$(DGL)
PECylinder.o:PECylinder.cpp PECylinder.h
	$(CC) -c PECylinder.cpp $(DGL)

clean:
	rm *.o


