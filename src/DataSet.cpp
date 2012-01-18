#include <Rcpp.h>
#include <H5Cpp.h>

using namespace Rcpp ;

RCPP_MODULE(h5dataset) {
	using namespace H5 ;
	class_<DataSet>("DataSet")
	.constructor()
	
	.method( "getId", &DataSet::getId)
	;
}
