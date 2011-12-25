\name{HDF5Summary}
\alias{HDF5Summary}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Summary of HDF5 file structure }
\description{
  Outputs a summary of a HDF5 File.
}
\usage{
HDF5Summary(filename,options)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{filename}{ HDF5 file name }
  \item{options}\tabular{rll}{
         \tab fullDetail   \tab if "true", the dataset size and data type will be returned.\cr
		\tab   \tab  if "false, only the names are returned (default)
					   }
}
\author{ Wilson Lau }
\note{ None at this time }

\seealso{ HDF5ReadData HDF5WriteData HDF5ReadAttribute HDF5WriteAttribute }
\examples{
 
 # summary of a hdf5 file
 summary<-HDF5Summary("./Kidneycortex_Female_W10.h5")

 # summary of the file with dataset size and type
 summary<-HDF5Summary("./Kidneycortex_Female_W10.h5",options=list(fullDetail="true"))
}
\keyword{ database }% at least one, from doc/KEYWORDS
