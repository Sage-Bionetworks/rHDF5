#pragma warning(disable:4786)
#include <string>
#include <sstream>

#include "RException.h"
#include "RProblem.h"
#include "RObjectFactory.h"

using namespace std;
using namespace R;

RObjectFactory* RObjectFactory::m_instance=0;

//
// routine:     Instance
// description: return instance if instantiated; else throw exception
//
RObjectFactory& RObjectFactory::Instance()
{
    const string rName="RObjectFactory::Instance/";
    if (m_instance==0)
        throw RException(rName+"Factory has not been instantiated.");
    return *m_instance;
}
//
// routine:     Instantiate
// description: instantiate the factory.  operation performed by RInitializer
//
void RObjectFactory::Instantiate()
{
    const string rName="RObjectFactory::Instantiate/";
    if (m_instance==0)
    {
        m_instance=new RObjectFactory;
        if (m_instance==0)
            throw RException(rName+"Cannot allocate factory (new failed).");
    }
}
//
// routine:     dtor
// description: unprotect appropriately
//
RObjectFactory::~RObjectFactory()
{
    if (m_debug)
    {
        ostringstream ostr;
        ostr << "Unprotectecting " << m_noOfObjects << " objects.";
        RMessage(ostr.str());
    }
    if (m_noOfObjects) 
        UNPROTECT(m_noOfObjects);
}
//
// routine:     Create
// description: Given an RObject (e.g., RVector), create the R object and
//              insert it.
//
void RObjectFactory::Create(RObject& rObj)
{
    rObj=Create(rObj.Type(),rObj.Size());
}
//
// routine:     Create
// description: create an RObject that has an R object.
//
RObject RObjectFactory::Create(RObject::OBJECT_TYPE objType,size_t noElements)
{
    const string rName="RObjectFactory::Create/";
    string rType=RObject::ConvertObjectType(objType);
    if (!noElements)
        throw RException(rName+"Cannot create zero element object.");
    SEXP r_object;
    if (m_debug)
    {
        ostringstream ostr;
        string objName=RObject::ConvertObjectType(objType);
        ostr << rName << "[" << m_noOfObjects << "] Creating object: " 
             << objName << "/Size: " << noElements;
        string msg=ostr.str();
        RMessage(msg);
    }
    try
    {
        switch(objType)
        {
        case RObject::OT_NUMERIC:
            PROTECT(r_object=NEW_NUMERIC(noElements));
            break;
        case RObject::OT_LOGICAL:
            PROTECT(r_object=NEW_LOGICAL(noElements));
            break;
        case RObject::OT_INTEGER:
            PROTECT(r_object=NEW_INTEGER(noElements));
            break;
        case RObject::OT_LIST:
            PROTECT(r_object=NEW_LIST(noElements));
            break;
        case RObject::OT_STRING:
            PROTECT(r_object=NEW_STRING(noElements));
            break;
        default:
            throw RException(rName+"Invalid object type.");
            break;
        }
    }
    catch(const RException& )
    {
        throw;
    }
    catch (...)
    {
        throw RException(rName+"Cannot new R object "+rType);
    }
    m_noOfObjects++;
    return RObject(r_object,objType,noElements);;
}
//
// routine:     Protect
// description: protect and coerce (typically r objects passed in c++ from R)
//
void RObjectFactory::Protect(RObject& rObj)
{
    const string rName="RObjectFactory::Protect/";
    rObj=Protect(rObj.Object(),rObj.Type());
}
//
// routine:     Protect
// description: protect and coerce (typically r objects passed in c++ from R)
//
RObject RObjectFactory::Protect(SEXP r_inObj,RObject::OBJECT_TYPE objType)
{
    const string rName="RObjectFactory::Protect/";
    string rType=RObject::ConvertObjectType(objType);
    if (m_debug)
    {
        ostringstream ostr;
        ostr << rName << "[" << m_noOfObjects << "] Coercing R object to " << rType;
        string msg=ostr.str();
        RMessage(msg);
    }
    try
    {
        switch(objType)
        {
        case RObject::OT_NUMERIC:
            PROTECT(r_inObj=AS_NUMERIC(r_inObj));
            break;
        case RObject::OT_LOGICAL:
            PROTECT(r_inObj=AS_LOGICAL(r_inObj));
            break;
        case RObject::OT_INTEGER:
            PROTECT(r_inObj=AS_INTEGER(r_inObj));
            break;
        case RObject::OT_LIST:
            PROTECT(r_inObj=AS_LIST(r_inObj));
            break;
        case RObject::OT_STRING:
            PROTECT(r_inObj=AS_CHARACTER(r_inObj));
            break;
        default:
            throw RException(rName+"Invalid object type.");
            break;
        }
    }
    catch (const RException &)
    {
        throw;
    }
    catch (...)
    {
        throw RException(rName+"Cannot protect/convert R object to "+rType);
    }
    //
    // get the length of the object
    //
    size_t size=LENGTH(r_inObj);
    if (m_debug)
    {
        ostringstream ostr;
        ostr << rName << "[" << m_noOfObjects << "] Size: " << size;
        string msg=ostr.str();
        RMessage(msg);
    }
    m_noOfObjects++;
    return RObject(r_inObj,objType,size);
}

