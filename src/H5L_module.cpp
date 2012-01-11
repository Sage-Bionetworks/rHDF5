#include <Rcpp.h>
#include <hdf5.h>

RCPP_MODULE(H5L){
        using namespace Rcpp ;

	function("H5Lcopy" , &H5Lcopy , "Copies a link from one location to another. ") ;
	function("H5Lcreate_external" , &H5Lcreate_external , "Creates an external link, a soft link to an object in a different file. ") ;
	function("H5Lcreate_hard" , &H5Lcreate_hard , "Creates a hard link to an object. ") ;
	function("H5Lcreate_soft" , &H5Lcreate_soft , "Creates a soft link to an object. ") ;
///	function("H5Lcreate_ud" , &H5Lcreate_ud , "Creates a link of a user-defined type. ") ;
	function("H5Ldelete" , &H5Ldelete , "Removes a link from a group. ") ;
///	function("H5Ldelete_by_idx" , &H5Ldelete_by_idx , "Removes the nth link in a group. ") ;
	function("H5Lexists" , &H5Lexists , "Determine whether a link with the specified name exists in a group. ") ;
///	function("H5Lget_info" , &H5Lget_info , "Returns information about a link. ") ;
///	function("H5Lget_info_by_idx" , &H5Lget_info_by_idx , "Retrieves metadata for a link in a group, according to the order within a field or index. ") ;
///	function("H5Lget_name_by_idx" , &H5Lget_name_by_idx , "Retrieves name of the nth link in a group, according to the order within a specified field or index. ") ;
	function("H5Lget_val" , &H5Lget_val , "Returns the value of a symbolic link. ") ;
///	function("H5Lget_val_by_idx" , &H5Lget_val_by_idx , "Retrieves value of the nth link in a group, according to the order within an index. ") ;
///	function("H5Literate" , &H5Literate , "Iterates through links in a group ") ;
///	function("H5Literate_by_name" , &H5Literate_by_name , "Iterates through links in a group. ") ;
	function("H5Lmove" , &H5Lmove , "Renames a link within an HDF5 file. ") ;
///	function("H5Lregister" , &H5Lregister , "Registers user-defined link class or changes behavior of existing class. ") ;
////	function("H5Lunpack_elink_val" , &H5Lunpack_elink_val , "Decodes external link information. ") ;
///	function("H5Lunregister" , &H5Lunregister , "Unregisters a class of user-defined links. ") ;
///	function("H5Lvisit" , &H5Lvisit , "Recursively visits all links starting from a specified group. ") ;
///	function("H5Lvisit_by_name" , &H5Lvisit_by_name , "Recursively visits all links starting from a specified group. ") ;
}
