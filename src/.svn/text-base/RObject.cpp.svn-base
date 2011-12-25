#pragma warning(disable:4786)
#include <sstream>

#include "RObjectFactory.h"
#include "RObject.h"


using namespace std;
using namespace R;

//
// routine:     Names
// description: Sets the names
//
void RObject::Names(const std::vector<std::string>& names)
{
    const string rName="RObject::Names/";
    size_t noNames=names.size();
    if (!m_size || noNames!=m_size)
        throw RException(rName+"Size of names/objects inconsistent.");
    //
    // create the string vector (which holds the names)
    //
    RObjectFactory& rfac=RObjectFactory::Instance();
    RObject r_string=rfac.Create(OT_STRING,noNames);
    //
    // iterate of the stl::vector and set the r string vector
    //
    for (size_t index=0;index<m_size;index++)
    {
        SET_STRING_ELT(r_string.Object(),index,mkChar(names[index].c_str()));
    }
    //
    // set the names in the data object
    //
    SET_NAMES(m_r_object,r_string.Object());

}
//
// routine:     GetRType
// description: xxx
//
RObject::OBJECT_TYPE RObject::GetRType(SEXP r_obj)
{
    const string rName="RObject::GetRType/";
    OBJECT_TYPE ot=OT_NULL;
    if (IS_LOGICAL(r_obj))
        ot=OT_LOGICAL;
    else if (IS_INTEGER(r_obj))
        ot=OT_INTEGER;
    else if (IS_NUMERIC(r_obj))
        ot=OT_NUMERIC;
    else if (IS_CHARACTER(r_obj))
        ot=OT_STRING;
    else if (IS_LIST(r_obj))
        ot=OT_LIST;
    else if (isFrame(r_obj))
        ot=OT_DATAFRAME;
    return ot;    
}
//
// routine:     ConvertObjectType
// description:
//
string RObject::ConvertObjectType(OBJECT_TYPE objType)
{
    const string rName="RObject::ConvertObjectType/";
    string rType;
    switch(objType)
    {
    case OT_NUMERIC:
        rType="Numeric";
        break;
    case OT_LOGICAL:
        rType="Logical";
        break;
    case OT_INTEGER:
        rType="Integer";
        break;
    case OT_LIST:
        rType="List";
        break;
    case OT_STRING:
        rType="String";
        break;
    default:
        rType="Null";
        break;
    }
    return rType;
}
//
// routine:     Dimensions
// description: xxx
//
void RObject::Dimensions(size_t noRows,size_t noCols)
{
    const string rName="Dimensions/";
    //
    // set rows/cols members
    //
	if (noRows*noCols!=m_size)
        throw RException(rName+"Inconsistent size with nrows/ncols");
    m_numberOfRows=noRows;
    m_numberOfColumns=noCols;
    //
    // we need a vector of 2 ints to set the dim; we won't protect since
    // its so temporary
    //
    SEXP r_int=NEW_INTEGER(2);
    int* lDim=INTEGER_POINTER(r_int);
    lDim[0]=noRows;
    lDim[1]=noCols;
    SET_DIM(m_r_object,r_int);
}
//
// routine:     xxx
// description: xxx
//
/*
void RObject::xxx
{
    const string rName="xxx/";
}
*/