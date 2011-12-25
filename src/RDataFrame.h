#ifndef RDATAFRAME_INC
#define RDATAFRAME_INC
#include <vector>
#include <string>

#include "Int64.h"
#include "RException.h"
#include "RObject.h"
#include "HDF5CompoundType.h"
#include "HDF5DataType.h"

extern "C" {
#include <R.h>
#include <Rdefines.h>
}
namespace R
{

class RDataFrame: public RObject
{
public:
    RDataFrame(SEXP& obj);
    virtual ~RDataFrame() 
        {}
	template<typename T>
    void Insert(const std::string& name, const std::vector<T>& values);
	template<typename T>
    void Extract(const std::string& name, std::vector<T>& values) const;
	template<typename T>
    void Extract(const size_t columnIndex, std::vector<T>& values) const;
	seg::HDF5CompoundType CompoundType() 
	{return m_compoundType;};

private:
	seg::HDF5CompoundType m_compoundType;
};

template<typename T>
inline void RDataFrame::Insert(const std::string& name, const std::vector<T>& values)
{
	m_compoundType.AddColumn(name,values);
}

template<typename T>
void RDataFrame::Extract(const std::string& name, std::vector<T>& values) const
{
	m_compoundType.GetColumnData(name,values);
}

template<typename T>
void RDataFrame::Extract(const size_t columnIndex, std::vector<T>& values) const
{
	m_compoundType.GetColumnData(columnIndex,values);
}
}

#endif