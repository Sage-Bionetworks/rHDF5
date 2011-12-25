\name{ResolverLogin}
\alias{ResolverLogin}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Log into Resolver }
\description{
  Log into Resolver database for getting core expression (and related) data.
}
\usage{
ResolverLogin(user, pwd, dbname, dbserver, debug = FALSE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{user}{ Resolver user name }
  \item{pwd}{ Resolver user password }
  \item{dbname}{ Resolver db (e.g., "MRLSNAP1") }
  \item{dbserver}{ Resolver server (e.g., "snwspr18.merck.com") }
  \item{debug}{ Output debug (or more verbose) information }
}
\value{
	A double representing the handle associated with the Resolver database.
}
\author{ r. kuraisa }
\note{ 
  Currently, you cannot logout after logging into Resolver.  If this is desired,
  then you must exit R and execute another login. 
}

\seealso{ GetResolverEG RDAExecute RDAExamples  }
\examples{
  # login 
  server = "joy.merck.com"
  hc = ResolverLogin("you", "you", dbname="MRLSNAP1", dbserver=server)
}
\keyword{ database }% at least one, from doc/KEYWORDS
