#include <Rcpp.h>
#include <hdf5.h>

using namespace Rcpp;
class H5constants{
public:
	hid_t get_H5_VERS_MAJOR(){
		return(H5_VERS_MAJOR);
	}

	hid_t get_H5_VERS_MINOR(){
		return(H5_VERS_MINOR);
	}

	hid_t get_H5_VERS_RELEASE(){
                return(H5_VERS_RELEASE);
        }

	char * get_H5_VERS_SUBRELEASE(){
                return(H5_VERS_SUBRELEASE);
        }

	char * get_H5_VERS_INFO(){
                return(H5_VERS_INFO);
        }

	hid_t get_H5P_DEFAULT(){
		return(H5P_DEFAULT);
	}
	
	//H5F constants

	uint get_H5F_ACC_RDONLY(){
                return(H5F_ACC_RDONLY);
        }

        uint get_H5F_ACC_RDWR(){
                return(H5F_ACC_RDWR);
        }
        uint get_H5F_ACC_TRUNC(){
                return(H5F_ACC_TRUNC);
        }
        uint get_H5F_ACC_EXCL(){
                return(H5F_ACC_EXCL);
        }
        uint get_H5F_ACC_DEBUG(){
                return(H5F_ACC_DEBUG);
        }
        uint get_H5F_ACC_CREAT(){
                return(H5F_ACC_CREAT);
        }
        uint get_H5F_OBJ_FILE(){
                return(H5F_OBJ_FILE);
        }
        uint get_H5F_OBJ_DATASET(){
                return(H5F_OBJ_DATASET);
        }
        uint get_H5F_OBJ_GROUP(){
                return(H5F_OBJ_GROUP);
        }
        uint get_H5F_OBJ_DATATYPE(){
                return(H5F_OBJ_DATATYPE);
        }
        uint get_H5F_OBJ_ATTR(){
                return(H5F_OBJ_ATTR);
        }
        uint get_H5F_OBJ_ALL(){
                return(H5F_OBJ_ALL);
        }
        uint get_H5F_OBJ_LOCAL(){
                return(H5F_OBJ_LOCAL);
        }
        size_t get_H5F_FAMILY_DEFAULT(){
                return(H5F_FAMILY_DEFAULT);
        }

	//H5D constants

	size_t get_H5D_CHUNK_CACHE_NSLOTS_DEFAULT(){
                return(H5D_CHUNK_CACHE_NSLOTS_DEFAULT);
        }

        size_t get_H5D_CHUNK_CACHE_NBYTES_DEFAULT(){
                return(H5D_CHUNK_CACHE_NBYTES_DEFAULT);
        }

        double get_H5D_CHUNK_CACHE_W0_DEFAULT(){
                return(H5D_CHUNK_CACHE_W0_DEFAULT);
        }
};

RCPP_MODULE(H5constants){
	class_<H5constants>( "H5constants" )

	.constructor()
	
	.method( "get_H5_VERS_MAJOR" , &H5constants::get_H5_VERS_MAJOR )
	.method( "get_H5_VERS_MINOR" , &H5constants::get_H5_VERS_MINOR )
	.method( "get_H5_VERS_MINOR" , &H5constants::get_H5_VERS_MINOR )
	.method( "get_H5_VERS_MINOR" , &H5constants::get_H5_VERS_MINOR )
	.method( "get_H5_VERS_MINOR" , &H5constants::get_H5_VERS_MINOR )
	.method( "get_H5P_DEFAULT" , &H5constants::get_H5P_DEFAULT )
	//H5F getters
	.method( "get_H5F_ACC_RDONLY", &H5constants::get_H5F_ACC_RDONLY )
        .method( "get_H5F_ACC_RDWR", &H5constants::get_H5F_ACC_RDWR )
        .method( "get_H5F_ACC_TRUNC", &H5constants::get_H5F_ACC_TRUNC )
        .method( "get_H5F_ACC_EXCL", &H5constants::get_H5F_ACC_EXCL )
        .method( "get_H5F_ACC_DEBUG", &H5constants::get_H5F_ACC_DEBUG )
        .method( "get_H5F_ACC_CREAT", &H5constants::get_H5F_ACC_CREAT )
        .method( "get_H5F_OBJ_FILE", &H5constants::get_H5F_OBJ_FILE )
        .method( "get_H5F_OBJ_DATASET", &H5constants::get_H5F_OBJ_DATASET )
        .method( "get_H5F_OBJ_GROUP", &H5constants::get_H5F_OBJ_GROUP )
        .method( "get_H5F_OBJ_DATATYPE", &H5constants::get_H5F_OBJ_DATATYPE )
        .method( "get_H5F_OBJ_ATTR", &H5constants::get_H5F_OBJ_ATTR )
        .method( "get_H5F_OBJ_ALL", &H5constants::get_H5F_OBJ_ALL )
        .method( "get_H5F_OBJ_LOCAL", &H5constants::get_H5F_OBJ_LOCAL )
        .method( "get_H5F_FAMILY_DEFAULT", &H5constants::get_H5F_FAMILY_DEFAULT )
	//H5Dgetters
	.method( "get_H5D_CHUNK_CACHE_NSLOTS_DEFAULT", &H5constants::get_H5D_CHUNK_CACHE_NSLOTS_DEFAULT )
        .method( "get_H5D_CHUNK_CACHE_NBYTES_DEFAULT", &H5constants::get_H5D_CHUNK_CACHE_NBYTES_DEFAULT )
        .method( "get_H5D_CHUNK_CACHE_W0_DEFAULT", &H5constants::get_H5D_CHUNK_CACHE_W0_DEFAULT )
	;

}

