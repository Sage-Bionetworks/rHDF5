"BSAExecute" <-
function(ids=c(),
         fields="all",
         itype="bsa",
         task="annotation",
         options=list(),
         debug=FALSE)
        
{
    #
    #   Low level function accessing BSA data
    #
    #   Arguments:
    #   ids:        Input ids (e.g., sample barccode) to get information about.
    #   fields:     BSA fields or names of attributes
    #   itype:      Type of input ids.
    #               [bsa chip pc]
    #   task:       The task to execute in getting BSA information.
    #               [annotation info]

    #
    # check task
    #
    if (!is.character(task))
        stop("'task' must be character.");
    ltask<-tolower(task)
    #
    # check ids
    #
    if (is.null(ids) && ltask!="info")
        stop("'ids' must be specified.")
    else
        ids<-as.character(ids)
    #
    # check fields
    #
    if (!is.character(fields))
        stop("'fields' must be character.");
    #
    # check itype
    #
    if (!is.character(itype))
        stop("'itype' must be character.");
    litype<-tolower(itype)
    #
    # set options
    #
   	toDebug=ifelse(debug,"true","false") 
    if (!missing(options))
        options<-as.list(options)
    else
        options<-list(Debug=toDebug)
    #
    # check task 
    #
    if (ltask != "info" && ltask !="annotation")
        stop("'task' must be either 'annotation' or 'info'.")
    if (ltask == "info")
        ltask<-"Columns"
    #
    # create the attributes list
    #
	paramAttr<-list(CollapseCols="true",
                   InputType=itype,
                   IncludeCA="true",
                   Debug=toDebug)
	#
	#Looking at each option so we don't pass in duplicate options
	#
	tempOptions<-names(options)
	for(option in tempOptions)
		paramAttr[option]<-options[option]
    attributes<-c(paramAttr)
    #
    # invoke the dll
    #
    bdata<-.Call("BSAExecute", 
                 ltask,
                 fields,
                 litype,
                 ids,
                 attributes,
                 NAOK=T,
                 specialsok=T)
}
