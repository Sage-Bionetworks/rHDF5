#if defined(WIN32) || defined(WIN64)
//#pragma warning(disable:4700)
#endif
#ifndef __HDF5GROUP_H_
#define __HDF5GROUP_H_  
#include <string>
#include <map>
#include "hdf5.h"
#include "HDF5Object.h"
#include "HDF5Exception.h"
#include "HDF5Dataset.h"
#include "HDF5CompoundType.h"
#include "HDF5Attribute.h"
#include "StringUtils.h"


//*******************************************************************************
//*     This class provides functions to access a HDF5 group.  This class should not be
//* instantiated explicitly.  It should be instantiated by using HDF5DA class.
//*******************************************************************************

namespace seg
{
        class HDF5Group : public HDF5Object
        {
         public:
                 
                 // users should not instantiate this class explicitly.
                HDF5Group();
                HDF5Group(int ownerID,  const std::string& name,  const std::string& hierarchicalName="");
            virtual ~HDF5Group(); 
                HDF5Group(const HDF5Object& obj, const std::string& groupName);
                HDF5Group& operator=(const HDF5Group& gp);
                
                // create a new sub group within this group
                HDF5Group CreateGroup(const std::string& groupName);
                
                // open an existing group within this group
                HDF5Group OpenGroup(const std::string& groupName);
                
                // open an existing group within this group by its full path
                HDF5Group OpenGroupByFullPath(const std::string& fullyQualifiedName);
                
                // delete an existing group within this group
                void DeleteGroup(const std::string& groupName);

                // read data from an exising dataset
                template <typename T>
                void ReadData(const std::string& datasetName, seg::Matrix<T>& data);
                void ReadData(const std::string& datasetName, seg::HDF5CompoundType& data);
                
                // read some rows of data from exising dataset
                template <typename T>
                void ReadData(const std::string& datasetName, size_t startRowIdx, size_t nRows, seg::Matrix<T>& data);
                void ReadData(const std::string& datasetName, size_t startRowIdx, size_t nRows, seg::HDF5CompoundType& data);
 
                // read data from an existing dataset specified by it full path.
                template <typename T>
                void ReadDataByFullPath(const std::string& fullyQualifiedName, seg::Matrix<T>& data);
                void ReadDataByFullPath(const std::string& fullyQualifiedName, seg::HDF5CompoundType& data);
                
                // read rows of data from an existing dataset specified by it full path.
                template <typename T>
                void ReadDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, seg::Matrix<T>& data);
                void ReadDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, seg::HDF5CompoundType& data);
                
                // write to a new dataset
                template <typename T>
                void WriteData(const std::string& datasetName, const seg::Matrix<T>& data, const int compressedlevel=0);
                void WriteData(const std::string& datasetName, const seg::HDF5CompoundType& data, const int compressedlevel=0);
                
                // overwrite some rows of data in an existing dataset
                template <typename T>
                void WriteData(const std::string& datasetName, size_t startRowIdx, size_t nRows, const seg::Matrix<T>& data, const int compressedlevel=0);
                void WriteData(const std::string& datasetName, size_t startRowIdx, size_t nRows, const seg::HDF5CompoundType& data, const int compressedlevel=0);
                
                // write to a new dataset specified by its full path.
                template <typename T>
                void WriteDataByFullPath(const std::string& fullyQualifiedName, const seg::Matrix<T>& data, const int compressedlevel=0);
                void WriteDataByFullPath(const std::string& fullyQualifiedName, const seg::HDF5CompoundType& data, const int compressedlevel=0);

                // overwrite some rows of a existing dataset specified by its full path.
                template <typename T>
                void WriteDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, const seg::Matrix<T>& data, const int compressedlevel=0);
                void WriteDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, const seg::HDF5CompoundType& data, const int compressedlevel=0);

                // delete an existing dataset
                void DeleteData(const std::string& datasetName);
                
                // delete an existing dataset
                void DeleteDataByFullPath(const std::string& fullyQualifiedName);

                // delete an existing dataset by its full path
                HDF5Dataset OpenDataset(const std::string& datasetName);

                // open an existing dataset by full path. 
                HDF5Dataset OpenDatasetByFullPath(const std::string& fullyQualifiedName);

                // create a new attribute 
                template <typename T>
                void CreateAttribute(const std::string& attributeName, const seg::Matrix<T>& attributeData, const int compressedlevel=0);
                
                // read data from an existing attribute
                template <typename T>
                void ReadAttribute(const std::string& attributeName, seg::Matrix<T>& attributeData);
                
                // delete an existing attribute
                void DeleteAttribute(const std::string& attributeName);
                
                // open an attribute
                HDF5Attribute OpenAttribute(const std::string& attributeName);
                
                // check if an attribute already exists
                bool ContainAttribute( const std::string& attributeName) const;

                // Return true if a group/dataset/attribute exists given its fully qualified name; false otherwise. 
                bool FullPathExist(const std::string& fullyQualifiedName) const;
                bool GroupFullPathExist(const std::string& fullyQualifiedName) const;
                bool DatasetFullPathExist(const std::string& fullyQualifiedName) const;
                bool AttributeFullPathExist(const std::string& fullyQualifiedName) const;
                
                size_t NumberOfGroups() const;
                size_t NumberOfDatasets() const;
                size_t NumberOfAttributes() const;
                std::vector <std::string> GetGroupNames() const;
                std::vector <std::string> GetDatasetNames() const;
                std::vector <std::string> GetAttributeNames() const;
                
                // return all group names with their full paths.
                std::vector <std::string> GetGroupNamesFullPath() const;

                // return all group names with their full paths.
                std::vector <std::string> GetGroupNamesFullPathDetails(const std::string& rootPath="/") const;

                // return all data names with their full paths
                std::vector <std::string> GetDatasetNamesFullPath() const;

                // return all data names with their full paths, as well as their data sizes and types.
                std::vector <std::string> GetDatasetNamesFullPathDetails(const std::string& rootPath="/") const;

                // return all attribute names with their full paths
                std::vector <std::string> GetAttributeNamesFullPath() const;

                // return all attribute names with their full paths, as well as their data sizes and types.
                std::vector <std::string> GetAttributeNamesFullPathDetails(const std::string& rootPath="/") const;

                // return a summary of this group.
                virtual std::string ToString(const std::string& tabs="");

        private: 
        
                const HDF5Group& This()
                { HDF5Group* obj = const_cast<HDF5Group*> (this);
                  return *obj;
                }

                const std::string& GetHierarchicalName(){return m_hierarchicalName;}
                 virtual void Open();
                 virtual void Close();

                std::vector <std::string> m_groupnames;
                std::vector <std::string> m_datasetnames;
                std::string m_hierarchicalName;
            std::vector <std::string> m_attributenames;

        };

