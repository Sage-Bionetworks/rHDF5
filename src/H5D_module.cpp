#include <rHDF5.h>

RCPP_MODULE(H5D){
        using namespace Rcpp ;

	//
        //H5D: Dataset Interface
        //

	function( "H5Dclose", &H5Dclose , "Closes the specified dataset. " ) ;
	function( "H5Dcreate", &H5Dcreate , "Creates a new dataset and links it to a location in the file. " ) ;
	function( "H5Dcreate2", &H5Dcreate2 , "Creates a new dataset and links it into the file. " ) ;
	function( "H5Dcreate_anon", &H5Dcreate_anon , "Creates a dataset in a file without linking it into the file structure. " ) ;
////	function( "H5Dextend", &H5Dextend , "Extends a dataset. " ) ;
	function( "H5Dfill", &H5Dfill , "Fills dataspace elements with a fill value in a memory buffer. " ) ;
	function( "H5Dget_access_plist", &H5Dget_access_plist , "Returns the dataset access property list associated with a dataset. " ) ;
	function( "H5Dget_create_plist", &H5Dget_create_plist , "Returns an identifier for a copy of the dataset creation property list for a dataset. " ) ;
////	function( "H5Dget_offset", &H5Dget_offset , "Returns dataset address in file. " ) ;
	function( "H5Dget_space", &H5Dget_space , "Returns an identifier for a copy of the dataspace for a dataset. " ) ;
///	function( "H5Dget_space_status", &H5Dget_space_status , "Determines whether space has been allocated for a dataset. " ) ;
////	function( "H5Dget_storage_size", &H5Dget_storage_size , "Returns the amount of storage allocated for a dataset. " ) ;
	function( "H5Dget_type", &H5Dget_type , "Returns an identifier for a copy of the datatype for a dataset. " ) ;
///	function( "H5Diterate", &H5Diterate , "Iterates over all selected elements in a dataspace. " ) ;
	function( "H5Dopen", &H5Dopen , "Opens an existing dataset. " ) ;
	function( "H5Dopen2", &H5Dopen2 , "Opens an existing dataset. " ) ;
	function( "H5Dread", &H5Dread , "Reads raw data from a dataset into a buffer. " ) ;
////	function( "H5Dset_extent", &H5Dset_extent , "Changes the sizes of a dataset’s dimensions. " ) ;///const hzize_t
////	function( "H5Dvlen_get_buf_size", &H5Dvlen_get_buf_size , "Determines the number of bytes required to store VL data. " ) ;///hsize_t ptr
	function( "H5Dvlen_reclaim", &H5Dvlen_reclaim , "Reclaims VL datatype memory buffers. " ) ;
	function( "H5Dwrite", &H5Dwrite , "Writes raw data from a buffer to a dataset. " ) ;
}
