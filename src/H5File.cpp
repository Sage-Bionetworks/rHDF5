#include <rHDF5.h>

using namespace Rcpp ;

#ifndef H5_NO_NAMESPACE
	using namespace H5;
#endif

IntegerVector getObjIDs(unsigned types, size_t max_objs){
        IntegerVector oid_list(max_objs) ;

        H5File file ;
        file.getObjIDs( types, max_objs, oid_list.begin() ) ;

        return oid_list ;
}

ssize_t getObjCount( unsigned types ){
	H5File file ;

	return file.getObjCount( types ) ;
}

static bool isHdf5( const H5std_string &name ){

	return H5::H5File::isHdf5( name ) ;
}


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

	;

	// wrapper function for H5::H5File::getObjIDs
	function( "getObjIDs", &getObjIDs ) ;
	function( "getObjCount", &getObjCount ) ;	
	function( "isHdf5", &isHdf5 ) ;
}
