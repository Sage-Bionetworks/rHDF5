#ifndef STRING_UTILS_INC
#define STRING_UTILS_INC
//
//  class:          StringUtils (a namespace)
//  description:    Utilities for strings
// 
#pragma warning(disable:4251)
#include <string>
#include <algorithm>
#include <vector>

#include "Matrix.h"

namespace seg
{

class StringUtils
{

public :
    //
    // extract fields delimited by spaces from a string to a matrix of
    // strings
    //
    void static ExtractFields(const std::string& input,
                              Matrix<std::string>& output);
    
    // tokenize the input string, str, by the delimiter (default is "/").
    // If one of the tokens should contain a delimiter, use the escape character before the delimiter, which
    // is actually the same as the delimiter. 
    //  Eg. "The/character/"//"/is/included" --> 
    // The
    // Character
    // "/"
    // is
    // included
    //
    // parameter, outTokens, is the output of all the tokens after parsing.
    //
    void static Parse(const std::string& input,
                      char delimiter,
                      std::vector<std::string>& outTokens);
    //
    // String comparing ignoring case
    //
    bool static CompareNoCase(const std::string& s1, const std::string& s2);
    //
    // String srcStr contains searchStr ignoring case
    //
    bool static ContainsNoCase(const std::string& srcStr, const std::string& searchStr);
    //
    // toupper and tolower
    //
    void static ToLower(const std::string& input, std::string& output);
    void static ToUpper(const std::string& input, std::string& output);

private:

    void static ParseIt(const std::string& input,
                        const std::string& delimiter, 
                        std::vector<std::string>& outTokens,
                        std::string& holdingBuffer);
};

}

#endif