//===============================================
//   inline implementations
//===============================================
        inline  HDF5Group::HDF5Group()
        {
                m_opened=false;
        }

//===============================================
        inline  HDF5Group::HDF5Group(int ownerID, const std::string& name,  const std::string& hierarchicalName)
        {
                m_opened=false;
                        m_ownerID = ownerID;
                        m_hierarchicalName = hierarchicalName;
                        m_name = name;
                        Open();
                   GetGroupNames();
                   GetDatasetNames();
                   GetAttributeNames();
        };

//===============================================
        inline  HDF5Group& HDF5Group::operator=(const HDF5Group& gp)
        {
                Close();
                m_ownerID=gp.m_ownerID;
                m_hierarchicalName = gp.m_hierarchicalName;
                m_name=gp.m_name;
                Open();
                   GetGroupNames();
                   GetDatasetNames();
                   GetAttributeNames();
                   return *this;
        };

//===============================================
    inline      HDF5Group::~HDF5Group() 
                {
                        Close();
                };

//===============================================
        inline  HDF5Group::HDF5Group(const HDF5Object& obj, const std::string& groupName)
        {
                   hid_t loc_id = obj.ID();
                   Assert(loc_id, "HDF5Group::HDF5Group() Unknown HDF5 object");

                   if(obj.Exist(groupName))
                   {
                           //herr_t status = H5Gunlink(loc_id, groupName.c_str());
                           std::string objname = (const_cast< HDF5Object& > (obj)).GetName();
                           Assert(-1, "HDF5Group::HDF5Group() " + objname + "/" + groupName + " already exists");
                   }

                   hid_t       group_id;  /* identifiers */
                   /* Create a group */
                   group_id = H5Gcreate(loc_id, groupName.c_str(), 0);
                   Assert(group_id, "HDF5Group::HDF5Group() Failed to create group - "+groupName);

                   m_ID=group_id;
                   m_ownerID=loc_id;
                   m_name=groupName;
                   m_opened=true;
                   GetGroupNames();
                   GetDatasetNames();
                   GetAttributeNames();
        };
        
//===============================================
        inline void HDF5Group::Open()
        {
           if(!m_opened)
           {
                   m_ID=H5Gopen(m_ownerID,m_name.c_str());
                   Assert(m_ID, "HDF5Group::Open() Failed to open existing group - "+m_name);
                   m_opened=true;
           }
        }

//===============================================
        inline void HDF5Group::Close()
        {
                        if(m_opened)
                        {
                                herr_t status = H5Gclose(m_ID);
                                Assert(status, "HDF5Group::Close() Failed to close existing group - "+m_hierarchicalName+"/"+m_name);
                        }
                        m_opened=false;
        }

