#ifndef RHDF5_H5G_OBJ_T_H
#define RHDF5_H5G_OBJ_T_H

#include <rHDF5Forward.h>

namespace Rcpp{
        template <>
        SEXP wrap( const H5G_obj_t& mb ) {
                int& foo = (int&)mb ;
                return wrap(foo) ;
        }

        template <>
        H5G_obj_t as( SEXP s ) {
                int tmp = as<int>(s) ;
                return (H5G_obj_t)tmp;
        }
}

#endif
