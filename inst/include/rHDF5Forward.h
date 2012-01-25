#ifndef RHDF5FORWARD_H
#define RHDF5FORWARD_H

#include <RcppCommon.h>
#include <H5FDpublic.h>
#include <H5public.h>
#include <H5Fpublic.h>
#include <H5Gpublic.h>
#include <H5Rpublic.h>
#include <H5Cpp.h>

using namespace H5 ;

namespace Rcpp{
        template <> SEXP wrap( const hsize_t& ) ;
        template <> hsize_t as( SEXP ) ;

        template <> SEXP wrap( const hssize_t& ) ;
        template <> hssize_t as( SEXP ) ;
	
	template <> SEXP wrap( const H5F_close_degree_t& ) ;
	template <> H5F_close_degree_t as( SEXP ) ;

	template <> SEXP wrap( const H5FD_mem_t& ) ;
	template <> H5FD_mem_t as( SEXP ) ;
	
	template <> SEXP wrap( const H5F_scope_t& ) ;
        template <> H5F_scope_t as( SEXP ) ;

	template <> SEXP wrap( const H5G_obj_t& ) ;
        template <> H5G_obj_t as( SEXP ) ;

	template <> SEXP wrap( const H5R_type_t& ) ;
        template <> H5R_type_t as( SEXP ) ;
	
	template <> SEXP wrap( const FileCreatPropList& ) ;
//	template <> FileCreatPropList as( SEXP ) ;

}

#endif
