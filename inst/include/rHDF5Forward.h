#ifndef RHDF5FORWARD_H
#define RHDF5FORWARD_H

#include <RcppCommon.h>
#include <H5public.h>

namespace Rcpp{
        template <> SEXP wrap( const hsize_t& ) ;
        template <> hsize_t as( SEXP ) ;
}

#endif
