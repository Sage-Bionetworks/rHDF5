#ifndef RVECTOR_CPP
#define RVECTOR_CPP

#include "RCreateVector.h"
#include "Matrix.h"
#include "RVector.h"
#include "RInsertMatrix.h"
#include "RExtractData.h"

namespace R
{
//
// routine:     ctor
// description: create using an existing R object (SEXP)
//
template<class RT>
RVector<RT>::RVector(SEXP r_obj)
{
    const std::string rName="RVector::ctor/";
    //
    // create the r vector of LOGICALS 
    //
    m_r_object=r_obj;
    m_type=RObject::GetRType(r_obj);
    m_size=LENGTH(r_obj);
    if (m_size)
        RCreateVector(*this);
}
//
// routine:     ctor
// description: create via RObject
//
template<class RT>
RVector<RT>::RVector(const RObject& rObj)
{
    const std::string rName="RVector::ctor/";
    m_r_object=rObj.Object();
    m_type=rObj.Type();
    m_size=rObj.Size();
    m_c_data=0;;
}
//
// routine:     Create
// description: create brand new, using a size
//
template<class RT>
void RVector<RT>::Create(size_t size)
{
    const std::string rName="RVector::Create/";
	if (m_size)
        throw RException(rName+"Vector already created.");
    if (size)
        RCreateVector(*this,size);
}
//
// routine:     Insert
// description: xxx
//
template<class RT>
void RVector<RT>::Insert(const seg::Matrix<RT>& mData,bool transpose)
{
    const std::string rName="RVector::Insert/";
    size_t noData=mData.Size();
    //
    // validation
    //
    if (noData!=m_size)
        throw RException(rName+"Inconsistent size with c++ data");
    //
    // set the dimension
    //
    if (m_size)
    {
        //
        // copy the data
        //
        for (size_t index=0;index<noData;index++)
            m_c_data[index]=mData[index];
        //
        // if it's a matrix, set dimension and transpose
        //
        if (transpose)
        {
            //
            // set dimension
            //
            size_t noRows=mData.NumberOfRows();
            size_t noCols=mData.NumberOfColumns();
            Dimensions(noRows,noCols);
            //
            // transpose
            //
			seg::Matrix<RT> mt(m_c_data,noRows,noCols);      // shallow copy
            mt.Transpose();
        }
    }
//    RInsertMatrix(values,*this,setDim);
}
//
// routine:     Extract
// description: xxx
//
template<class RT>
void RVector<RT>::Extract(seg::Matrix<RT>& values) const
{
    const std::string rName="RVector::Extract/";
    bool transpose=false;
    if (m_numberOfRows>1 && m_numberOfColumns>1)
        transpose=true;
    values.Resize(m_numberOfRows,m_numberOfColumns);

    //
    // iterate
    //
    for (size_t index=0;index<m_size;index++)
        values[index]=m_c_data[index];
    //
    // transpose
    //
    if (transpose)
    {
        seg::Matrix<RT> mt(values);  // shallow copy
        mt.Transpose();
    }
}
//
// routine:     Insert
// description: xxx
//
template<class RT>
void RVector<RT>::Insert(const std::vector<RT>& mData)
{
    const std::string rName="RVector::Insert/";
    size_t noData=mData.size();
    //
    // validation
    //
    if (noData!=m_size)
        throw RException(rName+"Inconsistent size with c++ data");
    //
    // set the dimension
    //
    if (m_size)
    {
        //
        // copy the data
        //
        for (size_t index=0;index<noData;index++)
            m_c_data[index]=mData[index];
    }
//    RInsertMatrix(values,*this,setDim);
}
//
// routine:     Extract
// description: xxx
//
template<class RT>
void RVector<RT>::Extract(std::vector<RT>& values) const
{
    const std::string rName="RVector::Extract/";
    bool transpose=false;
    if (m_numberOfRows>1 && m_numberOfColumns>1)
        throw RException(rName+"Can't extract 2-d array into a vector");
    values.resize(m_size);

    //
    // iterate
    //
    for (size_t index=0;index<m_size;index++)
        values[index]=m_c_data[index];
}
//
// routine:     Extract
// description: xxx
//
template<class RT>
RT RVector<RT>::Extract(size_t element) const
{
    const std::string rName="RVector::Extract/";
    if (element>=m_size)
        throw RException(rName+"Element larger than size of vector");
    return m_c_data[element];
}

}

#endif
