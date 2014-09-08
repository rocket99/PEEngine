#Makefile

CC=g++ --std=c++11

ALL:PEShaders.o PEShaderManager.o PEGLProgram.o 

PEShaders.o:PEShaders.cpp PEShaders.h
	$(CC) -c PEShaders.cpp
PEGLProgram.o:PEGLProgram.cpp PEGLProgram.h
	$(CC) -c PEGLProgram.cpp -DGL_GLEXT_PROTOTYPES
PEShaderManager.o:PEShaderManager.cpp PEShaderManager.h
	$(CC) -c PEShaderManager.cpp -DGL_GLEXT_PROTOTYPES

clean:
	rm *.o


