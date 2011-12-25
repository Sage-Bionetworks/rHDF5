#if defined(WIN32) || defined(WIN64)
//#pragma warning(disable:4700)
#endif
#ifndef __HDF5OBJECT_H_
#define __HDF5OBJECT_H_ 
#include <string>
#include <vector>
#include "HDF5Exception.h"
#include "hdf5.h"

//*******************************************************************************
//*     This class is the parent of all HDF5 classes.  It is a abstract class and not 
//* to be instantiated.
//*******************************************************************************

namespace seg
{
        class HDF5Object
        {
         public:

                virtual ~HDF5Object();
                virtual bool Exist( const std::string& objname) const;
                static void Assert(int result, const std::string& msg);
                hid_t ID() const { return m_ID;};
                const std::string& GetName();
                virtual void CheckOpen() const;
                virtual std::string ToString(const std::string& tabs="")=0;

        protected:
                
                 virtual void Open()=0;
                 virtual void Close()=0;
                 bool m_opened;

                 hid_t m_ID;
                 hid_t m_ownerID;
                 std::string m_name;

        };

//===============================================
inline HDF5Object::~HDF5Object()
{
         m_opened=false;
 };

//===============================================
inline bool HDF5Object::Exist( const std::string& objname) const
{
   herr_t status = H5Eset_auto(NULL, NULL);
   status = H5Gget_objinfo (m_ID, objname.c_str(), 0, NULL);
   return status==0;
}

//===============================================
inline void HDF5Object::Assert(int result, const std::string& msg)
{
        if( result <0 )
                throw HDF5Exception(msg); 
}

//===============================================
inline const std::string& HDF5Object::GetName()
{
        return m_name;
}

//===============================================
inline void HDF5Object::CheckOpen() const
{
        if (!m_opened)
                throw HDF5Exception("HDF5 Object is not opened."); 
}

//===============================================
/*
 * Operator function.
 */
extern "C" herr_t GetGroupNamesFn(hid_t loc_id, const char *name, void *groupNames);
//{
//    H5G_stat_t statbuf;
//
//    /*
//     * Get type of the object and display its name and type.
//     * The name of the object is \t\t\tpassed to this function by 
//     * the Library. Some magic :-)
//     */
//      std::vector < std::string> *gps = (std::vector < std::string> *)groupNames;
//    H5Gget_objinfo(loc_id, name, true, &statbuf);
//    switch (statbuf.type) {
//    case H5G_GROUP: 
//              gps->push_back(name);
//         break;
//    default: 
//      /* function used internally. should never get to this point */
//              break;
//    }
//    return 1;
// }
//===============================================
extern "C" herr_t GetDatasetNamesFn(hid_t loc_id, const char *name, void *datasetNames);
//{
//    H5G_stat_t statbuf;
//
//      std::vector < std::string> *dsets = (std::vector < std::string> *)datasetNames;
//    H5Gget_objinfo(loc_id, name, true, &statbuf);
//    switch (statbuf.type) {
//    case H5G_DATASET: 
//               dsets->push_back(name);
//         break;
//    default:
//      /* function used internally. should never get to this point */
//              break;
//    }
//    return 1;
// }

//===============================================
extern "C" herr_t GetAttributeNamesFn(hid_t loc_id, const char *name, void *attNames);
//{
//      std::vector < std::string> *atts = (std::vector < std::string> *)attNames;
//      atts->push_back(name);
//    return 1;
// }
//#include "HDF5Object.cpp"
}
#endif
