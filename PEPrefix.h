#ifndef __PEPrefix_H__
#define __PEPrefix_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define _GNU_SOURCE
#include <assert.h>

#ifdef __cplusplus
#include <iostream>
#include <vector>
#include <map>
#include <list>
using namespace std;
#endif

#define PELog(format, ...) printf("%s:(%d)" format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define PE_Assert(expr, msg)  (void)((expr)?((void)0):assert_msg(__FILE__, __LINE__, msg))
void assert_msg(const char *file, int line, const char *msg)
{
	printf("%s(%d):%s\n", file, line, msg);
	abort();
}

#endif
