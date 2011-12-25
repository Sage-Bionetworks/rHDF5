#ifndef HDF5EXCEPTION_H_INC_
#define HDF5EXCEPTION_H_INC_

// System includes
#include <string>

#define ERR_MSG(e, x){strstream str; string desc(e.Description()); \
        str << x <<": " << desc <<"\n";\
        str.str()[str.pcount()]=0; throw HDF5Exception(str.str());}

namespace seg
{

class HDF5Exception
{
public:
        HDF5Exception(const std::string& msg):msg(msg){ };
    std::string msg;
};
#include "HDF5Exception.cpp"
}

#endif  // HDF5EXCEPTION_H_INC_
