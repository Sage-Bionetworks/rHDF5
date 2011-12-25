#ifndef R_EXCEPTION_INC
#define R_EXCEPTION_INC
#pragma warning(disable:4251)
#include <string>
#include <iostream>
namespace R
{
//
// class:       RException
// description:
//
class RException
{
public:
    RException(const std::string& msg,bool debug=false) :
    m_message(msg)
        { if (debug) std::cerr << msg << std::endl;}
    std::string m_message;
};

}
#endif
