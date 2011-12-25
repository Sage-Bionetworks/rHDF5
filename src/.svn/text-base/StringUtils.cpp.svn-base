#pragma warning(disable:4786)
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "StringUtils.h"

using namespace std;
using namespace seg;
//
// extract
//
void StringUtils::ExtractFields(const string& input,Matrix<string>& output)
{
    vector<string> mValues;
    if (input!="")
    {
        istringstream istr(input);
        istream_iterator<std::string> istrIter(istr);
        istream_iterator<std::string> end;
        copy(istrIter,end,inserter(mValues,mValues.begin()));
        //
        // copy into matrix
        //
        output=mValues;
    }
}
//
// parse
//
void StringUtils::Parse(const std::string& input,
                        char delimiter,
                        std::vector<std::string>& outTokens)
{ 
    string strDelimiter;
    strDelimiter+=delimiter;
    string holdingBuffer;
    ParseIt(input,strDelimiter,outTokens,holdingBuffer);
}
//
// contains
//
bool StringUtils::ContainsNoCase(const std::string& srcStr, const std::string& searchStr)
{
    string src;
    string search;
    StringUtils::ToLower(srcStr,src);
    StringUtils::ToLower(searchStr,search);
    string::size_type pos=src.find(search);
    bool found;
    if (pos==string::npos)
        found=false;
    else
        found=true;
    return found;
}
//
// cmp
//
bool StringUtils::CompareNoCase(const std::string& s1, const std::string& s2)
{
    bool same=true;
    //
    // must be the same length
    //
    if (s1.size() != s2.size())
        same=false;
    else
    {
        string::const_iterator iter1=s1.begin();
        string::const_iterator iter2=s2.begin();
        string::const_iterator end1=s1.end();
        string::const_iterator end2=s2.end();
        while (iter1!=end1 && iter2!=end2)
        {
            if (toupper(*iter1)!=toupper(*iter2))
            {
                same=false;
                break;
            }
            iter1++;
            iter2++;
        }
    }
    return same;
}
//
// tolower
//
void StringUtils::ToLower(const std::string& input,std::string& output)
{
    string::const_iterator inIt=input.begin();
    string::const_iterator endIt=input.end();
    output="";
    while (inIt!=endIt)
        output+=tolower(*inIt++);
}
//
// toupper
//
void StringUtils::ToUpper(const std::string& input, std::string& output)
{
    string::const_iterator inIt=input.begin();
    string::const_iterator endIt=input.end();
    output="";
    while (inIt!=endIt)
        output+=toupper(*inIt++);
}
//
// private parse
//
void StringUtils::ParseIt(const string& input, 
                          const string& delimiter,
                          vector<string>& outTokens,
                          string& holdingBuffer)
{
    size_t index = input.find_first_of(delimiter);
    //
    // If we have a delimiter, parsing is required.
    //
    if(index != string::npos)
    {
        size_t sizeIn=input.size();
        size_t sizeDelimiter=delimiter.size();
        //
        // check character after delimiter. if it's not a delimiter
        // then we're not in going to escape.  However, we may be
        // processing the a previous escape.
        //
        if(input[index+sizeDelimiter] != delimiter[0])  
        {
            //
            // get the substring
            //
            string inSub=input.substr(0,index+sizeDelimiter/2);
            //
            // if the size of the delimiter is a factor of 2,
            // then we were previously escaping so we don't have a token.
            //
            if((sizeDelimiter%2)==0)
            {
                //
                // place the string with only one occurrence of the delimiter
                // (since it's been escaped) in the holding buffer
                //
                holdingBuffer += inSub;
            }
            //
            // else we have a real token based on substring and holding buffer
            //
            else
            {
                outTokens.push_back(holdingBuffer+inSub);
                holdingBuffer="";           // reset the holding buffer
            }
            //
            // continue parsing by updating our input string and resetting
            // the delimiter
            //
            string newInput=input.substr(index+sizeDelimiter,sizeIn);
            ParseIt(newInput,delimiter.substr(0,1),outTokens,holdingBuffer);
        }
        //
        // else we're escaping so append the delimiter and continue
        //
        else
            ParseIt(input,delimiter+delimiter[0],outTokens,holdingBuffer);
    }
    //
    // else we have our final token
    //
    else
    { 
        outTokens.push_back(holdingBuffer+input.substr(0,index));
    }
}