#Makefile

CC=g++ --std=c++11

ALL:PEShaders.o PEShaderManager.o PEGLProgram.o 

PEShader.o:PEShaders.cpp PEShaders.h
	$(CC) -c PEShaders.cpp
PEGLProgram.o:PEGLProgram.cpp PEGLProgram.h
	$(CC) -c PEGLProgram.cpp
PEShaderManager.o:PEShaderManager.cpp PEShaderManager.h
	$(CC) -c PEShaderMananger.cpp

clean:
	rm *.o


