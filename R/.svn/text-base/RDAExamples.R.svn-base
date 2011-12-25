"RDAExamples" <-
function(user, 
         pwd, 
         db = "MRLSP01", 
         server = "snwspr18.merck.com", 
         debug = FALSE)
{
	#
	# A function that illustrates executing the following:
	#      o  the function ResolverLogin to log into Resolver.
	#      o  the function GetResolverEG to get Resolver 
	#         data.
	#      o  RDANames to list valid names.
	#      o  RDASummary to summarize the results from
	#         executing GetResolverEG.
	#      o  RDAids to create lists for specifying either
	#         predefined named queries or user-defined
	#         named queries.
	#
	# Arguments
	#   user   Valid Resolver user name.
	#   pwd    Password associated with user.
	#   server Resolver server
	#   db     Resolver database name
	#
	if(missing(user))
		stop("'user' is required.")
	else
		user<-as.character(user)
	if(missing(pwd))
		stop("'pwd' is required.")
	else
		pwd<-as.character(pwd)
	cat(">>> List of all of the valid names ...\n")
	RDA.names <- RDANames("all")
	cat(">>>     Species: ", RDA.names$species[1:5], "\n")
	cat(">>>              ", RDA.names$species[6:length(RDA.names$species)], "\n")
	cat(">>>     Fields: ", RDA.names$fields[1:5], "\n")
	cat(">>>             ", RDA.names$fields[6:9], "\n")
	cat(">>>             ", RDA.names$fields[10:length(RDA.names$fields)], "\n")
	cat(">>>     tod: ", RDA.names$tod, "\n")
	cat(">>>     lod: ", RDA.names$lod, "\n")
	cat(">>>     tod PDQ: ", RDA.names$todPDQ, "\n")
	cat(">>>     lod PDQ: ", RDA.names$lodPDQ, "\n")
	cat("\n>>> 1. Executing -- ResolverLogin ...\n")
	hconn <- ResolverLogin(user, pwd, db, server, debug)
	cat("\n>>> 2. Executing -- GetResolverEG with the following specifications:\n")
	cat(">>>     species:  human\n")
	cat(">>>     fields:   eg\n")
	cat(">>>     tod ids:  explicitly defined\n")
	cat(">>>     lod ids:  not specified; get all that map to the tods\n")
	cat(">>>     tod:      re (implictly defined)\n")
	cat(">>>     lod:      sequence (implicitly defined)\n")
	eg <- GetResolverEG(hconn, "eg", "human", c(10000629692., 10000629693., 10000629694., 10000629695., 10000629696.))
	cat(">>> 3. Executing -- RDASummary to summarize the results for core expression data \n")
	RDASummary(eg,all=TRUE)
	cat("\n>>> 4. Executing -- GetResolverEG with the following specifications:\n")
	cat(">>>     species:  human\n")
	cat(">>>     fields:   value, pvalue\n")
	cat(">>>     tod ids:  explicitly defined\n")
	cat(">>>     lod ids:  not specified; get all that map to the tods\n")
	cat(">>>     tod:      re (implictly defined)\n")
	cat(">>>     lod:      sequence (implicitly defined)\n")
	eg <- GetResolverEG(hconn, c("value", "pvalue"), "human", c(10000629692., 10000629693., 10000629694., 10000629695., 10000629696.))
	cat(">>> 5. Executing -- RDASummary to summarize the results for core expression data")
	RDASummary(eg,all=TRUE)
	cat("\n>>> 6. Executing -- GetResolverEG with the following specifications:\n")
	cat(">>>     species:  human\n")
	cat(">>>     fields:   eg\n")
	cat(">>>     tod ids:  indirectly by project code using a predefined named query\n")
	cat(">>>     lod ids:  not specified; get all that map to the tods\n")
	cat(">>>     tod:      re (implictly defined)\n")
	cat(">>>     lod:      sequence (implicitly defined)\n")
	eg <- GetResolverEG(hconn, "eg", "human", RDAids("edc", "1000094"))
	cat(">>> 7. Executing -- RDASummary to summarize the results for core expression data")
	RDASummary(eg,all=TRUE)
	cat("\n>>> 8. Executing -- GetResolverEG with the following specifications:\n")
	cat(">>>     species:  mouse\n")
	cat(">>>     fields:   value error background seqcount\n")
	cat(">>>     tod ids:  indirectly by user defined named query\n")
	cat(">>>     lod ids:  not specified; get all that map to the tods\n")
	cat(">>>     tod:      ie (exlicitly defined)\n")
	cat(">>>     lod:      sequence (implicitly defined)\n")
	cat(">>>     options:  include flagged data\n")
	opts <- list(IncludeFlaggedData="True",OrderBy="none")
	eg <- GetResolverEG(hconn, c("value", "error", "background", "seqcount"), "mouse", RDAids("PDQ_IE_EXPNAME_CHIP", c("PTPN1//DIO","MT2001"), T), tod = "ie", options = opts)
	cat(">>> 9. Executing -- RDASummary to summarize the results for core expression data")
	RDASummary(eg,all=TRUE)
	cat("\n>>> 10. Executing -- GetResolverEG with the following specifications:\n")
	cat(">>>     species:  human\n")
	cat(">>>     fields:   eg\n")
	cat(">>>     tod ids:  indirectly by project code defined named query\n")
	cat(">>>     lod ids:  not specified; get all that map to the tods\n")
	cat(">>>     tod:      re (implicitly defined)\n")
	cat(">>>     lod:      sequence (implicitly defined)\n")
	cat(">>>     bsa:      include bsa information\n")
	cat(">>>     options:  include flagged data\n")
	opts <- list(IncludeFlaggedData="True")
	eg <- GetResolverEG(hconn, "eg", "human", RDAids("pc","11068"), options = opts)
	cat(">>> 11. Executing -- RDASummary to summarize the results for core expression data")
	RDASummary(eg,all=TRUE)
	invisible()
}
