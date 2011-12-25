"HDF5WriteAttribute" <-
function (filename,
			path,
			data,
			options=list())
{
	#
	# Write an attribute to the existing dataset or group
	#
	# Arguments
	#  filename - HDF5 file name in full path
	#  path		- the full path of the attribute
	#  data     - attribute data to be written.
	#  options  overwrite - logical value to indicate if an existing attribute will get
	#						overwritten.
	#           compresslevel - integer value (0-9) to indicate data compression level.
	#							Higher compression results in longer time. Default(0)
	#
	if (missing(filename))
		stop("HDF5WriteAttribute: parameter filename is missing.")
	if (missing(path))
		stop("HDF5WriteAttribute: parameter path is missing.")
	if (length(data)==0)	
		stop("HDF5WriteAttribute: data does not exist or is empty.")

 	paramAttr=list()
	tempOptions<-names(options)
	for(option in tempOptions)
		if ((tolower(option)=="overwrite")||
			(tolower(option)=="compresslevel"))
			paramAttr[option]<-toString(options[option])
		else 
			paramAttr[option]<-options[option]
			
	lintdata<-integer()
	ldoubledata<-double()
	lstrdata<-as.character(list())
	ldataframedata<-a<-as.data.frame(list())
	if (is.vector(data))
		data<-as.array(data)
	if (is.integer(data))
		lintdata<-t(data)
	if (is.double(data))
		ldoubledata<-t(data)
	if (is.character(data))
		lstrdata<-t(data)
		
	size<-dim(data)	
    paramAttr["row"]<-toString(size[1])		
    paramAttr["col"]<-toString(size[2])		
    if (is.na(size[1]) && !is.na(size[2]))
		paramAttr["row"]<-"1"
    if (is.na(size[2]) && !is.na(size[1]))
		paramAttr["col"]<-"1"
    
    results<-HDF5Execute("writeattr",
	                      filename=filename,
                        path=path,
                        intdata=lintdata,
                        doubledata=ldoubledata,
                        strdata=lstrdata,
                        dataframedata=ldataframedata,
                        attributes=paramAttr,
                        debug=FALSE)

        
}
