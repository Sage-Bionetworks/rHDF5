#if defined(WIN32) || defined(WIN64)
//#pragma warning(disable:4700)
//#pragma warning(disable:4996)
#endif
#ifndef __HDF5DA_H_
#define __HDF5DA_H_	

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include "StringUtils.h"
#include "hdf5.h"
#include "HDF5DataType.h"
#include "HDF5CompoundType.h"
#include "HDF5Exception.h"
#include "HDF5Group.h"
#include "HDF5Dataset.h"
#include "HDF5Attribute.h"
#include "Matrix.h"

//*******************************************************************************
//*	This class is the main wrapper of the lower level HDF5 routines provided by the 
//* HDF5 Group. Most of the routines are template functions. 
//* This class provides read/write access to the other HDF5 data objects - 
//* HDF5Group, HDF5Dataset, HDf5Attribute
//*******************************************************************************

namespace seg
{
class HDF5DA : public HDF5Object
{
 public:
	
	virtual ~HDF5DA();
	
	// instantiate a new data acces object with a new or existing hdf5 file name
	HDF5DA(const std::string& filename, const bool forceNewFile=true);

	// open an existing dataset. 
	HDF5Dataset OpenDataset(const std::string& datasetName);

	// open an existing dataset by full path. 
	HDF5Dataset OpenDatasetByFullPath(const std::string& fullyQualifiedName);
	
	// read an existing dataset. Use GetDatasetNamesFullPathDetails to find out all dataset
	// names, sizes and data types.
	template <typename T>
	void ReadData(const std::string& datasetName, seg::Matrix<T>& data);
	
	// read an existing dataset. Use GetDatasetNamesFullPathDetails to find out all dataset
	// names, sizes and data types.
	void ReadData(const std::string& datasetName, seg::HDF5CompoundType& data);

	// read certain rows in an existing dataset.  startRowIdx is zero based
	// Use GetDatasetNamesFullPathDetails to find out all dataset names, sizes and data types.
	template <typename T>
	void ReadData(const std::string& datasetName, size_t startRowIdx, size_t nRows, seg::Matrix<T>& data);
	
	// read certain rows in an existing dataset.  startRowIdx is zero based
	// Use GetDatasetNamesFullPathDetails to find out all dataset names, sizes and data types.
	void ReadData(const std::string& datasetName, size_t startRowIdx, size_t nRows, seg::HDF5CompoundType& data);

	// read an existing dataset with a fully qualified Name.   
	// Use GetDatasetNamesFullPathDetails to find out all dataset names, sizes and data types.
	template <typename T>
	void ReadDataByFullPath(const std::string& fullyQualifiedName, seg::Matrix<T>& data);
	void ReadDataByFullPath(const std::string& fullyQualifiedName, seg::HDF5CompoundType& data);

