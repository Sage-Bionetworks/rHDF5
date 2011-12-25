#pragma warning(disable:4786)
#pragma warning(disable:4068)
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#if defined(WIN32) || defined(WIN64)
#include <io.h>
#else
#include <sys/io.h>
#endif

#include "StringUtils.h"
#include "STLTypes.h"
#include "HDF5_entry.h"
#include "RDev.h"
#include "HDF5OutputConverter.h"
#include "HDF5DA.h"

using namespace std;
using namespace R;
using namespace seg;


std::string ExtractAttribute(vector<STLTypes::NameValuePair>& inAttributes,  
						 const std::string& field);
void ReadSummary(RString& rFilename, vector<STLTypes::NameValuePair>& inAttributes, SEXP& results);
void ReadData( RString& rFilename, 
			   RString& rPath, 
			   vector<STLTypes::NameValuePair>& inAttributes, SEXP& results);
void WriteData( RString& rFilename, 
			   RString& rPath, 
			   RVector<int> rIntdata,
			   RVector<double> rDoubledata,
			   RString rStrdata,
			   RDataFrame rDataframdata,
			   vector<STLTypes::NameValuePair>& inAttributes, SEXP& results);
void WriteAttribute( RString& rFilename, 
			   RString& rPath, 
			   RVector<int> rIntdata,
			   RVector<double> rDoubledata,
			   RString rStrdata,
			   vector<STLTypes::NameValuePair>& inAttributes, SEXP& results);
void ReadAttribute( RString& rFilename, 
			   RString& rPath, 
			   vector<STLTypes::NameValuePair>& inAttributes, SEXP& results);
bool CheckGroup(HDF5DA& da, const string& strPath);
bool CheckDataset(HDF5DA& da, const string& strPath);
bool CheckAttribute(HDF5DA& da, const string& strPath);

static const string BAT_HOME="BAT_HOME";
static const string FILENAME="FILENAME";
static const string TASKNAME="TASKNAME";

static const string SUMMARYTASK="summary";
static const string FULLDETAIL="fulldetail";
static const string READDATATASK="readdata";
static const string WRITEDATATASK="writedata";
static const string WRITEATTRTASK="writeattr";
static const string STARTINDEX="startindex";
static const string COMPRESSLEVEL="compresslevel";
static const string NROWS="nrows";
static const string ROW="row";
static const string COL="col";
static const string NEWFILE="forcenewfile";
static const string OVERWRITE="overwrite";
static const string READATTRTASK="readattr";


//
// routine:     HDF5Execute	
//
SEXP HDF5Execute(SEXP task,       
                 SEXP filename,   
                 SEXP path,     //
				 SEXP intdata,     //
				 SEXP doubledata,     //
				 SEXP strdata,     //
				 SEXP dataframedata,     //
                 SEXP aAttributes)
{
    SEXP results = R_NilValue; //initialize to the build-in NULL object

    const int NO_COMPONENTS=10;
    bool debug=false;
    try
    {
        RInitializer rInit;
        //
        // protect/coerce the input args
        //
        RString rTask(task);
        RString rFilename(filename);
        RString rPath(path);
		RVector<int> rIntdata(intdata);
		RVector<double> rDoubledata(doubledata);
		RString rStrdata(strdata);
		RDataFrame rDataframedata(dataframedata);
        RList rAttributes(aAttributes);

		vector<STLTypes::NameValuePair> inAttributes;
        string name;
        string data;
        int len=0;
        int i=0;
        //
        // attributes
        //
        rAttributes.ExtractNameValue(inAttributes);
        if (StringUtils::CompareNoCase(ExtractAttribute(inAttributes,"Debug"),"true"))
        {
             debug=true;
             rInit.Debug(debug);
        }
		
		// converter
		HDF5OutputConverter oc;

		if(StringUtils::CompareNoCase(rTask.Data(0),SUMMARYTASK))
		{
	        ReadSummary(rFilename,inAttributes, results);
		}
		else if (StringUtils::CompareNoCase(rTask.Data(0),READDATATASK))
		{
			ReadData(rFilename, rPath, inAttributes, results);
		}
		else if (StringUtils::CompareNoCase(rTask.Data(0),WRITEDATATASK))
		{
			WriteData(rFilename, rPath, rIntdata, rDoubledata, rStrdata, rDataframedata, inAttributes, results);
		}
		else if (StringUtils::CompareNoCase(rTask.Data(0),WRITEATTRTASK))
		{
			WriteAttribute(rFilename, rPath, rIntdata, rDoubledata, rStrdata, inAttributes, results);
		}
		else if (StringUtils::CompareNoCase(rTask.Data(0),READATTRTASK))
		{
			ReadAttribute(rFilename, rPath, inAttributes, results);
		}
		rInit.Cleanup();
    }
    catch (const RException& exc)
    {
        RProblem(exc.m_message);
    }
    catch (const HDF5Exception& exc)
    {
		RProblem(exc.msg);
    }
    catch (...)
    {
        RProblem("Unknown error encountered");
    }
    return results;
}

