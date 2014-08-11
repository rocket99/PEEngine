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

#define ASSERT_ENABLE 1
#if ASSERT_ENABLE>0
	#define PE_Assert(expr, msg) do{ 	\
		if(!(expr)) {		 	\
			PELog(msg);		\
			assert(expr);		\
		}				\
		}while(0)				
#else
	#define PE_Assert(expr, msg) // assert(expr) 
#endif


#endif
