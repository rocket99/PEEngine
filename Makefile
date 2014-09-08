#Makefile

LINK = -lglfw3 -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lpthread -lXi
BASE:PEObject.o PENode.o PERealNode.o PEPolygon.o PERect.o PEMeshSurface.o \
		PEPolarSurface.o PESphere.o PECylinder.o PEBox.o PELayer3D.o PELight.o 
MATH:PECamera.o PEDataType.o PEMatrix.o PEVector.o
SHADER:PEGLProgram.o PEGLShaderManager.o PEShaders.o
CC = g++ --std=c++11
ALL:main
main:main.o $(BASE) $(MATH) $(SHADER)
	$(CC) -o main main.o $(BASE) $(MATH) $(SHADER) $(LINK)
$(BASE):
	cd ./Base && $(MAKE)	
$(MATH):
	cd ./Math && $(MAKE)
$(SHADER):
	cd ./Shader && $(MAKE)

clean:
	rm *.o main
	cd Base/ && rm *.o
	cd Math/ && rm *.o
	cd Shader/ && rm *.o