// check if a group exists
bool CheckGroup(HDF5DA& da, const string& strPath)
{
	vector<string> gpsummary;
	gpsummary=da.GetGroupNamesFullPath();
	for(size_t i=0; i<gpsummary.size(); i++)
	{
		std::vector<std::string> names;
		StringUtils::Parse(gpsummary[i],' ',names);
		if(names[0]==strPath)
			return true;
	}
	return false;
}

// check if a dataset exists
bool CheckDataset(HDF5DA& da, const string& strPath)
{
	vector<string> dasummary;
	dasummary=da.GetDatasetNamesFullPath();
	for(size_t i=0; i<dasummary.size(); i++)
	{
		std::vector<std::string> names;
		StringUtils::Parse(dasummary[i],' ',names);
		if(names[0]==strPath)
			return true;
	}
	return false;
}

// check if an attribute exists
bool CheckAttribute(HDF5DA& da, const string& strPath)
{
	vector<string> attsummary;
	attsummary=da.GetAttributeNamesFullPath();
	for(size_t i=0; i<attsummary.size(); i++)
	{
		std::vector<std::string> names;
		StringUtils::Parse(attsummary[i],' ',names);
		if(names[0]==strPath)
			return true;
	}
	return false;
}

// Read the file and print out summary
void ReadSummary(RString& rFilename, vector<STLTypes::NameValuePair>& inAttributes, SEXP& results)
{
	HDF5DA da(rFilename.Data(0),false);
	HDF5OutputConverter oc;
	string fileSummary;
	vector<string> gpsummary, dasummary, attsummary;

 	string detail = ExtractAttribute(inAttributes,FULLDETAIL);
			
	gpsummary=da.GetGroupNamesFullPathDetails();
	// print detail which includes the data type and size
	if(StringUtils::CompareNoCase(detail,"true"))
	{
		dasummary=da.GetDatasetNamesFullPathDetails();
		attsummary=da.GetAttributeNamesFullPathDetails();
	}
	else
	{
		dasummary=da.GetDatasetNamesFullPath();
		attsummary=da.GetAttributeNamesFullPath();
	}
		
	fileSummary=da.ToString();
	results=oc.ConvertSummaryOutput(fileSummary,gpsummary, dasummary, attsummary).Object();
}

// Read data from file
void ReadData( RString& rFilename, 
			   RString& rPath, 
			   vector<STLTypes::NameValuePair>& inAttributes, SEXP& results)
{
	HDF5DA da(rFilename.Data(0),false);
	HDF5OutputConverter oc;
	string strPath(rPath.Data(0));

	// check if this is a valid dataset
	vector<string> dasummary=da.GetDatasetNamesFullPath();
	bool isDataset = (find( dasummary.begin( ), dasummary.end( ), strPath)!=dasummary.end( ));
	if(!isDataset)
		throw RException("path - "+strPath+" is not dataset.");

	HDF5Dataset ds = da.OpenDatasetByFullPath(strPath);

 	string startStr = ExtractAttribute(inAttributes,STARTINDEX);
	string nrowsStr = ExtractAttribute(inAttributes,NROWS);
	size_t start=0;
	size_t nRows=ds.NumberOfRows();
	// if only start index is supplied, we need to figure out the nrows.
	if ((startStr.size()>0)) 
	{
		start = atoi(startStr.c_str());
		nRows = nRows-start;
	}
	// nrows is supplied as well
	if (nrowsStr.size()>0)
		nRows = atoi(nrowsStr.c_str());

	switch (ds.GetDataType())
	{
		case HDF5DataType::CHAR:{
			Matrix<char> data;
			da.ReadDataByFullPath(strPath, start, nRows, data);
			results=oc.ConvertIntMatrix(data);
			break;}
		case HDF5DataType::INT:{
			Matrix<int> data;
			da.ReadDataByFullPath(strPath, start, nRows, data);
			results=oc.ConvertIntMatrix(data);
			break;}
		case HDF5DataType::INT64:{
			Matrix<__int64> data;
			da.ReadDataByFullPath(strPath, start, nRows, data);
			results=oc.ConvertDoubleMatrix(data);
			break;}
		case HDF5DataType::FLOAT:{
			Matrix<float> data;
			da.ReadDataByFullPath(strPath, start, nRows, data);
			results=oc.ConvertDoubleMatrix(data);
			break;}
		case HDF5DataType::DOUBLE:{
			Matrix<double> data;  
			da.ReadDataByFullPath(strPath, start, nRows, data);
			results=oc.ConvertDoubleMatrix(data);
			break;}
		case HDF5DataType::STRING:{
			Matrix<string> data;
			da.ReadDataByFullPath(strPath, start, nRows, data);
			results=oc.ConvertStrMatrix(data);
			break;}
		case HDF5DataType::COMPOUND:{
			HDF5CompoundType data;
			da.ReadDataByFullPath(strPath, start, nRows, data);
			results=oc.ConvertCompoundType(data);
			break;}
		default:
			throw RException("Unknown data type");
		}
}

