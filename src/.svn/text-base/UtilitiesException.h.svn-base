#ifndef UTILITIES_EXCEPTION_INC
#define UTILITIES_EXCEPTION_INC
#include <string>
#include <iostream>
namespace seg
{

class UtilitiesException
{
public:
    UtilitiesException(const std::string &msg, bool logIt=false)
    {   m_message=msg;
        if (logIt)
            std::cerr << "Utilities exception: " << msg << std::endl;
    }
    std::string m_message;
};

}
#endif