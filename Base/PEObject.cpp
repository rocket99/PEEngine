//
//  PEObject.cpp
//  Engine
//
//  Created by rocket99 on 14-8-20.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEObject.h"
#include "PEAutoReleasePool.h"

PEObject *PEObject::create(const char *str)
{
    PEObject *obj = new PEObject;
    obj->setName(str);
    return obj;
}

void PEObject::retain()
{
    ++ m_retain;
}

void PEObject::release()
{
    -- m_retain;
    if(m_retain == 0){
        delete this;
    }
}

void PEObject::autoRelease()
{
	-- m_retain;
	PEAutoReleasePool::Instance()->addObject(this);
}

void PEObject::setName(const char *str)
{
    this->m_name = str;
}

string PEObject::getName()
{
    return m_name;
}
int PEObject::retainCount()
{
    return m_retain;
}
