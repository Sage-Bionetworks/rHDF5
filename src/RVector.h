#ifndef RVECTOR_INC
#define RVECTOR_INC
#include <vector>

#include "Int64.h"
#include "Matrix.h"
#include "RObject.h"

namespace R
{
//
// template definition
//
template<class T>
class RVector : public RObject
{
public:
    RVector(size_t size)
        { Create(size); }
    RVector(SEXP r_obj);
    RVector(const RObject& rObj);
    ~RVector()
        {}
    void Create(size_t size);
    //
    // vector specific
    //
    T* Data()           
        { return m_c_data; }
    const T* Data() const
        { return m_c_data; }
    void Insert(const seg::Matrix<T>& values,bool transpose);
    void Insert(const std::vector<T>& values);
    T Extract(size_t element) const;
    void Extract(seg::Matrix<T>& values) const;
    void Extract(std::vector<T>& values) const;
    T*          m_c_data;
protected:
private:

};

}

#include "RVector.cpp"

#endif