// write data to file
void WriteData( RString& rFilename, 
			   RString& rPath, 
			   RVector<int> rIntdata,
			   RVector<double> rDoubledata,
			   RString rStrdata,
			   RDataFrame rDataframedata,
			   vector<STLTypes::NameValuePair>& inAttributes, SEXP& results)
{
	HDF5DA da(rFilename.Data(0),StringUtils::CompareNoCase(ExtractAttribute(inAttributes,NEWFILE),"true"));
	HDF5OutputConverter oc;
	string strPath(rPath.Data(0));
	string compressStr = ExtractAttribute(inAttributes,COMPRESSLEVEL);
	int compressedLevel = 0;
	if ((compressStr.size()>0))
		compressedLevel = atoi(compressStr.c_str());

	// the dimension of the data to be written
 	string strRow = ExtractAttribute(inAttributes,ROW);
	string strCol = ExtractAttribute(inAttributes,COL);
	size_t row=0;
	size_t col=0;
	if ((strRow.size()>0) && (strCol.size()>0))
	{
		row = atoi(strRow.c_str());
		col = atoi(strCol.c_str());
	}

	// if start index and nRows =0, it means user has not specified a subset to write,
	// therefore we will read the whole data set
 	string startStr = ExtractAttribute(inAttributes,STARTINDEX);
	string nrowsStr = ExtractAttribute(inAttributes,NROWS);
	size_t start=0;
	size_t nRows=0;
	bool writeAll=true;
	if (rIntdata.Size()>0) nRows=row;
	if (rDoubledata.Size()>0) nRows=row;
	if (rStrdata.Size()>0) nRows=row;
	if ((startStr.size()>0)) 
	{
		start = atoi(startStr.c_str());
		writeAll=false;
	}
	if (nrowsStr.size()>0)
	{
		nRows = atoi(nrowsStr.c_str());
		writeAll=false;
	}

	// delete the dataset first if it already exists
	string overwrite = ExtractAttribute(inAttributes,OVERWRITE);

	if(rIntdata.Size()>0)
	{
		// obtain the data from input
		rIntdata.Dimensions(row,col);
		Matrix<int> intdata;
		rIntdata.Extract(intdata);
		if(writeAll)
		{
			if(StringUtils::CompareNoCase(overwrite,"true"))
			{
				if(da.DatasetFullPathExist(strPath))
					da.DeleteDataByFullPath(strPath);
			}
			da.WriteDataByFullPath(strPath, intdata, compressedLevel);
		}
		else
			da.WriteDataByFullPath(strPath, start, nRows, intdata, compressedLevel);
	}
	else if(rDoubledata.Size()>0)
	{
		// obtain the data from input
		rDoubledata.Dimensions(row,col);
		Matrix<double> doubledata;
		rDoubledata.Extract(doubledata);
		if(writeAll)
		{
			if(StringUtils::CompareNoCase(overwrite,"true"))
			{
				if(da.DatasetFullPathExist(strPath))
					da.DeleteDataByFullPath(strPath);
			}
			da.WriteDataByFullPath(strPath, doubledata, compressedLevel);
		}
		else
			da.WriteDataByFullPath(strPath, start, nRows, doubledata, compressedLevel);

	}

	else if(rStrdata.Size()>0)
	{
		// obtain the data from input
		rStrdata.Dimensions(row,col);
		Matrix<string> strdata;
		rStrdata.Extract(strdata,row,col);
		if(writeAll)
		{
			if(StringUtils::CompareNoCase(overwrite,"true"))
			{
				if(da.DatasetFullPathExist(strPath))
					da.DeleteDataByFullPath(strPath);
			}
			da.WriteDataByFullPath(strPath, strdata, compressedLevel);
		}
		else
			da.WriteDataByFullPath(strPath, start, nRows, strdata, compressedLevel);
	}
	else if(rDataframedata.Size()>0)
	{
		if(writeAll)
		{
			if(StringUtils::CompareNoCase(overwrite,"true"))
			{
				if(da.DatasetFullPathExist(strPath))
					da.DeleteDataByFullPath(strPath);
			}
			da.WriteDataByFullPath(strPath, rDataframedata.CompoundType(), compressedLevel);
		}
		else
			da.WriteDataByFullPath(strPath, start, nRows, rDataframedata.CompoundType(), compressedLevel);
	}
}

