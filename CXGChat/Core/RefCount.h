#ifndef __REF_COUNT_H_
#define __REF_COUNT_H_

#include "Includes/PrecompileConfig.h"

// CRefCount
class CRefCount
{
public:
    CRefCount();
    virtual ~CRefCount();

public:
    long AddRef();
    long Release();

private:
	long            m_nRefCount;
	pthread_mutex_t		m_Mutex;
};

#endif



