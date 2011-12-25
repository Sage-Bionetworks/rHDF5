"HDF5Execute" <-
function(task=c(),
         filename="",
         path="",
         intdata=integer(),
         doubledata=double(),
         strdata=as.character(list()),
         dataframedata=as.data.frame(list()),
         attributes=list(),
         debug=FALSE)
        
{
    #
    #   Low level function accessing HDF5 data
    #
    #   Arguments:
    #   filename:        HDF5 file
    #   path:			 full path of the HDF5 data
    #   intdata			 integer data to be written to HDF5 file 
    #   doubledata		 double data to be written to HDF5 file
    #   strdata			 string data to be written to HDF5 file
    #   dataframedata	 dataframe data to be written to HDF5 file
    #   attributes:      options

    #
    # check task
    #
    if (!is.character(task))
        stop("'task' must be character.");
    ltask<-tolower(task)
    #
    # check filename
    #
    if (!is.character(filename))
        stop("'filename' must be character.");
    lfilename<-(filename)
    #
    # check path
    #
    if (!is.character(path))
        stop("'path' must be character.");
    lpath<-(path)
    #
    # check int data
    #
    if (!is.integer(intdata))
        stop("'intdata' must be integer.");
    lintdata<-(intdata)
    #
    # check double data
    #
    if (!is.double(doubledata))
        stop("'doubledata' must be double.");
    ldoubledata<-(doubledata)
    #
    # check string data
    #
    if (!is.character(strdata))
        stop("'strdata' must be character.");
    lstrdata<-(strdata)
    #
    # check data frame data
    #
    if (!is.data.frame(dataframedata))
        stop("'dataframedata' must be a data frame.");
    ldataframedata<-(dataframedata)
    #
    # set attributes
    #
   	toDebug=ifelse(debug,"true","false") 
	if (!missing(attributes)) attributes<-as.list(attributes) else attributes<-list(Debug=toDebug)
    #
    # create the attributes list
	# Looking at each option so we don't pass in duplicate attributes
    #
	paramAttr<-list(Debug=toDebug)
	tempOptions<-names(attributes)
	for(option in tempOptions)
		paramAttr[option]<-attributes[option]
    attributes<-c(paramAttr)
    filename <- path.expand(filename)

    #
    # invoke the dll
    #
    bdata<-.Call("HDF5Execute", 
                 ltask,
                 lfilename,
                 lpath,
                 lintdata,
                 ldoubledata,
                 lstrdata,
                 ldataframedata,
                 attributes,
                 NAOK=T,
                 specialsok=T)
}
