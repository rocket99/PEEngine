#ifndef __PEAutoReleasePool_H__
#define __PEAutoReleasePool_H__

#include "../PEPrefix.h"
#include "PEObject.h"

class PEAutoReleasePool
{
public:
	PEAutoReleasePool();
	~PEAutoReleasePool();

	static PEAutoReleasePool *Instance();
	static void purge();
	bool init();

	void addObject(PEObject *obj);
    bool isObjectInPool(PEObject *obj);
private:

	vector<PEObject *> m_objs;
	std::thread *m_thread;
	void clearNoReferenceCountObj();
};
#endif
