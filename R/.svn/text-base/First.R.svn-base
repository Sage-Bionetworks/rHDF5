.First.lib <-function(liba, pkg)
{
    lib<-sub("\/\/","\/",liba)
	cat("Loading DLL for ",pkg,"\n")
	library.dynam(pkg,pkg,lib)
	local({
		rdahome=paste(lib,"/",pkg,"/data",sep="")
		cat("Intializing BAT_HOME to ",rdahome,"\n")
		BATInit(rdahome)
	})
}
