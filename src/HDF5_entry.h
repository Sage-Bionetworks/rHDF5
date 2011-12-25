#ifndef HDF5_ENTRY_INC
#define HDF5_ENTRY_INC

#include "RDev.h"

extern "C" 
{

    R_DLL_API SEXP HDF5Execute(SEXP task,       
                 SEXP filename,   
                 SEXP path,     //
				 SEXP intdata,     //
				 SEXP doubledata,     //
				 SEXP strdata,     //
				 SEXP dataframedata,     //
                 SEXP aAttributes); // list (all input data with simple data type)

}

#endif
