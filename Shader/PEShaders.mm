
#include "PEShaders.h"

string PEShaderReader::readShaderSrc(const char *file)
{
    char *buffer = NULL;
    NSString *path = [[NSBundle mainBundle] pathForResource:[NSString stringWithFormat:@"%s", file]
                                                     ofType:nil];
    NSString *src = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];
    unsigned long len = [src lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    buffer = (char *)malloc(sizeof(char) * (len+1));
    if([src getCString:buffer maxLength:len+1 encoding:NSUTF8StringEncoding]){
        string str = buffer;
        free(buffer);
        return str;
    }
    return "";
}