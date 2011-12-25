"ResolverLogin" <-
function (user,
			pwd,
			dbname,
			dbserver,
			debug=FALSE)
{
	#
	# Log into an instance of Resolver
	#
	# Arguments
	#  user    User name in Resolver
	#  pwd     Password in Resolver
	#  db      Name of Resolver Database (e.g., "MRLPROD")
	#  server  Name of Resolver server (e.g., "joy.merck.com")
	#
    results<-RDAExecute("login",
                        dbuser=user,
                        dbpwd=pwd,
                        dbserver=dbserver,
                        dbname=dbname,
                        debug=debug)
    results$DbHandle
}