//===============================================
        inline HDF5Group HDF5Group::CreateGroup(const std::string& groupName)
                {
                        //HDF5Group gp= HDF5Group(This(),groupName);
                        //std::pair <std::string, HDF5Group> gp_Pair(groupName,gp);
                        //m_groups.insert(gp_Pair);
                        //return gp;
                        return HDF5Group(This(),groupName);
                };

//===============================================
inline HDF5Group HDF5Group::OpenGroup(const std::string& groupName)
 {
         CheckOpen();
         if (!Exist(groupName))
                 throw HDF5Exception("HDF5Group::OpenGroup() Failed to open non-existing group - "+m_hierarchicalName+"/"+m_name); 
         else
     {
                           //hid_t gpID=H5Gopen(m_ID,groupName.c_str());
                           //Assert(gpID, "Failed to open existing group - "+groupName);
                           //return m_groups.find( groupName )->second;
                 return HDF5Group(m_ID, groupName, m_hierarchicalName+"/"+m_name);
     }
}

//===============================================
inline HDF5Group HDF5Group::OpenGroupByFullPath(const std::string& fullyQualifiedName)
 {
        CheckOpen();
        // check if the name is a valid Group name
        if (!GroupFullPathExist(fullyQualifiedName))
                        throw HDF5Exception("Path (" + fullyQualifiedName+") does not exist."); 

        std::vector<std::string> names;
        std::string localName = fullyQualifiedName;
        StringUtils::Parse(localName,'/',names);
        if((names[0]=="") && (names.size()>1)) // the path starts with "/", strip it
        {
                names.erase(names.begin());
                localName=localName.substr(1);
        }
        if(names.size()>1)
        {
                size_t index = localName.find ("/");
                HDF5Group gp=  OpenGroup(names[0]);
                return gp.OpenGroupByFullPath(localName.substr(index+1));
        }
        else
        {
                return OpenGroup(localName);
        }
}

//===============================================
inline void HDF5Group::DeleteGroup(const std::string& groupName)
{
        CheckOpen();
        if(Exist(groupName))
        {
            herr_t status = H5Gunlink(m_ID, groupName.c_str() );
                Assert(status, "HDF5Group::DeleteGroup() Failed to delete group - "+groupName);
        }
}

//===============================================
inline void HDF5Group::ReadData(const std::string& datasetName, seg::HDF5CompoundType& data)
{
        CheckOpen();
        HDF5Dataset ds = OpenDataset(datasetName);
        ds.ReadData(data);
}

//===============================================
inline void HDF5Group::ReadData(const std::string& datasetName, size_t startRowIdx, size_t nRows, seg::HDF5CompoundType& data )
{
        CheckOpen();
        HDF5Dataset ds = OpenDataset(datasetName);
        ds.ReadData(startRowIdx,nRows,data);
}

//===============================================
template <typename T>
inline void HDF5Group::ReadData(const std::string& datasetName, seg::Matrix<T>& data)
{
        CheckOpen();
        HDF5Dataset ds = OpenDataset(datasetName);
        ds.ReadData(data);
}
//===============================================
template <typename T>
inline void HDF5Group::ReadData(const std::string& datasetName, size_t startRowIdx, size_t nRows, seg::Matrix<T>& data )
{
        CheckOpen();
        HDF5Dataset ds = OpenDataset(datasetName);
        ds.ReadData(startRowIdx,nRows,data);
}
//===============================================
inline void HDF5Group::ReadDataByFullPath(const std::string& fullyQualifiedName, seg::HDF5CompoundType& data)
{
        CheckOpen();
        if(!DatasetFullPathExist(fullyQualifiedName))
                throw HDF5Exception("Path (" + fullyQualifiedName+") does not exist."); 

        std::vector<std::string> names;
        std::string localName = fullyQualifiedName;
        StringUtils::Parse(localName,'/',names);
        if((names[0]=="") && (names.size()>1)) // the path starts with "/", strip it
        {
                names.erase(names.begin());
                localName=localName.substr(1);
        }
        if(names.size()>1)
        {
                size_t index = localName.find ( "/");
                HDF5Group gp=  OpenGroup(names[0]);
                gp.ReadDataByFullPath(localName.substr(index+1), data);
        }
        else
        {
                ReadData(localName,data);
        }
}
//===============================================
inline void HDF5Group::ReadDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, seg::HDF5CompoundType& data)
{
        CheckOpen();
        if(!DatasetFullPathExist(fullyQualifiedName))
                throw HDF5Exception("Path (" + fullyQualifiedName+") does not exist."); 

        std::vector<std::string> names;
        std::string localName = fullyQualifiedName;
        StringUtils::Parse(localName,'/',names);
        if((names[0]=="") && (names.size()>1)) // the path starts with "/", strip it
        {
                names.erase(names.begin());
                localName=localName.substr(1);
        }       
        if(names.size()>1)
        {
                size_t index = localName.find ( "/");
                HDF5Group gp=  OpenGroup(names[0]);
                gp.ReadDataByFullPath(localName.substr(index+1), startRowIdx, nRows, data);
        }
        else
        {
                ReadData(localName,startRowIdx, nRows,data);
        }
}

