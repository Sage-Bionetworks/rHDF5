#ifndef RSTRING_INC
#define RSTRING_INC
#include <string>
#include <vector>

#include "Matrix.h"
#include "RObject.h"

namespace R
{
class RString : public RObject
{
public:
    RString(size_t noElements)
        { Create(noElements); }
    RString(SEXP r_obj);
    ~RString()
        {}
    void Create(size_t noElements);
    //
    // String specific
    //
    const char* Data(size_t index)
        { return CHAR( CHARACTER_POINTER(m_r_object)[index] ); }
    void Insert(const std::string& value,size_t index);
    void Insert(const std::vector<std::string>& values);
    void Insert(const seg::Matrix<std::string>& values,bool setDim=false);
    void Extract(size_t index, std::string& value);
    void Extract(std::vector<std::string>& values);
    void Extract(seg::Matrix<std::string>& values);
    void Extract(seg::Matrix<std::string>& values, size_t rows, size_t cols);
	void ExtractAndConcatenate(std::string& values, char sep=' ');
protected:
private:

};

}

#endif
