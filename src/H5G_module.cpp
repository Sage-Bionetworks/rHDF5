#include <rHDF5.h>

RCPP_MODULE(H5G){
        using namespace Rcpp ;

	//
        //H5G: Group Interface
        //

	function( "H5Gclose" , &H5Gclose  , "Closes the specified group. " ) ;
        function( "H5Gcreate" , &H5Gcreate  , "Creates a new empty group and links it to a location in the file. " ) ;
        function( "H5Gcreate1" , &H5Gcreate1  , "Creates a new empty group and links it to a location in the file. " ) ;
        function( "H5Gcreate2" , &H5Gcreate2  , "Creates a new empty group and links it into the file. " ) ;
        function( "H5Gcreate_anon" , &H5Gcreate_anon  , "Creates a new empty group without linking it into the file structure. " ) ;
////    function( "H5Gget_comment" , &H5Gget_comment  , "Retrieves comment for specified object. " ) ;
        function( "H5Gget_create_plist" , &H5Gget_create_plist  , "Gets a group creation property list identifier. " ) ;
////    function( "H5Gget_info" , &H5Gget_info  , "Retrieves information about a group. " ) ;
////    function( "H5Gget_info_by_idx" , &H5Gget_info_by_idx  , "Retrieves information about a group, according to the group’s position within an index. " ) ;
////    function( "H5Gget_info_by_name" , &H5Gget_info_by_name  , "Retrieves information about a group. " ) ;
////    function( "H5Gget_linkval" , &H5Gget_linkval  , "Returns the name of the object that the symbolic link points to. " ) ;
////    function( "H5Gget_num_objs" , &H5Gget_num_objs  , "Returns number of objects in the group specified by its identifier. " ) ;
////    function( "H5Gget_objinfo" , &H5Gget_objinfo  , "Returns information about an object. " ) ;
////    function( "H5Gget_objname_by_idx" , &H5Gget_objname_by_idx , "Returns a name of an object specified by an index. " ) ;
////    function( "H5Gget_objtype_by_idx" , &H5Gget_objtype_by_idx  , "Returns the type of an object specified by an index. " ) ;
////    function( "H5Giterate" , &H5Giterate  , "Iterates an operation over the entries of a group. " ) ;
////    function( "H5Glink" , &H5Glink  , "Creates a link of the specified type from new_name to current_name. " ) ;
////    function( "H5Glink2" , &H5Glink2  , "This function is deprecated in favor of the functions H5Lcreate_hard and H5Lcreate_soft. " ) ;
        function( "H5Gmove" , &H5Gmove  , "Renames an object within an HDF5 file. " ) ;
        function( "H5Gopen" , &H5Gopen  , "Opens an existing group in a file. " ) ;
        function( "H5Gopen2" , &H5Gopen2  , "Opens an existing group with a group access property list. " ) ;
}