//===============================================
template <typename T>
inline void HDF5Group::ReadDataByFullPath(const std::string& fullyQualifiedName, seg::Matrix<T>& data)
{
        CheckOpen();
        if(!DatasetFullPathExist(fullyQualifiedName))
                throw HDF5Exception("Path (" + fullyQualifiedName+") does not exist."); 

        std::vector<std::string> names;
        std::string localName = fullyQualifiedName;
        StringUtils::Parse(localName,'/',names);
        if((names[0]=="") && (names.size()>1)) // the path starts with "/", strip it
        {
                names.erase(names.begin());
                localName=localName.substr(1);
        }
        if(names.size()>1)
        {
                size_t index = localName.find ( "/");
                HDF5Group gp=  OpenGroup(names[0]);
                gp.ReadDataByFullPath(localName.substr(index+1), data);
        }
        else
        {
                ReadData(localName,data);
        }
}
//===============================================
template <typename T>
inline void HDF5Group::ReadDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, seg::Matrix<T>& data)
{
        CheckOpen();
        if(!DatasetFullPathExist(fullyQualifiedName))
                throw HDF5Exception("Path (" + fullyQualifiedName+") does not exist."); 

        std::vector<std::string> names;
        std::string localName = fullyQualifiedName;
        StringUtils::Parse(localName,'/',names);
        if((names[0]=="") && (names.size()>1)) // the path starts with "/", strip it
        {
                names.erase(names.begin());
                localName=localName.substr(1);
        }       
        if(names.size()>1)
        {
                size_t index = localName.find ( "/");
                HDF5Group gp=  OpenGroup(names[0]);
                gp.ReadDataByFullPath(localName.substr(index+1), startRowIdx, nRows, data);
        }
        else
        {
                ReadData(localName,startRowIdx, nRows,data);
        }
}

//===============================================
inline void HDF5Group::WriteData(const std::string& datasetName, const seg::HDF5CompoundType& data, const int compressedlevel)
{
                CheckOpen();
                if(Exist(datasetName))
                        Assert(-1, "HDF5Group::WriteData() dataset - "+datasetName+" already exists");

                HDF5Dataset ds (This(),datasetName,data,compressedlevel);
};

//===============================================
        template <typename T>
        inline void HDF5Group::WriteData(const std::string& datasetName, const seg::Matrix<T>& data, const int compressedlevel)
        {
                CheckOpen();
                if(Exist(datasetName))
                {
                        //herr_t status = H5Gunlink(m_ID, datasetName.c_str() );
                        //Assert(status, "HDF5Group::WriteData() Failed to recreate dataset - "+datasetName);
                        Assert(-1, "HDF5Group::WriteData() dataset - "+datasetName+" already exists");
                }
                HDF5Dataset ds (This(),datasetName,data,compressedlevel);
        };
//===============================================
template <typename T>
inline void HDF5Group::WriteData(const std::string& datasetName, size_t startRowIdx, size_t nRows, const seg::Matrix<T>& data, const int compressedlevel)
{
  if(!Exist(datasetName) && (startRowIdx>0))
          Assert(-1,"HDF5Group::WriteData() Dataset - "+datasetName+" does not exist.");

        HDF5Dataset ds (m_ID,datasetName);
        ds.WriteData(startRowIdx,nRows,data,compressedlevel);
}
//===============================================
inline void HDF5Group::WriteData(const std::string& datasetName, size_t startRowIdx, size_t nRows, const seg::HDF5CompoundType& data, const int compressedlevel)
{
  if(!Exist(datasetName) && (startRowIdx>0))
          Assert(-1,"HDF5Group::WriteData() Dataset - "+datasetName+" does not exist.");

        HDF5Dataset ds (m_ID,datasetName);
        ds.WriteData(startRowIdx,nRows,data,compressedlevel);
}

//===============================================
inline void HDF5Group::WriteDataByFullPath(const std::string& fullyQualifiedName, const seg::HDF5CompoundType& data, const int compressedlevel)
{
        CheckOpen();
        std::string localName=fullyQualifiedName;
        if(fullyQualifiedName.find ("/")==0)
                localName=localName.substr(1);

        std::vector<std::string> names;
        StringUtils::Parse(localName,'/',names);
        if(names.size()>1)
        {
                size_t index = localName.find ("/");
                if(!Exist(names[0]))
                {
                        HDF5Group gp=  CreateGroup(names[0]);
                        gp.WriteDataByFullPath(localName.substr(index+1), data, compressedlevel);
                }
                else
                {
                        HDF5Group gp=  OpenGroup(names[0]);
                        gp.WriteDataByFullPath(localName.substr(index+1), data, compressedlevel);
                }
        }
        else
        {
                WriteData(localName,data, compressedlevel);
        }
}

