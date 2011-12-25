#pragma warning(disable:4786)
#include <sstream>
#include <iomanip>
#include <limits>

#include "RException.h"
#include "RObjectFactory.h"
#include "RString.h"
#include "RList.h"

using namespace std;
using namespace R;
using namespace seg;

//
// routine:     ctor
// description: create a list type by coercing to R LIST
//
RList::RList(SEXP r_obj)
{
    const std::string rName="RList::ctor/";
    //
    // create the r list
    //
    m_r_object=r_obj;
    m_type=OT_LIST;
    //m_size=LENGTH(r_obj);
    RObjectFactory::Instance().Protect(*this);
    m_listPos=m_size-1;
    //
    // Add names (if there)
    //
    SEXP r_names=GET_NAMES(m_r_object);
    size_t noNames=LENGTH(r_names);
    m_names.resize(noNames);
    for (size_t index=0;index<noNames; index++)
    {
        string lName=CHAR(STRING_ELT(r_names,index));
        m_names[index]=lName;
    }
}
//
// routine:     Create
// description: create an R string/char object (a vector of char*)
//
void RList::Create(size_t noElements)
{
    const std::string rName="RList::Create/";
	if (m_size)
        throw RException(rName+"String already created.");
    //
    // create the r vector of strings 
    //
    m_r_object=R_NilValue;
    m_type=OT_LIST;
    m_size=noElements;
    m_listPos=0;
    RObjectFactory::Instance().Create(*this);
}
//
// routine:     InsertElement
// description: If this is a list, insert object
//
void RList::InsertElement(RObject& rObj,const string& name)
{
    const string rName="RObject::InsertElement/";
    string rType=ConvertObjectType(m_type);
    //
    // sanity check
    //
    if (m_listPos >= m_size)
        throw RException(rName+"List is full.");
    //
    // set the name of the item
    //
    string theName=name;
    if (theName=="")
    {
        ostringstream ostr;
        ostr << m_listPos+1;
        theName="Item"+ostr.str();
    }
    m_names.push_back(theName);
    //
    // set the data
    //
    SET_ELEMENT(m_r_object,m_listPos,rObj.Object());
    //
    // if we're complete, set the names
    //
    if (m_listPos==m_size-1)
        Names(m_names);
    else
        m_listPos++;
}
//
// routine:     GetElement
// description: xxx
//
RObject RList::GetElement(size_t eIndex)
{
    const string rName="RList::GetElement/";
    if (eIndex>m_listPos)
    {
        ostringstream ostr;
        ostr << "index: " << eIndex << "  Pos: " << m_listPos;
        throw RException(rName+"Index beyone list size\n\t"+ostr.str());
    }
    SEXP r_element=VECTOR_ELT(m_r_object,eIndex);
    return RObject(r_element,RObject::GetRType(r_element),LENGTH(r_element));
}
//
// routine:     GetElement
// description: xxx
//
RObject RList::GetElement(const std::string& name)
{
    const string rName="RList::GetElement/";
    if (!m_size)
        throw RException(rName+"List is zero size.");
    SEXP r_element=R_NilValue;
    for (size_t index=0;index<m_size;index++)
    {
        if (m_names[index]==name)
        {
            r_element=VECTOR_ELT(m_r_object,index);
            break;
        }
    }
    return RObject(r_element,RObject::GetRType(r_element),LENGTH(r_element));
}
//
// routine:     ExtractNameValue
// description: xxx
//
void RList::ExtractNameValue(std::vector<seg::STLTypes::NameValuePair>& nvp)
{
    const string rName="RList::ExtractNameValue/";
    nvp.resize(0);
    //
    // iterate and find a string in the list
    //
    for (size_t aI=0;aI<m_size;aI++)
    {
        string name=m_names[aI];
        RObject element=GetElement(aI);
        if (element.Type()==RObject::OT_STRING)
        {
//            RString rString(element.Object());
            STLTypes::NameValuePair nameValue;
            nameValue.first=name;
            nameValue.second="";
            if(element.Size()==1)
            {
                SEXP cp=CHARACTER_POINTER(element.Object())[0];
                if (cp!=R_NilValue)
                    nameValue.second=CHAR(cp);
                else
                    nameValue.second="";
//                rString.Extract(0,nameValue.second);
            }
            nvp.push_back(nameValue);
        }
    }
}
