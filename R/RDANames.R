"RDANames" <-
function(argname)
{
#
# Returns valid values associated with the argument name used by the
# function "GetResolverEG". The argument name is one of the following:
#      species, 
#      fields, 
#      tod (type-of-data), 
#      lod (level-of-detail), 
#      todPDQ (tod predefined query),
#      lodPDQ(lod predefined query)
#
# [Note: This routine is used by the function "GetResolverEG" and should not
#  be modified.]
#
# Arguments
#  argname      argument name
#               (if missing, values for all arguments are returned)
#
	int.species=casefold(c("Candida","Chicken","Dog","Ecoli","Human",
                   "Mouse","Rat","Synthetic","Yeast","YeastGRM"))
	int.all.species=paste(int.species,collapse=" ")
	#
	# fields
	#
	int.fields=RDAFields("internal")
	int.all.fields=paste(int.fields,collapse=" ")
	#
	# lod pdq
	#
	int.lodPDQs=c("accession","bioset","code","name","query","genemodel_code")
	int.all.lodPDQs=paste(int.lodPDQs,collapse=" ")
	#
	# tod pdq
	#
	int.todPDQs=c("pc","edc","bioset","query", "puc")
	int.all.todPDQs=paste(int.todPDQs,collapse=" ")
	#
	# tods
	#
	int.tods=c("re","rp","ie","ip")
	int.all.tods=paste(int.tods,collapse=" ")
	#
	# lod
	#
	int.lods=c("reporter","sequence","unigene","genemodel","reliable_gm")
	int.all.lods=paste(int.lods,collapse=" ")
	#
	# output
	#
	if (missing(argname))
		argname="all"
	else
		argname=as.character(argname)
	result=switch(argname,
			species=int.species,
			fields=int.fields,
			tod=int.tods,
			lod=int.lods,
			todPDQ=int.todPDQs,
			lodPDQ=int.lodPDQs,
			all=list(species=int.species, 
                                 fields=int.fields,
	                         tod=int.tods,
	                         lod=int.lods,
	                         todPDQ=int.todPDQs,
     				 lodPDQ=int.lodPDQs),
			internal=list(species=int.species, allspecies=int.all.species,
	                              fields=int.fields, allfields=int.all.fields,
	                              tods=int.tods, alltods=int.all.tods,
	                              lods=int.lods, alllods=int.all.lods,
	                              todPDQs=int.todPDQs, alltodPDQs=int.all.todPDQs,
				      lodPDQs=int.lodPDQs, alllodPDQ=int.all.lodPDQs),
			stop(paste("Name type '",names,"' not defined.",sep=""))
			)
	return(result)
}
