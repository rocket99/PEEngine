//
//  PEObject.cpp
//  Engine
//
//  Created by rocket99 on 14-8-20.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEObject.h"
#include "PEAutoReleasePool.h"
#include "PENode.h"

PEObject *PEObject::create(const char *str)
{
    PEObject *obj = new PEObject;
    obj->setName(str);
    return obj;
}

void PEObject::retain()
{
    PENode *node = static_cast<PENode *>(this);
    if (node != NULL) {
        for(int i=0; i<node->getChildren().size(); ++i){
            node->getChildren()[i]->retain();
        }
    }
    ++ m_retain;
}

void PEObject::release()
{
    PENode *node = static_cast<PENode *>(this);
    if (node != NULL) {
        for(int i=0; i<node->getChildren().size(); ++i){
            node->getChildren()[i]->release();
        }
    }
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

void PEObject::safeDelete()
{
    if(PEAutoReleasePool::Instance()->isObjectInPool(this)){
        this->m_retain = 0;
        
    }else{
        delete this;
    }
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
