#include <rHDF5.h>

RCPP_MODULE(H5P){
        using namespace Rcpp ;

	function("H5Pall_filters_avail" , &H5Pall_filters_avail , "Verifies that all required filters are available. ") ;
	function("H5Pclose" , &H5Pclose , "Terminates access to a property list. ") ;
	function("H5Pclose_class" , &H5Pclose_class , "Closes an existing property list class. ") ;
	function("H5Pcopy" , &H5Pcopy , "Copies an existing property list to create a new property list. ") ;
	function("H5Pcopy_prop" , &H5Pcopy_prop , "Copies a property from one list or class to another ") ;
	function("H5Pcreate" , &H5Pcreate , "Creates a new property as an instance of a property list class. ") ;
///	function("H5Pcreate_class" , &H5Pcreate_class , "Creates a new property list class. ") ;
	function("H5Pequal" , &H5Pequal , "Compares two property lists or classes for equality. ") ;
	function("H5Pexist" , &H5Pexist , "Queries whether a property name exists in a property list or class. ") ;
///	function("H5Pfill_value_defined" , &H5Pfill_value_defined , "Determines whether fill value is defined. ") ;
	
	function("H5Pget" , &H5Pget , "Queries the value of a property. ") ;
//	function("H5Pget_alignment" , &H5Pget_alignment , "Retrieves the current settings for alignment properties from a file access property list. ") ;
///	function("H5Pget_alloc_time" , &H5Pget_alloc_time , "Retrieves the timing for storage space allocation. ") ;
//	function("H5Pget_attr_creation_order" , &H5Pget_attr_creation_order , "Retrieves tracking and indexing settings for attribute creation order ") ;
//	function("H5Pget_attr_phase_change" , &H5Pget_attr_phase_change , "Retrieves attribute storage phase change thresholds. ") ;
//	function("H5Pget_buffer" , &H5Pget_buffer , "Reads buffer settings. ") ;
//	function("H5Pget_cache" , &H5Pget_cache , "Queries the raw data chunk cache parameters. ") ;
///	function("H5Pget_char_encoding" , &H5Pget_char_encoding , "Retrieves the character encoding used to create a string. ") ;
////	function("H5Pget_chunk" , &H5Pget_chunk , "Retrieves the size of chunks for the raw data of a chunked layout dataset. ") ;
	function("H5Pset_alignment" , &H5Pset_alignment , "Sets alignment properties of a file access property list. ") ;
	//function("" , & , " ") ;
	//function("" , & , " ") ;
	//function("" , & , " ") ;
	//function("" , & , " ") ;

        //function("" , & , " ") ;

//////
//TODO: finish writing property methods
/////

}
