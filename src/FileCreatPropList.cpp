#include <rHDF5.h>

using namespace Rcpp ;

#ifndef H5_NO_NAMESPACE
	using namespace H5;
#endif

RCPP_MODULE(filecreatproplist){
	class_<FileCreatPropList>( "FileCreatPropList" ) 
	
	.constructor()
	.constructor<const hid_t>()
	
	//.method( "getVersion", &FileCreatPropList::getVersion )
	.method( "setUserblock", &FileCreatPropList::setUserblock )
	.method( "getUserblock", &FileCreatPropList::getUserblock )
	//.method( "getSizes", &FileCreatPropList::getSizes )
	.method( "setSizes", &FileCreatPropList::setSizes )
	//.method( "getSymk", &FileCreatPropList::getSymk )
	.method( "setSymk", &FileCreatPropList::setSymk )
	.method( "getIstorek", &FileCreatPropList::getIstorek )
	.method( "setIstorek", &FileCreatPropList::setIstorek )
	.method( "fromClass", &FileCreatPropList::fromClass )
	;
}
