#ifndef RHDF5_HSIZE_T_H
#define RHDF5_HSIZE_T_H

#include <rHDF5Forward.h>
#include <Rcpp.h>

namespace Rcpp{
        template <>
        SEXP wrap( const hsize_t& mb ) {
                size_t& foo = (size_t&)mb ;
                return wrap(foo) ;
        }

        template <>
        hsize_t as( SEXP s ) {
                size_t tmp = as<size_t>(s) ;
                return (hsize_t)tmp;
        }
}

#endif
