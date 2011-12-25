#ifndef _INT64_INC
#define _INT64_INC
#pragma warning(disable:4996)       // security/deprecated warning

#include <iostream>

namespace seg
{
#if defined(WIN32) || defined(WIN64)
typedef __int64 INT64;
typedef unsigned __int64 UINT64;
#if _MSC_VER < 1399
inline std::ostream& operator<<(std::ostream& out, UINT64 ln)
{ char buffer[34];      return out << _ui64toa(ln, buffer, 10);}

inline std::ostream& operator<<(std::ostream& out, INT64 ln)
{ char buffer[34];      return out << _i64toa(ln, buffer, 10);}
#endif
#else
typedef long long INT64;
typedef unsigned long long UINT64;
#endif
}
#endif