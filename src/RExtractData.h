#ifndef R_EXTRACT_TO_MATRIX_INC
#define R_EXTRACT_TO_MATRIX_INC
#include "Matrix.h"
#include "Int64.h"

namespace R
{
template<class T> class RVector;

void RExtractToMatrix(const RVector<double>& rData,
                      seg::Matrix<seg::INT64>& mData,
                      bool transpose);
void RExtractToMatrix(const RVector<double>& rData,
                      seg::Matrix<float>& mData,
                      bool transpose);


}
#endif