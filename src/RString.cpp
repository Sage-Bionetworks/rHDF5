#pragma warning(disable:4786)
#include <string>

#include "RException.h"
#include "RObjectFactory.h"
#include "RString.h"

using namespace std;
using namespace seg;
using namespace R;

//
// routine:     ctor
// description: create a string type by coercing to R STRING
//
RString::RString(SEXP r_obj)
{
    const std::string rName="RString::ctor/";
    //
    // create/coerce a string
    //
    m_r_object=r_obj;
    m_type=OT_STRING;
    m_size=LENGTH(r_obj);
    if (m_size)
        RObjectFactory::Instance().Protect(*this);
}
//
// routine:     Create
// description: create an R string/char object (a vector of char*)
//
void RString::Create(size_t noElements)
{
    const std::string rName="RString::Create/";
	if (m_size)
        throw RException(rName+"String already created.");
    //
    // create the r vector of strings 
    //
    m_r_object=R_NilValue;
    m_type=OT_STRING;
    m_size=noElements;
    if (m_size)
        RObjectFactory::Instance().Create(*this);
}
//
// routine:     Insert
// description: insert value into the string vector
//
void RString::Insert(const std::string& value,size_t index)
{
    const std::string rName="RString::Insert/";
    if (index>=m_size)
        throw RException(rName+"Index beyone string size");
    //
    // copy it
    //
    SET_STRING_ELT(m_r_object,index,mkChar(value.c_str()));
}
//
// routine:     Insert
// description: insert all the values
//
void RString::Insert(const std::vector<std::string>& values)
{
    const std::string rName="RString::Insert/";
    if (values.size()!=m_size)
        throw RException(rName+"Inconsistent sizes");
    //
    // copy them
    //
    for (size_t index=0;index<m_size;index++)
        SET_STRING_ELT(m_r_object,index,mkChar(values[index].c_str()));
}
//
// routine:     Insert
// description: insert all the values; possibly set dimensions (& transpose)
//
void RString::Insert(const seg::Matrix<string>& values,bool setDim)
{
    const std::string rName="RString::Insert/";
    if (values.Size()!=m_size)
        throw RException(rName+"Inconsistent sizes");
    if (m_size)
    {
        //
        // set the dim (and transpose)
        //
        if (setDim)
        {
            size_t noRows=values.NumberOfRows();
            size_t noCols=values.NumberOfColumns();
            Dimensions(noRows,noCols);
            //
            // transpose
            //
            Matrix<string> tData;
            tData=values;        // deep copy
            tData.Transpose();
            //
            // copy
            //
            for (size_t index=0;index<m_size;index++)
                SET_STRING_ELT(m_r_object,index,mkChar(tData[index].c_str()));
        }
        else
        {
            //
            // just copy the data
            //
            for (size_t index=0;index<m_size;index++)
                SET_STRING_ELT(m_r_object,index,mkChar(values[index].c_str()));
        }
    }
}
//
// routine:     Extract
// description: extract an element
//
void RString::Extract(size_t index, std::string& value)
{
    const string rName="RString::Extract/";
    if (index>=m_size)
        throw RException(rName+"Index beyond string size");
    //
    // copy it
    //
//    value=CHAR( CHARACTER_POINTER(m_r_object)[index] );
    SEXP cp=CHARACTER_POINTER(m_r_object)[index];
    if (cp!=R_NilValue)
        value=CHAR(cp);
    else
        value="";
}
//
// routine:     Extract
// description: extract all elements
//
void RString::Extract(std::vector<std::string>& values)
{
    const string rName="RString::Extract/";
    values.resize(m_size);
    if (m_size)
    {
        for (size_t index=0;index<m_size;index++)
        {
            Extract(index,values[index]);
            //values[index]=CHAR( CHARACTER_POINTER(m_r_object)[index] );
        }
    }
}
//
// routine:     Extract
// description: extract all elements
//
void RString::Extract(seg::Matrix<std::string>& values)
{
    const string rName="RString::Extract/";
    values.Resize(m_size);
    if (m_size)
    {
        for (size_t index=0;index<m_size;index++)
        {
            values[index]=CHAR( CHARACTER_POINTER(m_r_object)[index] );
        }
    }
}

 //
// routine:     Extract
// description: extract all elements
//
void RString::Extract(seg::Matrix<std::string>& values, size_t rows, size_t cols)
{
    const string rName="RString::Extract/";
    values.Resize(rows,cols);
    if (m_size)
    {
        for (size_t r=0;r<rows;r++)
        {
			 for (size_t c=0;c<cols;c++)
			{
				values(r,c)=CHAR( CHARACTER_POINTER(m_r_object)[r*cols+c] );
			 }
        }
    }
}

//
// routine:     ExtractAndConcatenate
// description: extract all elements and concatenates them into a string
//
void RString::ExtractAndConcatenate(std::string& values, char sep)
{
    const string rName="RString::ExtractAndConcatenate/";
	
    if (m_size)
    {
        for (size_t index=0;index<m_size;index++)
        {
			values += CHAR( CHARACTER_POINTER(m_r_object)[index] );
			if( index!=m_size-1)
				values += sep;
        }
    }
}