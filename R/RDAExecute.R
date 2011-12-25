"RDAExecute" <-
function(
        task,
        species,
        rHandle,
        todIds,
        lodIds,
        tod="re",
        lod="sequence",
        fields="eg",
        todQuery,
        lodQuery,
        dbuser,
        dbpwd,
        dbname,
        dbserver,
        options,
        debug=FALSE)
        
{
    #
    #   Low level function accessing the Resolver Data Client to get Resolver data
    #
    #   Arguments:
    #   task:       The task to execute in getting Resolver data.
    #               [expression annotation egall metainfo resolverids opendb closedb
    #                login logout]
    #   species:    The species database.
    #               [human yeast mouse rat dog ecoli chicken yeastgrm synthetic candida]
    #   tod:        Type of data
    #               [re rp ie ip (for "Ratio Experiment", "Ratio Profile", etc.)]
    #   lod:        Level of detail
    #               [feature reporter sequence unigene]
    #   fields:     A comma separated list of one or more expression fields.
    #               [value error pvalue seqcount background xdev logintensity intensity1 
    #                intensity2 failcode controlflag]
    #   todQuery:   A list containing named query data for getting tod IDs.  Query data
    #               includes query name and query arguments.
    #   lodQuery:   A list containing named query data for getting lod IDs.
    #   todIds:     A vector of doubles containing tod ids for getting expression data.
    #               [Note: tod ids must somehow be obtained from one of the following:
    #                   1. An explicit list of ids
    #                   2. Indirectly obtained via the todQuery parameter (see above)
    #                   3. Indirectly obtained via the lod ids (in which case all of the
    #                       tod ids associated with the lod ids are used)]
    #   lodIds: A vector of doubles containing lod ids for getting expression data.
    #               [Note: lod ids must somehow be obtained from one of the following:
    #                   1. An explicit list of ids
    #                   2. Indirectly obtained via the lodQuery parameter (see above)
    #                   3. Indirectly obtained via the tod ids (in which case all of the
    #                      lod ids associated with the tod ids are used)]

    #
    # check task
    #
    if (missing(task))
        stop("'task' must be specified.")
    else
        task=as.character(task)
    task=casefold(task)
    if (task!="login" && missing(species))
        stop("species is required for task") 
    #
    # set species
    #
    if (!missing(species))
        species=as.character(species)
    else
        species=character()
    #
    # set fields
    #
    if (!missing(fields))
        fields=as.character(fields)
    #
    # set db handle
    #
    if (!missing(rHandle))
        rHandle=as.double(rHandle)
    else
        rHandle=double()
    #
    # set tod ids
    #
    if (!missing(tod))
        tod=as.character(tod)
    if (!missing(todIds))
        todIds=as.double(todIds)
    else
        todIds=double()
    #
    # set lod ids
    #
    if (!missing(lod))
        lod=as.character(lod)
    if (!missing(lodIds))
        lodIds=as.double(lodIds)
    else
        lodIds=double()
    #
    # set tod query
    #
    if (missing(todQuery))
        todQuery=list(empty="")
    else
    {
        todQuery=as.list(todQuery)
        if (is.null(todQuery$name))
            stop("tod query must have name")
        if (is.null(todQuery$params))
            stop("tod query requires parameter(s)")
    }
    #
    # set lod query
    #
    if (missing(lodQuery))
        lodQuery=list(empty="")
    else
    {
        lodQuery=as.list(lodQuery)
        if (is.null(lodQuery$name))
            stop("lod query must have name")
        if (is.null(lodQuery$params))
            stop("lod query requires parameter(s)")
    }
    #
    # set options
    #
    if (!missing(options))
        options=as.list(options)
    else
	{
        options=list(IncludeFlaggedData="True")
	}
    #
    # set db info
    #
    if (!missing(dbuser))
        dbuser=as.character(dbuser)
    else
        dbuser=character()
    if (!missing(dbpwd))
        dbpwd=as.character(dbpwd)
    else
        dbpwd=character()
    if (!missing(dbname))
        dbname=as.character(dbname)
    else
        dbname=character()
    if (!missing(dbserver))
        dbserver=as.character(dbserver)
    else
        dbserver=character()
    #
    # create the attributes list
    #
   	toDebug=ifelse(debug,"true","false") 
	paramAttr=list(SelectedTask=task,
                      typeofdata=tod, 
                      levelofdetail=lod, 
                      species=species,
                      DbUser=dbuser,
                      DbPassword=dbpwd,
                      DbName=dbname,   
                      DbServer=dbserver,
                      RowQuery=todQuery$name,
                      RowQueryValues=todQuery$params, 
                      ColumnQuery=lodQuery$name,
                      ColumnQueryValues=lodQuery$params,
                      Debug=toDebug)
    attributes=c(paramAttr,options)
    #
    # invoke the dll
    #
    .Call("RDAExecute", 
               rHandle,
               todIds,
               lodIds,
               fields,
               attributes,
               NAOK=T,
               specialsok=T)
}