	// read certain rows in an existing dataset with a fully qualified name.  startRowIdx is zero based
	// Use GetDatasetNamesFullPathDetails to find out all dataset names, sizes and data types.
	template <typename T>
	void ReadDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, seg::Matrix<T>& data);
	void ReadDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, seg::HDF5CompoundType& data);

	// write a new dataset.
	// Exception will be thrown is the dataset already exists.
	template <typename T>
	void WriteData(const std::string& datasetName, const seg::Matrix<T>& data, const int compressedlevel=0);
	void WriteData(const std::string& datasetName, const seg::HDF5CompoundType& data, const int compressedlevel=0);

	// write a new dataset inside a group. The group will be created if not existed yet.
	// Exception will be thrown is dataset already exists in the group.
	template <typename T>
	void WriteData(const std::string& groupName, const std::string& datasetName, const seg::Matrix<T>& data, const int compressedlevel=0);

	// overwrite some rows in an exising dataset. startRowIdx is zero based
	// dataset will be extended if necessary.
	// Exception will be thrown is dataset does not exist.
	template <typename T>
	void WriteData(const std::string& datasetName, size_t startRowIdx, size_t nRows, const seg::Matrix<T>& data, const int compressedlevel=0);
	void WriteData(const std::string& datasetName, size_t startRowIdx, size_t nRows, const seg::HDF5CompoundType& data, const int compressedlevel=0);

	// write a new dataset by a fully Qualified Name. All parent groups will be created if not existed yet.
	// Exception will be thrown is the dataset already exists.
	template <typename T>
	void WriteDataByFullPath(const std::string& fullyQualifiedName, const seg::Matrix<T>& data, const int compressedlevel=0);
	void WriteDataByFullPath(const std::string& fullyQualifiedName, const seg::HDF5CompoundType& data, const int compressedlevel=0);

	// overwrite some rows in an exising dataset by a fully Qualified Name. startRowIdx is zero based
	// All parent groups will be created if not existed yet.
	// Exception will be thrown is the dataset does not exist. 
	template <typename T>
	void WriteDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, const seg::Matrix<T>& data, const int compressedlevel=0);
	void WriteDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, const seg::HDF5CompoundType& data, const int compressedlevel=0);

	// Delete an existing dataset within a group
	void DeleteData(const std::string& groupName, const std::string& datasetName);

	// Delete an existing dataset by it full path
	void DeleteDataByFullPath(const std::string& fullyQualifiedName);

	// Create a new group.
	HDF5Group CreateGroup(const std::string& groupName);
	
	// Open an exising group.
	HDF5Group OpenGroup(const std::string& groupName);

	// open an existing group by full path. 
	HDF5Group OpenGroupByFullPath(const std::string& fullyQualifiedName);
	
	// Delete an existing group.
	void DeleteGroup(const std::string& groupName);

	// Return true if a group or dataset exists given its fully qualified name; false otherwise. 
	bool FullPathExist(const std::string& fullyQualifiedName) const;
	bool GroupFullPathExist(const std::string& fullyQualifiedName) const;
	bool DatasetFullPathExist(const std::string& fullyQualifiedName) const;
	bool AttributeFullPathExist(const std::string& fullyQualifiedName) const;

	size_t NumberOfGroups() const;
	size_t NumberOfDatasets() const;

	// Return all group names under the root.
	std::vector <std::string> GetGroupNames() const;
	
	// Return all dataset names under the root.
	std::vector <std::string> GetDatasetNames() const;
	
	// return all group names with their full paths.
	std::vector <std::string> GetGroupNamesFullPath() const;

	// return all group names with their full paths + details. 
	std::vector <std::string> GetGroupNamesFullPathDetails(const std::string& rootPath="/") const;
	
	// return all data names with their full paths
	std::vector <std::string> GetDatasetNamesFullPath() const;

	// return all data names with their full paths + details. - <path> <row> <col> <datatype>
	std::vector <std::string> GetDatasetNamesFullPathDetails(const std::string& rootPath="/") const;
	
	// return all attribute names with their full paths
	std::vector <std::string> GetAttributeNamesFullPath() const;

	// return all attribute names with their full paths + details. - <path> <row> <col> <datatype>
	std::vector <std::string> GetAttributeNamesFullPathDetails(const std::string& rootPath="/") const;
	
	// return a summary of the entire hierarchical structure of the hdf5 file.
	virtual std::string ToString(const std::string& tabs="");

 private:
	 
    virtual void Open();
    virtual void Close();

	const HDF5DA& This();

	template <typename T>
	void WriteData(int locID, const std::string& datasetName, const seg::Matrix<T>& data, const int compressedlevel=0);
	
	void WriteData(int locID, const std::string& datasetName, const seg::HDF5CompoundType& data, const int compressedlevel=0);

	std::vector <std::string> m_groupnames;
	std::vector <std::string> m_datasetnames;

};
//
//===============================================
inline HDF5DA::HDF5DA(const std::string& filename, bool forceNewFile)
{
	m_opened=false;
	m_name=filename;
	std::fstream fin;
	fin.open(m_name.c_str(), std::ios::in);
	bool exist = fin.is_open();
	if ((forceNewFile) || (!exist))
	{
		m_ID = H5Fcreate(m_name.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
			Assert(m_ID,"HDF5DA::HDF5DA() Failed to open HDF5 file - "+m_name);
		 m_opened=true;
	}
	else
	{
		Assert(H5Fis_hdf5(filename.c_str()),"HDF5DA::HDF5DA() Input file not in HDF5 format - "+m_name);
		fin.close();
		Open();
	   GetGroupNames();
	   GetDatasetNames();
	}
}

inline HDF5DA::~HDF5DA()
{
	Close();
}

//===============================================
inline const HDF5DA& HDF5DA::This()
{ 
	HDF5DA* obj = const_cast<HDF5DA*> (this);
	  return *obj;
}


//===============================================
inline void HDF5DA::Open()
{
   if(!m_opened)
   {
	   m_ID = H5Fopen(m_name.c_str(),H5F_ACC_RDWR,H5P_DEFAULT);
	   Assert(m_ID, "HDF5DA::Open() Failed to open HDF5 file - "+m_name);
	   m_opened=true;
   }
}

//===============================================
void inline HDF5DA::Close()
{
	if(m_opened)
	{
		herr_t status = H5Fclose(m_ID);
		Assert(status, "HDF5DA::Close() Failed to close HDF5 file - "+m_name);
	}
	m_opened=false;
}

//===============================================
inline void HDF5DA::WriteData(const std::string& datasetName, const seg::HDF5CompoundType& data, const int compressedlevel)
{
	WriteData(m_ID, datasetName, data, compressedlevel);
}

//===============================================
template <typename T>
inline void HDF5DA::WriteData(const std::string& datasetName, const seg::Matrix<T>& data, const int compressedlevel)
{
	WriteData(m_ID, datasetName, data, compressedlevel);
}

//===============================================
template <typename T>
inline void HDF5DA::WriteData(const std::string& groupName, const std::string& datasetName, const seg::Matrix<T>& data, const int compressedlevel)
{
	if(Exist(groupName))
	{
		HDF5Group gp=OpenGroup(groupName);
		gp.WriteData(datasetName,data, compressedlevel);
	}
	else
	{
		HDF5Group gp=CreateGroup(groupName);
		gp.WriteData(datasetName,data, compressedlevel);
	}
}

//===============================================
inline void HDF5DA::WriteData(int locID, const std::string& datasetName, const seg::HDF5CompoundType& data, const int compressedlevel)
{
	HDF5Dataset ds (This(),datasetName,data,compressedlevel);
};

//===============================================
template <typename T>
inline void HDF5DA::WriteData(int locID, const std::string& datasetName, const seg::Matrix<T>& data, const int compressedlevel)
{
	HDF5Dataset ds (This(),datasetName,data,compressedlevel);
};

//===============================================
template <typename T>
inline void HDF5DA::WriteData(const std::string& datasetName, size_t startRowIdx, size_t nRows, const seg::Matrix<T>& data, const int compressedlevel)
{
  if(!Exist(datasetName))
	  Assert(-1,"HDF5DA::WriteData() Dataset - "+m_name+" does not exist.");

	HDF5Dataset ds (m_ID,datasetName);
	ds.WriteData(startRowIdx,nRows,data,compressedlevel);
}
//===============================================
inline void HDF5DA::WriteData(const std::string& datasetName, size_t startRowIdx, size_t nRows, const seg::HDF5CompoundType& data, const int compressedlevel)
{
  if(!Exist(datasetName))
	  Assert(-1,"HDF5DA::WriteData() Dataset - "+m_name+" does not exist.");

	HDF5Dataset ds (m_ID,datasetName);
	ds.WriteData(startRowIdx,nRows,data,compressedlevel);
}

//===============================================
inline void HDF5DA::WriteDataByFullPath(const std::string& fullyQualifiedName, const seg::HDF5CompoundType& data, const int compressedlevel)
{
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
		WriteData(localName,data,compressedlevel);
	}
}

