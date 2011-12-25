// HDF5.cpp : Defines the entry point for the console application.
//
#include <string>
#include <sstream>
#include <assert.h>
#include "HDF5DA.h"
using namespace std;
using namespace seg;

static unsigned
align (unsigned offset, unsigned alignto)
{
#if 0
	unsigned mask = alignto - 1;

	if ((offset & mask) == 0)
		return offset;
	else
		return (offset + alignto) & ~mask;
#else
	return offset;
#endif
}

void readFile()
{
	string filename0 = "Kidneycortex_Female_W10.h5";
	HDF5DA hd(filename0, false);
//	cout << hd.ToString() << endl;

	vector<string> gps = hd.GetGroupNames();
	for (size_t i=0;i<gps.size(); i++)
	{
		HDF5Group gp = hd.OpenGroup(gps[i]);
		vector<string> dss = gp.GetDatasetNames();
		for (size_t j=0;j<dss.size(); j++)
		{
			HDF5Dataset ds = gp.OpenDataset(dss[j]);
			HDF5DataType::DataType dt=  ds.GetDataType();
			switch(dt)
			{
			case HDF5DataType::INT:
				{
					Matrix<int> data;
					ds.ReadData(data);
					/*for(int a =0; a<10; a++)
					{
						for(size_t j=0; j<data.NumberOfColumns(); j++)
						{
							cout << data[a*data.NumberOfColumns()+j] << " ";
						}
						cout << "\n";
					}*/
					break;
				}
			case HDF5DataType::FLOAT:
			case HDF5DataType::DOUBLE:
				{
					Matrix<double> data;
					ds.ReadData(data);
					/*for(int a =0; a<10; a++)
					{
						for(size_t j=0; j<data.NumberOfColumns(); j++)
						{
							cout << data[a*data.NumberOfColumns()+j] << " ";
						}
						cout << "\n";
					}*/
					break;
				}
			case HDF5DataType::STRING:
				{
					Matrix<string> data;
					ds.ReadData(data);
					for(int a =0; a<10; a++)
					{
						for(size_t j=0; j<data.NumberOfColumns(); j++)
						{
							cout << data[a*data.NumberOfColumns()+j] << " ";
						}
						cout << "\n";
					}
					break;
				}
			}
		}
	}
}

bool checkResult(const Matrix<string>& indata,const Matrix<string>&outdata)
{
	for(size_t i=0; i<indata.NumberOfRows(); i++)
	{
		for(size_t j=0; j<indata.NumberOfColumns(); j++)
		{
				if ((indata[i*indata.NumberOfColumns()+j].compare(outdata[i*indata.NumberOfColumns()+j]))!=0)
					return false;
		}
	}
	return true;

}

bool checkResultStr1(const Matrix<char*>& indata,const Matrix<char*>&outdata)
{
	for(size_t i=0; i<indata.NumberOfRows(); i++)
	{
		for(size_t j=0; j<indata.NumberOfColumns(); j++)
		{
			char* d1=indata[i*indata.NumberOfColumns()+j];
			char* d2=outdata[i*indata.NumberOfColumns()+j];
				string str3(d1), str4(d2);
				if ((str3.compare(str4))!=0)
					return false;
		}
	}
	return true;

}
bool checkResultStr1(const Matrix<char*>& indata,const Matrix<char*>&outdata, size_t rIndex, size_t nRows)
{
	size_t r=0;
	for(size_t i=rIndex; i<nRows; i++)
	{
		for(size_t j=0; j<indata.NumberOfColumns(); j++)
		{
			char* d1=indata[i*indata.NumberOfColumns()+j];
			char* d2=outdata[r*indata.NumberOfColumns()+j];
				string str3(d1), str4(d2);
				if ((str3.compare(str4))!=0)
					return false;
		}
		r++;
	}
	return true;

}

template<typename T>
bool checkResult( Matrix<T>& indata, Matrix<T>&outdata)
{
	if(typeid(T)==typeid(char*))
	{
		return checkResultStr1((reinterpret_cast< const Matrix<char *>& >(indata)),(reinterpret_cast< const Matrix<char *>& >(outdata)));
	}
	else 
	{
		for(size_t i=0; i<indata.NumberOfRows(); i++)
		{
			for(size_t j=0; j<indata.NumberOfColumns(); j++)
			{
				/*T d1=;
				T d2=;*/
				//outdata.Print(cout);
				 
				if(indata[i*indata.NumberOfColumns()+j]!= outdata[i*indata.NumberOfColumns()+j] )
					return false;
			}
		}
	}
	return true;
}

