//
//PEShaderReader
//
#include "PEShaders.h"

string PEShaderReader::readShaderSrc(const char *file)
{
	FILE *fp = fopen(file, "rt");
	if(fp == NULL){
		PELog("can open file %s\n", file);
		return "";
	}
	char a;
	size_t len = 1;
	while(fread(&a, 1, sizeof(char), fp) == 1){
		++ len;
	}
	char *buf = new char[len];
	fseek(fp, 0, SEEK_SET);
	int ret = fread(buf, sizeof(char), len, fp);
	buf[ret] = '\0';
	string src = buf;
	delete [] buf;
	return src;
}

