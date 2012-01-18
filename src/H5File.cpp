#include <rHDF5.h>

using namespace Rcpp ;

#ifndef H5_NO_NAMESPACE
	using namespace H5;
#endif

RCPP_MODULE(h5file){
	class_<H5File>( "H5File" ) 

	.constructor()
	
//	.method( "openFile", &H5File::openFile )
	.method( "close", &H5File::close )
	.method( "flush", &H5File::flush )
//	.method( "getAccessPlist", &H5File::getAccessPlist )
//	.method( "getCreatePlist", &H5File::getCreatePlist )
	.method( "getFileName", &H5File::getFileName )
	.method( "getFileSize", &H5File::getFileSize )
	.method( "getFreeSpace", &H5File::getFreeSpace )
///	.method( "getObjCount", &H5File::getObjCount )
///	.method( "getObjIDs", &H5File::getObjIDs )
	.method( "getObjType", &H5File::getObjType )
//	.method( "getRegion", &H5File::getRegion )
//	.method( "getVFDHandle", &H5File::getVFDHandle )
//	.method( "getVFDHandle", &H5File::getVFDHandle )
	.method( "reOpen", &H5File::reOpen )
	.method( "reopen", &H5File::reopen )
//	.method( "reference", &H5File::reference  )
	.method( "fromClass", &H5File::fromClass )
	.method( "throwException", &H5File::throwException  )
	.method( "getLocId", &H5File::getLocId )
	.method( "getId", &H5File::getId )
//	.method( "isHdf5", &H5File::isHdf5 )

	;
}
