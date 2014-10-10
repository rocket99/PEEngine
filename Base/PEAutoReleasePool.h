#ifndef __PEAutoReleasePool_H__
#define __PEAutoReleasePool_H__

#include "../PEPrefix.h"
#include "PEObject.h"

class PEAutoReleasePool
{
public:
	static PEAutoReleasePool *Instance();
	static void purge();
	void addObject(PEObject *obj);
	void clearNoReferenceCountObj();
    bool isObjectInPool(PEObject *obj);
private:
	
	vector<PEObject *> m_objs;

};
#endif
