#ifndef __HDF5DATATYPE_H_
#define __HDF5DATATYPE_H_       
#include "hdf5.h"
#include "HDF5Exception.h"
#include <typeinfo>
#include "StringUtils.h"

#if !defined(WIN32) && !defined(WIN64)
#define __int64 long long
#endif

//*******************************************************************************
//*     This class provides utility functions to work with HDF5 data types. These functions
//* are used by other HDF5 classes in this library.
//*******************************************************************************


namespace seg
{
        class HDF5DataType
        {
                public:
                        // These are the current supported data type. 
                        // note: BOOL is treated as INT8 in HDF5 API. 
                        // Even though data is saved as H5T_NATIVE_CHAR, its type is still mapped to H5T_NATIVE_INT
                        // therefore BOOL will be mapped to CHAR which is the closest
                        enum DataType{ CHAR, INT, INT64, LONG, FLOAT, DOUBLE, STRING, COMPOUND, UNKNOWN };  

                        // map to a lower level HDF5 type with fixed length.
                         static hid_t MapNativeType_FixedSizeString( const size_t size );
                         
                         // map to a lower level HDF5 type
                        template <typename T>
                         static hid_t MapNativeType( T type );
                        
                        // map to one of the enumerations above.
                        template <typename T>
                         static DataType MapHDF5Type( T type ); 

                         // map to one of the enumerations above.
                        static DataType MapHDF5TypeFromString( const std::string& type); 
                        
                         // map the lower level attribute type to our enumeration.
                         static DataType GetAttributeDataType(hid_t obj);
                         
                         // map the lower level dataset type to our enumeration.
                         static DataType GetDataSetDataType(hid_t obj);

                         // return a string representation of the type
                         static std::string ToString(DataType dt);

        };

//===============================================
inline HDF5DataType::DataType HDF5DataType::GetDataSetDataType(hid_t obj) 
 {
        hid_t type = H5Dget_type(obj);
        H5T_class_t cls = H5Tget_class(type);
        size_t typesize = H5Tget_size(type);
        if (cls == H5T_INTEGER) 
        {
                switch (typesize)
                {
                        case 1:
                          return CHAR;
                        case 8:
                          return INT64;
                        default: 
                          return INT;
                }
        }
        if (cls == H5T_FLOAT) return (typesize==4)? FLOAT : DOUBLE;
        if (cls == H5T_STRING) return STRING;
        if (cls == H5T_COMPOUND) return COMPOUND;
        return UNKNOWN;
 }

//===============================================
inline HDF5DataType::DataType HDF5DataType::GetAttributeDataType(hid_t obj) 
 {
        hid_t type = H5Aget_type(obj);
        H5T_class_t cls = H5Tget_class(type);
        size_t typesize = H5Tget_size(type);
        if (cls == H5T_INTEGER) 
        {
                switch (typesize)
                {
                        case 1:
                          return CHAR;
                        case 8:
                          return INT64;
                        default: 
                          return INT;
                }
        }

        if (cls == H5T_FLOAT)   return (typesize==4)? FLOAT : DOUBLE;
        if (cls == H5T_STRING)  return STRING;
        if (cls == H5T_COMPOUND) return COMPOUND;
        return UNKNOWN;
 }

 //===============================================
template <typename T>
 inline HDF5DataType::DataType HDF5DataType::MapHDF5Type(T type)  
{ 
        if(typeid(type)==typeid(double))
                return DOUBLE;
        else if(typeid(type)==typeid(float)) 
                return FLOAT;
        else if ((typeid(type)==typeid(int))||
                        (typeid(type)==typeid(long)))
                return INT;
        else if (typeid(type)==typeid(__int64))
                return INT64;
        else if ((typeid(type)==typeid(char))||
                        (typeid(type)==typeid(bool)))   //bool is INT8 which is a char
                return CHAR;
        else if ((typeid(type)==typeid(std::string))||
                         (typeid(type)==typeid(char*)) ) 
                return STRING;
        else
                return UNKNOWN;
 }
 //===============================================
 inline HDF5DataType::DataType HDF5DataType::MapHDF5TypeFromString(const std::string& type)  
{ 
        if(StringUtils::CompareNoCase(type,"DOUBLE"))
                return DOUBLE;
        else if(StringUtils::CompareNoCase(type,"FLOAT")) 
                return FLOAT;
        else if ((StringUtils::CompareNoCase(type,"INT"))||
                        (StringUtils::CompareNoCase(type,"LONG")))
                return INT;
        else if (StringUtils::CompareNoCase(type,"INT64"))
                return INT64;
        else if ((StringUtils::CompareNoCase(type,"CHAR"))||
                        (StringUtils::CompareNoCase(type,"BOOL")))      //bool is INT8 which is a char
                return CHAR;
        else if ((StringUtils::CompareNoCase(type,"STRING"))||
                         (StringUtils::CompareNoCase(type,"CHAR*"))) 
                return STRING;
        else if (StringUtils::CompareNoCase(type,"COMPOUND"))
                return COMPOUND;
        else
                return UNKNOWN;
 }
 
//===============================================
// this function identifies the real data type.
template <typename T> 
inline hid_t HDF5DataType::MapNativeType( T type )  
{
        if(typeid(type)==typeid(double))
                return H5T_NATIVE_DOUBLE;
        else if (typeid(type)==typeid(float)) 
                return H5T_NATIVE_FLOAT;
        else if ((typeid(type)==typeid(int))||
                        (typeid(type)==typeid(long)))   
                return H5T_NATIVE_INT;
        else if (typeid(type)==typeid(__int64)) 
                return H5T_NATIVE_LLONG;
        else if (typeid(type)==typeid(char))
                return H5T_NATIVE_CHAR;
        else if ((typeid(type)==typeid(std::string))||
                         (typeid(type)==typeid(char*)) ) 
        {
                hid_t atype = H5Tcopy (H5T_C_S1);
                if(H5Tset_size(atype, H5T_VARIABLE )<0) 
                        throw HDF5Exception("Failed to set size for string data tye");

                return atype;
        }
        else if (typeid(type)==typeid(bool))    
                return H5T_NATIVE_CHAR;
        else
        {
                std::string typeStr = typeid(type).name();
                throw HDF5Exception("Unknown data type: "+typeStr);
        }
};

//===============================================
// this function identifies the real data type.
inline hid_t HDF5DataType::MapNativeType_FixedSizeString(const size_t size )  
{
                hid_t atype = H5Tcopy (H5T_C_S1);
                if(H5Tset_size(atype, size) <0)
                        throw HDF5Exception("Failed to set size for string data tye");

                return atype;
};

//===============================================
inline std::string HDF5DataType::ToString(DataType dt)
{
        switch(dt)
        {
        case CHAR: return "CHAR";
        case INT: return "INT";
        case INT64: return "INT64";
        case LONG: return "LONG";
        case FLOAT: return "FLOAT";
        case DOUBLE: return "DOUBLE";
        case STRING: return "STRING";
        case COMPOUND: return "COMPOUND";
        case UNKNOWN: return "UNKNOWN";
        }
        return "UNKNOWN";
}

#include "HDF5DataType.cpp"
}

#endif
