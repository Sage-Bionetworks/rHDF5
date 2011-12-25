BATInit<-function(home)
{
	#
	# Initializes the RDA environment by setting the
	# environment variable RDA_HOME to the path specified.
	#
	# Arguments
	#    home:		the root or home path of the RDA chapter
	#
	invisible(.Call("BATInit",home))
}
