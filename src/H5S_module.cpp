#include <rHDF5.h>

RCPP_MODULE(H5S){
        using namespace Rcpp ;

	function("H5Sclose" , &H5Sclose , "Releases and terminates access to a dataspace. ") ;
	function("H5Scopy" , &H5Scopy , "Creates an exact copy of a dataspace. ") ;
///	function("H5Screate" , &H5Screate , "Creates a new dataspace of a specified type. ") ;
////	function("H5Screate_simple" , &H5Screate_simple , "Creates a new simple dataspace and opens it for access. ") ; ////hsize_t*
	function("H5Sdecode" , &H5Sdecode , "Decode a binary object description of data space and return a new object handle. ") ;
////	function("H5Sencode" , &H5Sencode , "Encode a data space object description into a binary buffer. ") ;
	function("H5Sextent_equal" , &H5Sextent_equal , "Determines whether two dataspace extents are equal. ") ;
////	function("H5Sget_select_bounds" , &H5Sget_select_bounds , "Gets the bounding box containing the current selection. ") ;
////	function("H5Sget_select_elem_npoints" , &H5Sget_select_elem_npoints , "Gets the number of element points in the current selection. ") ;
////	function("H5Sget_select_elem_pointlist" , &H5Sget_select_elem_pointlist , "Gets the list of element points currently selected. ") ;
////	function("H5Sget_select_hyper_blocklist" , &H5Sget_select_hyper_blocklist , "Gets the list of hyperslab blocks currently selected. ") ;
////	function("H5Sget_select_hyper_nblocks" , &H5Sget_select_hyper_nblocks , "Get number of hyperslab blocks. ") ;
////	function("H5Sget_select_npoints" , &H5Sget_select_npoints , "Determines the number of elements in a dataspace selection. ") ;
///	function("H5Sget_select_type" , &H5Sget_select_type , "Determines the type of the dataspace selection. ") ;
////	function("H5Sget_simple_extent_dims" , &H5Sget_simple_extent_dims , "Retrieves dataspace dimension size and maximum size. ") ; ////hsize_t*
	function("H4Sget_simple_extent_ndims" , &H5Sget_simple_extent_ndims , "Determines the dimensionality of a dataspace. ") ;
////	function("H5Sget_simple_extent_npoints" , &H5Sget_simple_extent_npoints , "Determines the number of elements in a dataspace. ") ;
///	function("H5Sget_simple_extent_type" , &H5Sget_simple_extent_type , "Determines the current class of a dataspace. ") ;
	
	function("H5Sis_simple" , &H5Sis_simple , "Determines whether a dataspace is a simple dataspace. ") ;
////	function("H5Soffset_simple" , &H5Soffset_simple , "Sets the offset of a simple dataspace. ") ;
	function("H5Sselect_all" , &H5Sselect_all , "Selects an entire dataspace. ") ;
///	function("H5Sselect_elements" , &H5Sselect_elements , "Selects array elements to be included in the selection for a dataspace. ") ;
///	function("H5Sselect_hyperslab" , &H5Sselect_hyperslab , "Selects a hyperslab region to add to the current selected region. ") ;
	function("H5Sselect_none" , &H5Sselect_none , "Resets the selection region to include no elements. ") ;
	function("H5Sselect_valid" , &H5Sselect_valid , "Verifies that the selection is within the extent of the dataspace. ") ;
	
	function("H5Sset_extent_none" , &H5Sset_extent_none , "Removes the extent from a dataspace. ") ;
////	function("H5Sset_extent_simple" , &H5Sset_extent_simple , "Sets or resets the size of an existing dataspace. ") ; ////const hsize_t *

}
