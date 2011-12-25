#pragma warning(disable:4786)
#include "Matrix.h"
#include "RInsertMatrix.h"
#include "RVector.h"

using namespace std;
using namespace R;
using namespace seg;
//
// specialized to INT64
//
void R::RInsertMatrix(const Matrix<INT64>& mData, 
                   RVector<double>& rData,
                   bool transpose)
{
    const std::string rName="RInsertMatrix/";
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
        double* r_cdata=rData.Data();
        //
        // copy the data
        //
        for (size_t index=0;index<noData;index++)
            r_cdata[index]=mData[index];
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
            rData.Dimensions(noRows,noCols);
            //
            // transpose
            //
            Matrix<double> mt(r_cdata,noRows,noCols);      // shallow copy
            mt.Transpose();
        }
    }
}
//
// specialized to double
//
void R::RInsertMatrix(const Matrix<double>& mData, 
                   RVector<double>& rData,
                   bool transpose)
{
    const std::string rName="RInsertMatrix/";
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
        double* r_cdata=rData.Data();
        //
        // copy the data
        //
        for (size_t index=0;index<noData;index++)
            r_cdata[index]=mData[index];
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
            rData.Dimensions(noRows,noCols);
            //
            // transpose
            //
            Matrix<double> mt(r_cdata,noRows,noCols);      // shallow copy
            mt.Transpose();
        }
    }
}
//
// specialized to float
//
void R::RInsertMatrix(const Matrix<float>& mData, 
                   RVector<double>& rData,
                   bool transpose)
{
    const std::string rName="RInsertMatrix/";
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
        double* r_cdata=rData.Data();
        //
        // copy the data
        //
        for (size_t index=0;index<noData;index++)
            r_cdata[index]=mData[index];
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
            rData.Dimensions(noRows,noCols);
            //
            // transpose
            //
            Matrix<double> mt(r_cdata,noRows,noCols);      // shallow copy
            mt.Transpose();
        }
    }
}

//
// specialized to long to int
//
void R::RInsertMatrix(const Matrix<long>& mData, 
                   RVector<int>& rData,
                   bool transpose)
{
    const std::string rName="RInsertMatrix/";
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
        int* r_cdata=rData.Data();
        //
        // copy the data
        //
        for (size_t index=0;index<noData;index++)
            r_cdata[index]=mData[index];
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
            rData.Dimensions(noRows,noCols);
            //
            // transpose
            //
            Matrix<int> mt(r_cdata,noRows,noCols);      // shallow copy
            mt.Transpose();
        }
    }
}
//
// specialized to char to int
//
void R::RInsertMatrix(const Matrix<signed char>& mData, 
                   RVector<int>& rData,
                   bool transpose)
{
    const std::string rName="RInsertMatrix/";
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
        int* r_cdata=rData.Data();
        //
        // copy the data
        //
        for (size_t index=0;index<noData;index++)
            r_cdata[index]=mData[index];
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
            rData.Dimensions(noRows,noCols);
            //
            // transpose
            //
            Matrix<int> mt(r_cdata,noRows,noCols);      // shallow copy
            mt.Transpose();
        }
    }
}


//
// specialized to char to int
//
void R::RInsertMatrix(const Matrix<char>& mData, 
                   RVector<int>& rData,
                   bool transpose)
{
    const std::string rName="RInsertMatrix/";
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
        int* r_cdata=rData.Data();
        //
        // copy the data
        //
        for (size_t index=0;index<noData;index++)
            r_cdata[index]=mData[index];
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
            rData.Dimensions(noRows,noCols);
            //
            // transpose
            //
            Matrix<int> mt(r_cdata,noRows,noCols);      // shallow copy
            mt.Transpose();
        }
    }
}




//
// specialized to char to int
//
void R::RInsertMatrix(const Matrix<int>& mData, 
                   RVector<int>& rData,
                   bool transpose)
{
    const std::string rName="RInsertMatrix/";
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
        int* r_cdata=rData.Data();
        //
        // copy the data
        //
        for (size_t index=0;index<noData;index++)
            r_cdata[index]=mData[index];
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
            rData.Dimensions(noRows,noCols);
            //
            // transpose
            //
            Matrix<int> mt(r_cdata,noRows,noCols);      // shallow copy
            mt.Transpose();
        }
    }
}


