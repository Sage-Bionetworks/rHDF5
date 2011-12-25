\name{RDAids}
\alias{RDAids}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ ID Generator}
\description{
  Generate a list that can be used as an argument to GetResolverEG for
  either tod or lod ids. The list is based on an existing named query in
  Resolver.  The named query can either be a predefined query or a user defined
  query.
  
  The generated list includes a field that is a string which concatentates
  all of the parameters into a single string delimited by a delimiter
  (Default delimiter: "/").
}
\usage{
RDAids(qname, qparams, userquery = FALSE, delimiter = "/")
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{qname}{ name of predfined query (see RDANames) or user query. }
  \item{qparams}{ character vector for parameters associated with the 
  predefined query or user query. }
  \item{userquery}{ flag to indicate if query is user defined. }
  \item{delimiter}{ delimiter between multiple parameters in query.}
}
\value{
   The return list contains the following fields:
  \item{type }{type of query.}
  \item{name }{name of query.}
  \item{params }{parameters of query concatentated as a single string delimited
  by the delimiter (default:"/").}
}
\author{ r. kuraisa }
\note{ If a character within a parameter is also the delimiter either select another
 delimiter or repeat the character within the parameter (see Examples) }

\seealso{ GetResolverEG RDAExecute RDANames RDAFields RDAExamples RDASummary ResolverLogin  }
\examples{
 # create tod ids using a predefined query for project unit code (puc)
 # Note: "puc" is deprecated; users show use "edc" (experiment definition code)
 todids = RDAids("puc", "1000094")
 eg = GetResolverEG(hconn, fields="eg", species="human",todids=todids)

 todids = RDAids("edc", "1000094")
 eg = GetResolverEG(hconn, fields="eg", species="human",todids=todids)

 # create tod ids using a user named query "MyIEQuery" and takes two parameters
 # Note: the second parameter includes a character ("/") which is also the delimiter;
 # this is escaped by inserting the character twice.
 todids = RDAids(""PDQ_IE_EXPNAME_CHIP"", c("PTPN1//DIO","MT2001"), T)
 fields = c("value", "error", "background", "seqcount")
 eg = GetResolverEG(hconn, fields=fields, species="mouse", todids=todids, tod="ie")
}
\keyword{ database }% at least one, from doc/KEYWORDS
