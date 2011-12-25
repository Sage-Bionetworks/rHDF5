#ifndef RT_OBJECT_INC
#define RT_OBJECT_INC

#include "RObject.h"

namespace R
{

template<class T>
class RTObject : public RObject
{
public:
    RTObject() {}
    ~RTObject() {}
    void Create(size_t size) { Create(m_objType,size); }
    T   m_objType;
};

#endif