//
//  PEObject.h
//  Engine
//
//  Created by rocket99 on 14-8-20.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PEObject__
#define __Engine__PEObject__

#include "PEPrefix.h"

class PEObject
{
public:
    static PEObject *create(const char *str);
    void setName(const char *str);
    string getName();
    int retainCount();
    void retain();
    void release();
protected:
    PEObject(){};
    virtual ~PEObject(){};
private:
    int m_retain;
    string m_name;
};

#endif /* defined(__Engine__PEObject__) */


