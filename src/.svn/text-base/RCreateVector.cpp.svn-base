#pragma warning(disable:4786)
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <limits>

#include "RObjectFactory.h"
#include "RCreateVector.h"
#include "RException.h"

using namespace R;
using namespace std;
//
// specialized
//
template<> void RCreateVector<int>(RVector<int>& rObj,size_t size)
{
    const std::string rName="RCreateVector/";
    rObj=RObjectFactory::Instance().Create(RObject::OT_INTEGER,size);
    rObj.m_c_data=INTEGER_POINTER(rObj.Object());
}
template<> void RCreateVector<double>(RVector<double>& rObj,size_t size)
{
    const std::string rName="RCreateVector/";
    rObj=RObjectFactory::Instance().Create(RObject::OT_NUMERIC,size);
    rObj.m_c_data=NUMERIC_POINTER(rObj.Object());
}

template<> void RCreateVector<int>(RVector<int>& rObj)
{
    const std::string rName="RCreateVector/";
    rObj.Type(RObject::OT_INTEGER);
    RObjectFactory::Instance().Protect(rObj);
    rObj.m_c_data=INTEGER_POINTER(rObj.Object());
}
template<> void RCreateVector<double>(RVector<double>& rObj)
{
    const std::string rName="RCreateVector/";
    rObj.Type(RObject::OT_NUMERIC);
    RObjectFactory::Instance().Protect(rObj);
    rObj.m_c_data=NUMERIC_POINTER(rObj.Object());
}
//template<> void RCreateVector<std::string>(RVector<std::string>& rObj)
//{
//    const std::string rName="RCreateVector/";
//	rObj.Type(RObject::OT_STRING);
//    RObjectFactory::Instance().Protect(rObj);
//    rObj.m_c_data=STRING_PTR(rObj.Object());
//}
