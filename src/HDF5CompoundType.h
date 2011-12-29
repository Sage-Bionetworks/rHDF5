#ifndef __COMPOUNDTYPE_H_
#define __COMPOUNDTYPE_H_       

#include <cstring>
#include <vector>
#include <sstream>
#include "HDF5DataType.h"
#include "HDF5Exception.h"
#include "StringUtils.h"

/////////////////////////////////////////////////////////////////////////////
// This class represents the HDF5compound type which is similar to R dataframe.
// It is basically a table where each column can be of different types
/////////////////////////////////////////////////////////////////////////////
namespace seg
{

class HDF5CompoundType 
{
public:

        HDF5CompoundType(){Initialize();};
        ~HDF5CompoundType(){};

        //Return ColumnIndex from ColumnName
        void GetColumnIndex(const std::string& columnName, size_t& index) const;

        //Return ColumnName from ColumnIndex.  Note:  Index starts from 0
        void GetColumnName(const size_t columnIndex, std::string& name) const;

        //Return the name the individual columns of the result set  
    void GetColumnNames(std::vector<std::string>& columnNames) const;

        //Return the type the individual columns of the result set  
        void GetColumnTypes(std::vector<HDF5DataType::DataType>& columnTypes) const;

        //Return the type the individual columns of the result set  
    void GetColumnTypes(std::vector<std::string>& columnTypes) const;

        //Return the type the individual column of the result set. Note:  Index starts from 0
    void GetColumnType(const size_t columnIndex, 
                                           HDF5DataType::DataType& columnType) const;

        //Return the type the individual column of the result set. Note:  Index starts from 0 
    void GetColumnType(const size_t columnIndex, 
                                                          std::string& columnType) const;

        //retrieve the column data by the index. 
        template<typename T>
        void GetColumnData(const size_t columnIndex, std::vector<T>& data) const;

        //------------------------------------------------------
        //Retrieve a indexed column as std::vector of std::string
        // if override is true, all data type will be converted to std::string. Note:  Index starts from 0
    void GetStringColumn(const size_t columnIndex, 
                                                            std::vector<std::string>& columnValues, bool override=false) const;
        
        //Retrieve a named column as std::vector of std::string
    // if override is true, all data type will be converted to std::string.
        void GetStringColumn(const std::string& columnName, 
                                                            std::vector<std::string>& columnValues, bool override=false) const;

        //------------------------------------------------------
        //Retrieve a indexed column as std::vector of int. Note:  Index starts from 0
        void GetIntColumn(const size_t columnIndex, 
                                                        std::vector<int>& columnValues) const;

        //Retrieve a named column as std::vector of int
        void GetIntColumn(const std::string& columnName, 
                                                        std::vector<int>& columnValues) const;

        //------------------------------------------------------
        //Retrieve a indexed column as std::vector of double. Note:  Index starts from 0
        void GetDoubleColumn(const size_t columnIndex, 
                                                           std::vector<double>& columnValues) const;

        //Retrieve a named column as std::vector of double
        void GetDoubleColumn(const std::string& columnName, 
                                                           std::vector<double>& columnValues) const;

        //------------------------------------------------------
        //Retrieve a indexed column as std::vector of boolean. Note:  Index starts from 0
        void GetBooleanColumn(const size_t columnIndex, 
                                                            std::vector<bool>& columnValues) const;

        //Retrieve a named column as std::vector of boolean
        void GetBooleanColumn(const std::string& columnName, 
                                                            std::vector<bool>& columnValues) const;

        // Initialize the result set.  Initialize all data members.
        void Initialize();

        // add an integer column
        void AddColumn(const std::string& columnName,
                               const std::vector<int>& columnValues) ;

        // add an double column
        void AddColumn(const std::string& columnName,
                               const std::vector<double>& columnValues) ;

        // add an std::string column
        void AddColumn(const std::string& columnName,
                const std::vector<std::string>& columnValues) ;

        // return the lower level hdf types of the columns.  It is for internal use. 
        void GetHDF5Types(std::vector<hid_t>& hdf5types) const;

        size_t NumberOfRows()const  
        { return m_rows;}; 
        size_t NumberOfColumns()const
        { return m_columns; };

        // map the entire dataset memory to a char* array.  This is for internal use.  
        void MapToVector(size_t datasize, const std::vector<size_t>& offsets, const std::vector<hid_t>& hdftypes, unsigned char* buf) const;
 
