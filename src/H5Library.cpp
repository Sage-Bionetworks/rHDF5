#include <H5Cpp.h>
#include <Rcpp.h>

using namespace Rcpp ;

#ifndef H5_NO_NAMESPACE
	using namespace H5 ;
#endif

static void open(){
	H5::H5Library::open() ;
}

static void _close(){
	H5::H5Library::close() ;
}

static void dontAtExit(){
	H5Library::dontAtExit() ;
}

static Rcpp::List getLibVersion(){
	
	unsigned majnum ;
	unsigned minnum ;
	unsigned relnum ;

	H5::H5Library::getLibVersion(majnum, minnum, relnum ) ;

	return Rcpp::List::create(Rcpp::Named("majnum", majnum),
				  Rcpp::Named("minnum", minnum),
				  Rcpp::Named("relnum", relnum)) ;	
}

static void checkVersion( unsigned majnum, unsigned minnum, unsigned relnum){
	H5::H5Library::checkVersion(majnum, minnum, relnum) ;
}

static void garbageCollect(){
	H5::H5Library::garbageCollect() ;
}

static void setFreeListLimits(int reg_global_lim, int reg_list_lim, int arr_global_lim, int arr_list_lim, int blk_global_lim, int blk_list_lim){
	H5::H5Library::setFreeListLimits(reg_global_lim, reg_list_lim, arr_global_lim, arr_list_lim, blk_global_lim, blk_list_lim) ;
}



RCPP_MODULE(h5library){
	function( ".open", &open ) ;
	function( ".close", &_close ) ;
	function( "dontAtExit", &dontAtExit ) ;
	function( "getLibVersion", &getLibVersion ) ;
	function( "checkVersion", &checkVersion ) ;
	function( "garbageCollect", &garbageCollect ) ;
	function( "setFreeListLimits", &setFreeListLimits ) ;
}
