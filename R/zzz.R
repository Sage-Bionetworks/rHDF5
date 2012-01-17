
.onLoad <- function(libname, pkgname) {
    require("methods", character=TRUE, quietly=TRUE)
    loadRcppModules()
    ## load and attach hdf5 constants
    env <- new.env()
    setPackageName("hdf5Constants", env)
    cc <- new(H5constants)
    lapply(names(H5constants@methods), function(ff){
		x <- gsub("^get_", "", ff)
		assign(x, eval(parse(text=sprintf("cc$%s()", ff))), envir = env)
    	}
    )
    attach(env, name="hdf5Constants")
}

