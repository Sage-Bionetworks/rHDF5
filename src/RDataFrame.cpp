#ifndef RDATAFRAME_CPP
#define RDATAFRAME_CPP

#pragma warning(disable:4786)
#include <sstream>
#include "RDataFrame.h"
#include "RVector.h"
#include "RString.h"
#include "Matrix.h"

using namespace std;

namespace R
{
RDataFrame::RDataFrame(SEXP& r_obj)
{
    const string rName="RDataFrame::RDataFrame/";
        m_r_object=r_obj;
        m_numberOfColumns = length(r_obj);
        m_numberOfRows = 0;
        if(m_numberOfColumns>0)
                m_numberOfRows  =  length(VECTOR_ELT(r_obj,0));

    m_type=OT_DATAFRAME;
    m_size=LENGTH(r_obj);
        // get names
        SEXP colnames = getAttrib(r_obj, R_NamesSymbol);
        for(size_t i=0; i<m_numberOfColumns; i++)
                m_names.push_back(CHAR(STRING_ELT(colnames,(int)i)));

    for (size_t pos = 0; pos < m_numberOfColumns; pos++)
        {
          SEXP item =  (VECTOR_ELT (r_obj, (int)pos));
          SEXPTYPE type =  TYPEOF (item);
          switch (type)
            {
            case REALSXP:
                        {
                                std::vector<double> doubleCol;
                                RVector<double> doubleVec(item);
                                doubleVec.Extract(doubleCol);
                                m_compoundType.AddColumn(m_names[pos],doubleCol);
                        }
              break;
            case INTSXP:
                        {
                                std::vector<int> intCol;
                                RVector<int> intVec(item);
                                intVec.Extract(intCol);
                                m_compoundType.AddColumn(m_names[pos],intCol);
                        }
              break;
            case STRSXP:
                        {
                                std::vector<std::string> strCol;
                                RString stdVec(item);
                                stdVec.Dimensions(m_numberOfRows,1);
                                //seg::Matrix<std::string> strdata;
                                stdVec.Extract(strCol);
                                m_compoundType.AddColumn(m_names[pos],strCol);
                        }
              break;
            default:
                throw RException(rName+"No support for converting R type.");
            }
        }
}
}
#endif 