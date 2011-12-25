\name{HDF5ReadAttribute}
\alias{HDF5ReadAttribute}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Reading HDF5 attribute }
\description{
  Read an attribute from HDF5 file.
}
\usage{
HDF5ReadAttribute(filename,path)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{filename}{ HDF5 file name in full path }
  \item{path}{ the full path of the attribute within the HDF5 file}
}
\author{ Wilson Lau }
\note{ None at this time }

\seealso{ HDF5Summary HDF5ReadData HDF5WriteData HDF5WriteAttribute }
\examples{
 
 # read the attribute named "attInt" of a group "dsGrp" 
 att<-HDF5ReadAttribute("./Kidneycortex_Female_W10.h5","/dsGrp/attInt")

 # read the attribute named "attInt" of a dataset "dsInt" within a group "dsGrp" 
 att<-HDF5ReadAttribute("./Kidneycortex_Female_W10.h5","/dsGrp/dsInt/attInt")
}
\keyword{ database }% at least one, from doc/KEYWORDS