//===============================================
template <typename T>
inline void HDF5Group::WriteDataByFullPath(const std::string& fullyQualifiedName, const seg::Matrix<T>& data, const int compressedlevel)
{
        CheckOpen();
        std::string localName=fullyQualifiedName;
        if(fullyQualifiedName.find ("/")==0)
                localName=localName.substr(1);

        std::vector<std::string> names;
        StringUtils::Parse(localName,'/',names);
        if(names.size()>1)
        {
                size_t index = localName.find ("/");
                if(!Exist(names[0]))
                {
                        HDF5Group gp=  CreateGroup(names[0]);
                        gp.WriteDataByFullPath(localName.substr(index+1), data, compressedlevel);
                }
                else
                {
                        HDF5Group gp=  OpenGroup(names[0]);
                        gp.WriteDataByFullPath(localName.substr(index+1), data, compressedlevel);
                }
        }
        else
        {
                WriteData(localName,data, compressedlevel);
        }
}
//===============================================
template <typename T>
inline void HDF5Group::WriteDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, const seg::Matrix<T>& data, const int compressedlevel)
{
        CheckOpen();
        std::string localName=fullyQualifiedName;
        if(fullyQualifiedName.find ("/")==0)
                localName=localName.substr(1);

        std::vector<std::string> names;
        StringUtils::Parse(localName,'/',names);
        if(names.size()>1)
        {
                size_t index = localName.find ("/");
                if(!Exist(names[0]))
                {
                        HDF5Group gp=  CreateGroup(names[0]);
                        gp.WriteDataByFullPath(localName.substr(index+1), startRowIdx, nRows, data, compressedlevel);
                }
                else
                {
                        HDF5Group gp=  OpenGroup(names[0]);
                        gp.WriteDataByFullPath(localName.substr(index+1), startRowIdx, nRows, data, compressedlevel);
                }
        }
        else
        {
                WriteData(localName, startRowIdx, nRows,data,compressedlevel);
        }
}
//===============================================
inline void HDF5Group::WriteDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, const seg::HDF5CompoundType& data, const int compressedlevel)
{
        CheckOpen();
        std::string localName=fullyQualifiedName;
        if(fullyQualifiedName.find ("/")==0)
                localName=localName.substr(1);

        std::vector<std::string> names;
        StringUtils::Parse(localName,'/',names);
        if(names.size()>1)
        {
                size_t index = localName.find ("/");
                if(!Exist(names[0]))
                {
                        HDF5Group gp=  CreateGroup(names[0]);
                        gp.WriteDataByFullPath(localName.substr(index+1), startRowIdx, nRows, data, compressedlevel);
                }
                else
                {
                        HDF5Group gp=  OpenGroup(names[0]);
                        gp.WriteDataByFullPath(localName.substr(index+1), startRowIdx, nRows, data, compressedlevel);
                }
        }
        else
        {
                WriteData(localName, startRowIdx, nRows, data,compressedlevel);
        }
}

//===============================================
        inline void HDF5Group::DeleteData(const std::string& datasetName)
        {
                CheckOpen();
                if(Exist(datasetName))
                {
                        herr_t status = H5Gunlink(m_ID, datasetName.c_str() );
                        Assert(status, "HDF5Group::DeleteData() Failed to delete dataset - "+datasetName);
                }
};

//===============================================
inline void HDF5Group::DeleteDataByFullPath(const std::string& fullyQualifiedName)
{
        CheckOpen();
        if (!DatasetFullPathExist(fullyQualifiedName))
                        throw HDF5Exception("Data set (" + fullyQualifiedName+") does not exist."); 

        std::vector<std::string> names;
        std::string localName = fullyQualifiedName;
        StringUtils::Parse(localName,'/',names);
        if((names[0]=="") && (names.size()>1)) // the path starts with "/", strip it
        {
                names.erase(names.begin());
                localName=localName.substr(1);
        }
        if(names.size()>1)
        {
                size_t index = localName.find ("/");
                HDF5Group gp=  OpenGroup(names[0]);
                return gp.DeleteDataByFullPath(localName.substr(index+1));
        }
        else
        {
                return DeleteData(localName);
        }
};
 
//===============================================
        inline HDF5Dataset HDF5Group::OpenDataset(const std::string& datasetName)
         {
                 CheckOpen();
                 if (!Exist(datasetName))
                         throw HDF5Exception("Failed to open non-existing dataset - "+datasetName); 
                 else
                 {
                   //hid_t dsID=H5Dopen(m_ID,datasetName.c_str());
                   //Assert(dsID, "Failed to open existing dataset - "+datasetName);
                   return HDF5Dataset(m_ID,datasetName);
                 }
        }

