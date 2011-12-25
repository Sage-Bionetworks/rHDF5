\name{GetResolverEG}
\alias{GetResolverEG}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Get Resolver Core Expression Data }
\description{
  Return a list containing core expression data and associated
  annotation.
}
\usage{
GetResolverEG(hconn, fields, species, todids = list(), 
              lodids = list(), tod = "re", lod = "sequence", 
              bsa = FALSE, debug = FALSE, options = list(),
              bsa.simplify = TRUE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{hconn}{ Db handle returned from ResolverLogin function }
  \item{fields}{ Names of fields that will return data.  Either "eg" or
                 a character vector of one or more from the supported fields
                 (see function RDANames).  "eg" is a short-cut for a list of
		 predefined names associated with ratio data.  Specifying "eg"
                 returns data for the following fields:
                 \tabular{l}{
                              value \cr
                              pvalue \cr
                              error \cr
                              logintensity \cr
                              xdev \cr
                              failcode \cr
                              controlflag
                            }
                }
  \item{species}{ Warehouse species in Resolver (See function \emph{RDANames}). }
  \item{todids}{ Either a vector of doubles containing tod ids or a list 
                 specifying a name query to get the tod ids (see function
                 \emph{RDAids}). }
  \item{lodids}{ Either a vector of doubles containing lod ids or a list 
                 specifying a name query to get the lod ids (see function
                 \emph{RDAids}). }
  \item{tod}{ Type of data (See function \emph{RDANames}) }
  \item{lod}{ Level of data or detail (see function \emph{RDANames}). }
  \item{bsa}{ Include BSA information (see function \emph{BSAInfo}). }
  \item{debug}{ Output debug information. }
  \item{options}{ Optional list of name-value data. All values associated with a name is
                  a string.  Options include: 
				  \tabular{lll}{
						Name \tab Value \tab Default \cr	
						IncludeFlaggedData \tab "True" or "False" \tab "True" \cr
				        CollapseData \tab "True" or "False" \tab "True" \cr
						OrderBy \tab "none" or "pairid" \tab "pairid" \cr
						PrimarySeqName \tab "True" or "False" \tab "False"} }
  \item{bsa.simplify}{ Convert the bsa result to a data frame or
                       set of data frames. }
}
%- \details{
%-   ~~ If necessary, more details than the __description__  above ~~
%- }
\value{
  A list containing the follow fields or components:
  \item{ced }{A list containing core expression data for each field}
  \item{todids }{A numeric vector containing the tod ids}
  \item{lodids }{A numeric vector containing the lod ids}
  \item{todinfo }{A list containing tod annotation information}
  \item{lodinfo }{A list containing lod annotation information}
}
%- \references{ ~put references to the literature/web site here ~ }
\author{ r. kuraisa }
\note{ None at this time. }

\seealso{ RDAExecute RDANames RDAids RDAExamples RDAFields RDASummary ResolverLogin  }
\examples{
  # login 
  server <- "snwspr18.merck.com"
  db <- "MRLSP01"
  hconn <- ResolverLogin("you", "you", db, server)

  # full eg using specified tod ids
  todIDs <- c(10000629692., 10000629693., 10000629694., 10000629695., 10000629696.);
  eg <- GetResolverEG(hconn, "eg", "human", todIDs)
  RDASummary(eg)

  # only some specified fields
  todIDs <- c(10000629692., 10000629693., 10000629694., 10000629695., 10000629696.);
  eg <- GetResolverEG(hconn, c("value", "pvalue"), "human", todIDs)
  RDASummary(eg)

  # using project unit code pdq to get tod ids
  eg <- GetResolverEG(hconn, "eg", "human", RDAids("puc", "10083"))
  RDASummary(eg)

  # intensity data using:
  #      1. specified fields
  #      2. user-defined named query (MyIEQuery) to get tod ids
  #      3. option to include flagged data (controlflag and failcode)
  opts <- list(IncludeFlaggedData="True")
  fields <- c("value", "error", "background", "seqcount")
  todIDs <- RDAids("MyIEQuery", c("MT2001", "PTPN1//DIO", TRUE)
  eg <- GetResolverEG(hconn, fields, "mouse", todIDs, tod = "ie", options = opts)

  # ratio data in project 10920 without sorting
  opts <- list(OrderBy="none");
  eg <- GetResolverEG(hconn, "eg", "human", RDAids("pc","10929"), options = opts)

  # include bsa information
  eg <- GetResolverEG(hconn, "eg", "human", RDAids("pc","11068"))

 
}
\keyword{ database }% at least one, from doc/KEYWORDS