        // Operator overloaded using a member function
        bool operator==( HDF5CompoundType &other ); 

private:

        // each column can be of different data types
        typedef struct{
                std::vector<int> intColumn;
                std::vector<double> doubleColumn;
                std::vector<std::string> strColumn;
                std::vector<bool> boolColumn;
        } column;

        std::vector<column> m_data;
        std::vector<std::string> m_columnNames;
        std::vector<HDF5DataType::DataType> m_columnTypes;

        size_t m_rows;
        size_t m_columns;
};

//===============================================
//   inline implementations
//===============================================
///////////////////////////////////////////////////////
// Initialize the result set
///////////////////////////////////////////////////////
inline void HDF5CompoundType::Initialize()
{
        m_rows=0;
        m_columns=0;
        m_data.clear();
        m_columnNames.clear();
        m_columnTypes.clear();
}

///////////////////////////////////////////////////////
//Return ColumnIndex from ColumnName
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetColumnIndex(const std::string& columnName, size_t& index) const
{
        for(size_t i=0; i<m_columns; i++)
                if (columnName==m_columnNames[i])
                        index=i;
}

///////////////////////////////////////////////////////
//Return ColumnName from ColumnIndex
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetColumnName(const size_t columnIndex, std::string& name) const
{
        name= m_columnNames[columnIndex];
}

///////////////////////////////////////////////////////
// Retrieve a indexed column as std::vector of int
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetIntColumn(  const size_t columnIndex, 
                                                                          std::vector<int>& columnValue) const
{
        columnValue= m_data[columnIndex].intColumn;
}

///////////////////////////////////////////////////////
//Retrieve a named column as std::vector of int
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetIntColumn(  const std::string& columnName, 
                                                                          std::vector<int>& columnValues) const
{
        size_t idx;
        GetColumnIndex(columnName,idx);
        columnValues= m_data[idx].intColumn;
}

///////////////////////////////////////////////////////
// Retrieve a named column as std::vector of double
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetDoubleColumn(const std::string& columnName, 
                                                                                  std::vector<double>& columnValues) const
{
        size_t idx;
        GetColumnIndex(columnName,idx);
        columnValues= m_data[idx].doubleColumn;
}

///////////////////////////////////////////////////////
// Retrieve a named column as std::vector of double
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetDoubleColumn(const size_t columnIndex, 
                                                                                  std::vector<double>& columnValues) const
{
        columnValues= m_data[columnIndex].doubleColumn;
}

///////////////////////////////////////////////////////
// Retrieve a indexed column as std::vector of boolean
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetBooleanColumn(const size_t columnIndex, 
                                                                                        std::vector<bool>& columnValues) const
{
        columnValues= m_data[columnIndex].boolColumn;
}


///////////////////////////////////////////////////////
// Retrieve a named column as std::vector of boolean
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetBooleanColumn(const std::string& columnName, 
                                                                                   std::vector<bool>& columnValues) const
{
        size_t idx;
        GetColumnIndex(columnName,idx);
        columnValues= m_data[idx].boolColumn;
}

///////////////////////////////////////////////////////
// Retrieve a indexed column as std::vector of std::string  
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetStringColumn(const size_t columnIndex, 
                                                                                  std::vector<std::string>& columnValues,
                                                                                  bool override) const
{
        if(m_columnTypes[columnIndex]==HDF5DataType::STRING)
                columnValues=m_data[columnIndex].strColumn;
        else if(override)
        {
                 for(size_t i=0;i<m_rows; i++)
                 {
                         std::ostringstream str;
                         HDF5DataType::DataType dt;
                         GetColumnType(columnIndex,dt);
                         switch(dt)
                         {
                         case HDF5DataType::DOUBLE:
                          str << m_data[columnIndex].doubleColumn[i];
                                  break;
                         case HDF5DataType::INT:
                          str << m_data[columnIndex].intColumn[i];
                                  break;
                         case HDF5DataType::STRING:
                          str << m_data[columnIndex].boolColumn[i];
                                  break;
                         default:
                                 throw HDF5Exception("Unsupported data type: "+HDF5DataType::ToString(m_columnTypes[columnIndex]));
                         }
                     columnValues.push_back(str.str());
                 }
        }
        else
                throw HDF5Exception("Incorrect data type. Correct type is "+HDF5DataType::ToString(m_columnTypes[columnIndex]));
}

///////////////////////////////////////////////////////
//Retrieve a named column as std::vector of std::string  
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetStringColumn(const std::string& columnName, 
                                                                                  std::vector<std::string>& columnValues,
                                                                                  bool override) const
{
        size_t idx;
        GetColumnIndex(columnName,idx);
        GetStringColumn(idx,columnValues,override);
}

///////////////////////////////////////////////////////
//Return the name the individual columns of the result set 
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetColumnNames(std::vector<std::string>& columnNames) const
{
        columnNames= m_columnNames;
}

///////////////////////////////////////////////////////
//Return the type the individual columns of the result set 
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetColumnTypes(std::vector<HDF5DataType::DataType>& columnTypes) const
{
        columnTypes= m_columnTypes;
}

///////////////////////////////////////////////////////
//Return the type the individual columns of the result set 
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetColumnTypes(std::vector<std::string>& columnTypes) const
{
    for(size_t i=0; i<m_columnTypes.size(); i++)
                columnTypes.push_back(HDF5DataType::ToString(m_columnTypes[i]));
}

///////////////////////////////////////////////////////
//Return the type the individual column of the result set 
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetColumnType(const size_t columnIndex, 
                                                                         HDF5DataType::DataType& columnType) const
{
        columnType=m_columnTypes[columnIndex];
}

///////////////////////////////////////////////////////
//Return the type the individual column of the result set 
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetColumnType(const size_t columnIndex, 
                                                                                std::string& columnType) const
{
        columnType=HDF5DataType::ToString(m_columnTypes[columnIndex]);
}

///////////////////////////////////////////////////////
//Add new column to the set 
///////////////////////////////////////////////////////
inline void HDF5CompoundType::AddColumn(const std::string& columnName,
                               const std::vector<int>& columnValues) 
{
        if(m_rows==0)
                m_rows = columnValues.size();
        else if(m_rows!=columnValues.size())
                throw HDF5Exception("HDF5CompoundType::AddColumn - " + columnName + " is not the same size as other columns");

        m_columnTypes.push_back(HDF5DataType::INT);
        m_columnNames.push_back(columnName);
        column col;
        col.intColumn = columnValues;
        m_data.push_back(col);
        m_columns++;
}

///////////////////////////////////////////////////////
//Add new column to the set
///////////////////////////////////////////////////////
inline void HDF5CompoundType::AddColumn(const std::string& columnName,
                               const std::vector<double>& columnValues) 
{
        if(m_rows==0)
                m_rows = columnValues.size();
        else if(m_rows!=columnValues.size())
                throw HDF5Exception("HDF5CompoundType::AddColumn - " + columnName + " is not the same size as other columns");

        m_columnTypes.push_back(HDF5DataType::DOUBLE);
        m_columnNames.push_back(columnName);
        column col;
        col.doubleColumn = columnValues;
        m_data.push_back(col);
        m_columns++;
}

///////////////////////////////////////////////////////
//Add new column to the set
///////////////////////////////////////////////////////
inline void HDF5CompoundType::AddColumn(const std::string& columnName,
                                                                 const std::vector<std::string>& columnValues) 
{
        if(m_rows==0)
                m_rows = columnValues.size();
        else if(m_rows!=columnValues.size())
                throw HDF5Exception("HDF5CompoundType::AddColumn - " + columnName + " is not the same size as other columns");

        m_columnTypes.push_back(HDF5DataType::STRING);
        m_columnNames.push_back(columnName);
        column col;
        col.strColumn = columnValues;
        m_data.push_back(col);
        m_columns++;
}

///////////////////////////////////////////////////////
// Return the hdf5types of all columns
///////////////////////////////////////////////////////
inline void HDF5CompoundType::GetHDF5Types(std::vector<hid_t>& hdf5types) const
{
        for(size_t i=0;i<m_data.size(); i++)
        {
                 HDF5DataType::DataType dt;
                 GetColumnType(i,dt);
                 switch(dt)
                 {
                 case HDF5DataType::DOUBLE:
                  hdf5types.push_back(H5T_NATIVE_DOUBLE);
                          break;
                 case HDF5DataType::INT:
                  hdf5types.push_back(H5T_NATIVE_INT);
                          break;
                 case HDF5DataType::STRING:
                         {
                  hid_t stid = H5Tcopy(H5T_C_S1);
                          column col;
                          col=m_data[i];
                          size_t maxlen = 0;
                          for (size_t j=0; j<col.strColumn.size();j++)   
                                if(col.strColumn[j].size()>maxlen)
                                        maxlen=col.strColumn[j].size();

                          H5Tset_size(stid,maxlen+1);
                          hdf5types.push_back(stid);
                          break;
                         }
                 default:
                         throw HDF5Exception("HDF5CompoundType::GetHDF5Types - Unsupported data type: "+HDF5DataType::ToString(m_columnTypes[i]));
                 }
        }
}

///////////////////////////////////////////////////////
// Map all data to a single char* array buffer
///////////////////////////////////////////////////////
inline void HDF5CompoundType::MapToVector(size_t datasize, const std::vector<size_t>& offsets, const std::vector<hid_t>& hdftypes, unsigned char* buf) const
{
        // write data to the dataset
        unsigned ri,pos;
        size_t colcount=NumberOfColumns();
        size_t rowcount=NumberOfRows();

        for (ri = 0; ri < rowcount; ri++)
                for (pos = 0; pos < colcount; pos++)
                {
                        HDF5DataType::DataType type = m_columnTypes[pos];
                        void *ptr = &buf[(ri*datasize)+offsets[pos]];

                        switch (type)
                        {
                        case HDF5DataType::DOUBLE:{
                                std::vector<double> data;
                                GetDoubleColumn(pos,data);
                                memcpy (ptr, &(data[ri]), sizeof (double));
                                break;}
                        case HDF5DataType::INT:{
                                std::vector<int> data;
                                GetIntColumn(pos,data);
                                memcpy (ptr, &(data[ri]), sizeof (int));
                                break;}
                        case HDF5DataType::STRING:
                                {
                                        std::vector<std::string> data;
                                        GetStringColumn(pos,data);
                                        memset (ptr, 0, H5Tget_size (hdftypes[pos]));
                                        strcpy ((char *)ptr, (data[ri]).c_str());
                                }
                                break;
                        default:
                                throw HDF5Exception("HDF5CompoundType::MapToVector - Unsupported data type: "+HDF5DataType::ToString(type));
                        }       
                }
}

///////////////////////////////////////////////////////
// overloaded operator
///////////////////////////////////////////////////////
inline bool HDF5CompoundType::operator==( HDF5CompoundType &other )
{
        if (!(other.m_rows==m_rows)&& (other.m_columns==m_columns)&&(other.m_columnNames.size()==m_columnNames.size()))
                return false;

        for(size_t i=0; i<other.m_columnNames.size(); i++)
        {
                if (!(other.m_columnNames[i]==m_columnNames[i]) && (other.m_columnTypes[i]==m_columnTypes[i]))
                        return false;

                std::vector<std::string> str1,str2;
                GetStringColumn(i,str1,true);
                GetStringColumn(i,str2,true);
                for(size_t j=0; j<m_rows; j++)
                {
                        if (!(str1[j]==str2[j]))
                                return false;
                }
        }
        return true;
}

///////////////////////////////////////////////////////
// Return the column data by the index
///////////////////////////////////////////////////////
template<typename T>
inline void HDF5CompoundType::GetColumnData(const size_t columnIndex, std::vector<T>& data) const
{
        switch(m_columnTypes[columnIndex])
        {
        case HDF5DataType::DOUBLE:
                if (typeid(T)!=typeid(double))
                        throw HDF5Exception("HDF5CompoundType::GetColumnData - type mismatch.");
                GetDoubleColumn(columnIndex,reinterpret_cast< std::vector<double>& >(data));
                break;
        case HDF5DataType::INT:
                if (typeid(T)!=typeid(int))
                        throw HDF5Exception("HDF5CompoundType::GetColumnData - type mismatch.");
                GetIntColumn(columnIndex,reinterpret_cast< std::vector<int>& >(data));
                break;
        case HDF5DataType::STRING:
                if (typeid(T)!=typeid(std::string))
                        throw HDF5Exception("HDF5CompoundType::GetColumnData - type mismatch.");
                GetStringColumn(columnIndex,reinterpret_cast< std::vector<std::string>& >(data));
                break;
        default:
                throw HDF5Exception("HDF5CompoundType::GetColumnData - Unsupported data type: "+HDF5DataType::ToString(m_columnTypes[columnIndex]));
        }
}
#include "HDF5CompoundType.cpp"
}

#endif //__COMPOUNDTYPE_H_

