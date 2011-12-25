#ifndef __HDF5ATTRIBUTE_H_
#define __HDF5ATTRIBUTE_H_      
#include <string>
#include "hdf5.h"
#include "HDF5Object.h"
#include "HDF5Exception.h"
#include "Matrix.h"


//*******************************************************************************
//*     This class provides functions to access a HDF5 attribute.  This class should not 
//* be instantiated explicitly.  Since attribute can only belong to a group or dataset, 
//* it should therefore be instantiated though HDF5Group or HDF5Dataset. 
//*******************************************************************************

namespace seg
{
        class HDF5Dataset;
        class HDF5Attribute : public HDF5Object
        {
         public:
                 
                // users should not instantiate this class explicitly.
                virtual ~HDF5Attribute(); 
                HDF5Attribute();  
                template <typename T>
                HDF5Attribute(const HDF5Object& obj, const std::string& name, const seg::Matrix<T>& data, const int compressedlevel=0);
                HDF5Attribute(int ownerID, const std::string& name);
                HDF5Attribute& operator=(const HDF5Attribute& ds);

                template <typename T>
                void ReadData(seg::Matrix<T>& data);

                template <typename T>
                void WriteData(const seg::Matrix<T>& data, const int compressedlevel=0);

                size_t NumberOfRows() const;            
                size_t NumberOfColumns() const; 
                HDF5DataType::DataType GetDataType() const;
                virtual std::string ToString(const std::string& tabs="");

        private: 
                                
