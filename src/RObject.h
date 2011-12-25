#ifndef ROBJECT_INC
#define ROBJECT_INC
#pragma warning(disable:4251)
//
// class:       RObject
// description: A base class for the various subclasses associated with
//              R objects.  Common methods and attributes are here.  The
//              subclasses include: RVector, RString, and RList
//
#include <vector>
#include <string>
#include <math.h>

#include "Int64.h"
#include "RException.h"

extern "C" {
#include <R.h>
#include <Rdefines.h>
}
namespace R
{

class RObject
{
public:
    enum OBJECT_TYPE { OT_LOGICAL,OT_INTEGER,OT_NUMERIC,OT_LIST,
                       OT_STRING, OT_DATAFRAME, OT_NULL=-1 }; 
    RObject() : m_r_object(R_NilValue), 
                m_size(0),
                m_type(OT_NULL),
                m_numberOfColumns(0),
                m_numberOfRows(0)
        {}
    RObject(SEXP& r_obj,OBJECT_TYPE objType,size_t size) :
        m_r_object(r_obj),
        m_type(objType),
        m_size(size),
        m_numberOfRows(1),
        m_numberOfColumns(size)
        { if (!size) m_numberOfRows=0; }
    virtual ~RObject() 
        {}
    //
    // r object operations
    //
    void Names(const std::vector<std::string>& names);
    void Dimensions(size_t noRows,size_t noCols);

    SEXP& Object()  
        { return m_r_object; }
    const SEXP& Object() const 
        { return m_r_object; }
    size_t Size() const
        { return m_size; }
    OBJECT_TYPE Type() const
        { return m_type; }
    void Type(OBJECT_TYPE oType)
        { m_type=oType; }
    size_t Rows() const       
        { return m_numberOfRows; }
    size_t Columns() const
        { return m_numberOfColumns; }
    const std::vector<std::string>& Names() const
        { return m_names; }
    //
    // static converters
    //
    static std::string ConvertObjectType(OBJECT_TYPE objType);
    static OBJECT_TYPE GetRType(SEXP r_obj);
protected:
    SEXP                        m_r_object;
    OBJECT_TYPE                 m_type;
    size_t                      m_size;
    size_t                      m_numberOfRows;
    size_t                      m_numberOfColumns;
    std::vector<std::string>    m_names;

private:
};

}

#endif