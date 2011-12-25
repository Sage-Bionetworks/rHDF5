#pragma warning(disable:4786)
#include <string>
#include <sstream>
#include <sys/stat.h>

#include "StringUtils.h"
#include "STLTypes.h"
#include "bat_entry.h"
#include "RDev.h"

using namespace std;
using namespace R;
using namespace seg;

static const string BAT_HOME="BAT_HOME";


//
// routine:     BATInit
//
SEXP BATInit(SEXP s_batHome)
{
    //
    // set the environment variable "BAT_HOME"
    //
    const string rName="BATInit/";
    //
    // sanity-check
    //
    SEXP results = R_NilValue; //initialize to the build-in NULL object
    //
    // do it
    //
    try
    {
        RInitializer rInit;
        RString rHome(s_batHome);
        string homeDir;
        if (rHome.Size())
            rHome.Extract(0,homeDir);
        else
            homeDir="./";
        string env=BAT_HOME;
        env+="=";
        env+=homeDir;
        putenv(const_cast<char*> (env.c_str()));
        //
        // check if it exists
        //
        RVector<int> rExist(1);
        int* exist=rExist.Data();
        exist[0]=1;

		struct stat buf;
		if (stat(homeDir.c_str(), &buf )!=0)
            exist[0]=0;
        results=rExist.Object();
        rInit.Cleanup();
    }
    catch (const RException& exc)
    {
        RProblem(exc.m_message);
    }
    catch (...)
    {
        RProblem("Unknown error encountered");
    }
    return results;
}
