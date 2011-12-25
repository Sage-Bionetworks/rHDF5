"HDF5ReadData" <-
function (filename,path,options=list())
{
	#
	# Read data from HDF5 file
	#
	# Arguments
	#  filename - HDF5 file name in full path
	#  path		- the full path of the dataset
	#  options  startindex - the row index of data to start reading. Default(0)
	#			nrows - the number of rows of data to be read. Default(all rows)
	#
	if (missing(filename))
		stop("HDF5Read: parameter filename is missing.")
	if (missing(path))
		stop("HDF5Read: parameter path is missing.")
	
 	paramAttr=list()
	tempOptions<-names(options)
	for(option in tempOptions)
		if ((tolower(option)=="startindex") || (tolower(option)=="nrows"))
			paramAttr[option]<-toString(options[option])
		else 
			paramAttr[option]<-options[option]
		
    results<-HDF5Execute("readdata",
	                      filename=filename,
                        path=path,
                        intdata=integer(),
                        doubledata=double(),
                        strdata=as.character(list()),
                        dataframedata=as.data.frame(list()),
                        attributes=paramAttr,
                        debug=FALSE)

        
}
