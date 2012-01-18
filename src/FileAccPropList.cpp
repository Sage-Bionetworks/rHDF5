#include <rHDF5.h>
#include <H5Cpp.h>
using namespace Rcpp ;

#ifndef H5_NO_NAMESPACE
	using namespace H5;
#endif

RCPP_MODULE(fileaccproplist){
	class_<FileAccPropList>( "FileAccPropList" ) 

	.constructor()
	.constructor<const hid_t>()

	.method( "setStdio", &FileAccPropList::setStdio )
	.method( "setDriver", &FileAccPropList::setDriver )
	.method( "getDriver", &FileAccPropList::getDriver )
	.method( "setFamilyOffset", &FileAccPropList::setFamilyOffset )
	.method( "getFamilyOffset", &FileAccPropList::getFamilyOffset )
//	.method( "setSec2", &FileAccPropList::setSec2 )
	.method( "setCore", &FileAccPropList::setCore )
//	.method( "getCore", &FileAccPropList::getCore )
//	.method( "setFamily", &FileAccPropList::setFamily )
//	.method( "getFamily", &FileAccPropList::getFamily )
//	.method( "setSplit", &FileAccPropList::setSplit )
	.method( "setSieveBufSize", &FileAccPropList::setSieveBufSize )
	.method( "getSieveBufSize", &FileAccPropList::getSieveBufSize )
//	.method( "setMetaBlockSize", &FileAccPropList::setMetaBlockSize )
	.method( "getMetaBlockSize", &FileAccPropList::getMetaBlockSize )
//	.method( "setLog", &FileAccPropList::setLog )
//	.method( "setAlignment ", &FileAccPropList::setAlignment  )
//	.method( "getAlignment", &FileAccPropList::getAlignment )
	.method( "setMultiType", &FileAccPropList::setMultiType )
	.method( "getMultiType", &FileAccPropList::getMultiType )
	.method( "setCache", &FileAccPropList::setCache )
//	.method( "getCache", &FileAccPropList::getCache )
	.method( "setFcloseDegree", &FileAccPropList::setFcloseDegree )
	.method( "getFcloseDegree", &FileAccPropList::getFcloseDegree )
	.method( "setGcReferences", &FileAccPropList::setGcReferences )
	.method( "getGcReferences", &FileAccPropList::getGcReferences )
	.method( "fromClass", &FileAccPropList::fromClass )
	;
}
