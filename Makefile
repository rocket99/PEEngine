#Makefile

LINK = -lglfw3 -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lm -lrt -luuid -lc -ldl -lpng -ljpeg
BPath = Base/
MPath = Math/
SPath = Shader/
BASE =	$(BPath)PEObject.o $(BPath)PENode.o $(BPath)PERealNode.o $(BPath)PEPolygonNode.o \
		$(BPath)PERect.o $(BPath)PEMeshSurface.o $(BPath)PEPolarSurface.o $(BPath)PESphereSurface.o \
		$(BPath)PECylinder.o $(BPath)PECamera.o $(BPath)PEBoxNode.o $(BPath)PEPointSet.o\
		$(BPath)PELayer3D.o $(BPath)PELight.o $(BPath)PEAutoReleasePool.o 

MATH =	$(MPath)PEPolygon.o $(MPath)PEMatrix.o $(MPath)PEVector.o $(MPath)PELine.o \
		$(MPath)PEPlane.o  $(MPath)PEDataType.o $(MPath)PESphere.o

SHADER = $(SPath)PEGLProgram.o $(SPath)PEShaderManager.o $(SPath)PEShaders.o

CC = g++ --std=c++11
DGL = -DGL_GLEXT_PROTOTYPES
ALL:main
main:main.o PEScene.o TestScene.o PETexture.o PETextureManager.o PEKeyboardManager.o $(BASE) $(MATH) $(SHADER)
	$(CC) -o main main.o PEScene.o TestScene.o PETexture.o PETextureManager.o PEKeyboardManager.o $(BASE) $(MATH) \
		$(SHADER) $(LINK)
main.o:main.cpp PEEngine.h PEMacro.h
	$(CC) -c main.cpp
PEScene.o:PEScene.cpp PEScene.h TestScene.h
	$(CC) -c PEScene.cpp $(DGL)
PETexture.o:PETexture.cpp PETexture.h
	$(CC) -c PETexture.cpp $(DGL)
PETextureManager.o:PETextureManager.cpp PETextureManager.h
	$(CC) -c PETextureManager.cpp
TestScene.o:TestScene.h TestScene.cpp
	$(CC) -c TestScene.cpp 
PEKeyboardManager.o:PEKeyboardManager.cpp PEKeyboardManager.h
	$(CC) -c PEKeyboardManager.cpp

$(BASE):
	cd ./Base && $(MAKE)	
$(MATH):
	cd ./Math && $(MAKE)
$(SHADER):
	cd ./Shader && $(MAKE)

clean:
	rm *.o ./Base/*.o ./Math/*.o ./Shader/*.o ./main


