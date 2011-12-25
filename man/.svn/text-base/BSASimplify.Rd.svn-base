\name{BSASimplify}
\alias{BSASimplify}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Simplify the output from BSAExecute }
\description{
  Simplify the output from BSAExecute by converting the lists to a data frame
  or a set of data frames
}
\usage{
BSASimplify(bdata)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{bdata}{ A list returned from BSAExecute. }
}
\value{
  A data frame or set of data frames.  If the results from BSAExecute is
  a scalar (i.e., without time series), then a list with only one data frame
  is returned.  

  If there is at least one time series field, the returned value is a 
  list with components 'scalar.fields' and 'timeseries.fields'.  The
  former will be a data frame containing the scalar fields.  The
  'timeseries.fields' component will be a data frame if all the time
  series fields have the same number of values per sample, and the
  same times associated with those values.  The data frame will have 
  one row per value per sample, and one or two columns per times series 
  field.  If the time series fields do not have the same number or
  time points for each sample, the 'timeseries.fields' component will
  be a list with one component per time series field, each component
  a data frame with data and time points for that field.

}
\author{ r. raubertas }
\note{
 This is function is called by BSAExecute.
}

\seealso{ BSAExecute BSAInfo }
\examples{
    # get all annotation by project code (low level)
    bdata<-BSAExecute(("11173",itype="pc")

    # convert
    binfo<-BSASimplify(bdata)
}
\keyword{ database }% at least one, from doc/KEYWORDS
