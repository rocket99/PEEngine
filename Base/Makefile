#Makefile

CC=g++ --std=c++11 
DGL= -DGL_GLEXT_PROTOTYPES

ALL:	PEAutoReleasePool.o PEObject.o PENode.o PERealNode.o PELayer3D.o \
		PEPolygonNode.o PERect.o PESphereSurface.o PEPolarSurface.o PEMeshSurface.o \
		PELight.o PEBoxNode.o PECylinder.o PEFbxModel.o PECamera.o PEPointSet.o

PEAutoReleasePool.o: PEAutoReleasePool.cpp PEAutoReleasePool.h
	$(CC) -c PEAutoReleasePool.cpp
PEObject.o:PEObject.cpp PEObject.h PEAutoReleasePool.h
	$(CC) -c PEObject.cpp
PENode.o:PENode.cpp PENode.h
	$(CC) -c PENode.cpp		$(DGL)
PERealNode.o:PERealNode.cpp PERealNode.h PELayer3D.h ../PETextureManager.h
	$(CC) -c PERealNode.cpp $(DGL)
PELayer3D.o:PELayer3D.cpp PELayer3D.h
	$(CC) -c PELayer3D.cpp  $(DGL)
PEPolygonNode.o:PEPolygonNode.cpp PEPolygonNode.h
	$(CC) -c PEPolygonNode.cpp  $(DGL)
PERect.o:PERect.cpp PERect.h
	$(CC) -c PERect.cpp		$(DGL)
PEMeshSurface.o:PEMeshSurface.cpp PEMeshSurface.h 
	$(CC) -c PEMeshSurface.cpp  $(DGL)
PESphereSurface.o:PESphereSurface.cpp PESphereSurface.h
	$(CC) -c PESphereSurface.cpp	$(DGL)
PEPolarSurface.o:PEPolarSurface.cpp PEPolarSurface.h
	$(CC) -c PEPolarSurface.cpp	$(DGL)
PELight.o:PELight.cpp PELight.h 
	$(CC) -c PELight.cpp	$(DGL)
PEBoxNode.o:PEBoxNode.cpp PEBoxNode.h
	$(CC) -c PEBoxNode.cpp		$(DGL)
PECylinder.o:PECylinder.cpp PECylinder.h
	$(CC) -c PECylinder.cpp $(DGL)
PEFbxModel.o: PEFbxModel.cpp PEFbxModel.h
	$(CC) -c PEFbxModel.cpp $(DGL)
PECamera.o:PECamera.cpp PECamera.h
	$(CC) -c PECamera.cpp  $(DGL)
PEPointSet.o:PEPointSet.cpp PEPointSet.h
	$(CC) -c PEPointSet.cpp $(DGL)

clean:
	rm *.o