//===============================================
inline HDF5Dataset HDF5Group::OpenDatasetByFullPath(const std::string& fullyQualifiedName)
 {
         if (!DatasetFullPathExist(fullyQualifiedName))
                        throw HDF5Exception("Path (" + fullyQualifiedName+") does not exist."); 

         std::vector<std::string> names;
         StringUtils::Parse(fullyQualifiedName,'/',names);
         if(names.size()>1)
         {
                size_t index = fullyQualifiedName.find ("/");
                HDF5Group gp=  OpenGroup(names[0]);
                return gp.OpenDatasetByFullPath(fullyQualifiedName.substr(index+1));
        }
        else
        {
                return OpenDataset(fullyQualifiedName);
        }
}

//===============================================
template <typename T>
 inline void HDF5Group::CreateAttribute(const std::string& attributeName, const seg::Matrix<T>& attributeData, const int compressedlevel)
 {
  //  if(!m_opened)
                //Open();
        CheckOpen();
        if(AttributeFullPathExist(attributeName))
                throw HDF5Exception("Attribute (" + attributeName+") already exists."); 

        HDF5Attribute att(This(),attributeName,attributeData,compressedlevel);
 };
//===============================================
template <typename T>
 inline void HDF5Group::ReadAttribute(const std::string& attributeName, seg::Matrix<T>& attributeData)
 {
  //  if(!m_opened)
                //Open();
        CheckOpen();
        HDF5Attribute att = OpenAttribute(attributeName);
        att.ReadData(attributeData);
 };

//===============================================
 inline void HDF5Group::DeleteAttribute(const std::string& attributeName)
 {
        CheckOpen();
        if(AttributeFullPathExist(attributeName))
        {
                herr_t status = H5Adelete(m_ID,attributeName.c_str());
                Assert(status, "HDF5Dataset::DeleteAttribute() Failed to remove an existing attribute - "+attributeName);
        }
 }; 
//===============================================
 inline HDF5Attribute HDF5Group::OpenAttribute(const std::string& attributeName)
         {
                 CheckOpen();
                 if (!ContainAttribute(attributeName))
                         throw HDF5Exception("Failed to open non-existing attribute - "+attributeName); 
                 else
                 {
                   //hid_t dsID=H5Dopen(m_ID,datasetName.c_str());
                   //Assert(dsID, "Failed to open existing dataset - "+datasetName);
                   return HDF5Attribute(m_ID,attributeName);
                 }
        }


 //===============================================
 inline size_t HDF5Group::NumberOfAttributes() const
 {
        GetAttributeNames();
        return m_attributenames.size();
 }

