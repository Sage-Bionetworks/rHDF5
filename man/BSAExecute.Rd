\name{BSAExecute}
\alias{BSAExecute}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Execute BSA Data Access  }
\description{
  Call the bsa C++ DLL to execute a task associated with getting data from BSA.
}
\usage{
BSAExecute(ids, fields="all", itype="bsa", task="annotation",
           options, debug=FALSE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{ids}{ A character vector containing input ids for getting BSA data.
  See argument itype. }
  \item{fields}{ A character vector naming the fields (or attributes) to be
  retrieved from BSA associated with the input ids. }
  \item{itype}{ A string naming the type of input ids.  One of the following: 
  bsa (sample ids), chip (chip barcodes), or pc (project code). }
  \item{task}{ The task to execute in getting BSA data. One of the following:
  info; annotation. }
  \item{options}{ Optional arguments. }
  \item{debug}{ Control verbose output of information during execution. }
}
\value{
  A list containing the follow fields:
  \item{inputids }{A character vector containing the input ids}
  \item{sampleids }{A character vector containing the sample ids associated 
  with the inputids}
  \item{<field1> }{A list for one BSA attribute containing three fields: (1) description - describing 
  the attribute; (2) type - the data type of the attribute; and (3) values - the attribute's
  values associated with each input id}
  \item{<...> }{More attributes' lists}
  \item{<fieldn> }{The last attribute list}
}
\author{ r. kuraisa }
\note{
 This is an internal routine and invoked by BSAInfo. It should
 NOT be modified.
}

\seealso{ BSAInfo }
\examples{
    # get all annotation by project code
    bdata<-BSAExecute(("11173",itype="pc")

    # get a list of available attributes
    binfo<-BSAExecute(task="info")
}
\keyword{ database }% at least one, from doc/KEYWORDS
