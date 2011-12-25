#ifndef HDF5_CONVERTER_INC
#define HDF5_CONVERTER_INC
#include <string>

#include "RDev.h"

namespace R
{
class RObject;
//
// class:   HDF5OutputConverter
// description: Convert c++ output from HDF5 to s-plus list
//
class HDF5OutputConverter
{
public:
    HDF5OutputConverter() 
        {}
    ~HDF5OutputConverter()
        {}

	RList& ConvertSummaryOutput(const std::string& fileSummary,
								   const std::vector<std::string>& groupSummary,
								   const std::vector<std::string>& datasetSummary,
								   const std::vector<std::string>& attributeSummary);
	template<class type>
	SEXP ConvertIntMatrix(const seg::Matrix<type>& mData)
	{
		RVector<int>  rData(mData.Size());
		RInsertMatrix(mData,rData,true);
		return rData.Object();		
	}
	template<class type>
	SEXP ConvertDoubleMatrix(const seg::Matrix<type>& mData)
	{
		RVector<double>  rData(mData.Size());
		RInsertMatrix(mData,rData,true);
		return rData.Object();		
	}

	template<class type>
	SEXP ConvertStrMatrix(const seg::Matrix<type>& mData)
	{
		RString rData(mData.Size());
		rData.Insert(mData,true);
		return rData.Object();		
	}

	SEXP ConvertCompoundType(const seg::HDF5CompoundType& data);

private:
    //
    // Top level converters (a method per item in the output list)
    //
    void ConvertFileSummary(const std::string& fileSummary);
    void ConvertGroupSummary(const std::vector<std::string>& groupSummary);
    void ConvertDatasetSummary(const std::vector<std::string>& datasetSummary);
    void ConvertAttributeSummary(const std::vector<std::string>& attributeSummary);
    RList      m_list;
};

}
#endif
