#ifndef RHDF5_FILEACCPROPLIST_H
#define RHDF5_FILEACCPROPLIST_H

#include <rHDF5Forward.h>
#include <Rcpp.h>
#include <map>
#include <string> 
#include <utility>

using namespace std;

namespace Rcpp{

        template <> SEXP wrap( const FileAccPropList& myClass )
        {
            // No STL was actually necessary for this one.
            // Let's not complicate any class more than we have to.
            // The only STL objects we can pass are string, vector/deque/list<primitive> anyway
            hid_t result;

            // Have to do this for every member of the class that is important.
            // In this case, result was the only one that mattered.
            result = myClass.getId();

            return wrap(result);
        }

        template <> FileAccPropList as( SEXP s )
        {
            // Convert s into my ID using as.
            hid_t myID = as<hid_t>(s);

            // Initialize a new class based on the returned members.
            FileAccPropList result(myID);

            return result;
        }
}

#endif
