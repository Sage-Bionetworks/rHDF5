#include <Rcpp.h>
#include <hdf5.h>

RCPP_MODULE(H5A){
        using namespace Rcpp ;

	//
        // H5A: Attribute Interface
        //

	function( "H5Acreate" , &H5Acreate , "Creates an attribute attached to a specified object. " ) ;
        function( "H5Acreate2" , &H5Acreate2 , "Creates an attribute attached to a specified object. " ) ;
        function( "H5Acreate_by_name" , &H5Acreate_by_name , "Creates an attribute attached to a specified object. " ) ;
        function( "H5Adelete" , &H5Adelete , "Deletes an attribute from a specified location. " ) ;
////	function( "H5Adelete_by_idx" , &H5Adelete_by_idx , "Deletes an attribute from an object according to index order. " ) ;
        function( "H5Adelete_by_name" , &H5Adelete_by_name , "Removes an attribute from a specified location. " ) ;
        function( "H5Aexists" , &H5Aexists , "Determines whether an attribute with a given name exists on an object. " ) ;
        function( "H5Aexists_by_name" , &H5Aexists_by_name , "Determines whether an attribute with a given name exists on an object. " ) ;
        function( "H5Aget_create_plist" , &H5Aget_create_plist , "Gets an attribute creation property list identifier. " ) ;
////    function( "H5Aget_info" , &H5Aget_info , "Retrieves attribute information, by attribute identifier. " ) ;
////    function( "H5Aget_info_by_idx" , &H5Aget_info_by_idx , "Retrieves attribute information, by attribute index position. " ) ;
////    function( "H5Aget_info_by_name" , &H5Aget_info_by_name , "Retrieves attribute information, by attribute name. " ) ;
////    function( "H5Aget_name" , &H5Aget_name , "Gets an attribute name. " ) ;
////    function( "H5Aget_name_by_idx" , &H5Aget_name_by_idx , "Gets an attribute name, by attribute index position. " ) ;
        function( "H5Aget_space" , &H5Aget_space , "Gets a copy of the dataspace for an attribute. " ) ;
////    function( "H5Aget_storage_size" , &H5Aget_storage_size , "Returns the amount of storage required for an attribute. " ) ;
        function( "H5Aget_type" , &H5Aget_type , "Gets an attribute datatype. " ) ;
////    function( "H5Aiterate" , &H5Aiterate , "Calls a user’s function for each attribute on an object. " ) ;
////    function( "H5Aiterate1" , &H5Aiterate1 , "Calls a user’s function for each attribute on an object. " ) ;
////    function( "H5Aiterate2" , &H5Aiterate2 , "Calls user-defined function for each attribute on an object. " ) ;
////    function( "H5Aiterate_by_name" , &H5Aiterate_by_name , "Calls user-defined function for each attribute on an object. " ) ;
        function( "H5Aopen" , &H5Aopen , "Opens an attribute for an object specified by object identifier and attribute name. " ) ;
////    function( "H5Aopen_by_idx" , &H5Aopen_by_idx , "Opens an attribute for an object specified by object identifier and index. " ) ;
        function( "H5Aopen_by_name" , &H5Aopen_by_name , "Opens an attribute for an object by object name and attribute name. " ) ;
        function( "H5Aread" , &H5Aread , "Reads an attribute. " ) ;
        function( "H5Arename" , &H5Arename , "Renames an attribute. " ) ;
        function( "H5Arename_by_name" , &H5Arename_by_name , "Renames an attribute. " ) ;
        function( "H5Awrite" , &H5Awrite , "Writes data to an attribute. " ) ;
}

