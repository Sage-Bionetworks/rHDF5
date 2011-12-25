\name{RDANames}
\alias{RDANames}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Names for GetResolverEG }
\description{
  Returns valid names associated with arguments used by
  the function GetResolverEG.  The argument names include:
  species; fields; type of data; level of detail; predefined queries.
}
\usage{
RDANames(argname)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{argname}{ The argument name: species; fields; tod; lod;
  todPDQ; or lodPDQ.  If not specified, then all names are returned. }
}
\value{
	A list containing one or more of the following fields (depending on argname):
  \item{species }{comma separated list of species names.}
  \item{fields }{comma separated list of field names.}
  \item{tod }{comma separated list of type-of-data (tod) names.}
  \item{lod }{comma separated list of level-of data (lod) names.}
  \item{todPDQ }{comma separated list of predefined queries (pdq) for tods.}
  \item{lodPDQ }{comma separated list of predefined queries (pdq) for lods.}
}
\author{ r. kuraisa }
\note{
 This is invoked by GetResolverEG and should NOT be modified.
}

\seealso{ GetResolverEG RDAExamples ResolverLogin }
\examples{
 # list the names of the tod types
 RDANames("tod")

 # list the names of the lod types
 RDANames("lod")

 # list the names of all the tod predefined queries
 RDANames("todPDQ")

 # list all the names
 RDANames()
}
\keyword{ database }% at least one, from doc/KEYWORDS
