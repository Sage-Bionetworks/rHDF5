"GetResolverEG" <-
function(hconn, 
			fields, 
			species, 
			todids = list(), 
			lodids = list(), 
			tod = "re", 
			lod = "sequence",
            bsa = FALSE,
			debug = FALSE, 
			options = list(),
            bsa.simplify=TRUE)
{
	#
	# Get expression data (similar to eg in Matlab) from resolver.
	#
	# Arguments
	#  hconn     db handle returned from ResolverLogin function
	#  fields    core expression data field name.  Either "eg" or
	#            a character vector of one or more from the supported fields
	#            (see function RDANames).  "eg" is used only for ratio data and
	#            returns the following fields: value, pvalue, error, 
	#            xdev, intensity1, intensity2, and control|fail code.
	#  species   one of the supported species (see function RDANames)
	#            in MRLPROD
	#  todids    either a vector of doubles containing tod ids or a list
	#            specifying a name query to get the tod ids (see function
	#            RDAids)
	#  lodids    either a vector of doubles containing lod ids or a list
	#            specifying a name query to get the lod ids (see function
	#            RDAids)
	#  tod       type of data (see function RDANames)
	#  lod       level of detail (see function RDANames)
    #  bsa       include bsa information
	#  debug     output debug parameters
	#  options   name, value list of options 
    #  bsa.simplify convert bsa output to dataframes.
	#
	rdanames = RDANames("internal")
	#
	# check the args
	#
	hconn<-as.numeric(hconn)
	fields<-as.character(fields)
	species<-as.character(species)
	if(!is.list(todids) && !is.numeric(todids))
		stop("todids argument must be numeric or list")
	if(!is.list(lodids) && !is.numeric(lodids))
		stop("lodids argument must be numeric or list")
	tod=as.character(tod)
	lod=as.character(lod)
	#
	# lowercase input
	#
	fields = casefold(fields)
	species = casefold(species)
	tod = casefold(tod)
	lod = casefold(lod)
	#
	# validate species
	#
	if(length(species) != 1) stop("Only one species can be specified")
	if(is.na(match(species, rdanames$species)))
		stop("Invalid species - ", species, " (", rdanames$allspecies, ")")
	#
	# validate field
	#
	if(any(is.na(match(fields, rdanames$fields)))) stop("One or more invalid fields - ", fields, " (", rdanames$allfields, ")")
	if(length(fields) == 1 && fields[1] == "eg")
		fields = character()
	#
	# validate tod
	#
	if(length(tod) != 1) stop("Only one tod can be specified")
	if(is.na(match(tod, rdanames$tods)))
		stop("Invalid tod - ", tod, " (", rdanames$alltods, ")")
	#
	# validate lod
	#
	if(length(lod) != 1) stop("Only one lodcan be specified")
	if(is.na(match(lod, rdanames$lods)))
		stop("Invalid lod- ", lod, " (", rdanames$alllods, ")")
	#
	# internal data for processing todids; lodids
	#
	int.none = "none"
	int.id = "id"
	int.query = "query"
	int.userquery = "user"
	int.pdqquery = "pdq"
	RDA.todids = double()
	RDA.lodids = double()
	#
	# todids
	#   todids can be one of the following:
	#      (1) list (e.g., type='pdq', name="puc", param='10224')
	#      (2) numeric vector (e.g., 1000000001, 10000022)
	#
	if(is.double(todids)) {
		#
		# set the pdqs to noop; int
		#
		RDA.todQuery = ""
		RDA.todQueryParams = ""
		RDA.todids = todids
		int.todId.choice = int.id
	}
	else {
		if(is.list(todids) && length(todids) == 0) {
			#
			# nothing passed in
			#
			RDA.todQuery = ""
			RDA.todQueryParams = ""
			RDA.todids = double()
			int.todId.choice = int.none
		}
		else {
			int.todId.choice = int.query
			#
			# process the list - check the type
			#
			if(todids$type == int.userquery) {
				#
				# user query - validate param
				#
				if(length(todids$params) == 0) stop("User query ", todids$name, " has no parameters.")
				RDA.todQuery = todids$name
				RDA.todQueryParams = todids$params
			}
			else {
				#
				# pdq - first validate name
				#
				int.todId.pdq = match(todids$name, rdanames$todPDQ)
				if(is.na(int.todId.pdq))
					stop("Invalid query name in todids - ", todids$name, "(", rdanames$alltodPDQ, ")")
				#
				# valid params
				#
				if(length(todids$params) == 0) stop("Predefined query ", todids$name, " has no parameters.")
				#
				# build the real name of the pdq
				#
				RDA.todQuery = paste("PDQ_", tod, "_", todids$name, sep = "")
				RDA.todQuery = casefold(RDA.todQuery, upper = T)
				RDA.todQueryParams = todids$params
			}
		}
	}
	#
	# lodids
	#   lodids can be one of the following:
	#      (1) list (e.g., type='pdq', name="puc", param='10224')
	#      (2) numeric vector (e.g., 1000000001, 10000022)
	#
	if(is.double(lodids)) {
		#
		# set the pdqs to noop; int
		#
		RDA.lodQuery = ""
		RDA.lodQueryParams = ""
		RDA.lodids = lodids
		int.lodId.choice = int.id
	}
	else {
		if(is.list(lodids) && length(lodids) == 0) {
			#
			# nothing passed in
			#
			RDA.lodQuery = ""
			RDA.lodQueryParams = ""
			RDA.lodids = double()
			int.lodId.choice = int.none
		}
		else {
			int.lodId.choice = int.query
			#
			# process the list - check the type
			#
			if(lodids$type == int.userquery) {
				#
				# user query - validate param
				#
				if(length(lodids$params) == 0) stop("User query ", lodids$name, " has no parameters.")
				RDA.lodQuery = lodids$name
				RDA.lodQueryParams = lodids$params
			}
			else {
				#
				# pdq - first validate name
				#
				int.lodId.pdq = match(lodids$name, rdanames$lodPDQ)
				if(is.na(int.lodId.pdq))
					stop("Invalid query name in lodids - ", lodids$name, "(", rdanames$alllodPDQ, ")")
				#
				# valid params
				#
				if(length(lodids$params) == 0) stop("Predefined query ", lodids$name, " has no parameters.")
				#
				# build the real name of the pdq (genemodel is special)
				#
                if (lod=="genemodel" || lod=="reliable_gm")
                {
				    RDA.lodQuery = "PDQ_GENEMODEL_CODE"
                }
                else
                {
				    RDA.lodQuery = paste("PDQ_", lod, "_", lodids$name, sep = "")
                }
				RDA.lodQuery = casefold(RDA.lodQuery, upper = T)
				RDA.lodQueryParams = lodids$params
			}
		}
	}
	#
	# check for someway to get ids
	#
	if(int.lodId.choice == int.none && int.todId.choice == int.none) stop("Neither tod ids nor lod ids are specified")
	#
	# create the query lists
	#
	lodQueryList = list(name = RDA.lodQuery, params = RDA.lodQueryParams)
	todQueryList = list(name = RDA.todQuery, params = RDA.todQueryParams)
	#
	# task
	#
	task = "egall"
	if(debug) {
		cat(">>> Parameters to ResolverDataService\n")
		cat(">>> task: ", task, "\n")
		cat(">>> fields: ", fields, "\n")
		cat(">>> todids: ", RDA.todids, "\n")
		cat(">>> lodids: ", RDA.lodids, "\n")
		cat(">>> tod: ", tod, "\n")
		cat(">>> lod: ", lod, "\n")
		cat(">>> lodQueryList: ", lodQueryList$name," ",lodQueryList$params, "\n")
		cat(">>> todQueryList: ", todQueryList$name," ",todQueryList$params, "\n")
		cat(">>> species: ", species, "\n")
		cat(">>> rHandle: ", hconn, "\n")
	}
	#
	# execute
	#
	results = RDAExecute(task = task, species = species, rHandle = hconn, fields = fields, tod = tod, lod = lod, lodQuery = lodQueryList, todQuery = todQueryList, todIds = RDA.todids, lodIds = as.double(RDA.lodids), debug = debug, options = options)
	#
	# create the list
	#
    if(bsa) {
        #
        # there may be more than one experimental and/or reference sample; 
        # so we'll just take the first one of each
        #
        ecodes <- c()
        rcodes <- c()
        no.ecodes <- length(results$todinfo$biosample$experimentalcode)
        no.rcodes <- length(results$todinfo$biosample$referencecode)
        for (ie in 1:no.ecodes) {
            ecodes <- c(ecodes,
                        results$todinfo$biosample$experimentalcode[[ie]][1])
        }

        for (ir in 1:no.rcodes) {
            rcodes <- c(rcodes,
                        results$todinfo$biosample$referencecode[[ir]][1])
        }

        bsainfo.exp <- BSAInfo(ecodes,itype="bsa",simplify.out=bsa.simplify)
        bsainfo.ref <- BSAInfo(rcodes,itype="bsa",simplify.out=bsa.simplify)
        rr <- list(ced = results$ced, 
                   todids = results$todids, 
                   lodids = results$lodids, 
                   todinfo = results$todinfo, 
                   lodinfo = results$lodinfo,
                   bsainfo.exp = bsainfo.exp,
                   bsainfo.ref = bsainfo.ref)
    }
    else
	{
	    rr <- list(ced = results$ced, 
		           todids = results$todids, 
				   lodids = results$lodids, 
				   todinfo = results$todinfo, 
				   lodinfo = results$lodinfo)
	}

	if( (lod == "sequence") && (!is.null(options$primaryseqname)) && (as.logical(options$PrimarySeqName)))
	{
		seqName<-strsplit(rr$lodinfo$lodname,",")
		for(idx in 1:length(seqName))
		{
			rr$lodinfo$lodname[idx] <-seqName[[idx]][1]
		}
	}
	rr
}