// writing attribute to the file
void WriteAttribute( RString& rFilename, 
			   RString& rPath, 
			   RVector<int> rIntdata,
			   RVector<double> rDoubledata,
			   RString rStrdata,
			   vector<STLTypes::NameValuePair>& inAttributes, SEXP& results)
{
	HDF5DA da(rFilename.Data(0),StringUtils::CompareNoCase(ExtractAttribute(inAttributes,NEWFILE),"true"));
	HDF5OutputConverter oc;
	string strPath(rPath.Data(0));

	// read the compress level
	string compressStr = ExtractAttribute(inAttributes,COMPRESSLEVEL);
	int compressedLevel = 0;
	if ((compressStr.size()>0))
		compressedLevel = atoi(compressStr.c_str());

	// the dimension of the data to be read
	string strRow = ExtractAttribute(inAttributes,ROW);
	string strCol = ExtractAttribute(inAttributes,COL);
	size_t row=0;
	size_t col=0;
	if ((strRow.size()>0) && (strCol.size()>0))
	{
		row = atoi(strRow.c_str());
		col = atoi(strCol.c_str());
	}

	string::size_type index = strPath.find_last_of('/');
	if((index == string::npos  )||(index==0))
		throw RException("Attribute can only be directly under an existing dataset or group.");

	string parent = strPath.substr(0,index);
	string attr = strPath.substr(index+1,string::npos);
	
	// are we going to overwrite an existing attribute
	bool overwrite = StringUtils::CompareNoCase(ExtractAttribute(inAttributes,OVERWRITE),"true");
	
	if(rIntdata.Size()>0)
	{
		// obtain the data from input
		rIntdata.Dimensions(row,col);
		Matrix<int> intdata;
		rIntdata.Extract(intdata);
		if(CheckDataset(da,parent))
		{
			HDF5Dataset ds = da.OpenDatasetByFullPath(parent);
			if (overwrite)
				ds.DeleteAttribute(attr);

			ds.CreateAttribute(attr,intdata, compressedLevel);
		}
		else if(CheckGroup(da,parent))
		{
			HDF5Group gp = da.OpenGroupByFullPath(parent);
			if (overwrite)
				gp.DeleteAttribute(attr);
			gp.CreateAttribute(attr,intdata, compressedLevel);
		}
		else
			throw RException("Attribute can only be directly under an existing dataset or group.");
	}
	else if(rDoubledata.Size()>0)
	{
		// obtain the data from input
		rDoubledata.Dimensions(row,col);
		Matrix<double> doubledata;
		rDoubledata.Extract(doubledata);
		if(CheckDataset(da,parent))
		{
			HDF5Dataset ds = da.OpenDatasetByFullPath(parent);
			if (overwrite)
				ds.DeleteAttribute(attr);

			ds.CreateAttribute(attr,doubledata, compressedLevel);
		}
		else if(CheckGroup(da,parent))
		{
			HDF5Group gp = da.OpenGroupByFullPath(parent);
			if (overwrite)
				gp.DeleteAttribute(attr);

			gp.CreateAttribute(attr,doubledata, compressedLevel);
		}
		else
			throw RException("Attribute can only be directly under an existing dataset or group.");
	}
	else if(rStrdata.Size()>0)
	{
		// obtain the data from input
		rStrdata.Dimensions(row,col);
		Matrix<string> strdata;
		rStrdata.Extract(strdata,row,col);
		if(CheckDataset(da,parent))
		{
			HDF5Dataset ds = da.OpenDatasetByFullPath(parent);
			if (overwrite)
				ds.DeleteAttribute(attr);

			ds.CreateAttribute(attr,strdata, compressedLevel);
		}
		else if(CheckGroup(da,parent))
		{
			HDF5Group gp = da.OpenGroupByFullPath(parent);
			if (overwrite)
				gp.DeleteAttribute(attr);

			gp.CreateAttribute(attr,strdata, compressedLevel);
		}
		else
			throw RException("Attribute can only be directly under an existing dataset or group.");
	}
}

