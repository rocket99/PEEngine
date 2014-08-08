#ifndef __PEPrefix_H__
#define __PEPrefix_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


#ifdef __cplusplus
#include <iostream>
#include <vector>
#include <map>
#include <list>
using namespace std;
#endif

#define PELog(format, ...) printf("%s:(%d)" format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif
