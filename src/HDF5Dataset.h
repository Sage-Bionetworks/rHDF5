#if defined(WIN32) || defined(WIN64)
#pragma warning(disable:4700)
#endif
#ifndef __HDF5DATASET_H_
#define __HDF5DATASET_H_        
#include <cstring>
#include <algorithm>
#include "hdf5.h"
#include "HDF5Object.h"
#include "HDF5Exception.h"
#include "Matrix.h"
#include "HDF5DataType.h" 
#include "HDF5CompoundType.h" 
#include "HDF5Attribute.h"

//*******************************************************************************
//*     This class provides functions to access a HDF5 dataset.  This class should not be
//* instantiated explicitly.  It should be instantiated by using HDF5DA or HDF5Group.
//*******************************************************************************

namespace seg
{
        class HDF5Dataset : public HDF5Object
        {

         public:

                // users should not instantiate this class explicitly.
                virtual ~HDF5Dataset(); 
            HDF5Dataset();  
                template <typename T>
                HDF5Dataset(const HDF5Object& obj, const std::string& name, const seg::Matrix<T>& data, const int compressedlevel=0);
                HDF5Dataset(const HDF5Object& obj, const std::string& name, const seg::HDF5CompoundType& data, const int compressedlevel=0);
                HDF5Dataset(int ownerID, const std::string& name);
                HDF5Dataset& operator=(const HDF5Dataset& ds);
                
                // read data from this dataset
                template <typename T>
                void ReadData(seg::Matrix<T>& data);
                void ReadData(seg::HDF5CompoundType& data);
                
                // read rows of data from this dataset
                template <typename T>
                void ReadData(size_t startRowIdx, size_t nRows, seg::Matrix<T>& data);
                void ReadData(size_t startRowIdx, size_t nRows, seg::HDF5CompoundType& data);
                
                // write data to this dataset
                template <typename T>
                void WriteData(const seg::Matrix<T>& data, const int compressedlevel=0);
                void WriteData(const seg::HDF5CompoundType& data, const int compressedlevel=0);

                // overwrite rows of data in this dataset
                // dataset will be extended if necessary.
                template <typename T>
                void WriteData(size_t startRowIdx, size_t nRows, const seg::Matrix<T>& data, const int compressedlevel=0);
                void WriteData(size_t startRowIdx, size_t nRows, const seg::HDF5CompoundType& data, const int compressedlevel=0);

                // create a new attribute
                template <typename T>
                void CreateAttribute(const std::string& attributeName, const seg::Matrix<T>& attributeData, const int compressedlevel=0);
                
                // read data from an existing attribute
                template <typename T>
                void ReadAttribute(const std::string& attributeName, seg::Matrix<T>& attributeData);
                
                // delete an existing attribute
                void DeleteAttribute(const std::string& attributeName);
                
                // return an existing attribute object
                HDF5Attribute OpenAttribute(const std::string& attributeName);
                
                size_t NumberOfAttributes() const;
                
                // return all attribute names associated with this dataset
                const std::vector <std::string>& GetAttributeNames() const;

                // return true if an attribute exists
                virtual bool Exist( const std::string& attributeName) const;
                
                size_t NumberOfRows() const;                  
                size_t NumberOfColumns() const; 
                
                // return the type of data stored in this dataset
                HDF5DataType::DataType GetDataType() const;
                
                // return a summary of this dataset
                virtual std::string ToString(const std::string& tabs="");

        private: 

                const HDF5Dataset& This()
                { HDF5Dataset* obj = const_cast<HDF5Dataset*> (this);
                  return *obj;
                }

                virtual void Open();
                virtual void Close();
                void SelectHyperslab(size_t startRowIdx, size_t nRows, hid_t& dataspace, hid_t& memspace);
                
                std::vector <std::string> m_attributenames;
        };

//===============================================
//   inline implementations because it contains template functions 
//===============================================
        inline HDF5Dataset::HDF5Dataset()
        {
                m_opened = false;
        }

