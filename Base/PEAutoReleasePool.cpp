#include "PEAutoReleasePool.h"
#include "PENode.h"

static PEAutoReleasePool *pool = NULL;

PEAutoReleasePool::PEAutoReleasePool()
{
	m_thread = nullptr;
}

PEAutoReleasePool::~PEAutoReleasePool()
{

}

PEAutoReleasePool *PEAutoReleasePool::Instance()
{
	if(NULL == pool){
		pool = new PEAutoReleasePool();
		pool->init();
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

bool PEAutoReleasePool::init()
{
	m_thread = new std::thread(std::bind(&PEAutoReleasePool::clearNoReferenceCountObj, this));
	return true;
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
		if((*it)->retainCount() == 0){
            PENode *node = static_cast<PENode *>(*it);
            if(node != NULL){
                for(int i=0; i<node->getChildren().size(); ++i){
                    node->getChildren()[i]->safeDelete();
                }
            }
            (*it)->safeDelete();
			m_objs.erase(it);
		}else{
			++ it;
		}
	}
}

bool PEAutoReleasePool::isObjectInPool(PEObject *obj)
{
	vector<PEObject *>::iterator it = m_objs.begin();
	while(it != m_objs.end() && *it != obj){
		++ it;
	}
	return it != m_objs.end();
}



