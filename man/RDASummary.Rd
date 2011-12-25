\name{RDASummary}
\alias{RDASummary}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Summary of data access structure }
\description{
  Outputs a summary of one or more fields in the output structure (list)
  returned from GetResolverEG.
}
\usage{
RDASummary(rdaList, ced = T, todinfo = F, lodinfo = F, all = F)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{rdaList}{ Output list returned by GetResolverEG. }
  \item{ced}{ Summarize on the core expression data. }
  \item{todinfo}{ Summarize the tod annotation information. }
  \item{lodinfo}{ Summarize the tod annotation information. }
  \item{all}{ Summarize entire structure. }
}
\author{ r. kuraisa }
\note{ None at this time }

\seealso{ GetResolverEG RDAExamples }
\examples{
 # full eg using specified tod ids
 todIDs = c(10000629692., 10000629693., 10000629694., 10000629695., 10000629696.);
 eg = GetResolverEG(hc, "eg", "human", todIDs)

 # summary of only the core expression data (ced)
 RDASummary(eg)

 # summary of the ced, tod and lod info
 RDASummary(eg,todinfo=T,lodinfo=T)

 # summary of all
 RDASummary(eg,all=T)

 # list all the names
 RDANames()
}
\keyword{ database }% at least one, from doc/KEYWORDS
