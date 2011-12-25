"RDAFields" <-
function(argname)
{
#
# Returns valid field names associated with ratio or intensity data
# used by the function "GetResolverEG". The argument name is one of
# the following:
#      ratio, 
#      intensity
#
# [Note: This routine is used by the function "GetResolverEG" and should not
#  be modified.]
#
# Arguments
#  argname      argument name
#               (if missing, field names for both data are returned)
#
	fields.ratio<-c("value","error","pvalue","controlflag","failcode",
                       "xdev","intensity1","intensity2","logintensity")
	fields.intensity<-c("value","error","pvalue","controlflag","failcode",
                           "background","seqcount")
	fields.internal<-c("value","pvalue","error","xdev","controlflag","failcode","intensity1",
                          "intensity2","logintensity","background","seqcount","eg")
	#
	# output
	#
	if (missing(argname))
	    argname<-"all"
        else
            argname<-as.character(argname)
	result<-switch(argname,
		      ratio=fields.ratio,
		      intensity=fields.intensity,
		      all=list(ratio=fields.ratio,
                               intensity=fields.intensity),
		      internal=fields.internal,
		      stop(paste("Name type '",names,"' not defined.",sep<-""))
		      )
        return(result)
	
}
