\name{RDAFields}
\alias{RDAFields}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Field names of core expression data from Resolver}
\description{
Returns valid field names associated with ratio or intensity data
used by the function GetResolverEG.
}
\usage{
RDAFields(argname)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{argname}{ Type of data: "ratio" or "intensity".  If not specified field
  names for both types are returned. }
}
\value{
 If an argument is specified ("ratio" or "intensity") then a vector of strings is
 returned.  If no argument is specified then a list is returned with two fields:
  \item{ratio }{A vector of strings naming the available fields for ratio tods.}
  \item{intensity }{A vector of strings naming the available fields for intensity tods.}
}
\author{ r. kuraisa }
\note{
 This is invoked by RDANames and should NOT be modified.
}

\seealso{ GetResolverEG RDANames }
}
\examples{
 # list the intensity field names
 RDAFields("intensity")

 # list field names for both intensity and ratio types
 RDAFields()
}
\keyword{ database }% at least one, from doc/KEYWORDS