template<typename T>
bool checkResult( Matrix<T>& indata, Matrix<T>&outdata, size_t rIndex, size_t nRows)
{
	if(typeid(T)==typeid(char*))
	{
		return checkResultStr1((reinterpret_cast< const Matrix<char *>& >(indata)),(reinterpret_cast< const Matrix<char *>& >(outdata)),rIndex,nRows);
	}
	else 
	{
		size_t r=0;
		for(size_t i=rIndex; i<nRows; i++)
		{
			for(size_t j=0; j<indata.NumberOfColumns(); j++)
			{
				/*T d1=;
				T d2=;*/
				//outdata.Print(cout);
				 
				if(indata[i*indata.NumberOfColumns()+j]!= outdata[r*indata.NumberOfColumns()+j] )
					return false;
			}
			r++;
		}
	}
	return true;
}


void testDA(string& filename)
{
	int ROWS =10;
	int COLS =5;
	size_t i,j;
	size_t rIndex=2;
	Matrix<int> indata(ROWS,COLS);Matrix<int> oindata(ROWS,COLS);
	Matrix<__int64> in64data(ROWS,COLS);Matrix<__int64> oin64data(ROWS,COLS);
	Matrix<string> strdata(ROWS,COLS);Matrix<string> ostrdata(ROWS,COLS);
	Matrix<char*> strdata1(ROWS,COLS);Matrix<char*> ostrdata1(ROWS,COLS);
	Matrix<char> chardata(ROWS,COLS);Matrix<char> ochardata(ROWS,COLS);
	Matrix<bool> booldata(ROWS,COLS);Matrix<bool> obooldata(ROWS,COLS);
	Matrix<float> floatdata(ROWS,COLS);Matrix<float> ofloatdata(ROWS,COLS);
	Matrix<double> doubledata(ROWS,COLS);Matrix<double> odoubledata(ROWS,COLS);
	Matrix<int> emptydata;
	char ch='a';
	for (j = 0; j < ROWS; j++) {
		for (i = 0; i < COLS; i++)
		{
		    indata(j,i) = i + j;
			in64data(j,i) = i + j;
			std::stringstream str;
			str<<(i+j);
			char buf[10];
			sprintf(buf,"%d",i+j);
			strdata(j,i) = buf;
			strdata(j,i)+="abcaaaaaaa";
			char * c = const_cast<char*> (strdata(j,i).c_str());
			strdata1(j,i) = c;
			chardata(j,i) = ch++;
			booldata(j,i) = ((i+j)%2 == 0);
			floatdata(j,i) = float(i+j)/3;
			doubledata(j,i) = double(i+j)/3;

//			cout<<booldata(j,i)<<" ";
		}	
		cout << endl;
    }

	/* data with fewer rows */
	int ROWSR=ROWS-5;
	Matrix<int> indataR(ROWSR,COLS);
	Matrix<__int64> in64dataR(ROWSR,COLS);
	Matrix<string> strdataR(ROWSR,COLS);
	Matrix<char*> strdata1R(ROWSR,COLS);
	Matrix<char> chardataR(ROWSR,COLS);
	Matrix<bool> booldataR(ROWSR,COLS);
	Matrix<float> floatdataR(ROWSR,COLS);
	Matrix<double> doubledataR(ROWSR,COLS);
	ch='A';
	for (j = 0; j < ROWSR; j++) {
		for (i = 0; i < COLS; i++)
		{
		    indataR(j,i) = i + j*10;
			in64dataR(j,i) = i + j*10;
			std::stringstream str;
			str<<(i+j);
			char buf[10];
			sprintf(buf,"%d",i+j);
			strdataR(j,i) = buf;
			strdataR(j,i) += "ABCAAAAAAA";
			char * c = const_cast<char*> (strdataR(j,i).c_str());
			strdata1R(j,i) = c;
			chardataR(j,i) = ch++;
			booldataR(j,i) = !((i+j)%2 == 0);
			floatdataR(j,i) = float(i+j)/30;
			doubledataR(j,i) = double(i+j)/30;
		}	
		cout << endl;
    }

	/* attributes data */
	int ANX =1;
	int ANY =5;
	Matrix<int> aindata(ANX,ANY);Matrix<int> oaindata;
	Matrix<string> aindataStr(ANX,ANY);Matrix<string> oaindataStr;
	Matrix<char*> aindataStr1(ANX,ANY);Matrix<char*> oaindataStr1;
	Matrix<__int64> aindataInt64(ANX,ANY);Matrix<__int64> oaindataInt64;

	for (j = 0; j < ANX; j++) {
		for (i = 0; i < ANY; i++)
		{
		    aindata(j,i) = i + j;
		    aindataInt64(j,i) = i + j;
			std::stringstream str;
			str<<(i+j);
			char buf[10];
			sprintf(buf,"%d",i+j);
			aindataStr(j,i) = buf;
			aindataStr(j,i)+="abcaaaaaaa";
			char * c = const_cast<char*> (aindataStr(j,i).c_str());
			aindataStr1(j,i) = c;
		}	
    }

	if(filename=="")
	{
		filename = "test.h5"; 
		//fstream fin;
		//fin.open(filename.c_str(),ios::in);
		//if( fin.is_open() )
		//{
		//	string cmd = "del "+filename;
		//	system(cmd.c_str());
		//}
	}
	//HDF5DA hd0(filename,2,false);
	HDF5DA hd0(filename,filename=="test.h5");
	cout << hd0.ToString() << endl;
	std::vector<std::string> gpnames;
	std::vector<std::string> dsnames;
	std::vector<std::string> attnames;
	
	if(filename=="test.h5")
	{
	hd0.WriteDataByFullPath("/testGroup1/gp-gp-testGroup2/gp-gp-testdsInt", indata);
	dsnames=hd0.GetDatasetNamesFullPath();
	cout << endl<< "all datasets" << endl;
	for(i=0; i<dsnames.size(); i++)
		cout << dsnames[i] << endl;

	cout<< " WriteDataByFullPath Int... " ;
	hd0.WriteDataByFullPath("/testGroup1/gp-gp-testGroup2/gp-gp-testdsInt", rIndex,ROWSR, indataR);
	HDF5Group gp0 = hd0.OpenGroup("testGroup1");
	//gp0.CreateAttribute("gp-gp-testGroup2",aindata);
	hd0.ReadDataByFullPath("/testGroup1/gp-gp-testGroup2/gp-gp-testdsInt",rIndex,ROWSR,oindata); 
	cout<< (checkResult(indataR,oindata)?"\t\t\tpassed":"\t\t\tfailed") <<endl;
	}

	cout<< " ======== testing DA ========" << endl;
	if(filename=="test.h5")
	{
	cout<< " WriteData Int... " ;
	hd0.WriteData("testdsInt",indata);
	cout<< "\t\t\tpassed"<<endl;
	cout<< " WriteData Int64... " ;
	hd0.WriteData("testdsInt64",in64data);
	cout<< "\t\t\tpassed"<<endl;
	cout<< " WriteData Char... " ;
	hd0.WriteData("testdsChar",chardata);
	cout<< "\t\t\tpassed"<<endl;
	cout<< " WriteData Bool... " ;
	hd0.WriteData("testdsBool",booldata);
	cout<< "\t\t\tpassed"<<endl;
	cout<< " WriteData char*... " ;
	hd0.WriteData("testdsChar*",strdata1);
	cout<< "\t\t\tpassed"<<endl;
	cout<< " WriteData String... " ;
	hd0.WriteData("testdsStr",strdata);
	cout<< "\t\t\tpassed"<<endl;
	cout<< " WriteData float... " ;
	hd0.WriteData("testdsFloat",floatdata);
	cout<< "\t\t\tpassed"<<endl;
	cout<< " WriteData double... " ;
	hd0.WriteData("testdsDouble",doubledata);
	cout<< "\t\t\tpassed"<<endl;


	cout<< " WriteData by rows Int... " ;
	hd0.WriteData("testdsInt",rIndex,ROWSR,indataR);
	hd0.ReadData("testdsInt",rIndex,ROWSR,oindata); 
	cout<< (checkResult(indataR,oindata)?"\t\t\tpassed":"\t\t\tfailed") <<endl;
	}
	cout<< " ReadData Int... " ;
	hd0.WriteData("testdsInt",0,indata.NumberOfRows(),indata);
	hd0.ReadData("testdsInt",oindata); 
	cout<< (checkResult(indata,oindata)?"\t\t\tpassed":"\t\t\tfailed") <<endl;
	cout<< " ReadData Int64... " ;
	hd0.ReadData("testdsInt64",oin64data); 
	cout<< (checkResult(in64data,oin64data)?"\t\t\tpassed":"\t\t\tfailed") <<endl;
	cout<< " ReadData Char... " ;
	hd0.ReadData("testdsChar",ochardata);
	cout<< (checkResult(chardata,ochardata)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " ReadData Bool... " ;
	hd0.ReadData("testdsBool",obooldata);
	cout<< (checkResult(booldata,obooldata)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " ReadData char*... " ;
	hd0.ReadData("testdsStr",ostrdata1);
	cout<< (checkResult(strdata1,ostrdata1)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " ReadData String... " ;
	hd0.ReadData("testdsStr",ostrdata);
	cout<< (checkResult(strdata,ostrdata)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " ReadData Float... " ;
	hd0.ReadData("testdsFloat",ofloatdata);
	cout<< (checkResult(floatdata,ofloatdata)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " ReadData Double... " ;
	hd0.ReadData("testdsDouble",odoubledata);
	cout<< (checkResult(doubledata,odoubledata)?"\t\t\tpassed":"\t\t\tfailed")<<endl;


	cout<< " ReadData by rows Int... " ;
	hd0.ReadData("testdsInt",rIndex,ROWSR,oindata); 
	cout<< (checkResult(indata,oindata,rIndex,ROWSR)?"\t\t\tpassed":"\t\t\tfailed") <<endl;
	cout<< " ReadData by rows Int64... " ;
	hd0.ReadData("testdsInt64",rIndex,ROWSR,oin64data); 
	cout<< (checkResult(in64data,oin64data,rIndex,ROWSR)?"\t\t\tpassed":"\t\t\tfailed") <<endl;
	cout<< " ReadData by rows Char... " ;
	hd0.ReadData("testdsChar",rIndex,ROWSR,ochardata);
	cout<< (checkResult(chardata,ochardata,rIndex,ROWSR)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " ReadData by rows Bool... " ;
	hd0.ReadData("testdsBool",rIndex,ROWSR,obooldata);
	cout<< (checkResult(booldata,obooldata,rIndex,ROWSR)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " ReadData by rows char*... " ;
	hd0.ReadData("testdsStr",rIndex,ROWSR,ostrdata1);
	cout<< (checkResult(strdata1,ostrdata1,rIndex,ROWSR)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " ReadData by rows String... " ;
	hd0.ReadData("testdsStr",rIndex,ROWSR,ostrdata);
	cout<< (checkResult(strdata,ostrdata,rIndex,ROWSR)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " ReadData by rows Float... " ;
	hd0.ReadData("testdsFloat",rIndex,ROWSR,ofloatdata);
	cout<< (checkResult(floatdata,ofloatdata,rIndex,ROWSR)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " ReadData by rows Double... " ;
	hd0.ReadData("testdsDouble",rIndex,ROWSR,odoubledata);
	cout<< (checkResult(doubledata,odoubledata,rIndex,ROWSR)?"\t\t\tpassed":"\t\t\tfailed")<<endl;

	cout<< " ======== testing Group ========" << endl;
	if(filename=="test.h5")
	{
	cout<< " Create Group... " ;
	hd0.CreateGroup("testGroup0");
	HDF5Group gp = hd0.OpenGroup("testGroup0");
	cout<< "\t\t\tpassed"<<endl;
	cout<< " Create char * attribute in group... " ;
	gp.CreateAttribute("gp-testAtt1",aindataStr1,true);
	cout<< (gp.ContainAttribute("gp-testAtt1")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Read attribute in dataset... " ;
	gp.ReadAttribute("gp-testAtt1",oaindataStr1);
	cout<< (checkResult(aindataStr1,oaindataStr1)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Check if testGroup0 in dataset... " ;
	cout<< (hd0.Exist("testGroup0")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Write Group data str... " ;
	hd0.WriteData("testGroup1", "gp-testdsStr",strdata1);
	cout<< "\t\t\tpassed"<<endl;
	cout<< " Read Group Data str... " ;
	gp = hd0.OpenGroup("testGroup1");
	gp.ReadData("gp-testdsStr",ostrdata1);
	cout<< (checkResult(strdata1,ostrdata1)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Write Group data int... " ;
	hd0.WriteData("testGroup1", "gp-testdsInt",indata);
	cout<< (hd0.Exist("testGroup1")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Read Group Data int... " ;
	gp = hd0.OpenGroup("testGroup1");
	gp.ReadData("gp-testdsInt",oindata);
	cout<< (checkResult(indata,oindata)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Delete data in Group testGroup1... " ;
	gp.DeleteData("gp-testdsStr");
	cout<< (!gp.Exist("gp-testdsStr")?"\t\t\tpassed":"\t\t\tfailed")<<endl;

	cout<< " Open Group testGroup1... " ;
	gp   = hd0.OpenGroup("testGroup1");
	cout<< (gp.Exist("gp-testdsInt")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Create sub Group gp-gp-testGroup1... " ;
	HDF5Group subgp;
	if(!gp.Exist("gp-gp-testGroup1"))
		subgp = gp.CreateGroup("gp-gp-testGroup1");
	else
		subgp = gp.OpenGroup("gp-gp-testGroup1");


	cout<< (gp.Exist("gp-gp-testGroup1")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Write data in sub Group gp-gp-testGroup1... " ;
	subgp.WriteData("gp-gp-testdsInt",indata);
	cout<< (subgp.Exist("gp-gp-testdsInt")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Read data in sub Group gp-gp-testGroup1... " ;
	subgp.ReadData("gp-gp-testdsInt",oindata);
	cout<< (checkResult(indata,oindata)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	subgp.ReadData("gp-gp-testdsInt",rIndex,ROWSR,oindata);
	cout<< (checkResult(indata,oindata,rIndex,ROWSR)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Delete data in sub Group gp-gp-testGroup1... " ;
	subgp.WriteData("gp-gp-testdsStr",strdata);
	subgp.DeleteData("gp-gp-testdsStr");
	cout<< (!subgp.Exist("gp-gp-testdsStr")?"\t\t\tpassed":"\t\t\tfailed")<<endl;

	cout<< " Delete data by full path in sub Group gp-gp-testGroup1... " ;
	subgp.WriteData("gp-gp-testdsStr",strdata);
	hd0.DeleteDataByFullPath("/testGroup1/gp-gp-testGroup1/gp-gp-testdsStr");
	cout<< (!subgp.Exist("gp-gp-testdsStr")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	hd0.WriteData("/gp-gp-testdsStr",strdata);
	hd0.DeleteDataByFullPath("/gp-gp-testdsStr");
	cout<< (!subgp.Exist("gp-gp-testdsStr")?"\t\t\tpassed":"\t\t\tfailed")<<endl;

	cout<< " ======== testing DataSet ========" << endl;

	cout<< " Open data in Group gp-testGroup1... " ;
	HDF5Dataset ds= gp.OpenDataset("gp-testdsInt");
	cout<< "\t\t\tpassed"<<endl;
	cout<< " Create string attribute in dataset... " ;
	ds.CreateAttribute("gp-testAtt",aindataStr,false);
	cout<< (ds.Exist("gp-testAtt")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Read attribute in dataset... " ;
	ds.ReadAttribute("gp-testAtt",oaindataStr);
	cout<< (checkResult(aindataStr,oaindataStr)?"\t\t\tpassed":"\t\t\tfailed")<<endl;

	cout<< " Create char * attribute in dataset... " ;
	ds.CreateAttribute("gp-testAtt1",aindataStr1);
	cout<< (ds.Exist("gp-testAtt1")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Read attribute in dataset... " ;
	ds.ReadAttribute("gp-testAtt1",oaindataStr1);
	cout<< (checkResult(aindataStr1,oaindataStr1)?"\t\t\tpassed":"\t\t\tfailed")<<endl;

	cout<< " Create Int64 attribute in dataset... " ;
	ds.CreateAttribute("gp-testAttInt64",aindataInt64);
	cout<< (ds.Exist("gp-testAttInt64")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Read attribute in dataset... " ;
	ds.ReadAttribute("gp-testAttInt64",oaindataInt64);
	cout<< (checkResult(aindataInt64,oaindataInt64)?"\t\t\tpassed":"\t\t\tfailed")<<endl;

	cout<< " Create int attribute in dataset in subgroup... " ;
	ds = subgp.OpenDataset("gp-gp-testdsInt");
	ds.CreateAttribute("gp-gp-testAtt",aindata);
	cout<< (ds.Exist("gp-gp-testAtt")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Delete attribute in dataset in subgroup... " ;
	ds.DeleteAttribute("gp-gp-testAtt");
	cout<< (!ds.Exist("gp-gp-testAtt")?"\t\t\tpassed":"\t\t\tfailed")<<endl;

	cout<< " Delete subgroup gp-gp-gp-testGroup1... " ;
	HDF5Group subsubgp = subgp.CreateGroup("gp-gp-gp-testGroup1");
	subgp.DeleteGroup("gp-gp-gp-testGroup1");
	cout<< (!subgp.Exist("gp-gp-gp-testGroup1")?"\t\t\tpassed":"\t\t\tfailed")<<endl;

	cout<< " Open Data From /testGroup1/gp-gp-testGroup1/gp-gp-testdsInt... " ;
    HDF5Dataset ds1 = hd0.OpenDatasetByFullPath("/testGroup1/gp-gp-testGroup1/gp-gp-testdsInt");
	cout << endl;
	cout<< " Read Data From /testGroup1/gp-gp-testGroup1/gp-gp-testdsInt... " ;
    hd0.ReadDataByFullPath("/testGroup1/gp-gp-testGroup1/gp-gp-testdsInt",oindata);
	cout<< (checkResult(indata,oindata)?"\t\t\tpassed":"\t\t\tfailed")<<endl;

	cout<< " Read Data From testdsChar... " ;
    hd0.ReadDataByFullPath("/testdsChar",ochardata);
	cout<< (checkResult(chardata,ochardata)?"\t\t\tpassed":"\t\t\tfailed")<<endl;
    hd0.ReadDataByFullPath("/testdsChar",rIndex,ROWSR,ochardata);
	cout<< (checkResult(chardata,ochardata,rIndex,ROWSR)?"\t\t\tpassed":"\t\t\tfailed")<<endl;

	cout<< " Write Compound Data ... " <<endl;
	HDF5CompoundType ct;
	vector<string> vstrdata;strdataR.ToVector(vstrdata);
	vector<int> vintdata;indataR.ToVector(vintdata);
	vector<double> vdoubledata;doubledataR.ToVector(vdoubledata);
	ct.AddColumn("b",vstrdata);
	ct.AddColumn("c",vintdata);
	ct.AddColumn("a",vdoubledata);
	ct.AddColumn("aa",vdoubledata);
	ct.AddColumn("bb",vstrdata);
	hd0.WriteDataByFullPath("/compoundgp/compound",ct,9);
	hd0.WriteDataByFullPath("/compoundgp/compound",2,2,ct);
	
	cout<< " Read Compound Data ... " <<endl;
	hd0.WriteDataByFullPath("/compound",ct);
	HDF5CompoundType cto;
	hd0.ReadData("/compound",cto);
	cout<< (ct==cto?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	}

	hd0.DeleteData("testGroup0", "testdsInt");
	hd0.WriteDataByFullPath("testGroup0/testdsInt", indata);

	cout<< " Check Exist testGroup1/gp-gp-testGroup1/gp-gp-testdsInt... " ;
	cout<< (hd0.FullPathExist("/testGroup1/gp-gp-testGroup1/gp-gp-testdsInt")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Check Exist From testGroup1/gp-gp-testGroup11/gp-gp-testdsInt... " ;
	cout<< (hd0.FullPathExist("/testGroup1/gp-gp-testGroup11/gp-gp-testdsInt")?"\t\t\tfailed":"\t\t\tpassed")<<endl;

	cout<< " Check Exist for testdsChar... " ;
	cout<< (hd0.FullPathExist("/testdsChar")?"\t\t\tpassed":"\t\t\tfailed")<<endl;
	cout<< " Check Exist for testdsChar11... " ;
	cout<< (hd0.FullPathExist("/testdsChar11")?"\t\t\tfailed":"\t\t\tpassed")<<endl;
	cout<< " Check Exist for nonexistent name... " ;
	cout<< (hd0.FullPathExist("")?"\t\t\tfailed":"\t\t\tpassed")<<endl;

	cout<< " AppendData by rows Int... " <<endl;
	Matrix<int> indataA(ROWSR*2,COLS);
	for(i=0;i<indataR.Size(); i++)
	{ indataA[i]=indataR[i]; indataA[i+ROWSR*COLS]=indataR[i];} 
	indataA.Print(cout); cout<<endl;
	hd0.ReadData("testdsInt",oindata); 
	oindata.Print(cout);cout<<endl;
	hd0.WriteData("testdsInt",rIndex,ROWSR*2,indataA,0);
	hd0.ReadData("testdsInt",oindata); 
	oindata.Print(cout);cout<<endl;
	hd0.ReadData("testdsInt",rIndex,ROWSR*2,oindata); 
	oindata.Print(cout);cout<<endl;
	cout<< (checkResult(indataA,oindata)?"\t\t\tpassed":"\t\t\tfailed") <<endl;
	
	cout<< " AppendData by rows char* ... " <<endl;
	Matrix<char*> strdata1A(ROWS,COLS); 
	for(i=0;i<strdata1R.Size(); i++)
	{ strdata1A[i]=strdata1R[i]; strdata1A[i+ROWSR*COLS]=strdata1R[i];} 
	strdata1A.Print(cout); cout<<endl;
	size_t row = hd0.OpenDataset("testdsStr").NumberOfRows();
	hd0.WriteData("testdsStr",row,ROWSR*2,strdata1A);
	hd0.ReadData("testdsStr",row,ROWSR*2,ostrdata1); 
	ostrdata1.Print(cout);cout<<endl;
	cout<< (checkResult(strdata1A,ostrdata1)?"\t\t\tpassed":"\t\t\tfailed") <<endl;

	gpnames=hd0.GetGroupNamesFullPath();
	cout << "all groups" << endl;
	for(i=0; i<gpnames.size(); i++)
		cout << gpnames[i] << endl;
	dsnames=hd0.GetDatasetNamesFullPath();
	cout << endl<< "all datasets" << endl;
	for(i=0; i<dsnames.size(); i++)
		cout << dsnames[i] << endl;

	attnames=hd0.GetAttributeNamesFullPath();
	cout << endl<< "all attributes" << endl;
	for(i=0; i<attnames.size(); i++)
		cout << attnames[i] << endl;
	
	cout << hd0.ToString() << endl;

}


int main(int argc, char* argv[])
{
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
	if (0) {
#define FILE          "SDScompound.h5"
#define DATASETNAME   "ArrayOfStructures"
#define LENGTH        10
#define RANK          1
#define COLS          3

/* First structure  and dataset*/
	vector<int>    av;
	vector<string>  bv;
	vector<double> cv; 
    typedef struct s1_t {
		int a;
		float b;
		double c;
    } s1_t;
    s1_t       s1[LENGTH];
    hid_t      s1_tid;     /* File datatype identifier */

  
      int        i;
    hid_t      file, dataset, space; /* Handles */
    herr_t     status;
    hsize_t    dim[1] = {LENGTH};   /* Dataspace dimensions */


    /*
     * Initialize the data
     */
    for (i = 0; i< LENGTH; i++) {
        av.push_back(i);
	    ostringstream str;
		str<<i*i;
        bv.push_back(str.str());
        cv.push_back(1./(i+1));
		s1[i].a=i;
		s1[i].b=i*i;
		s1[i].c=1./(i+1);
    }

	int doublesize=sizeof(double);
	int intsize=sizeof(int);

	HDF5CompoundType ct;
	ct.AddColumn("b",bv);
	ct.AddColumn("c",cv);
	ct.AddColumn("a",av);

	hid_t hdftypes[COLS] = {0, H5T_NATIVE_DOUBLE, H5T_NATIVE_INT};

	hid_t stid = H5Tcopy(H5T_C_S1);
	size_t maxlen = 0;
	for (int i=0; i< bv.size();i++)   
		if(bv[i].size()>maxlen)
			maxlen=bv[i].size();
	H5Tset_size(stid,maxlen+1);
	hdftypes[0]=stid;
	//H5Tset_size(stid, H5T_VARIABLE );

	size_t offsets[COLS];
	size_t size=0;
	size_t count=0;
	int DOUBLEsize = H5Tget_size(H5T_NATIVE_DOUBLE);
	int INTsize = H5Tget_size(H5T_NATIVE_INT);

	//offsets[count]=align (size, 8);	hdftypes[count] = stid;size +=H5Tget_size(hdftypes[count++]); 
	offsets[count]=align (size, H5Tget_size (hdftypes[count])); size +=H5Tget_size(hdftypes[count++]); 
	count=1;
	offsets[count]=align (size, H5Tget_size (hdftypes[count])); size +=H5Tget_size(hdftypes[count++]); 
	offsets[count]=align (size, H5Tget_size (hdftypes[count])); size +=H5Tget_size(hdftypes[count++]); 
	size = align (size, H5Tget_size (hdftypes[0]));

	/*
     * Create the data space.
     */
    space = H5Screate_simple(RANK, dim, NULL);

    /*
     * Create the file.
     */
    file = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    /*
     * Create the memory datatype. 
     */
    s1_tid = H5Tcreate (H5T_COMPOUND, size);
    //H5Tinsert(s1_tid, "a_name", HOFFSET(s1_t, a), H5T_NATIVE_INT);
    //H5Tinsert(s1_tid, "c_name", HOFFSET(s1_t, c), H5T_NATIVE_DOUBLE);
    //H5Tinsert(s1_tid, "b_name", HOFFSET(s1_t, b), H5T_NATIVE_FLOAT);
	count=0;
    H5Tinsert(s1_tid, "b_name", offsets[count], hdftypes[count++]);
    H5Tinsert(s1_tid, "a_name", offsets[count], hdftypes[count++]);
    H5Tinsert(s1_tid, "c_name", offsets[count], hdftypes[count++]);

	if (H5Tpack (s1_tid) < 0)
	  assert ("Unable to pack type");

	if (H5Tlock (s1_tid) < 0)
	  assert( "Unable to lock type");
    /* 
     * Create the dataset.
     */
    dataset = H5Dcreate(file, DATASETNAME, s1_tid, space, H5P_DEFAULT);

    /*
     * Wtite data to the dataset; 
     */
    //status = H5Dwrite(dataset, s1_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, s1);

	{
				unsigned ri,pos;
				unsigned colcount=COLS;
				unsigned rowcount=LENGTH;
				//unsigned char buf[LENGTH][15];
				unsigned char* buf = new unsigned char[LENGTH*size];
				vector<HDF5DataType::DataType> types;
				ct.GetColumnTypes(types);

				for (ri = 0; ri < rowcount; ri++)
					for (pos = 0; pos < colcount; pos++)
					{
						HDF5DataType::DataType type = types[pos];
						//void *ptr = &buf[ri][offsets[pos]];
						void *ptr = &buf[(ri*size)+offsets[pos]];

						switch (type)
						{
						case HDF5DataType::DOUBLE:{
							vector<double> data;
							ct.GetDoubleColumn(pos,data);
							memcpy (ptr, &(data[ri]), sizeof (double));
							//unsigned char *p = &buf[ri][offsets[pos]];
							//memcpy (p, &(data[ri]), sizeof (double));
							break;}
						case HDF5DataType::INT:{
							vector<int> data;
							ct.GetIntColumn(pos,data);
							memcpy (ptr, &(data[ri]), sizeof (int));
							//unsigned char *p = &buf[ri][offsets[pos]];
							//memcpy (p, &(data[ri]), sizeof (int));
							break;}
						case HDF5DataType::STRING:
							{
								vector<string> data;
								ct.GetStringColumn(pos,data);

								memset (ptr, 0, H5Tget_size (hdftypes[pos]));
								strcpy ((char *)ptr, (data[ri]).c_str());

								//unsigned char *p = &buf[ri][offsets[pos]];
								//memset (ptr, 0, 2);//H5Tget_size (hdftypes[pos]));
								//strcpy ((char *)p, (data[ri]).c_str());

							}
							break;
						default:
							abort ();
						}
					}
					if (H5Dwrite (dataset,
						s1_tid,
						space,
						space,
						H5P_DEFAULT,
						buf) < 0)
						assert("Unable to write dataframe");

					delete [] buf;
			}


    /*
     * Release resources
     */
    H5Tclose(s1_tid);
    H5Sclose(space);
    H5Dclose(dataset);
    H5Fclose(file);
	}
	////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

if(1)
{
	#define FILE          "SDScompound.h5"
#define DATASETNAME   "ArrayOfStructures"
#define LENGTH        10
#define RANK          1
#define COLS          3

	
}
	readFile();
	string filename="";
	testDA(filename);
	filename="D:/Wilson/src/Projects/BAT/InHouseTools/HDF5/HDF5/Kidneycortex_Female_W10.h5";
	testDA(filename);


	return 0;
}

