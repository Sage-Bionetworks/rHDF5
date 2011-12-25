"BSAInfo" <-
function(ids=c(),
         fields="all",
         itype="bsa",
         task="annotation",
         options=list(),
         simplify.out=TRUE,
         debug=FALSE)
        
{
    #
    #   High level function for getting bsa information
    #
    #   Arguments:
    #   ids:        Input ids (e.g., sample barccode) to get information about.
    #   fields:     BSA fields or names of attributes
    #   itype:      Type of input ids.
    #               [bsa chip pc]
    #   task:       The task to execute in getting BSA information.
    #               [annotation info]
    #   simplify.out Use the simplify function to create an output
    #                structure containing data frames, etc.
	if(debug) {
		cat(">>> Parameters to BSAExecute\n")
		cat(">>> task: ", task, "\n")
		cat(">>> fields: ", fields, "\n")
		cat(">>> input type: ", itype, "\n")
		cat(">>> ids: ", ids, "\n")
		cat(">>> simplify.out",simplify.out, "\n")
		cat(">>> options: ", options, "\n")
	}

    #
    # call the lower level
    #
    bdata<-BSAExecute(ids,
               fields,
               itype,
               task,
               options,
               debug)
    if (simplify.out && tolower(task)!="info") {
        BSASimplify(bdata)
    }
    else {
        return(bdata)
    }
}
