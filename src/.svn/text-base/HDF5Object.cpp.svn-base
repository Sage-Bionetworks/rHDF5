#ifndef HDF5OBJECT_CPP
#define HDF5OBJECT_CPP
#include "HDF5Object.h"
//===============================================
/*
 * Operator function.
 */
herr_t seg::GetGroupNamesFn(hid_t loc_id, const char *name, void *groupNames)
{
    H5G_stat_t statbuf;

    /*
     * Get type of the object and display its name and type.
     * The name of the object is \t\t\tpassed to this function by 
     * the Library. Some magic :-)
     */
        std::vector < std::string> *gps = (std::vector < std::string> *)groupNames;
    H5Gget_objinfo(loc_id, name, true, &statbuf);
    switch (statbuf.type) {
    case H5G_GROUP: 
                gps->push_back(name);
         break;
    default: 
        /* function used internally. should never get to this point */
                break;
    }
    return 1;
}
//===============================================
herr_t seg::GetDatasetNamesFn(hid_t loc_id, const char *name, void *datasetNames)
{
    H5G_stat_t statbuf;

        std::vector < std::string> *dsets = (std::vector < std::string> *)datasetNames;
    H5Gget_objinfo(loc_id, name, true, &statbuf);
    switch (statbuf.type) {
    case H5G_DATASET: 
                 dsets->push_back(name);
         break;
    default:
        /* function used internally. should never get to this point */
                break;
    }
    return 1;
 }

//===============================================
herr_t seg::GetAttributeNamesFn(hid_t loc_id, const char *name, void *attNames)
{
        std::vector < std::string> *atts = (std::vector < std::string> *)attNames;
        atts->push_back(name);
    return 1;
 }
#endif
