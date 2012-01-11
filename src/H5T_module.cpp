#include <Rcpp.h>
#include <hdf5.h>

RCPP_MODULE(H5T){
        using namespace Rcpp ;
	
////	function("H5Tarray_create" , &H5Tarray_create , "Creates an array datatype object. ") ;
////	function("H5Tarray_create2" , &H5Tarray_create2 , "Creates an array datatype object. ") ;
	function("H5Tclose" , &H5Tclose , "Releases a datatype. ") ;
	function("H5Tcommit" , &H5Tcommit , "Commits a transient datatype, linking it into the file and creating a new named datatype. ") ;
	function("H5Tcommit1" , &H5Tcommit1 , "Commits a transient datatype to a file, creating a new named datatype. ") ;
	function("H5Tcommit_anon" , &H5Tcommit_anon , "Commits a transient datatype to a file, creating a new named datatype, but does not link it into the file structure. ") ;
	function("H5Tcommitted" , &H5Tcommitted , "Determines whether a datatype is a named type or a transient type. ") ;
	function("H5Tcompiler_conv" , &H5Tcompiler_conv , "Check whether the libraryÂis default conversion is hard conversion. ") ;
	function("H5Tconvert" , &H5Tconvert , "Converts data from one specified datatype to another. ") ;
	function("H5Tcopy" , &H5Tcopy , "Copies an existing datatype. ") ;
///	function("H5Tcreate" , &H5Tcreate , "Creates a new datatype. ") ;
	function("H5Tdecode" , &H5Tdecode , "Decode a binary object description of datatype and return a new object handle. ") ;
///	function("H5Tdetect_class" , &H5Tdetect_class , "Determines whether a datatype contains any datatypes of the given datatype class. ") ;
////	function("H5Tencode" , &H5Tencode , "Encode a datatype object description into a binary buffer. ") ; 
	function("H5Tenum_create" , &H5Tenum_create , "Creates a new enumeration datatype. ") ;
	function("H5Tenum_insert" , &H5Tenum_insert , "Inserts a new enumeration datatype member. ") ;
////	function("H5Tenum_nameof" , &H5Tenum_nameof , "Returns the symbol name corresponding to a specified member of an enumeration datatype. ") ;
	function("H5Tenum_valueof" , &H5Tenum_valueof , "Returns the value corresponding to a specified member of an enumeration datatype. ") ;
	function("H5Tequal" , &H5Tequal , "Determines whether two datatype identifiers refer to the same datatype. ") ;
///	function("H5Tfind" , &H5Tfind , "Finds a conversion function. ") ;
////	function("H5Tget_array_dims" , &H5Tget_array_dims , "Retrieves sizes of array dimensions. ") ;
////	function("H5Tget_array_dims2" , &H5Tget_array_dims2 , "Retrieves sizes of array dimensions. ") ;
	function("H5Tget_array_ndims" , &H5Tget_array_ndims , "Returns the rank of an array datatype. ") ;
///	function("H5Tget_class" , &H5Tget_class , "Returns the datatype class identifier. ") ;
	function("H5Tget_create_plist" , &H5Tget_create_plist , "Returns a copy of a datatype creation property list. ") ;
///	function("H5Tget_cset" , &H5Tget_cset , "Retrieves the character set type of a string datatype. ") ;
	function("H5Tget_ebias" , &H5Tget_ebias , "Retrieves the exponent bias of a floating-point type. ") ;
////	function("H5Tget_fields" , &H5Tget_fields , "Retrieves floating point datatype bit field information. ") ;
///	function("H5Tget_inpad" , &H5Tget_inpad , "Retrieves the internal padding type for unused bits in floating-point datatypes. ") ;
////	function("H5Tget_member_class" , &H5Tget_member_class , "Returns datatype class of compound datatype member. ") ;
////	function("H5Tget_member_index(" , &H5Tget_member_index( , "Retrieves the index of a compound or enumeration datatype member. ") ;
////	function("H5Tget_member_name" , &H5Tget_member_name , "Retrieves the name of a compound or enumeration datatype member. ") ;//unsigned
//	function("H5Tget_member_offset" , &H5Tget_member_offset , "Retrieves the offset of a field of a compound datatype. ") ; //unsigned
//	function("H5Tget_member_type" , &H5Tget_member_type , "Returns the datatype of the specified member. ") ; //unsigned
//	function("H5Tget_member_value" , &H5Tget_member_value , "Returns the value of an enumeration datatype member. ") ; //unsigned
///	function("H5Tget_native_type" , &H5Tget_native_type , "Returns the native datatype of a specified datatype. ") ;
	function("H5Tget_nmembers" , &H5Tget_nmembers , "Retrieves the number of elements in a compound or enumeration datatype. ") ;
///	function("H5Tget_norm" , &H5Tget_norm , "Retrieves mantissa normalization of a floating-point datatype. ") ;
	function("H5Tget_offset" , &H5Tget_offset , "Retrieves the bit offset of the first significant bit. ") ;
///	function("H5Tget_order" , &H5Tget_order , "Returns the byte order of an atomic datatype. ") ;
///	function("H5Tget_pad" , &H5Tget_pad , "Retrieves the padding type of the least and most-significant bit padding. ") ;
	function("H5Tget_precision" , &H5Tget_precision , "Returns the precision of an atomic datatype. ") ;
///	function("H5Tget_sign" , &H5Tget_sign , "Retrieves the sign type for an integer type. ") ;
	function("H5Tget_size" , &H5Tget_size , "Returns the size of a datatype. ") ;
///	function("H5Tget_strpad" , &H5Tget_strpad , "Retrieves the storage mechanism for a string datatype. ") ;
	function("H5Tget_super" , &H5Tget_super , "Returns the base datatype from which a datatype is derived. ") ;
////	function("H5Tget_tag" , &H5Tget_tag , "Gets the tag associated with an opaque datatype. ") ;
	function("H5Tinsert" , &H5Tinsert , "Adds a new member to a compound datatype. ") ;
	function("H5Tis_variable_str" , &H5Tis_variable_str , "Determines whether datatype is a variable-length string. ") ;
	function("H5Tlock" , &H5Tlock , "Locks a datatype. ") ;
	function("H5Topen" , &H5Topen , "Opens a named datatype. ") ;
	function("H5Topen2" , &H5Topen2 , "Opens a named datatype. ") ;
	function("H5Tpack" , &H5Tpack , "Recursively removes padding from within a compound datatype. ") ;
///	function("H5Tregister" , &H5Tregister , "Registers a conversion function. ") ;
///	function("H5Tset_cset" , &H5Tset_cset , "Sets character set to be used. ") ;
	function("H5Tset_ebias" , &H5Tset_ebias , "Sets the exponent bias of a floating-point type. ") ;
	function("H5Tset_fields" , &H5Tset_fields , "Sets locations and sizes of floating point bit fields. ") ;
///	function("H5Tset_inpad" , &H5Tset_inpad , "Fills unused internal floating point bits. ") ;

////	function("H5Tset_norm" , &H5Tset_norm , "Sets the mantissa normalization of a floating-point datatype. ") ;
	function("H5Tset_offset" , &H5Tset_offset , "Sets the bit offset of the first significant bit. ") ;
///	function("H5Tset_order" , &H5Tset_order , "Sets the byte order of a datatype. ") ;
///	function("H5Tset_pad" , &H5Tset_pad , "Sets the least and most-significant bits padding types. ") ;
	function("H5Tset_precision" , &H5Tset_precision , "Sets the precision of an atomic datatype. ") ;
///	function("H5Tset_sign" , &H5Tset_sign , "Sets the sign property for an integer type ") ;
	function("H5Tset_size" , &H5Tset_size , "Sets the total size for an atomic datatype. ") ;

///	function("H5Tset_strpad" , &H5Tset_strpad , "Defines the storage mechanism for character strings. ") ;
	function("H5Tset_tag" , &H5Tset_tag , "Tags an opaque datatype. ") ;
///	function("H5Tunregister" , &H5Tunregister , "Removes a conversion function. ") ;
	function("H5Tvlen_create" , &H5Tvlen_create , "Creates a new variable-length datatype. ") ;
}
