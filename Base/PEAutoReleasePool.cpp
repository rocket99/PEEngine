#include "PEAutoReleasePool.h"

static PEAutoReleasePool *pool = NULL;

PEAutoReleasePool *PEAutoReleasePool::Instance()
{
	if(NULL == pool){
		pool = new PEAutoReleasePool();
	}
	return pool;
}

void PEAutoReleasePool::purge()
{
	if(NULL != pool){
		delete pool;
	}
	pool = NULL;
}

void PEAutoReleasePool::addObject(PEObject *obj)
{
	if(isObjectInPool(obj)){
		return;
	}
	m_objs.push_back(obj);
}

void PEAutoReleasePool::clearNoReferenceCountObj()
{
	vector<PEObject *>::iterator it = m_objs.begin();
	while(it != m_objs.end()){
		if(*it->retainCount() == 0){
			delete *it;
			m_objs.erase(it);
		}else{
			++ it;
		}
	}
}

bool PEAutoReleasePool::isObjectInPool(PEObject *obj)
{
	vector<PEObject *>::iterator it = m_objs.begin();
	while(*it != obj && it != m_objs.end()){
		++ it;
	}
	return it != m_objs.end();
}