        inline HDF5Dataset::HDF5Dataset(int ownerID,  const std::string& name)
                {
                        m_opened=false;
                        m_ownerID = ownerID;
                        m_name = name;
                        Open();
                };

//===============================================
        template <typename T>
                inline HDF5Dataset::HDF5Dataset(const HDF5Object& obj, const std::string& name, const seg::Matrix<T>& data, const int compressedlevel)
                {
                        hid_t locID = obj.ID();
                   Assert(locID, "HDF5Dataset::HDF5Dataset() Unknown HDF5 parent object");

                    if(obj.Exist(name))
                   {
                           //herr_t status = H5Gunlink(locID, name.c_str());
                           //Assert(status, "HDF5Dataset::HDF5Dataset() Failed to remove an existing group - "+name);
                           std::string objname = (const_cast< HDF5Object& > (obj)).GetName();
                           Assert(-1, "HDF5Dataset::HDF5Dataset() "+ objname + "/" + name + " already exists");
                   }

                        /*
                         * Create a new dataset within the file using defined dataspace and
                         * datatype and default dataset creation properties.
                         */
                        hsize_t     dimsf[2];              /* dataset dimensions */
                        dimsf[0] = data.NumberOfRows();
                        dimsf[1] = data.NumberOfColumns();
                        Assert(((dimsf[0]>0)&&(dimsf[1]>0))?1:-1, "HDF5Dataset::HDF5Dataset() Cannot create dataspace with empty row or col");
                        hid_t dataspace = H5Screate_simple(2, dimsf, NULL); 
                        Assert(dataspace, "HDF5Dataset::HDF5Dataset() Failed to create dataspace");

                        herr_t status;
                        // always enable chunking for extensibility 
                        hid_t plist  = H5Pcreate(H5P_DATASET_CREATE);  //property list
                        hsize_t     cdims[2];
                        cdims[0] = data.NumberOfColumns()<data.NumberOfRows()?data.NumberOfColumns():data.NumberOfRows(); // the size of the chunks used to store a chunked layout dataset
                        cdims[1] = data.NumberOfColumns()<data.NumberOfRows()?data.NumberOfColumns():data.NumberOfRows();
                        status = H5Pset_chunk(plist, 2, cdims);

                        if(compressedlevel>0)
                        {
                                 // compressed dataset
                                status = H5Pset_deflate( plist, compressedlevel);  // 9 is max compression level
                        }
                        Matrix<T> tmp(1);
                        T type=tmp[0];  // initialize to avoid warnings
                        hid_t datatype=HDF5DataType::MapNativeType(type);
                        hid_t dataset = H5Dcreate(locID, name.c_str(), datatype, dataspace, plist);
                        if(dataset<0)
                        {
                                H5Sclose(dataspace);
                                H5Pclose(plist);
                                H5Tclose(datatype);
                        }
                        Assert(dataset, "HDF5Dataset::HDF5Dataset() Failed to create dataset - "+name);

                        m_name = name;
                        m_ID = dataset;
                        m_ownerID = locID;
                        m_opened=true;
                
                        if (typeid(type)==typeid(std::string))
                        {
                                seg::Matrix<char*> strs(data.Size());
                                for (size_t index=0;index<data.Size();index++)
                                        strs[index]=const_cast< char * > ((reinterpret_cast< const seg::Matrix<std::string>& >(data))[index].c_str());

                                status = H5Dwrite(m_ID, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, strs.Data());
                        }
                        else
                        {
                                status = H5Dwrite(m_ID, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, data.Data());
                        }
                        H5Sclose(dataspace);
                        H5Pclose(plist);
                        H5Tclose(datatype);
                        Assert(status, "HDF5Dataset::HDF5Dataset() Failed to write to dataset - "+m_name);
                }

//===============================================
inline HDF5Dataset::HDF5Dataset(const HDF5Object& obj, const std::string& name, const seg::HDF5CompoundType& data, const int compressedlevel)
{
        hid_t locID = obj.ID();
   Assert(locID, "HDF5Dataset::HDF5Dataset() Unknown HDF5 parent object");

    if(obj.Exist(name))
   {
           //herr_t status = H5Gunlink(locID, name.c_str());
           //Assert(status, "HDF5Dataset::HDF5Dataset() Failed to remove an existing group - "+name);
           std::string objname = (const_cast< HDF5Object& > (obj)).GetName();
           Assert(-1, "HDF5Dataset::HDF5Dataset() "+ objname + "/" + name + " already exists");
   }

        /*
         * Create a new dataset within the file using defined dataspace and
         * datatype and default dataset creation properties.
         */
        hsize_t     dimsf[1] = {data.NumberOfRows()};              /* dataset dimensions */
        Assert(((data.NumberOfRows()>0)&&(data.NumberOfColumns()>0))?1:-1, "HDF5Dataset::HDF5Dataset() Cannot create dataspace with empty row or col");
        hid_t dataspace = H5Screate_simple(1, dimsf, NULL); 
        Assert(dataspace, "HDF5Dataset::HDF5Dataset() Failed to create dataspace");
        herr_t status;

        // always enable chunking for extensibility 
        hid_t plist  = H5Pcreate(H5P_DATASET_CREATE);  //property list
        hsize_t     cdims[1]={data.NumberOfColumns()<data.NumberOfRows()?data.NumberOfColumns():data.NumberOfRows()};
        status = H5Pset_chunk(plist, 1, cdims);

        /* compression is not available for data frame */
        if(compressedlevel>0)
                status = H5Pset_deflate( plist, compressedlevel);  // 9 is max compression level

        // since we are treating the table as one single vector, we need to find out the offset of each column
        // in order to populate data at the right place.
        std::vector<hid_t> hdftypes;
        data.GetHDF5Types(hdftypes);
        std::vector<size_t> offsets;
        size_t size=0;
        for(size_t i=0;i<hdftypes.size(); i++)
        {
                offsets.push_back(size);
                size +=H5Tget_size(hdftypes[i]); 
        }

        // insert the columns in the table
    hid_t sid = H5Tcreate (H5T_COMPOUND, size);  // memory data type
        std::vector<std::string> names;
        data.GetColumnNames(names);
        for(size_t i=0;i<hdftypes.size(); i++)
            Assert(H5Tinsert(sid, names[i].c_str(), offsets[i], hdftypes[i]), "HDF5Dataset::HDF5Dataset() Failed to insert column to compound dataset - "+names[i]);

        Assert(H5Tpack (sid), "HDF5Dataset::HDF5Dataset() Failed to pack dataset - "+name);
        Assert(H5Tlock (sid), "HDF5Dataset::HDF5Dataset() Failed to lock dataset - "+name);

        // create data set
        hid_t dataset = H5Dcreate(locID, name.c_str(), sid, dataspace, plist);
        if(dataset<0)
        {
                H5Sclose(dataspace);
                H5Pclose(plist);
                H5Tclose(sid);
        }
        Assert(dataset, "HDF5Dataset::HDF5Dataset() Failed to create dataset - "+name);

        m_name = name;
        m_ID = dataset;
        m_ownerID = locID;
        m_opened=true;

        // write data to the dataset
        unsigned char* buf = new unsigned char[NumberOfRows()*size];
        data.MapToVector(size,offsets,hdftypes,buf);
        status = H5Dwrite (dataset,sid,dataspace,dataspace,H5P_DEFAULT,buf);
        delete [] buf;

        H5Sclose(dataspace);
        H5Pclose(plist);
        H5Tclose(sid);
        Assert(status, "HDF5Dataset::HDF5Dataset() Failed to write to dataset - "+m_name);
}

//===============================================
        inline HDF5Dataset::~HDF5Dataset() 
                {
                        Close();
                }

//===============================================
        inline HDF5Dataset& HDF5Dataset::operator=(const HDF5Dataset& ds)
        {
                Close();
                m_ownerID=ds.m_ownerID;
                m_name=ds.m_name;
                Open();
                return *this;
        }
        
//===============================================
        inline void HDF5Dataset::Open()
        {
           if(!m_opened)
           {
                   m_ID=H5Dopen(m_ownerID,m_name.c_str());
                   Assert(m_ID, "HDF5Dataset::Open() Failed to open existing dataset - "+m_name);
                   m_opened=true;
           }
        }

//===============================================
        inline void HDF5Dataset::Close()
        {
                        if(m_opened)
                        {
                                herr_t status = H5Dclose(m_ID);
                                Assert(status, "HDF5Dataset::Close() Failed to close existing dataset - "+m_name);
                        }
                        m_opened=false;
        }

//===============================================
template <typename T>
inline void HDF5Dataset::WriteData(const seg::Matrix<T>& data, const int compressedlevel)
{
        WriteData(0,data.NumberOfRows(),data,compressedlevel);
}

//===============================================
inline void HDF5Dataset::WriteData(const seg::HDF5CompoundType& data, const int compressedlevel)
{
        WriteData(0,data.NumberOfRows(),data,compressedlevel);
}
//===============================================
template <typename T>
inline void HDF5Dataset::WriteData(size_t startRowIdx, size_t nRows, const seg::Matrix<T>& data, const int compressedlevel)
{
        CheckOpen();
        Matrix<T> tmp(1);
        T type=tmp[0];  // initialize to avoid warnings
        hid_t datatype=HDF5DataType::MapNativeType(type);
        hid_t memspace = H5S_ALL;
        hid_t dataspace = H5S_ALL; 
        herr_t status;
        if((startRowIdx>=0) && (nRows>0)) // (nRows<=NumberOfRows()))  // write a region of data
        {
                HDF5DataType::DataType outdatatype=HDF5DataType::MapHDF5Type(type);
                HDF5DataType::DataType dsType=HDF5DataType::GetDataSetDataType(m_ID);

                herr_t status=0;
                if(dsType!=outdatatype)
                        Assert(-1, "HDF5Dataset::WriteData() Failed to write dataset - "+m_name + ". Data type not matched!");
                if(startRowIdx>NumberOfRows())
                        Assert(-1, "HDF5Dataset::WriteData() Starting row index exceeds the number of rows in the dataset.");
                if(nRows>data.NumberOfRows())
                        Assert(-1, "HDF5Dataset::WriteData() data space exceeds the number of rows of data.");
                if((nRows+startRowIdx)>NumberOfRows())
                {
                        hsize_t     dims[2];           /* dataset dimensions */     
                        dims[0]=((nRows+startRowIdx));
                        dims[1]=NumberOfColumns();
                        status = H5Dextend(m_ID,dims);
                        Assert(status, "HDF5Dataset::WriteData() Failed to extend current dataset - "+m_name);
                }

                SelectHyperslab(startRowIdx, nRows, dataspace, memspace);
        }
        else
        {
                 if(H5Gget_objinfo (m_ownerID, m_name.c_str(), 0, NULL)==0)
                 {
                                //herr_t status = H5Gunlink(m_ownerID, m_name.c_str());
                                Assert(-1, "HDF5Dataset::WriteData() dataset - "+m_name+" already exists");
                 }

                /*
                 * Create a new dataset within the file using defined dataspace and
                 * datatype and default dataset creation properties.
                 */
                hsize_t     dimsf[2];              /* dataset dimensions */
                dimsf[0] = data.NumberOfRows();
                dimsf[1] = data.NumberOfColumns();
                Assert(((dimsf[0]>0)&&(dimsf[1]>0))?1:-1, "HDF5Dataset::WriteData() Cannot create dataspace with empty row or col");
                dataspace = H5Screate_simple(2, dimsf, NULL); 
                if(dataspace<0)
                {
                        H5Sclose(memspace);
                        H5Tclose(datatype);
                }
                Assert(dataspace, "HDF5Dataset::WriteData() Failed to create dataspace");

                // always enable chunking for extensibility 
                hid_t plist = H5Pcreate(H5P_DATASET_CREATE);  //property list
                hsize_t     cdims[2];
                cdims[0] = data.NumberOfColumns()<data.NumberOfRows()?data.NumberOfColumns():data.NumberOfRows(); // the size of the chunks used to store a chunked layout dataset
                cdims[1] = data.NumberOfColumns()<data.NumberOfRows()?data.NumberOfColumns():data.NumberOfRows();
                status = H5Pset_chunk(plist, 2, cdims);

                if(compressedlevel>0)
                {
                        //  compressed dataset
                        status = H5Pset_deflate( plist, compressedlevel);  // 9 is max compression level
                }

                hid_t dataset = H5Dcreate(m_ownerID, m_name.c_str(), datatype, dataspace, plist); //NULL); //
                if(dataset<0)
                {
                        H5Sclose(memspace);
                        H5Pclose(plist);
                        H5Tclose(datatype);
                }
                Assert(dataset, "HDF5Dataset::WriteData() Failed to create dataset - "+m_name);

                m_ID = dataset;  
                m_opened=true;
                H5Pclose(plist);
        }
 
        if (typeid(type)==typeid(std::string))
        {
                seg::Matrix<char*> strs(data.Size());
                for (size_t index=0;index<data.Size();index++)
                        strs[index]=const_cast< char * > ((reinterpret_cast< const seg::Matrix<std::string>& >(data))[index].c_str());

                status = H5Dwrite(m_ID, datatype, memspace, dataspace, H5P_DEFAULT, strs.Data());
        }
        else
        {
                status = H5Dwrite(m_ID, datatype, memspace, dataspace, H5P_DEFAULT, data.Data());
        }
        H5Sclose(dataspace);
    H5Sclose(memspace);
        H5Tclose(datatype);
        Assert(status, "HDF5Dataset::WriteData() Failed to write to dataset - "+m_name);
}

//===============================================
inline void HDF5Dataset::WriteData(size_t startRowIdx, size_t nRows, const seg::HDF5CompoundType& data, const int compressedlevel)
{
        CheckOpen();
        hsize_t     dimsf[1] = {data.NumberOfRows()};              /* dataset dimensions */
        Assert(((data.NumberOfRows()>0)&&(data.NumberOfColumns()>0))?1:-1, "HDF5Dataset::HDF5Dataset() Cannot create dataspace with empty row or col");
        hid_t dataspace = H5Screate_simple(1, dimsf, NULL); 
        Assert(dataspace, "HDF5Dataset::HDF5Dataset() Failed to create dataspace");
        hid_t memspace =H5S_ALL; 
        herr_t status=0;
        if((startRowIdx>=0) && (nRows>0)) // (nRows<=NumberOfRows()))  // write a region of data
        {
                if(startRowIdx>NumberOfRows())
                        Assert(-1, "HDF5Dataset::WriteData() Starting row index exceeds the number of rows in the dataset.");
                if(nRows>data.NumberOfRows())
                        Assert(-1, "HDF5Dataset::WriteData() data space exceeds the number of rows of data.");
                if((nRows+startRowIdx)>NumberOfRows())
                {
                        hsize_t     dims[2];           /* dataset dimensions */     
                        dims[0]=((nRows+startRowIdx));
                        dims[1]=NumberOfColumns();
                        status = H5Dextend(m_ID,dims);
                        Assert(status, "HDF5Dataset::WriteData() Failed to extend current dataset - "+m_name);
                }

                SelectHyperslab(startRowIdx, nRows, dataspace, memspace);
        }

        // always enable chunking for extensibility 
        hid_t plist  = H5Pcreate(H5P_DATASET_CREATE);  //property list
        hsize_t     cdims[1]={ data.NumberOfColumns()<data.NumberOfRows()?data.NumberOfColumns():data.NumberOfRows()};
        status = H5Pset_chunk(plist, 1, cdims);
 
        /* compression is not available for data frame */
        if(compressedlevel>0)
                status = H5Pset_deflate( plist, compressedlevel);  // 9 is max compression level

        // since we are treating the table as one single vector, we need to find out the offset of each column
        // in order to populate data at the right place.
        std::vector<hid_t> hdftypes;
        data.GetHDF5Types(hdftypes);
        std::vector<size_t> offsets;
        size_t size=0;
        for(size_t i=0;i<hdftypes.size(); i++)
        {
                offsets.push_back(size);
                size +=H5Tget_size(hdftypes[i]); 
        }

        // insert the columns in the table
    hid_t sid = H5Tcreate (H5T_COMPOUND, size);  // memory data type
        std::vector<std::string> names;
        data.GetColumnNames(names);
        for(size_t i=0;i<hdftypes.size(); i++)
            Assert(H5Tinsert(sid, names[i].c_str(), offsets[i], hdftypes[i]), "HDF5Dataset::HDF5Dataset() Failed to insert column to compound dataset - "+m_name);

        Assert(H5Tpack (sid), "HDF5Dataset::HDF5Dataset() Failed to pack dataset - "+m_name);
        Assert(H5Tlock (sid), "HDF5Dataset::HDF5Dataset() Failed to lock dataset - "+m_name);

        // write data to the dataset
        unsigned char* buf = new unsigned char[NumberOfRows()*size];
        data.MapToVector(size,offsets,hdftypes,buf);
        status = H5Dwrite (m_ID,sid,memspace,dataspace,H5P_DEFAULT,buf);
        delete [] buf;

        if(memspace>0)
                H5Sclose(memspace);
        H5Sclose(dataspace);
        H5Pclose(plist);
        H5Tclose(sid);
        Assert(status, "HDF5Dataset::HDF5Dataset() Failed to write to dataset - "+m_name);
}

//===============================================
inline void HDF5Dataset::ReadData(size_t startRowIdx, size_t nRows, seg::HDF5CompoundType& data)
{
        CheckOpen();
        herr_t status=0;
        hid_t tid = H5Dget_type (m_ID);
        if(H5Tget_class (tid)!=H5T_COMPOUND)
                Assert(-1, "HDF5Dataset::ReadData() dataset is not a compound data type.");

        hid_t dataspace = H5Dget_space (m_ID);
        Assert(dataspace, "HDF5Dataset::ReadData() Failed to open dataspace of dataset "+m_name );

        hid_t memspace = H5S_ALL;
        if(startRowIdx>=NumberOfRows())
                Assert(-1, "HDF5Dataset::ReadData() Starting row index exceeds the number of rows in the dataset.");
        if((nRows+startRowIdx)>NumberOfRows())
                Assert(-1, "HDF5Dataset::ReadData() Unable to read more rows than the dataset contains.");

        if(nRows<NumberOfRows())  // read a region of data
        {
                SelectHyperslab(startRowIdx, nRows, dataspace, memspace);
        }
        else
        {
                nRows=NumberOfRows();
        }

        //hsize_t dims[1];
 //   hsize_t maxdims[1];
        //H5Sget_simple_extent_dims (dataspace, dims, maxdims);
        unsigned colcount = H5Tget_nmembers (tid), ci;
    size_t size = H5Tget_size (tid);
    //size_t ri, rowcount = (size_t)dims[0];
    char *buf = new char[nRows* size * 2];
    status = H5Dread (m_ID, tid, memspace, dataspace, H5P_DEFAULT, buf);
        Assert(status, "HDF5Dataset::ReadData() Failed to read dataset - "+m_name);
        size_t ri=0;

        // populate the output data
        for (ci = 0; ci < colcount; ci++)
        {
        hid_t ctid = H5Tget_member_type (tid, ci);
                H5T_class_t cls = H5Tget_class (ctid);
        size_t csize = H5Tget_size (ctid);
        size_t coffset = H5Tget_member_offset (tid, ci);
        unsigned char* itembuf=new unsigned char[size]; /* for overrun */
                std::string colname = H5Tget_member_name (tid, ci);

        switch (cls)
        {
           case H5T_INTEGER:
           {
                           std::vector<int> intColumn;
                                intColumn.resize(nRows);
                            size_t dsize = H5Tget_size (H5T_NATIVE_INT); 
                            for (ri = 0; ri < nRows; ri++) 
                            {  
                                        memcpy (itembuf, buf + ri * size + coffset, csize); 
                                        Assert(H5Tconvert (ctid, H5T_NATIVE_INT, 1, itembuf, NULL, H5P_DEFAULT),"HDF5Dataset::ReadData() type conversion failed"); 
                                        memcpy (&intColumn[ri], itembuf, dsize); 
                }
                                data.AddColumn(colname,intColumn);
             }
                break;
           case H5T_FLOAT:
           {
                           std::vector<double> doubleColumn;
                                doubleColumn.resize(nRows);
                            size_t dsize = H5Tget_size (H5T_NATIVE_DOUBLE); 
                            for (ri = 0; ri < nRows; ri++) 
                            {  
                                        memcpy (itembuf, buf + ri * size + coffset, csize); 
                                        Assert(H5Tconvert (ctid, H5T_NATIVE_DOUBLE, 1, itembuf, NULL, H5P_DEFAULT),"HDF5Dataset::ReadData() type conversion failed"); 
                                        memcpy (&doubleColumn[ri], itembuf, dsize); 
                }
                                data.AddColumn(colname,doubleColumn);
             }
                break;
            case H5T_STRING:
            {
                           std::vector<std::string> stringColumn;
                                stringColumn.resize(nRows);
                                hid_t memtid  = H5Tcopy (H5T_C_S1); //(H5T_STD_REF_OBJ);
                                Assert(memtid, "Unable to copy H5t_C_S1");
                            for (ri = 0; ri < nRows; ri++) 
                            {  
                                        memcpy (itembuf, buf + ri * size + coffset, csize); 
                                        stringColumn[ri]=(char*) itembuf;
                }
                                data.AddColumn(colname,stringColumn);
                                Assert(H5Tclose (memtid), "HDF5Dataset::ReadData() - failed to close referece type");
                        }
                break;
            default:
                        {
                                throw HDF5Exception("HDF5Dataset::ReadData() - unsupported compound data type "); 
                    }
                }
                Assert(H5Tclose (ctid), "HDF5Dataset::ReadData() - failed to close member type");
                delete [] itembuf;
    }
        delete [] buf;
        if(memspace>0)
                Assert(H5Sclose(memspace), "HDF5Dataset::ReadData() - failed to close memspace");
        Assert(H5Sclose(dataspace), "HDF5Dataset::ReadData() - failed to close dataspace");
}
//===============================================
inline void HDF5Dataset::ReadData(seg::HDF5CompoundType& data)
{
        ReadData(0,NumberOfRows(),data);
}

//===============================================
template <typename T>
inline void HDF5Dataset::ReadData(seg::Matrix<T>& data)
{
        ReadData(0,NumberOfRows(),data);
}

//===============================================
template <typename T>
inline void HDF5Dataset::ReadData(size_t startRowIdx, size_t nRows, seg::Matrix<T>& data)
{
        CheckOpen();
        Matrix<T> tmp(1);
        T type=tmp[0];  // initialize to avoid warnings

        hid_t memspace = H5S_ALL;
        hid_t dataspace = H5S_ALL;

        HDF5DataType::DataType outdatatype=HDF5DataType::MapHDF5Type(type);
        HDF5DataType::DataType datatype=HDF5DataType::GetDataSetDataType(m_ID);

        herr_t status=0;
        if(datatype!=outdatatype)
                Assert(-1, "HDF5Dataset::ReadData() Failed to read dataset - "+m_name + ". Data type not matched!");
        if(startRowIdx>=NumberOfRows())
                Assert(-1, "HDF5Dataset::ReadData() Starting row index exceeds the number of rows in the dataset.");
        if((nRows+startRowIdx)>NumberOfRows())
                Assert(-1, "HDF5Dataset::ReadData() Unable to read more rows than the dataset contains.");

        if(nRows<NumberOfRows())  // read a region of data
        {
                SelectHyperslab(startRowIdx, nRows, dataspace, memspace);
        }
        else
        {
                nRows=NumberOfRows();
        }
        data.Resize(nRows,NumberOfColumns());

        if(typeid(type) == typeid(bool))
        {
                hid_t nativedatatype= HDF5DataType::MapNativeType(type);
                // HDF5 API reads bool data as 4 byte char
                seg::Matrix<char> charData(nRows,NumberOfColumns());
                status = H5Dread(m_ID, nativedatatype, memspace, dataspace, H5P_DEFAULT, charData.Data());
                size_t i;
                for(i=0; i<charData.Size(); i++)
                        reinterpret_cast< seg::Matrix<bool>& >(data)[i]=(charData[i]==1);
                H5Tclose(nativedatatype);
        }
        else if ((typeid(type)==typeid(std::string))  || 
                    (typeid(type)==typeid(char*)))
        {
                size_t total = data.Size();
                size_t index=0;
                htri_t isVarStr=H5Tis_variable_str(H5Dget_type(m_ID));
                if(isVarStr==1)
                {
                        hid_t nativedatatype= HDF5DataType::MapNativeType(type);
                        if (typeid(type)==typeid(std::string)) 
                        {
                                seg::Matrix<char *> tmpData(nRows,NumberOfColumns());
                                status = H5Dread(m_ID, nativedatatype, memspace, dataspace, H5P_DEFAULT, tmpData.Data());
                                for (index=0;index<tmpData.Size();index++)
                                        (reinterpret_cast< seg::Matrix<std::string>& >(data))[index]=tmpData[index];
                        }
                        else
                                status = H5Dread(m_ID, nativedatatype, memspace, dataspace, H5P_DEFAULT, data.Data());

                        H5Tclose(nativedatatype);
                }
                else
                {
                        size_t len = H5Tget_size(H5Dget_type(m_ID));
                        hid_t nativedatatype = HDF5DataType::MapNativeType_FixedSizeString(len);
                        char** d = (char**) malloc(total*sizeof(char*)); 
                        d[0]=(char*) malloc(len*total*sizeof(char));
                        for (size_t i=1; i < total; i++) 
                                d[i] = d[0]+i*len;

                        status = H5Dread(m_ID, nativedatatype, memspace, dataspace, H5P_DEFAULT, &d[0][0]); 
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
                status = H5Dread(m_ID, nativedatatype, memspace, dataspace, H5P_DEFAULT, data.Data());
                H5Tclose(nativedatatype);
        }
    H5Sclose (dataspace);
    H5Sclose (memspace);
        Assert(status, "HDF5Dataset::ReadData() Failed to read dataset - "+m_name);
}

//===============================================
template <typename T>
 inline void HDF5Dataset::CreateAttribute(const std::string& attributeName, const seg::Matrix<T>& attributeData, const int compressedlevel)
 {
        CheckOpen();
        HDF5Attribute att(This(),attributeName,attributeData, compressedlevel);
 };
//===============================================
template <typename T>
 inline void HDF5Dataset::ReadAttribute(const std::string& attributeName, seg::Matrix<T>& attributeData)
 {
        CheckOpen();
        HDF5Attribute att = OpenAttribute(attributeName);
        att.ReadData(attributeData);
 };
//===============================================
 inline void HDF5Dataset::DeleteAttribute(const std::string& attributeName)
 {
        CheckOpen();
        if(Exist(attributeName))
        {
                herr_t status = H5Adelete(m_ID,attributeName.c_str());
                Assert(status, "HDF5Dataset::DeleteAttribute() Failed to remove an existing attribute - "+attributeName);
        }
 }; 
//===============================================
 inline         HDF5Attribute HDF5Dataset::OpenAttribute(const std::string& attributeName)
         {
                 CheckOpen();
                 if (!Exist(attributeName))
                         throw HDF5Exception("Failed to open non-existing attribute - "+attributeName); 
                 else
                 {
                   //hid_t dsID=H5Dopen(m_ID,datasetName.c_str());
                   //Assert(dsID, "Failed to open existing dataset - "+datasetName);
                   return HDF5Attribute(m_ID,attributeName);
                 }
        }

//===============================================
inline bool HDF5Dataset::Exist( const std::string& attributeName) const
{
   GetAttributeNames();
   return (std::find(m_attributenames.begin(), m_attributenames.end(), attributeName)!=m_attributenames.end());
}

//===============================================
 inline size_t HDF5Dataset::NumberOfRows() const
 {
        CheckOpen();
        hid_t dataspace = H5Dget_space(m_ID);    /* dataspace identifier */
        // HDF5 library does not return correct value when there is only 1 row or 1 col
        // since there is minimum 1 row or 1 col anyways, we will initialize it here.
        hsize_t  dims_out[2]={1,1}, maxdim[2]={1,1};
        int status_n  = H5Sget_simple_extent_dims(dataspace, dims_out,maxdim);
        Assert(status_n, "HDF5Dataset::NumberOfRows() Failed to get dataspace dimensions - "+m_name);

        return (size_t)dims_out[0];
 }

//===============================================
 inline size_t HDF5Dataset::NumberOfColumns() const
 {
        CheckOpen();
        hid_t dataspace = H5Dget_space(m_ID);    /* dataspace identifier */
        // HDF5 library does not return correct value when there is only 1 row or 1 col
        // since there is minimum 1 row or 1 col anyways, we will initialize it here.
        hsize_t     dims_out[2]={1,1}, maxdim[2]={1,1};  
        int status_n  = H5Sget_simple_extent_dims(dataspace, dims_out,maxdim);
        Assert(status_n, "HDF5Dataset::NumberOfColumns() Failed to get dataspace dimensions - "+m_name);
        return (size_t)dims_out[1];
 }

//===============================================
 inline size_t HDF5Dataset::NumberOfAttributes() const
 {
        GetAttributeNames();
        return m_attributenames.size();
 }

//===============================================
inline HDF5DataType::DataType HDF5Dataset::GetDataType() const
 {
         return HDF5DataType::GetDataSetDataType(m_ID);
 }

//===============================================
inline const std::vector <std::string>& HDF5Dataset::GetAttributeNames() const
 {
        CheckOpen();
        unsigned int i,j=0;
        hsize_t totalObjs=0;
        //H5Gget_num_objs(m_ID,&totalObjs);
        totalObjs = H5Aget_num_attrs(m_ID);
        std::vector< std::string > atts;
    for (i=0; i<totalObjs; i++)
        {
                H5Aiterate(m_ID, &j, GetAttributeNamesFn, &atts);
        }
        const_cast< std::vector<std::string>& > (m_attributenames) = atts;
        return m_attributenames;
 }

//===============================================
inline void HDF5Dataset::SelectHyperslab(size_t startRowIdx, size_t nRows, hid_t& dataspace, hid_t& memspace)
{
                        hsize_t     count[2];              /* size of the hyperslab in the file */
                        hsize_t     offset[2];             /* hyperslab offset in the file */
                        hsize_t     count_out[2];          /* size of the hyperslab in memory */
                        hsize_t     offset_out[2];         /* hyperslab offset in memory */
                        hsize_t     dimsm[2];           /* dataset dimensions */     
                        herr_t      status;
                        dataspace = H5Dget_space (m_ID);    /* dataspace handle */
                        /* 
                         * Define hyperslab in the dataset. 
                         */
                        offset[0] = startRowIdx;
                        offset[1] = 0;
                        count[0]  = nRows;
                        count[1]  = NumberOfColumns();
                        status = H5Sselect_hyperslab (dataspace, H5S_SELECT_SET, offset, NULL, 
                                                                                  count, NULL);
                        Assert(status,"Failed to select hyperslab for data space");
                        /*
                         * Define the memory dataspace.
                         */
                        dimsm[0] = nRows;
                        dimsm[1] = NumberOfColumns();
                        memspace = H5Screate_simple (2, dimsm, NULL);   
                        offset_out[0] = 0;
                        offset_out[1] = 0;
                        count_out[0]  = nRows;
                        count_out[1]  = NumberOfColumns();
                        status = H5Sselect_hyperslab (memspace, H5S_SELECT_SET, offset_out, NULL, 
                                                                          count_out, NULL);
                        Assert(status,"Failed to select hyperslab for memory space");
};

//===============================================
 inline std::string HDF5Dataset::ToString(const std::string& tabs)
 {
         std::ostringstream str;
         str << tabs <<"Datasetname: " << m_name.c_str() << "\n";
         str << tabs<< "Rows: " << NumberOfRows() << "\n";
         str << tabs<< "Cols: " << NumberOfColumns() << "\n";
         str << tabs<< "Data type: " << HDF5DataType::ToString(GetDataType()) << "\n";
         str << tabs<< "Number Of Attributes: " << NumberOfAttributes() << std::endl;
         std::vector< std::string> atts = GetAttributeNames();
         for(size_t i=0 ;i< atts.size(); i++)
         {
                        HDF5Attribute att = OpenAttribute(atts[i]);
                        str << att.ToString(tabs+"\t") << std::endl;
         }
         return str.str();
 }
#include "HDF5Dataset.cpp"
}

#endif