                 virtual void Open();
                 virtual void Close();

        };

//===============================================
//   inline implementations because of template functions
//===============================================
inline HDF5Attribute::HDF5Attribute()
{
        m_opened = false;
}

inline HDF5Attribute::HDF5Attribute(int ownerID,  const std::string& name)
{
        m_opened=false;
        m_ownerID = ownerID;
        m_name = name;
        Open();
};
//===============================================
// constructor  
//===============================================
template <typename T>
inline HDF5Attribute::HDF5Attribute(const HDF5Object& obj, const std::string& name, const seg::Matrix<T>& data, const int compressedlevel)
{
        hid_t locID = obj.ID();
   Assert(locID, "HDF5Attribute::HDF5Attribute() Unknown HDF5 parent object");

    if(obj.Exist(name))
   {
           std::string objname = (const_cast< HDF5Object& > (obj)).GetName();
           Assert(-1, "HDF5Attribute::HDF5Attribute() "+ objname + "/" + name + " already exists");
   }

        /*
         * Create a new attribute within the file using defined dataspace and
         * datatype and default attribute creation properties.
         */
        hsize_t     dimsf[2];              /* attribute dimensions */
        dimsf[0] = data.NumberOfRows();
        dimsf[1] = data.NumberOfColumns();
        Assert(((dimsf[0]>0)&&(dimsf[1]>0))?1:-1, "HDF5Attribute::HDF5Attribute() Cannot create dataspace with empty row or col");
        hid_t dataspace = H5Screate_simple(2, dimsf, NULL); 
        Assert(dataspace, "HDF5Attribute::HDF5Attribute() Failed to create dataspace");

        herr_t status;
        // always enable chunking for extensibility 
        hid_t plist  = H5Pcreate(H5P_DATASET_CREATE);  //property list
        hsize_t     cdims[2];
        cdims[0] = data.NumberOfColumns()<data.NumberOfRows()?data.NumberOfColumns():data.NumberOfRows(); // the size of the chunks used to store a chunked layout dataset
        cdims[1] = data.NumberOfColumns()<data.NumberOfRows()?data.NumberOfColumns():data.NumberOfRows();
        status = H5Pset_chunk(plist, 2, cdims);

         // compressed attribute
        if(compressedlevel>0)
                status = H5Pset_deflate( plist, compressedlevel);  // 9 is max compression level

        Matrix<T> tmp(1);
        T type=tmp[0];  // initialize to avoid warnings
        hid_t datatype=HDF5DataType::MapNativeType(type);
        hid_t attribute = H5Acreate(locID, name.c_str(), datatype, dataspace, plist);
        if(attribute<0)
        {
                H5Sclose(dataspace);
                H5Pclose(plist);
                H5Tclose(datatype);
        }
        Assert(attribute, "HDF5Attribute::HDF5Attribute() Failed to create attribute - "+name);

        m_name = name;
        m_ID = attribute;
        m_opened = true;
        
        if (typeid(type)==typeid(std::string))
        {
                seg::Matrix<char*> strs(data.Size());
                for (size_t index=0;index<data.Size();index++)
                        strs[index]=const_cast< char * > ((reinterpret_cast< const seg::Matrix<std::string>& >(data))[index].c_str());

                status = H5Awrite(m_ID, datatype, strs.Data());
        }
        else
        {
                status = H5Awrite(m_ID, datatype, data.Data());
        }
        H5Sclose(dataspace);
        H5Pclose(plist);
        H5Tclose(datatype);
        Assert(status, "HDF5Attribute::HDF5Attribute() Failed to write to attribute - "+m_name);
}   

//===============================================
// destructor
//===============================================
inline HDF5Attribute::~HDF5Attribute() 
{
        Close();
}
//===============================================
// overloaded =
//===============================================
inline HDF5Attribute& HDF5Attribute::operator=(const HDF5Attribute& att)
{
                Close();
                m_ownerID=att.m_ownerID;
                m_name=att.m_name;
                Open();
                return *this;
}
        
//===============================================
// open the attribute
//===============================================
inline void HDF5Attribute::Open()
{
   if(!m_opened)
   {
           m_ID=H5Aopen_name(m_ownerID,m_name.c_str());
           Assert(m_ID, "HDF5Attribute::Open() Failed to open existing attribute - "+m_name);
           m_opened=true;
   }
}
//===============================================
// close attr
//===============================================
inline void HDF5Attribute::Close()
{
        if(m_opened)
        {
                herr_t status = H5Aclose(m_ID);
                Assert(status, "HDF5Attribute::Close() Failed to close existing attribute - "+m_name);
        }
        m_opened=false;
}

//===============================================
// write attr to file
//===============================================
template <typename T>
inline void HDF5Attribute::WriteData(const seg::Matrix<T>& data, const int compressedlevel)
{
        CheckOpen();
     if(H5Gget_objinfo (m_ownerID, m_name.c_str(), 0, NULL)==0)
         {
           Assert(-1, "HDF5Attribute::WriteData() "+  m_name + " already exists");       
         }

        /*
         * Create a new attribute within the file using defined dataspace and
         * datatype and default attribute creation properties.
         */
        hsize_t     dimsf[2];              /* attribute dimensions */
        dimsf[0] = data.NumberOfRows();
        dimsf[1] = data.NumberOfColumns();
        Assert(((dimsf[0]>0)&&(dimsf[1]>0))?1:-1, "HDF5Attribute::WriteData() Cannot create dataspace with empty row or col");
        hid_t dataspace = H5Screate_simple(2, dimsf, NULL); 
        Assert(dataspace, "HDF5Attribute::WriteData() Failed to create dataspace");

        herr_t status;
        // always enable chunking for extensibility 
        hid_t plist  = H5Pcreate(H5P_DATASET_CREATE);  //property list
        hsize_t     cdims[2];
        cdims[0] = data.NumberOfColumns()<data.NumberOfRows()?data.NumberOfColumns():data.NumberOfRows(); // the size of the chunks used to store a chunked layout dataset
        cdims[1] = data.NumberOfColumns()<data.NumberOfRows()?data.NumberOfColumns():data.NumberOfRows();
        status = H5Pset_chunk(plist, 2, cdims);

        // compressed attribute
        if(compressedlevel>0)
                status = H5Pset_deflate( plist, compressedlevel);  // 9 is max compression level

        Matrix<T> tmp(1);
        T type=tmp[0];  // initialize to avoid warnings
        hid_t datatype=HDF5DataType::MapNativeType(type);
        hid_t attribute = H5Acreate(m_ownerID, m_name.c_str(), datatype, dataspace, plist);
        if(attribute<0)
        {
                H5Sclose(dataspace);
                H5Pclose(plist);
                H5Tclose(datatype);
        }
        Assert(attribute, "HDF5Attribute::WriteData() Failed to create attribute - "+m_name);

        m_ID = attribute;
        m_opened = true;
                
        if (typeid(type)==typeid(std::string))
        {
                seg::Matrix<char*> strs(data.Size());
                for (size_t index=0;index<data.Size();index++)
                        strs[index]=const_cast< char * > ((reinterpret_cast< const seg::Matrix<std::string>& >(data))[index].c_str());
                status = H5Awrite(m_ID, datatype, strs.Data());
        }
        else
        {
                status = H5Awrite(m_ID, datatype, data.Data());
        }
        H5Sclose(dataspace);
        H5Pclose(plist);
        H5Tclose(datatype);
        Assert(status, "HDF5Attribute::WriteData() Failed to write to attribute - "+m_name);
}

//===============================================
// read attr
//===============================================
template <typename T>
inline void HDF5Attribute::ReadData(seg::Matrix<T>& data)
{
        CheckOpen();
        Matrix<T> tmp(1);
        T type=tmp[0];  // initialize to avoid warnings
        hid_t nativedatatype=HDF5DataType::MapNativeType(type);
        HDF5DataType::DataType outdatatype=HDF5DataType::MapHDF5Type(type);
        HDF5DataType::DataType datatype=GetDataType();

        herr_t status=0;
        status = (datatype==outdatatype)?0:-1;
        Assert(status, "HDF5Attribute::ReadData() Failed to read attribute - "+m_name + ". Data type not matched!");

        data.Resize(NumberOfRows(),NumberOfColumns());

        if(typeid(type) == typeid(bool))
        {
                // HDF5 API reads bool data as 4 byte char
                seg::Matrix<char> charData(NumberOfRows(),NumberOfColumns());
                status = H5Aread(m_ID, nativedatatype, charData.Data());
                size_t i;
                for(i=0; i<charData.Size(); i++)
                        (reinterpret_cast<seg::Matrix<bool>& >(data))[i]=(charData[i]==1);
        }
        else if ((typeid(type)==typeid(std::string))  || 
                    (typeid(type)==typeid(char*)))
        {
                size_t total = data.Size();
                size_t index=0;
                htri_t isVarStr=H5Tis_variable_str(H5Aget_type(m_ID));
                size_t len = H5Tget_size(H5Aget_type(m_ID));

                // if string / char*  matrix has variable length
                if(isVarStr==1)
                {
                        hid_t nativedatatype= HDF5DataType::MapNativeType(type);
                        // if string type, we need to read to char* type first and copy back to string
                        if (typeid(type)==typeid(std::string)) 
                        {
                                seg::Matrix<char *> tmpData(NumberOfRows(),NumberOfColumns());
                                status = H5Aread(m_ID, nativedatatype, tmpData.Data());
                                for (index=0;index<tmpData.Size();index++)
                                        (reinterpret_cast< seg::Matrix<std::string>& >(data))[index]=tmpData[index];
                        }
                        else
                                status = H5Aread(m_ID, nativedatatype, data.Data());

                        H5Tclose(nativedatatype);
                }
                else  // fixed size string
                {
                        hid_t nativedatatype = HDF5DataType::MapNativeType_FixedSizeString(len);
                        char** d = (char**) malloc(total*sizeof(char*)); 
                        d[0]=(char*) malloc(len*total*sizeof(char));
                        for (size_t i=1; i < total; i++) 
                                d[i] = d[0]+i*len;

                        status = H5Aread(m_ID, nativedatatype, &d[0][0]); 
                        for (index=0;index<data.Size();index++)
                        {
                                if(typeid(type)==typeid(std::string)) 
                                        (reinterpret_cast< seg::Matrix<std::string>& >(data))[index] = (char*)d[index];  
                                else
                                        (reinterpret_cast< seg::Matrix<char*>& >(data))[index] =(char*)d[index];
                        }
                        H5Tclose(nativedatatype);
                        free(d[0]);
                        free(d);
                }
        }
        else
        {
                hid_t nativedatatype= HDF5DataType::MapNativeType(type);
                status = H5Aread(m_ID, nativedatatype, data.Data());
                H5Tclose(nativedatatype);
        }
        Assert(status, "HDF5Attribute::ReadData() Failed to read attribute - "+m_name);
}

//===============================================
inline size_t HDF5Attribute::NumberOfRows() const
 {
        CheckOpen();
        hid_t dataspace = H5Aget_space(m_ID);    /* dataspace identifier */
        Assert(dataspace, "HDF5Attribute::NumberOfRows() Failed to get dataspace - "+m_name);
        hsize_t  dims_out[2]={1,1}, maxdim[2]={1,1};
        int status_n  = H5Sget_simple_extent_dims(dataspace, dims_out,maxdim);
        Assert(status_n, "HDF5Attribute::NumberOfRows() Failed to get dataspace dimensions - "+m_name);
        return (size_t)dims_out[0];
 }

//===============================================
inline size_t HDF5Attribute::NumberOfColumns() const
 {
        CheckOpen();
        hid_t dataspace = H5Aget_space(m_ID);    /* dataspace identifier */
        Assert(dataspace, "HDF5Attribute::NumberOfColumns() Failed to get dataspace - "+m_name);
        hsize_t     dims_out[2]={1,1}, maxdim[2]={1,1}; 
        int status_n  = H5Sget_simple_extent_dims(dataspace, dims_out,maxdim);
        Assert(status_n, "HDF5Attribute::NumberOfColumns() Failed to get dataspace dimensions - "+m_name);
        return (size_t)dims_out[1];
 }

//===============================================
inline HDF5DataType::DataType HDF5Attribute::GetDataType() const
 {
         CheckOpen();
         return HDF5DataType::GetAttributeDataType(m_ID);
 }

//===============================================
inline std::string HDF5Attribute::ToString(const std::string& tabs)
 {
         std::ostringstream str;
         str << tabs<< "Attributename: " << m_name.c_str() << "\n";
         str << tabs<< "Rows: " << NumberOfRows() << "\n";
         str << tabs<< "Cols: " << NumberOfColumns() << "\n";
         str << tabs<< "Data type: " << HDF5DataType::ToString(GetDataType()) << "\n";
         return str.str();
 }
#include "HDF5Attribute.cpp"
}               

#endif
