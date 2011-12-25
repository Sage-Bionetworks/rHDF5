#ifndef ROBJECT_FACTORY_INC
#define ROBJECT_FACTORY_INC
//
//  class:          RObjectFactory
//  description:    A singleton (instantiated and destroyed by RInitializer)
//                  for createing (with protection) R objects.
//
//                  When the factory is destroyed, the UNPROTECT (an R macro)
//                  is called.
//
#pragma warning(disable:4251)
#include <vector>
#include <string>

#include "RObject.h"

namespace R
{

class RObjectFactory
{
public:
    friend class RInitializer;
    static RObjectFactory& Instance();   // just get not create
    static void DestroyInstance()
        { delete m_instance; m_instance=0; }
    //
    // R object creation
    //
    RObject Create(RObject::OBJECT_TYPE objectType,size_t noElements);
    void Create(RObject& rObj);
    //
    // R object protection (typically for input arguments from R)
    //
    RObject Protect(SEXP r_inObj,RObject::OBJECT_TYPE objType);
    void Protect(RObject& rObj);
    //
    // misc
    //
    void Debug(bool debug)
        { m_debug=debug; }

protected:

private:
    RObjectFactory() : m_noOfObjects(0), m_debug(false)
        {}
    ~RObjectFactory();
    static void Instantiate();          // invoked by RInitializer to create factory

    static RObjectFactory* m_instance;

    size_t              m_noOfObjects;
    bool                m_debug;
};

}

#endif