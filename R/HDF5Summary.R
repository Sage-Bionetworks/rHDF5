"HDF5Summary" <-
function (filename,options=list())
{
	#
	# Return the summary of the HDF5 file.
	#
	# Arguments
	#  filename		HDF5 file name
	#  options   
	#		fullDetail	-	if "true", the dataset size and data type will be returned.
	#						otherwise, only the names are returned.  (default)
	#
	    results<-HDF5Execute("summary",
                        filename=filename,
                        path="",
                        intdata=integer(),
                        doubledata=double(),
                        strdata=as.character(list()),
                        dataframedata=as.data.frame(list()),
                        attributes=options,
                        debug=FALSE)
    
}
