#include <rHDF5.h>
#include <H5Cpp.h>
#define EXPORT_NUMERIC double
#include <map>
#include <string>
#include <utility>

using namespace std ;
using namespace Rcpp ;

#ifndef H5_NO_NAMESPACE
	using namespace H5;
#endif

// Please note that class FileAccPropList was provided "wrap" and "as" in ../inst/include/rHDF5Forward.h
//                                                                        ../inst/include/rHDF5_FileAccPropList.h

// Helper function for getCore
// I wonder if this generates a "meaningful" R object.
std::map<string, EXPORT_NUMERIC> fileaccproplist_getCore(FileAccPropList* obj)
{
    size_t increment;
    hbool_t backing_core;
    map<string, EXPORT_NUMERIC> result;

    obj->getCore(increment, backing_core);

    result.insert( pair<string, EXPORT_NUMERIC >("increment", (EXPORT_NUMERIC) increment) );
    result.insert( pair<string, EXPORT_NUMERIC >("backing_core", (EXPORT_NUMERIC) backing_core) );
 
    return result;
}

// Helper function for setFamily.  
void fileaccproplist_setFamily(FileAccPropList* obj, hsize_t memb_size, FileAccPropList memb_plist)
{
    obj->setFamily(memb_size, memb_plist);
}

// Helper function for getFamily.
// The documentation in HDF5/c++ does not seem to match the return... 
std::map<string, EXPORT_NUMERIC> fileaccproplist_getFamily(FileAccPropList* obj)  
{
    hsize_t memb_size;
    FileAccPropList memb_plist;
    map<string, EXPORT_NUMERIC> result;

    obj->getFamily(memb_size, memb_plist);

    result.insert( pair<string, EXPORT_NUMERIC>("memb_size",  (EXPORT_NUMERIC) memb_size) );
    result.insert( pair<string, EXPORT_NUMERIC>("memb_plist", (EXPORT_NUMERIC) memb_plist.getId() ) );  //getId is how I "wrap" memb_plist, 
                                                                                                        //but I didn't want to return a SEXP.
    return result;
}

// Helper function for setSplit
void fileaccproplist_setSplit( FileAccPropList* obj, FileAccPropList meta_plist, FileAccPropList raw_plist, string meta_ext, string raw_ext )
{
    obj->setSplit(meta_plist, raw_plist, meta_ext.c_str(), raw_ext.c_str());
}

// Helper function for setMetaBlockSize
void fileaccproplist_setMetaBlockSize( FileAccPropList* obj, hsize_t block_size)
{
    obj->setMetaBlockSize(block_size);
}  

// Helper function for setLog
void fileaccproplist_setLog( FileAccPropList* obj, string logfile, unsigned flags, size_t buf_size)
{
    obj->setLog(logfile.c_str(), flags, buf_size);
}


// Helper function for setAlignment
void fileaccproplist_setAlignment( FileAccPropList* obj, hsize_t threshold, hsize_t alignment)
{
    obj->setAlignment(threshold, alignment);
}


// Helper function for getAlignment
std::map<string, EXPORT_NUMERIC> fileaccproplist_getAlignment(FileAccPropList* obj)
{
    hsize_t threshold;
    hsize_t alignment;
    map<string, EXPORT_NUMERIC> result;

    obj->getAlignment(threshold, alignment);

    result.insert( pair<string, EXPORT_NUMERIC>("threshold", (EXPORT_NUMERIC) threshold ) );
    result.insert( pair<string, EXPORT_NUMERIC>("alignment", (EXPORT_NUMERIC) alignment ) );  
                                                                             
    return result;
}

// Helper function for getCache
std::map<string, EXPORT_NUMERIC> fileaccproplist_getCache(FileAccPropList* obj)
{
    int mdc_nelmts;
    size_t rdcc_nelmts;
    size_t rdcc_nbytes;
    double rdcc_w0;
    map<string, EXPORT_NUMERIC> result;

    obj->getCache(mdc_nelmts, rdcc_nelmts, rdcc_nbytes, rdcc_w0);

    result.insert( pair<string, EXPORT_NUMERIC>("mdc_nelmts", (EXPORT_NUMERIC) mdc_nelmts ) );
    result.insert( pair<string, EXPORT_NUMERIC>("rdcc_nelmts", (EXPORT_NUMERIC) rdcc_nelmts ) );
    result.insert( pair<string, EXPORT_NUMERIC>("rdcc_nbytes", (EXPORT_NUMERIC) rdcc_nbytes ) );
    result.insert( pair<string, EXPORT_NUMERIC>("rdcc_w0", (EXPORT_NUMERIC) rdcc_w0 ) );

    return result;
}

RCPP_MODULE(fileaccproplist){
	class_<FileAccPropList>( "FileAccPropList" ) 

	.constructor()
	.constructor<const hid_t>()

	.method( "setStdio", &FileAccPropList::setStdio )
	.method( "setDriver", &FileAccPropList::setDriver )
	.method( "getDriver", &FileAccPropList::getDriver )
	.method( "setFamilyOffset", &FileAccPropList::setFamilyOffset )
	.method( "getFamilyOffset", &FileAccPropList::getFamilyOffset )
	.method( "setSec2", &FileAccPropList::setSec2 )
	.method( "setCore", &FileAccPropList::setCore )
	.method( "setSieveBufSize", &FileAccPropList::setSieveBufSize )
	.method( "getSieveBufSize", &FileAccPropList::getSieveBufSize )
	.method( "getMetaBlockSize", &FileAccPropList::getMetaBlockSize )
	.method( "setMultiType", &FileAccPropList::setMultiType )
	.method( "getMultiType", &FileAccPropList::getMultiType )
	.method( "setCache", &FileAccPropList::setCache )
	.method( "setFcloseDegree", &FileAccPropList::setFcloseDegree )
	.method( "getFcloseDegree", &FileAccPropList::getFcloseDegree )
	.method( "setGcReferences", &FileAccPropList::setGcReferences )
	.method( "getGcReferences", &FileAccPropList::getGcReferences )
	.method( "fromClass", &FileAccPropList::fromClass )

// Methods implemented through helper functions.
        .method("getCore", &fileaccproplist_getCore)
        .method("setFamily", &fileaccproplist_setFamily)  
        .method("getFamily", &fileaccproplist_getFamily)
        .method("setSplit", &fileaccproplist_setSplit)
        .method("setMetaBlockSize", &fileaccproplist_setMetaBlockSize)
        .method("setLog", &fileaccproplist_setLog)
        .method("setAlignment", &fileaccproplist_setAlignment)
        .method("getAlignment", &fileaccproplist_getAlignment)
        .method("getCache", &fileaccproplist_getCache)
	;
}
