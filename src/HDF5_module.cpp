#include <Rcpp.h>
#include <hdf5.h>

RCPP_MODULE(HDF5){
	using namespace Rcpp ;
	
	// General Library Functions
	function( "H5open" , &H5open , "Initializes the HDF5 library. " ) ;
	function( "H5close" , &H5close , "Flushes all data to disk, closes all open identifiers, and cleans up memory. " ) ;
	function( "H5set_free_list_limits" , &H5set_free_list_limits , "Sets free-list size limits. " ) ;
	function( "H5garbage_collect" , &H5garbage_collect , "Garbage collects on all free-lists of all types. ") ;
	function( "H5dont_atexit" , &H5dont_atexit , "Instructs library not to install atexit cleanup routine. " ) ;
////	function( "H5get_libversion" , &H5get_libversion , "Returns the HDF library release number. " ) ;
	function( "H5check_version" , &H5check_version , "Verifies that HDF5 library versions are consistent." ) ;
////	function( "H5_VERSION_GE" , &H5_VERSION_GE , "Determines whether the version of the library being used is greater than or equal to the specified version. " ) ;
////	function( "H5_VERSION_LE" , &H5_VERSION_LE , "Determines whether the version of the library being used is less than or equal to the specified version. " ) ;
        
}                     


