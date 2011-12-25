#pragma warning(disable:4786)
#include <string>
#include <math.h>

#include "RProblem.h"
#include <R.h>

using namespace R;
using namespace std;


void R::RProblem(const std::string& message)
{
    PROBLEM message.c_str() ERROR;
}
void R::RMessage(const std::string& message)
{
    Rprintf("%s\n",message.c_str());
}
