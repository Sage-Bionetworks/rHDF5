#ifndef RLIST_INC
#define RLIST_INC
#include <string>
#include <vector>

#include "STLTypes.h"
#include "RObject.h"

namespace R
{
class RList : public RObject
{
public:
    RList() : m_listPos(0)
        {}
    RList(size_t noElements) : m_listPos(0)
        { Create(noElements); }
    RList(SEXP r_obj);
    ~RList()
        {}
    void Create(size_t noElements);
    //
    // List specific
    //
    void InsertElement(RObject& rObj,const std::string& name="");
    RObject GetElement(size_t eIndex);
    RObject GetElement(const std::string& name);
    void ExtractNameValue(std::vector<seg::STLTypes::NameValuePair>& nvp);
protected:
private:
    size_t                      m_listPos;
};

}

#endif