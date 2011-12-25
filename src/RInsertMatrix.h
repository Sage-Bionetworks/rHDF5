#ifndef RINSERT_MATRIX_INC
#define RINSERT_MATRIX_INC
#include "Int64.h"
#include "Matrix.h"

namespace R
{

template<class T> class RVector;

void RInsertMatrix(const seg::Matrix<seg::INT64>& mData, 
                   RVector<double>& rData,
                   bool transpose);
void RInsertMatrix(const seg::Matrix<double>& mData, 
                   RVector<double>& rData,
                   bool transpose);
void RInsertMatrix(const seg::Matrix<float>& mData, 
                   RVector<double>& rData,
                   bool transpose);
void RInsertMatrix(const seg::Matrix<long>& mData, 
                   RVector<int>& rData,
                   bool transpose);
void RInsertMatrix(const seg::Matrix<signed char>& mData, 
                   RVector<int>& rData,
                   bool transpose);
void RInsertMatrix(const seg::Matrix<char>& mData, 
                   RVector<int>& rData,
                   bool transpose);
void RInsertMatrix(const seg::Matrix<int>& mData, 
                   RVector<int>& rData,
                   bool transpose);
}
#endif