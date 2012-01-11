#include <Rcpp.h>
#include <hdf5.h>

RCPP_MODULE(H5F){
        using namespace Rcpp ;

	//
        //H5F: File Interface
        //

	function( "H5Fclear_elink_file_cache" , &H5Fclear_elink_file_cache  , "Clears the external link open file cache. " ) ;
        function( "H5Fclose" , &H5Fclose  , "Terminates access to an HDF5 file. " ) ;
        function( "H5Fcreate" , &H5Fcreate  , "Creates an HDF5 file. " ) ;
////    function( "H5Fflush" , &H5Fflush  , "Flushes all buffers associated with a file to disk. " ) ;
        function( "H5Fget_access_plist" , &H5Fget_access_plist  , "Returns a file access property list identifier. " ) ;
        function( "H5Fget_create_plist" , &H5Fget_create_plist  , "Returns a file creation property list identifier. " ) ;
////    function( "H5Fget_filesize(" , &H5Fget_filesize , "Returns the size of an HDF5 file " ) ;
////    function( "H5Fget_freespace" , &H5Fget_freespace  , "Returns the amount of free space in a file. " ) ;
////    function( "H5Fget_info" , &H5Fget_info  , "Returns global information for a file. " ) ;
////    function( "H5Fget_intent" , &H5Fget_intent  , "Determines the read/write or read-only status of a file. " ) ;
////    function( "H5Fget_mdc_config" , &H5Fget_mdc_config  , "Obtain current metadata cache configuration for target file. " ) ;
////    function( "H5Fget_mdc_hit_rate" , &H5Fget_mdc_hit_rate  , "Obtain target file's metadata cache hit rate. " ) ;
////    function( "H5Fget_mdc_size" , &H5Fget_mdc_size  , "Obtain current metadata cache size data for specified file. " ) ;
////    function( "H5Fget_name" , &H5Fget_name  , "Retrieves name of file to which object belongs. " ) ;
        function( "H5Fget_obj_count" , &H5Fget_obj_count  , "Returns the number of open object identifiers for an open file. " ) ;
////    function( "H5Fget_obj_ids" , &H5Fget_obj_ids  , "Returns a list of open object identifiers. " ) ;
        function( "H5Fmount" , &H5Fmount  , "Mounts a file. " ) ;
        function( "H5Fopen" , &H5Fopen  , "Opens an existing HDF5 file. " ) ;
        function( "H5Freopen" , &H5Freopen  , "Returns a new identifier for a previously-opened HDF5 file. " ) ;
        function( "H5Freset_mdc_hit_rate_stats" , &H5Freset_mdc_hit_rate_stats  , "Reset hit rate statistics counters for the target file. " ) ;
////    function( "H5Fset_mdc_config" , &H5Fset_mdc_config  , "Attempt to configure metadata cache of target file. " ) ;
        function( "H5Funmount" , &H5Funmount  , "Unmounts a file. " ) ;
}
