#include <H5Cpp.h>
#include <Rcpp.h>

using namespace Rcpp ;

#ifndef H5_NO_NAMESPACE
	using namespace H5 ;
#endif

RCPP_MODULE(h5library){
	class_<H5Library>( "H5Library" ) 

	//// none of these compile.
	//.method( "open", &H5Library::open )
	//.method( "close", &H5Library::close )
	//.method( "dontAtExit", &H5Library::dontAtExit )
	//.method( "getLibVersion", &H5Library::getLibVersion )
	//.method( "checkVersion", &H5Library::checkVersion )
	//.method( "garbageCollect", &H5Library::garbageCollect )
	//.method( "setFreeListLimits", &H5Library::setFreeListLimits )
	
	;
}
