"RDASummary" <-
function(rdaList, ced = T, todinfo = F, lodinfo = F, bsainfo = F, all = F)
{
	#
	# Outputs a summary of the output list created by the function GetResolverEG
	#
	# Arguments
	#  rdaList    the list created by the function GetResolverEG.
	#  ced        a flag to control the summary of core expression
	#             data (CED).
	#  todinfo    a flag to control the summary of type-of-data
	#             information.
	#  lodinfo    a flag to control the summary of level-of-data
	#             information.
    #  bsainfo    a flag to control summary of bsa info
	#  all        a flag to control the summary of all of the elements
	#             in the list.
	#
	if(!is.list(rdaList)) stop("rdaList must be a list created by the function GetResolverEG")
	#
	# ced 
	#
	if(ced || all) {
		cat("<list>$ced summary\n")
		#
		# get all the fields
		#
		cedFields <- attributes(rdaList$ced)
		if(is.null(cedFields$names))
			cat("No CED fields present\n")
		else {
			fNames <- cedFields$names
			noAllFields <- length(fNames)
			#
			# iterate over the fields
			#
			for(index in 1:noAllFields) {
				info.label <- fNames[index]
				if(!is.null(rdaList$ced[[index]])) {
					info.nrow <- nrow(rdaList$ced[[index]])
					info.ncol <- ncol(rdaList$ced[[index]])
					info.dim <- paste(info.nrow, "x", info.ncol)
				}
				else info.dim <- "Null"
				info.line <- paste(">> ", info.label, ": ", info.dim, sep = "")
				#
				# output info
				#
				cat(info.line, "\n")
			}
		}
	}
	#
	# Information about the number of tod ids
	#
	if(todinfo || all) {
		cat("\n<list>$todids summary\n")
		#
		# get number of ids
		#
		noIDs <- length(rdaList$todids)
		if(noIDs == 0)
			cat("No tod ids present\n")
		else {
			info.line <- paste(">> Number of ids: ", noIDs, sep = "")
			#
			# output info
			#
			cat(info.line, "\n")
		}
	}
	#
	# Information about the number of tod ids
	#
	if(lodinfo || all) {
		cat("\n<list>$lodids summary\n")
		#
		# get number of ids
		#
		noIDs <- length(rdaList$lodids)
		if(noIDs == 0)
			cat("No tod ids present\n")
		else {
			info.line <- paste(">> Number of ids: ", noIDs, sep = "")
			#
			# output info
			#
			cat(info.line, "\n")
		}
	}
	#
	# tod info
	#
	if(todinfo || all) {
		cat("\n<list>$todinfo summary\n")
		#
		# get number of ids
		#
		noIDs <- length(rdaList$todids)
		if(noIDs == 0)
			cat("No tod ids present\n")
		else {
			info.line <- paste(">> Number of ids: ", noIDs, sep = "")
			#
			# output info
			#
			cat(info.line, "\n")
		}
		#
		# get all the info fields
		#
		todinfo <- attributes(rdaList$todinfo)
		if(is.null(todinfo$names))
			cat("No tod info present\n")
		else {
			fNames <- todinfo$names
			noAllFields <- length(fNames)
			#
			# iterate over the fields
			#
			for(index in 1:noAllFields) {
				info.label <- fNames[index]
				if(!is.null(rdaList$todinfo[[index]])) {
					info.nrow <- length(rdaList$todinfo[[index]])
					info.dim <- paste(info.nrow)
				}
				else info.dim <- "Null"
				info.line <- paste(">> Number of ", info.label,": ", info.dim, sep = "")
				#
				# output info
				#
				cat(info.line, "\n")
			}
		}
	}
	#
	# lod info
	#
	if(lodinfo || all) {
		cat("\n<list>$lodinfo summary\n")
		#
		# get number of ids
		#
		noIDs <- length(rdaList$lodids)
		if(noIDs == 0)
			cat("No lod ids present\n")
		else {
			info.line <- paste(">> Number of ids: ", noIDs, sep = "")
			#
			# output info
			#
			cat(info.line, "\n")
		}
		#
		# get all the info fields
		#
		lodinfo <- attributes(rdaList$lodinfo)
		if(is.null(lodinfo$names))
			cat("No lod info present\n")
		else {
			fNames <- lodinfo$names
			noAllFields <- length(fNames)
			#
			# iterate over the fields
			#
			for(index in 1:noAllFields) {
				info.label <- fNames[index]
				if(!is.null(rdaList$lodinfo[[index]])) {
					info.nrow <- length(rdaList$lodinfo[[index]])
					info.dim <- paste(info.nrow)
				}
				else info.dim <- "Null"
				info.line <- paste(">> Number of ", info.label, ": ", info.dim, sep = "")
				#
				# output info
				#
				cat(info.line, "\n")
			}
		}
	}
    #
    # bsainfo
    #
	if(bsainfo || all) {
        #
        # reference
        #
		cat("\n<list>$bsainfo.ref summary\n")
		#
		# get number of attributes
		#
		noFields <- length(rdaList$bsainfo.ref)
		if(noFields == 0)
			cat("bsainfo.ref present\n")
		else {
			info.line <- paste(">> Number of attributes: ", noFields-2, sep = "")
			#
			# output info
			#
			cat(info.line, "\n")
		}
        if(bsainfo) {
            bf <- attributes(rdaList$bsainfo.ref)
            #
            # get the attribute names (skip the input ids)
            #
            noCs <- 0;
            aName <- c()
            for(index in 1:noFields) {
                if (index > 2) {
                    l1 <- nchar(bf$name[index])
                    if (l1+noCs > 50) {
                        csep <- "\n\t"
                        noCs <- l1
                    }
                    else {
                        noCs <- noCs+l1
                        csep <- "\t"
                    }

                    aName <- paste(aName, bf$name[index],sep=csep)
                }
            }
            info.line <- paste(">> Attributes:\n",aName,sep="")
            cat(info.line,"\n")
        }
        #
        # experimental
        #
		cat("\n<list>$bsainfo.exp summary\n")
		#
		# get number of attributes
		#
		noFields <- length(rdaList$bsainfo.exp)
		if(noFields == 0)
			cat("bsainfo.exp present\n")
		else {
			info.line <- paste(">> Number of attributes: ", noFields-2, sep = "")
			#
			# output info
			#
			cat(info.line, "\n")
		}
        if(bsainfo) {
            bf <- attributes(rdaList$bsainfo.exp)
            #
            # get the attribute names (skip the input ids)
            #
            noCs <- 0;
            aName <- c()
            for(index in 1:noFields) {
                if (index > 2) {
                    l1 <- nchar(bf$name[index])
                    if (l1+noCs > 50) {
                        csep <- "\n\t"
                        noCs <- l1
                    }
                    else {
                        noCs <- noCs+l1
                        csep <- "\t"
                    }

                    aName <- paste(aName, bf$name[index],sep=csep)
                }
            }
            info.line <- paste(">> Attributes: ",aName,sep="\n")
            cat(info.line,"\n")
        }
    }
	invisible()
}
