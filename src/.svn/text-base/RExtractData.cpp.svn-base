#pragma warning(disable:4786)
#include "Matrix.h"
#include "RExtractData.h"
#include "RVector.h"

using namespace std;
using namespace R;

//
// specialize to INT64/double
//
void R::RExtractToMatrix(const RVector<double>& rData,
                         seg::Matrix<seg::INT64>& mData,
                         bool transpose)
{
    const std::string rName="RExtractToMatrix/";
    size_t noElements=rData.Size();
    size_t noRows=rData.Rows();
    size_t noCols=rData.Columns();
    mData.Resize(noRows,noCols);
    const double* cData=rData.Data();
    if (noElements)
    {
        //
        // iterate
        //
        for (size_t index=0;index<noElements;index++)
            mData[index]=cData[index];
        //
        // transpose
        //
        if (transpose)
        {
            seg::Matrix<seg::INT64> mt(mData);  // shallow copy
            mt.Transpose();
        }
    }
}
//
// specialize to float/double
//
void R::RExtractToMatrix(const RVector<double>& rData,
                         seg::Matrix<float>& mData,
                         bool transpose)
{
    const std::string rName="RExtractToMatrix/";
    size_t noElements=rData.Size();
    size_t noRows=rData.Rows();
    size_t noCols=rData.Columns();
    mData.Resize(noRows,noCols);
    const double* cData=rData.Data();
    if (noElements)
    {
        //
        // iterate
        //
        for (size_t index=0;index<noElements;index++)
            mData[index]=cData[index];
        //
        // transpose
        //
        if (transpose)
        {
            seg::Matrix<float> mt(mData);  // shallow copy
            mt.Transpose();
        }
    }
}