//===============================================
template <typename T>
inline void HDF5DA::WriteDataByFullPath(const std::string& fullyQualifiedName, const seg::Matrix<T>& data, const int compressedlevel)
{
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
		WriteData(localName,data,compressedlevel);
	}
}

//===============================================
template <typename T>
inline void HDF5DA::WriteDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, const seg::Matrix<T>& data, const int compressedlevel)
{
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
inline void HDF5DA::WriteDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, const seg::HDF5CompoundType& data, const int compressedlevel)
{
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
inline void HDF5DA::ReadDataByFullPath(const std::string& fullyQualifiedName, seg::HDF5CompoundType& data)
{
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
		size_t index = localName.find ("/");
		HDF5Group gp=  OpenGroup(names[0]);
		gp.ReadDataByFullPath(localName.substr(index+1), data);
	}
	else
	{
		ReadData(localName,data);
	}
}
//===============================================
inline void HDF5DA::ReadDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, seg::HDF5CompoundType& data)
{
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
		size_t index = localName.find ("/");
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
inline void HDF5DA::ReadDataByFullPath(const std::string& fullyQualifiedName, seg::Matrix<T>& data)
{
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
		size_t index = localName.find ("/");
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
inline void HDF5DA::ReadDataByFullPath(const std::string& fullyQualifiedName, size_t startRowIdx, size_t nRows, seg::Matrix<T>& data)
{
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
		size_t index = localName.find ("/");
		HDF5Group gp=  OpenGroup(names[0]);
		gp.ReadDataByFullPath(localName.substr(index+1), startRowIdx, nRows, data);
	}
	else
	{
		ReadData(localName,startRowIdx, nRows,data);
	}
}

//===============================================
inline void HDF5DA::ReadData(const std::string& datasetName, seg::HDF5CompoundType& data)
{
	HDF5Dataset ds = OpenDataset(datasetName);
	ds.ReadData(data);
}

//===============================================
inline void HDF5DA::ReadData(const std::string& datasetName, size_t startRowIdx, size_t nRows, seg::HDF5CompoundType& data )
{
	HDF5Dataset ds = OpenDataset(datasetName);
	ds.ReadData(startRowIdx, nRows, data);
}

//===============================================
template <typename T>
inline void HDF5DA::ReadData(const std::string& datasetName, seg::Matrix<T>& data)
{
	HDF5Dataset ds = OpenDataset(datasetName);
	ds.ReadData(data);
}

//===============================================
template <typename T>
inline void HDF5DA::ReadData(const std::string& datasetName, size_t startRowIdx, size_t nRows, seg::Matrix<T>& data )
{
	HDF5Dataset ds = OpenDataset(datasetName);
	ds.ReadData(startRowIdx, nRows, data);
}


//===============================================
inline void HDF5DA::DeleteData(const std::string& groupName, const std::string& datasetName)
{
	if(groupName.size()==0)
	{
		herr_t status = H5Gunlink(m_ID, datasetName.c_str() );
		Assert(status, "HDF5DA::DeleteData() Failed to delete data set - "+datasetName);
	}
	else
	{
		HDF5Group gp = OpenGroup(groupName);
		gp.DeleteData(datasetName);
	}
}

//===============================================
inline void HDF5DA::DeleteDataByFullPath(const std::string& fullyQualifiedName)
{
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
	 	return gp.DeleteDataByFullPath(localName.substr(index));
	}
	else
	{
		return DeleteData("",localName);
	}
}

