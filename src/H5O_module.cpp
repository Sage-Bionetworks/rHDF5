#include <Rcpp.h>
#include <hdf5.h>

RCPP_MODULE(H5O){
        using namespace Rcpp ;

        function("H5Oclose" , &H5Oclose , "Closes an object in an HDF5 file. ") ;
        function("H5Ocopy" , &H5Ocopy , "Copies an object in an HDF5 file. ") ;
        function("H5Odecr_refcount" , &H5Odecr_refcount , "Decrements an object reference count. ") ;
////	function("H5Oget_comment" , &H5Oget_comment , "Retrieves comment for specified object. ") ;
////	function("H5Oget_comment_by_name" , &H5Oget_comment_by_name , "Retrieves comment for specified object. ") ;
///	function("H5Oget_info" , &H5Oget_info , "Retrieves the metadata for an object specified by an identifier. ") ;
///	function("H5Oget_info_by_idx" , &H5Oget_info_by_idx , "Retrieves the metadata for an object, identifying the object by an index position. ") ;
///	function("H5Oget_info_by_name" , &H5Oget_info_by_name , "Retrieves the metadata for an object, identifying the object by location and relative name. ") ;
	function("H5Oincr_refcount" , &H5Oincr_refcount , "Increments an object reference count. ") ;
	function("H5Olink" , &H5Olink , "Creates a hard link to an object in an HDF5 file. ") ;
	function("H5Oopen" , &H5Oopen , "Opens an object in an HDF5 file by location identifier and path name. ") ;
	
////	function("H5Oopen_by_addr" , &H5Oopen_by_addr , "Opens an object using its address within an HDF5 file. ") ;
///	function("H5Oopen_by_idx" , &H5Oopen_by_idx , "Open the nth object in a group. ") ;
	function("H5Oset_comment" , &H5Oset_comment , "Sets comment for specified object. ") ;
	function("H5Oset_comment_by_name" , &H5Oset_comment_by_name , "Sets comment for specified object. ") ;
///	function("H5Ovisit" , &H5Ovisit , "Recursively visits all objects accessible from a specified object. ") ;
///	function("H5Ovisit_by_name" , &H5Ovisit_by_name , "Recursively visits all objects starting from a specified object. ") ;
}
