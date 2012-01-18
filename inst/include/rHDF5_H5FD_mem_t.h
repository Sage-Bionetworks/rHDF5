#ifndef RHDF5_H5FD_MEM_T_H
#define RHDF5_H5FD_MEM_T_H

#include <rHDF5Forward.h>
#include <Rcpp.h>

using namespace H5 ;

namespace Rcpp{
        template <>
        SEXP wrap( const H5FD_mem_t& mb ) {
                int& foo = (int&)mb ;
                return wrap(foo) ;
        }

        template <>
        H5FD_mem_t as( SEXP s ) {
                int tmp = as<int>(s) ;
                return (H5FD_mem_t)tmp;
        }
}

#endif