//===============================================
inline HDF5Dataset HDF5DA::OpenDataset(const std::string& datasetName)
 {
	 if (!Exist(datasetName))
		 throw HDF5Exception("Failed to open non-existing dataset - "+datasetName); 
	 else
	 {
 	   return HDF5Dataset(m_ID,datasetName);
	 }
}

//===============================================
inline HDF5Dataset HDF5DA::OpenDatasetByFullPath(const std::string& fullyQualifiedName)
 {
	 if (!DatasetFullPathExist(fullyQualifiedName))
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
	 	return gp.OpenDatasetByFullPath(localName.substr(index+1));
	}
	else
	{
		return OpenDataset(localName);
	}
}

//===============================================
inline HDF5Group HDF5DA::CreateGroup(const std::string& groupName)
{
    Assert(m_ID, "HDF5DA::CreateGroup() Unknown HDF5 file");
  	return HDF5Group(This(),groupName);
}

//===============================================
inline HDF5Group HDF5DA::OpenGroup(const std::string& groupName)
 {
	 if (!Exist(groupName))
		 throw HDF5Exception("Failed to open non-existing group - "+groupName); 
	 else
	 {
		 return HDF5Group(m_ID, groupName);
	  }
}
//===============================================
inline HDF5Group HDF5DA::OpenGroupByFullPath(const std::string& fullyQualifiedName)
 {
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
inline void HDF5DA::DeleteGroup(const std::string& groupName)
{
	if(Exist(groupName))
	{
	    herr_t status = H5Gunlink(m_ID, groupName.c_str() );
		Assert(status, "HDF5DA::DeleteGroup() Failed to delete group - "+groupName);
	}
}


//===============================================
inline bool HDF5DA::FullPathExist(const std::string &fullyQualifiedName) const
{
	return GroupFullPathExist(fullyQualifiedName) || 
		DatasetFullPathExist(fullyQualifiedName) || 
		AttributeFullPathExist(fullyQualifiedName);
}
//===============================================
inline bool HDF5DA::GroupFullPathExist(const std::string &fullyQualifiedName) const
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
inline bool HDF5DA::DatasetFullPathExist(const std::string &fullyQualifiedName) const
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
inline bool HDF5DA::AttributeFullPathExist(const std::string &fullyQualifiedName) const
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
inline size_t HDF5DA::NumberOfGroups() const
{
	GetGroupNames();
	return m_groupnames.size();
}

//===============================================
inline size_t HDF5DA::NumberOfDatasets() const
{
	GetDatasetNames();
	return m_datasetnames.size();
}

//===============================================
inline std::vector <std::string> HDF5DA::GetGroupNames() const
{
	hsize_t i=0;
	int j=0;
	hsize_t totalObjs=0;
	H5Gget_num_objs(m_ID,&totalObjs);
	std::vector< std::string > gps;
    for (i=0; i<totalObjs; i++)
	{
		H5Giterate(m_ID, "/", &j, GetGroupNamesFn, &gps);
	}
	const_cast< std::vector<std::string>& > (m_groupnames) = gps;
	return m_groupnames;
}

//===============================================
inline std::vector <std::string> HDF5DA::GetDatasetNames() const
{
	hsize_t i=0;
	int j=0;
	hsize_t totalObjs=0;
	H5Gget_num_objs(m_ID,&totalObjs);
	std::vector< std::string > ds;
    for (i=0; i<totalObjs; i++)
	{
		H5Giterate(m_ID, "/", &j, GetDatasetNamesFn, &ds);
	}
	const_cast< std::vector<std::string>& > (m_datasetnames) = ds;
	return m_datasetnames;
}
////===============================================
//inline std::vector <std::string> HDF5DA::GetAttributeNames() const
//{
//	unsigned int i,j=0;
//	hsize_t totalObjs=0;
//	totalObjs = H5Aget_num_attrs(m_ID);
//	std::vector< std::string > atts;
//    for (i=0; i<totalObjs; i++)
//	{
//		H5Aiterate(m_ID, &j, GetAttributeNamesFn, &atts);
//	}
//	const_cast< std::vector<std::string>& > (m_attributenames) = atts;
//	return m_attributenames;
//}
//===============================================
inline std::vector <std::string> HDF5DA::GetGroupNamesFullPath() const
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
inline std::vector <std::string> HDF5DA::GetGroupNamesFullPathDetails(const std::string& rootPath) const
{
	size_t i,j=0;
	std::vector< std::string > gps;
	std::vector< std::string > myGps=GetGroupNames();
	for(i=0; i<myGps.size(); i++)
	{
		HDF5DA *thisDA =  (const_cast< HDF5DA* > (this));
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
inline std::vector <std::string> HDF5DA::GetDatasetNamesFullPath() const
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
inline std::vector <std::string> HDF5DA::GetDatasetNamesFullPathDetails(const std::string& rootPath) const
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
		ds.push_back(rootPath+dsnames[i]+ " " + strRows + " " +strCols + " " + HDF5DataType::ToString(hd5ds.GetDataType()));
	}
	std::vector< std::string > gps=GetGroupNames();
	for(i=0; i<gps.size(); i++)
	{
		HDF5DA *thisDA =  (const_cast< HDF5DA* > (this));
		HDF5Group gp = thisDA->OpenGroup(gps[i]);
		std::vector <std::string> dsInGrp = gp.GetDatasetNamesFullPathDetails(rootPath+gp.GetName()+"/");
		for(j=0; j<dsInGrp.size(); j++)
		{
			ds.push_back(dsInGrp[j]);
		}
	}
	return ds;
}

//===============================================
inline std::vector <std::string> HDF5DA::GetAttributeNamesFullPath() const
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
inline std::vector <std::string> HDF5DA::GetAttributeNamesFullPathDetails(const std::string& rootPath) const
{
	size_t i,j=0;
	std::vector< std::string > att;
	// attributes of groups
	std::vector< std::string > gps=GetGroupNames();
	for(i=0; i<gps.size(); i++)
	{
		HDF5DA *thisDA =  (const_cast< HDF5DA* > (this));
		HDF5Group gp = thisDA->OpenGroup(gps[i]);
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
		HDF5DA *thisDA =  (const_cast< HDF5DA* > (this));
		HDF5Dataset ds = thisDA->OpenDataset(dss[i]);
		std::vector <std::string> attInDs = ds.GetAttributeNames();
		for(j=0; j<attInDs.size(); j++)
		{
			att.push_back(attInDs[j]);
		}
	}
	return att;
}

//===============================================
inline std::string HDF5DA::ToString(const std::string& tabs)
{
	 std::ostringstream str;
	 size_t i=0;
	 str<< "Filename: " << m_name.c_str() << "\n";
	 str<< "Number Of Groups: " << NumberOfGroups() << std::endl;
	 std::vector< std::string> gps = GetGroupNames();
	 for(i=0 ;i< gps.size(); i++)
	 {
			HDF5Group gp = OpenGroup(gps[i]);
			str<< gp.ToString("\t") << std::endl;
	 }
	 str<< "Number Of Datasets: " << NumberOfDatasets() << std::endl;
	 std::vector< std::string> dss = GetDatasetNames();
	 for(i=0 ;i< dss.size(); i++)
	 {
			HDF5Dataset ds = OpenDataset(dss[i]);
			str<< ds.ToString("\t") << std::endl;
	 }

	return str.str();
}
#include "HDF5DA.cpp"
}


#endif
