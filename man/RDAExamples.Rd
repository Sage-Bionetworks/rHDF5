\name{RDAExamples}
\alias{RDAExamples}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Resolver Data Access Examples }
\description{
  A function that executes various GetResolverEG in getting core
  expression data.
}
\usage{
RDAExamples(user, pwd, db = "MRLSP01", server = "snwspr18.merck.com", debug = FALSE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{user}{ Resolver user name }
  \item{pwd}{ Resolver user password }
  \item{db}{ Resolver db (e.g., "MRLSP01") }
  \item{server}{ Resolver server (e.g., "snwspr18.merck.com") }
  \item{debug}{ Output debug (or more verbose) information }
}
\details{
  Runs various examples getting data from Resolver and summarizes
  the results to standard output.
}
%- \references{ ~put references to the literature/web site here ~ }
\author{ r. kuraisa }
\note{
 To see output as the examples are being executed be sure to disable
 buffered output (via command window Misc->Buffered Output) }

\seealso{ GetResolverEG RDAExecute RDANames RDAids RDAFields RDASummary ResolverLogin  }
\examples{
  # Note: To see output as the examples are being executed
  # be sure to disable buffered output (via command window
  # Misc->Buffered Output)
  server = "sse0pr08.merck.com"
  RDAExamples("you", "you", "MRLPROD", server)
}
\keyword{ database }% at least one, from doc/KEYWORDS
