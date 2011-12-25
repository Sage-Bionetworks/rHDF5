#pragma warning(disable:4786)
#include <string>

#include "RException.h"
#include "RInitializer.h"
#include "RObjectFactory.h"

using namespace std;
using namespace R;

//
// method:      ctor
// description: 
//
RInitializer::RInitializer() : m_debug(false)
{
    RObjectFactory::Instantiate();
    RObjectFactory::Instance().m_noOfObjects=0;
}
//
// method:      dtor
// description: 
//
RInitializer::~RInitializer()
{
}
//
// method:      dtor
// description: 
//
void RInitializer::Cleanup()
{
    RObjectFactory::DestroyInstance();
}
//
// method:      Debug
// description: 
//
void RInitializer::Debug(bool debug)
{
    m_debug=debug;
    RObjectFactory::Instance().m_debug=debug;
}
