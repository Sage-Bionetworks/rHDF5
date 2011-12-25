\name{RDAExecute}
\alias{RDAExecute}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Execute Resolver Data Access  }
\description{
  Call the bat C++ DLL to execute a task associated with getting data from Resolver.
}
\usage{
RDAExecute(task, species, rHandle, todIds, lodIds, 
           tod = "re", lod = "sequence", fields = "eg", 
           todQuery, lodQuery, 
           dbuser, dbpwd, dbname, dbpath, options, 
           debug = FALSE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{task}{ The task to execute in getting Resolver data. One of the following:
expression; annotation; egall; metainfo; resolverids; opendb; closedb;
 login; logout. }
  \item{species}{ The species database.  One of the following:
  human; yeast; mouse; rat; dog; ecoli; chicken; yeastgrm; synthetic; candida.}
  \item{rHandle}{ db handle returned from ResolverLogin function. }
  \item{todIds}{ A vector of doubles containing tod ids for getting expression data. }
  \item{lodIds}{ A vector of doubles containing lod ids for getting expression data. }
  \item{tod}{ Type of data.  One of the following: re; rp; ie; ip. }
  \item{lod}{ Level of detail.  One of the following: feature; reporter; sequence; unigene. }
  \item{fields}{ A comma separated list of one or more expression fields: value; error;
  pvalue; seqcount; background; xdev; logintensity; intensity1; intensity2;
  failcode; controlflag}
  \item{todQuery}{ A list containing named query data for getting tod IDs.  Query data
  includes query name and query arguments. }
  \item{lodQuery}{ A list containing named query data for getting lod IDs. }
  \item{dbuser}{ Resolver user name. }
  \item{dbpwd}{ Resolver user password. }
  \item{dbname}{ Resolver database (e.g., "MRLSP01") }
  \item{dbserver}{ Resolver server (e.g., "snwspr18.merck.com") }
  \item{options}{ Optional arguments. }
  \item{debug}{ Control verbose output of information during execution. }
}
\value{
  A list containing the follow fields or components:
  \item{ced }{A list containing core expression data for each field}
  \item{todids }{A numeric vector containing the tod ids}
  \item{lodids }{A numeric vector containing the lod ids}
  \item{todinfo }{A list containing tod annotation information}
  \item{lodinfo }{A list containing lod annotation information}
}
\author{ r. kuraisa }
\note{
 This is an internal routine and invoked by GetResolverEG and ResolverLogin.
 It should NOT be modified.
}

\seealso{ GetResolverEG ResolverLogin  }
\keyword{ database }% at least one, from doc/KEYWORDS
