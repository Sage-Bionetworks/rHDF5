#include <Rcpp.h>
#include <hdf5.h>

RCPP_MODULE(H5I){
        using namespace Rcpp ;
	function("H5Iget_file_id" , &H5Iget_file_id , "Retrieves an identifier for the file containing the specified object. ") ;
////	function("H5Iget_name" , &H5Iget_name , "Retrieves a name of an object based on the object identifier. ") ;
	function("H5Iget_ref" , &H5Iget_ref , "Retrieves the reference count for an object. ") ;
///	function("H5Iget_type" , &H5Iget_type , "Retrieves the type of an object. ") ;
///	function("H5Iget_type_ref" , &H5Iget_type_ref , "Retrieves the reference count on an ID type. ") ;
	function("H5Iinc_ref" , &H5Iinc_ref , "Increments the reference count for an object. ") ;
///	function("H5Iinc_type_ref" , &H5Iinc_type_ref , "Increments the reference count on an ID type. ") ;
	function("H5Iis_valid" , &H5Iis_valid , "Determines whether an identifier is valid. ") ;
///	function("H5Inmembers" , &H5Inmembers , "Returns the number of identifiers in a given identifier type. ") ;
///	function("H5Iobject_verify" , &H5Iobject_verify , "Returns the object referenced by id. ") ;
///	function("H5Iregister" , &H5Iregister , "Creates and returns a new ID. ") ;
///	function("H5Iregister_type" , &H5Iregister_type , "Creates and returns a new ID type. ") ;
///	function("H5Iremove_verify" , &H5Iremove_verify , "Removes an ID from internal storage. ") ;
///	function("H5Isearch" , &H5Isearch , "Finds the memory referred to by an ID within the given ID type such that some criterion is satisfied. ") ;
///	function("H5Itype_exists" , &H5Itype_exists , "Determines whether an identifier type is registered. ") ;
}
