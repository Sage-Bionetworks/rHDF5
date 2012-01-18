#ifndef RHDF5_H5F_SCOPE_T_H
#define RHDF5_H5F_SCOPE_T_H

#include <rHDF5Forward.h>

namespace Rcpp{
        template <>
        SEXP wrap( const H5F_scope_t& mb ) {
                int& foo = (int&)mb ;
                return wrap(foo) ;
        }

        template <>
        H5F_scope_t as( SEXP s ) {
                int tmp = as<int>(s) ;
                return (H5F_scope_t)tmp;
        }
}

#endif
