"RDAids" <-
function(qname,qparams,userquery=FALSE,delimiter="/")
{
#
# Generate a list for either a predefined query or a user query
#
# Arguments
#  qname       name of predfined query (see RDANames) or user query.
#  qparams     character vector for parameters associated with the
#              predefined query or user query.
#  userquery   flag to indicate if query is user defined. 
#
	qname=as.character(qname)
	qparams=as.character(qparams)
	if (userquery)
	{
		#
		# user defined query
		#
		type="user"
		name=qname
	}
	else
	{
		#
		# pdq
		#
		type="pdq"
		name=casefold(qname)
	}
	#
	# combine the parameters into a single string,"/" delimited
	#
	int.params=paste(qparams,collapse=delimiter)
	#
	# create the list
	#
	list(type=type,name=name,params=int.params)
}