// the function does the real reading.  It is called in multiple places
template <class T>
void DoReadAttribute(HDF5DA& da, const string& strPath, Matrix<T>& data)
{
	// check if it is attribute of group
	size_t idx = strPath.find_last_of("/");
	string parentpath = strPath.substr(0,idx);
	string attr = strPath.substr(idx+1);
	vector<string> gpsummary=da.GetGroupNamesFullPath();
	bool parentIsAGroup = (find( gpsummary.begin( ), gpsummary.end( ), parentpath)!=gpsummary.end( ));
	if(parentIsAGroup)
		da.OpenGroupByFullPath(parentpath).ReadAttribute(attr,data);
	else
		da.OpenDatasetByFullPath(parentpath).ReadAttribute(attr,data);
}

// read attribute
void ReadAttribute( RString& rFilename, 
				    RString& rPath, 
				    vector<STLTypes::NameValuePair>& inAttributes, SEXP& results)
{
	HDF5DA da(rFilename.Data(0),false);
	HDF5OutputConverter oc;
	string strPath(rPath.Data(0));

	vector<string> attsummary=da.GetAttributeNamesFullPath();
	bool isAtt = (find( attsummary.begin( ), attsummary.end( ), strPath)!=attsummary.end( ));
	if(!isAtt)
		throw RException("path - "+strPath+" is not attribute.");

	// get the data type of the attribute
	attsummary=da.GetAttributeNamesFullPathDetails();
	vector<string> attLine;
	string attDataType;
	for(size_t i=0; i<attsummary.size(); i++)
	{
		std::vector<std::string> attLine;
		StringUtils::Parse(attsummary[i],' ',attLine);
		if(attLine[0]==strPath)
		{
			attDataType=attLine[attLine.size()-1];
			break;
		}
	}
													 
	switch (HDF5DataType::MapHDF5TypeFromString(attDataType))
	{
		case HDF5DataType::CHAR:{
			Matrix<char> data;
			DoReadAttribute(da,strPath,data);
			results=oc.ConvertIntMatrix(data);
			break;}
		case HDF5DataType::INT:{
			Matrix<int> data;
			DoReadAttribute(da,strPath,data);
			results=oc.ConvertIntMatrix(data);
			break;}
		case HDF5DataType::INT64:{
			Matrix<__int64> data;
			DoReadAttribute(da,strPath,data);
			results=oc.ConvertDoubleMatrix(data);
			break;}
		case HDF5DataType::FLOAT:{
			Matrix<float> data;
			DoReadAttribute(da,strPath,data);
			results=oc.ConvertDoubleMatrix(data);
			break;}
		case HDF5DataType::DOUBLE:{
			Matrix<double> data;  
			DoReadAttribute(da,strPath,data);
			results=oc.ConvertDoubleMatrix(data);
			break;}
		case HDF5DataType::STRING:{
			Matrix<string> data;
			DoReadAttribute(da,strPath,data);
			results=oc.ConvertStrMatrix(data);
			break;}
		default:
			throw RException("Unknown data type");
		}
}

// extract attributes from the NV pairs
std::string ExtractAttribute(vector<STLTypes::NameValuePair>& inAttributes, 
						 const std::string& field)
{
        //
        // attributes
        //
        size_t noAttrs=inAttributes.size();
        for (size_t aI=0;aI<noAttrs;aI++)
        {
            if (StringUtils::CompareNoCase(inAttributes[aI].first,field))
            {
				return inAttributes[aI].second;
            }
        }
		return "";
}
