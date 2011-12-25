#pragma warning(disable:4786)
#include <string>

#include "StringUtils.h"
#include "RInsertMatrix.h"
#include "RDev.h"
#include "HDF5OutputConverter.h"

using namespace std;
using namespace seg;
using namespace R;

static const string FILESUMMARY="filesummary";
static const string GROUPSUMMARY="groupsummary";
static const string DATASETSUMMARY="datasetsummary";
static const string ATTRIBUTESUMMARY="attributesummary";

//
// routine:     ConvertOuput
// description: Top-level
RList& 
HDF5OutputConverter::ConvertSummaryOutput(const std::string& fileSummary,
								   const std::vector<string>& groupSummary,
								   const std::vector<string>& datasetSummary,
								   const std::vector<string>& attributeSummary)
{
    const string rName="HDF5OutputConverter::ConvertSummaryOutput/";
    //
    // Each conversion is an item into the output list; so the size of the
    // list must be sized appropriately.  Here are the list items:
    //      todids
     //
    const size_t NO_ITEMS=4;
    m_list.Create(NO_ITEMS);
    ConvertFileSummary(fileSummary);
    ConvertGroupSummary(groupSummary);
	ConvertDatasetSummary(datasetSummary);
	ConvertAttributeSummary(attributeSummary);
    return m_list;
}


void HDF5OutputConverter::ConvertFileSummary(const std::string& fileSummary)
{
    const string rName="HDF5OutputConverter::ConvertFileSummary/";

	RString rstr(fileSummary.size()>0);
	if(fileSummary.size()>0)
		rstr.Insert(fileSummary,0);

	m_list.InsertElement(rstr,FILESUMMARY);
}

void HDF5OutputConverter::ConvertGroupSummary(const std::vector<string>& groupSummary)
{
    const string rName="HDF5OutputConverter::ConvertGroupSummary/";

	RString gpstr(groupSummary.size());
	for (size_t i=0; i< gpstr.Size(); i++)
		gpstr.Insert(groupSummary[i],i);

	m_list.InsertElement(gpstr,GROUPSUMMARY);
}

void HDF5OutputConverter::ConvertDatasetSummary(const std::vector<string>& datasetSummary)
{
    const string rName="HDF5OutputConverter::ConvertDatasetSummary/";

	RString dsstr(datasetSummary.size());
	for (size_t i=0; i< dsstr.Size(); i++)
		dsstr.Insert(datasetSummary[i],i);
	
	m_list.InsertElement(dsstr,DATASETSUMMARY);
}

void HDF5OutputConverter::ConvertAttributeSummary(const std::vector<string>& attributeSummary)
{
    const string rName="HDF5OutputConverter::ConvertAttributeSummary/";

	RString attstr(attributeSummary.size());
	for (size_t i=0; i< attstr.Size(); i++)
		attstr.Insert(attributeSummary[i],i);

	m_list.InsertElement(attstr,ATTRIBUTESUMMARY);
}

// Data Frame is basically a list of list
SEXP HDF5OutputConverter::ConvertCompoundType(const seg::HDF5CompoundType& data)
{
	SEXP vec, names;
	size_t colcount = data.NumberOfColumns();
	size_t rowcount = data.NumberOfRows();
	PROTECT (vec = allocVector (VECSXP, (int)colcount));
	PROTECT (names = allocVector (STRSXP, (int)colcount));
    for (size_t ci = 0; ci < colcount; ci++)
	{
		std::string name;
		data.GetColumnName(ci,name);
		SET_STRING_ELT(names, (int)ci, mkChar(name.c_str()));
		std::vector<HDF5DataType::DataType> types;
		data.GetColumnTypes(types);
		switch (types[ci])
		{
			case HDF5DataType::INT:
			{
				std::vector<int> coldata;
				data.GetColumnData(ci,coldata);
				SEXP col;
				PROTECT(col=allocVector (INTSXP, (R_len_t) rowcount));
				int *  ptr = INTEGER(col);
				for (size_t ri = 0; ri < rowcount; ri++) 
					*ptr++=coldata[ri];
				SET_ELEMENT(vec,ci,col);
				UNPROTECT(1);
			} 
        break;
			case HDF5DataType::DOUBLE:
			{
				std::vector<double> coldata;
				data.GetColumnData(ci,coldata);
				SEXP col;
				PROTECT(col=allocVector (REALSXP, (R_len_t) rowcount));
				double *  ptr = REAL(col);
				for (size_t ri = 0; ri < rowcount; ri++) 
					*ptr++=coldata[ri];
				SET_ELEMENT(vec,ci,col);
				UNPROTECT(1);
			}
         break;
			case HDF5DataType::STRING:
			{
				std::vector<std::string> coldata;
				data.GetColumnData(ci,coldata);
				SEXP col;
				PROTECT(col=allocVector (STRSXP, (R_len_t) rowcount));
				for (size_t ri = 0; ri < rowcount; ri++) 
					 SET_ELEMENT(col,ri,mkChar(coldata[ri].c_str()));
				SET_ELEMENT(vec,ci,col);
				UNPROTECT(1);
			}
         break;
		default:
			throw RException("HDF5OutputConverter::ConvertCompoundType: Unknown data type "+HDF5DataType::ToString(types[ci]));
		}
	}
	// this is a data frame
	setAttrib(vec, R_ClassSymbol, mkString("data.frame"));
	// set the row ids
	char buf[256];
	SEXP row_names;
	PROTECT(row_names = allocVector(STRSXP,rowcount));
	for(size_t i=0;i<rowcount; i++)
	{
		sprintf(buf,"%d", i+1);
		SET_STRING_ELT(row_names,i,mkChar(buf));
	}
	setAttrib(vec,R_RowNamesSymbol, row_names);
	UNPROTECT(1);
	// set the column names
	setAttrib(vec, R_NamesSymbol, names);
	UNPROTECT(2);
	return vec;

}