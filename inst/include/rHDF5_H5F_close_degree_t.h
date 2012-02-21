#ifndef RHDF5_H5F_CLOSE_DEGREE_T_H
#define RHDF5_H5F_CLOSE_DEGREE_T_H

#include <rHDF5Forward.h>
#include <Rcpp.h>

schmooga la munga

namespace Rcpp{
        template <>
        SEXP wrap( const H5F_close_degree_t& mb ) {
                int& foo = (int&)mb ;
                return wrap(foo) ;
        }

        template <>
        H5F_close_degree_t as( SEXP s ) {
                int tmp = as<int>(s) ;
                return (H5F_close_degree_t)tmp;
        }
}

#endif
