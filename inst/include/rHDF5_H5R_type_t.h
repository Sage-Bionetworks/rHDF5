#ifndef RHDF5_H5R_TYPE_T_H
#define RHDF5_H5R_TYPE_T_H

#include <rHDF5Forward.h>

namespace Rcpp{
        template <>
        SEXP wrap( const H5R_type_t& mb ) {
                int& foo = (int&)mb ;
                return wrap(foo) ;
        }

        template <>
        H5R_type_t as( SEXP s ) {
                int tmp = as<int>(s) ;
                return (H5R_type_t)tmp;
        }
}

#endif
