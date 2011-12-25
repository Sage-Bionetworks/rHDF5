#ifndef R_COPY_MATRIX_INC
#define R_COPY_MATRIX_INC
#include "Matrix.h"
#include "RVector.h"

namespace R
{

template<class M_TYPE, class R_TYPE>
void RCopyMatrix(const seg::Matrix<M_TYPE>& mData, 
                 RVector<R_TYPE>& rData,
                 bool isMatrix=false);
//
// common
//
template<class M_TYPE, class R_TYPE>
void RCopyMatrix(const seg::Matrix<M_TYPE>& mData, 
                 RVector<R_TYPE>& rData,
                 bool isMatrix)
{
    const std::string rName="RCopyMatrix/";
    size_t noData=mData.Size();
    size_t mSize=rData.Size();
    //
    // validation
    //
    if (noData!=mSize)
        throw RException(rName+"Inconsistent size with c++ data");
    //
    // set the dimension
    //
    if (mSize)
    {
        //
        // validate type
        //
        R_TYPE* r_cdata=rData.Data();
        //
        // copy the data
        //
        for (size_t index=0;index<noData;index++)
            r_cdata[index]=mData[index];
        //
        // if it's a matrix, set dimension and transpose
        //
        if (isMatrix)
        {
            //
            // set dimension
            //
            size_t noRows=mData.NumberOfRows();
            size_t noCols=mData.NumberOfColumns();
            rData.Dimensions(noRows,noCols);
            //
            // transpose
            //
            Matrix<M_TYPE> mt(r_cdata,noRows,noCols);      // shallow copy
            mt.Transpose();
        }
    }
}

}
#endif