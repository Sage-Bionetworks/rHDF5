#ifndef RINITAILIZER_INC
#define RINITAILIZER_INC
//
//  class:          RInitializer
//  description:    Kind of a "smart" class that instantiates the RObjectFactory
//                  (which is used to create the R objects) and destroys the factory
//                  via RInitializer's dtor.
//
//                  RInitializer should be instantiated as the first thing and when
//                  it goes out of scope, it's destructor will be called which will
//                  automatically destroy the object factory.  Typical usage:
//                      RInitializer rInit;
//                      //
//                      // create a vector of reals (20 elements) with PROTECT
//                      //
//                      SEXP s_num;
//                      RObjectFactory::OT_NUMERIC s_objType;
//                      s_num=RObjectFactory::Instance().CreateObject(s_objType,20);
//                      . . .
//
//                      return;     // obj factory destroyed and UNPROTECT called
//
#pragma warning(disable:4251)

namespace R
{

class RInitializer
{
public:
    RInitializer();
    ~RInitializer();
    void Cleanup();
    void Debug(bool debug);
private:
    bool    m_debug;
};

}

#endif