//===============================================
inline std::vector <std::string> HDF5Group::GetAttributeNames() const
 {
        CheckOpen();
        unsigned int i,j=0;
        hsize_t totalObjs=0;
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
inline bool HDF5Group::ContainAttribute( const std::string& attributeName) const
{
   GetAttributeNames();
   return (std::find(m_attributenames.begin(), m_attributenames.end(), attributeName)!=m_attributenames.end());
}

//===============================================
inline bool HDF5Group::FullPathExist(const std::string &fullyQualifiedName) const
{
/*      std::string localName = fullyQualifiedName;
        if((fullyQualifiedName.size()>0) && (fullyQualifiedName[0]!='/'))
                localName = "/"+localName;

        std::vector <std::string> gps = GetGroupNamesFullPathDetails();
        std::vector <std::string> dss = GetDatasetNamesFullPathDetails();
        std::vector <std::string> atts= GetAttributeNamesFullPathDetails();

        for(size_t i=0; i<gps.size(); i++)
        {
                std::vector<std::string> nameFullPath;
                StringUtils::Parse(gps[i],' ',nameFullPath); // parse the name from the full path
                if(nameFullPath[0]==localName)
                        return true;
        }
        for(size_t i=0; i<dss.size(); i++)
        {
                std::vector<std::string> nameFullPath;
                StringUtils::Parse(dss[i],' ',nameFullPath);
                if(nameFullPath[0]==localName)
                        return true;
        }
        for(size_t i=0; i<atts.size(); i++)
        {
                std::vector<std::string> nameFullPath;
                StringUtils::Parse(atts[i],' ',nameFullPath);
                if(nameFullPath[0]==localName)
                        return true;
        }
        return false;*/ 
        return GroupFullPathExist(fullyQualifiedName) || 
                DatasetFullPathExist(fullyQualifiedName) || 
                AttributeFullPathExist(fullyQualifiedName);
}
//===============================================
inline bool HDF5Group::GroupFullPathExist(const std::string &fullyQualifiedName) const
{
        std::string localName = fullyQualifiedName;
        if((fullyQualifiedName.size()>0) && (fullyQualifiedName[0]!='/'))
                localName = "/"+localName;

        std::vector <std::string> gps = GetGroupNamesFullPath();
        for(size_t i=0; i<gps.size(); i++)
        {
                if(gps[i]==localName)
                        return true;
        }
        return false;
}
//===============================================
inline bool HDF5Group::DatasetFullPathExist(const std::string &fullyQualifiedName) const
{
        std::string localName = fullyQualifiedName;
        if((fullyQualifiedName.size()>0) && (fullyQualifiedName[0]!='/'))
                localName = "/"+localName;

        std::vector <std::string> dss = GetDatasetNamesFullPath();
        for(size_t i=0; i<dss.size(); i++)
        {
                if(dss[i]==localName)
                        return true;
        }
        return false;
}
//===============================================
inline bool HDF5Group::AttributeFullPathExist(const std::string &fullyQualifiedName) const
{
        std::string localName = fullyQualifiedName;
        if((fullyQualifiedName.size()>0) && (fullyQualifiedName[0]!='/'))
                localName = "/"+localName;

        std::vector <std::string> atts= GetAttributeNamesFullPath();

        for(size_t i=0; i<atts.size(); i++)
        {
                if(atts[i]==localName)
                        return true;
        }
        return false;
}
//===============================================
inline size_t HDF5Group::NumberOfGroups() const
 {
        GetGroupNames();
        return m_groupnames.size();
 }

//===============================================
inline size_t HDF5Group::NumberOfDatasets() const
 {
        GetDatasetNames();
        return m_datasetnames.size();
 }
 
//===============================================
inline std::vector <std::string> HDF5Group::GetGroupNames() const
 {
        CheckOpen();
        hsize_t i=0;
        int j=0;
        hsize_t totalObjs=0;
        H5Gget_num_objs(m_ID,&totalObjs);
        std::vector< std::string > gps;
        std::string name = m_hierarchicalName+"/"+m_name;

    for (i=0; i<totalObjs; i++)
        {
                H5Giterate(m_ID, name.c_str(), &j, GetGroupNamesFn, &gps);
        }
        const_cast< std::vector<std::string>& > (m_groupnames) = gps;
        return m_groupnames;
 }

//===============================================
inline std::vector <std::string> HDF5Group::GetDatasetNames() const
 {
        CheckOpen();
        hsize_t i=0;
        int j=0;
        hsize_t totalObjs=0;
        H5Gget_num_objs(m_ID,&totalObjs);
        std::vector< std::string > ds;
        std::string name = m_hierarchicalName+"/"+m_name;;
    for (i=0; i<totalObjs; i++)
        {
                H5Giterate(m_ID, name.c_str(), &j, GetDatasetNamesFn, &ds);
        }
        const_cast< std::vector<std::string>& > (m_datasetnames) = ds;
        return m_datasetnames;
 }
//===============================================
inline std::vector <std::string> HDF5Group::GetGroupNamesFullPath() const
{
        size_t i=0;
        std::vector< std::string > gps=GetGroupNamesFullPathDetails();
        for(i=0; i<gps.size(); i++)
        {
                std::vector< std::string > names;
                StringUtils::Parse(gps[i],' ',names);
                gps[i]=names[0];
        }
        return gps;
}
//===============================================
inline std::vector <std::string> HDF5Group::GetGroupNamesFullPathDetails(const std::string& rootPath) const
{
        size_t i,j=0;
        std::vector< std::string > gps;
        std::vector< std::string > myGps=GetGroupNames();
        for(i=0; i<myGps.size(); i++)
        {
                HDF5Group *thisDA =  (const_cast< HDF5Group* > (this));
                HDF5Group gp = thisDA->OpenGroup(myGps[i]);
                gps.push_back(rootPath+gp.GetName());
                std::vector <std::string> subgrp = gp.GetGroupNamesFullPathDetails(rootPath+gp.GetName()+"/");
                for(j=0; j<subgrp.size(); j++)
                {
                        gps.push_back(subgrp[j]);
                }
        }
        return gps;
}

//===============================================
inline std::vector <std::string> HDF5Group::GetDatasetNamesFullPath() const
{
        size_t i=0;
        std::vector< std::string > dss=GetDatasetNamesFullPathDetails();
        for(i=0; i<dss.size(); i++)
        {
                std::vector< std::string > names;
                StringUtils::Parse(dss[i],' ',names);
                dss[i]=names[0];
        }
        return dss;
}


//===============================================
inline std::vector <std::string> HDF5Group::GetDatasetNamesFullPathDetails(const std::string& rootPath) const
{
        size_t i,j=0;
        std::vector< std::string > ds;
        std::vector< std::string > dsnames=GetDatasetNames();
        for(i=0; i<dsnames.size(); i++)
        {
                HDF5Dataset hd5ds(m_ID,dsnames[i]);
                char buf[10];
                sprintf(buf,"%ld",hd5ds.NumberOfRows());
                std::string strRows=buf;
                sprintf(buf,"%ld",hd5ds.NumberOfColumns());
                std::string strCols=buf;
                ds.push_back(rootPath+dsnames[i]+ " " + strRows + " " + strCols + " " + HDF5DataType::ToString(hd5ds.GetDataType()));
        }
        std::vector< std::string > gps=GetGroupNames();
        for(i=0; i<gps.size(); i++)
        {
                HDF5Group *thisgp =  (const_cast< HDF5Group* > (this));
                HDF5Group gp = thisgp->OpenGroup(gps[i]);
                std::vector <std::string> dsInGrp = gp.GetDatasetNamesFullPathDetails(rootPath+gp.GetName()+"/");
                for(j=0; j<dsInGrp.size(); j++)
                {
                        ds.push_back(dsInGrp[j]);
                }
        }
        return ds;
}
//===============================================
inline std::vector <std::string> HDF5Group::GetAttributeNamesFullPath() const
{
        size_t i=0;
        std::vector< std::string > atts=GetAttributeNamesFullPathDetails();
        for(i=0; i<atts.size(); i++)
        {
                std::vector< std::string > names;
                StringUtils::Parse(atts[i],' ',names);
                atts[i]=names[0];
        }
        return atts;
}

//===============================================
inline std::vector <std::string> HDF5Group::GetAttributeNamesFullPathDetails(const std::string& rootPath) const
{
        size_t i,j=0;
        std::vector< std::string > att;
        std::vector< std::string > attnames=GetAttributeNames();
        for(i=0; i<attnames.size(); i++)
        {
                HDF5Attribute hd5Att(m_ID,attnames[i]);
                char buf[10];
                sprintf(buf,"%ld",hd5Att.NumberOfRows());
                std::string strRows=buf;
                sprintf(buf,"%ld",hd5Att.NumberOfColumns());
                std::string strCols=buf;
                att.push_back(rootPath+attnames[i]+ " " + strRows + " " + strCols + " " + HDF5DataType::ToString(hd5Att.GetDataType()));
                //att.push_back(rootPath+attnames[i]);
        }
        // attributes of groups
        std::vector< std::string > gps=GetGroupNames();
        for(i=0; i<gps.size(); i++)
        {
                HDF5Group *thisgp =  (const_cast< HDF5Group* > (this));
                HDF5Group gp = thisgp->OpenGroup(gps[i]);
                std::vector <std::string> attInGrp = gp.GetAttributeNamesFullPathDetails(rootPath+gp.GetName()+"/");
                for(j=0; j<attInGrp.size(); j++)
                {
                        att.push_back(attInGrp[j]);
                }
        }
        // attributes of datasets
        std::vector< std::string > dss=GetDatasetNames();
        for(i=0; i<dss.size(); i++)
        {
                HDF5Group *thisgp =  (const_cast< HDF5Group* > (this));
                HDF5Dataset ds = thisgp->OpenDataset(dss[i]);
                std::vector <std::string> attInDs = ds.GetAttributeNames();
                for(j=0; j<attInDs.size(); j++)
                {
                        HDF5Attribute hd5Att(ds.ID(),attInDs[j]);
                        char buf[10];
                        sprintf(buf,"%ld",hd5Att.NumberOfRows());
                        std::string strRows=buf;
                        sprintf(buf,"%ld",hd5Att.NumberOfColumns());
                        std::string strCols=buf;
                        att.push_back(rootPath+ds.GetName()+"/"+attInDs[j]+ " " + strRows + " " +strCols + " " + HDF5DataType::ToString(hd5Att.GetDataType()));
                }
        }
        return att;
}

//===============================================
  inline std::string HDF5Group::ToString(const std::string& tabs)
 {
         std::ostringstream str;
         size_t i=0;
         str << tabs<< "Groupname: " << m_name.c_str() << "\n";
         str << tabs<< "Number Of Groups: " << NumberOfGroups() << std::endl;
         std::vector< std::string> gps = GetGroupNames();
         for(i=0 ;i< gps.size(); i++)
         {
                        HDF5Group gp = OpenGroup(gps[i]);
                        str << gp.ToString(tabs+"\t") << std::endl;
         }
         str << tabs<< "Number Of Datasets: " << NumberOfDatasets() << std::endl;
         std::vector< std::string> dss = GetDatasetNames();
         for(i=0 ;i< dss.size(); i++)
         {
                        HDF5Dataset ds = OpenDataset(dss[i]);
                        str << ds.ToString(tabs+"\t") << std::endl;
         }

        return str.str();
 }
#include "HDF5Group.cpp"
}

#endif
