\name{HDF5ReadData}
\alias{HDF5ReadData}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Reading HDF5 dataset }
\description{
  Read a dataset from HDF5 file.
}
\usage{
HDF5ReadData(filename,path,options)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{filename}{ HDF5 file name in full path }
  \item{path}{ the full path of the dataset within the HDF5 file}
  \item{options}\tabular{rll}{ 
	 \tab startindex   \tab the starting row index (zero based) of the dataset to be read. Default(0) \cr
	 \tab nrows   \tab the number of rows of data to be read. Default(all rows)\cr
	}
}
\author{ Wilson Lau }
\note{ None at this time }

\seealso{ HDF5Summary HDF5WriteData HDF5ReadAttribute HDF5WriteAttribute }
\examples{
 
 # read the dataset named "dsInt" in a hdf5 file
 data<-HDF5ReadData("./Kidneycortex_Female_W10.h5","/dsInt")

 # read the dataset named "dsInt" within a group "dsGrp" 
 data<-HDF5ReadData("./Kidneycortex_Female_W10.h5","/dsGrp/dsInt")

 # read only the 2nd and 3rd row of the dataset named "dsInt" within a group "dsGrp" 
 data<-HDF5ReadData("./Kidneycortex_Female_W10.h5","/dsGrp/dsInt", options=list(startindex=2, nrows=2))
}
\keyword{ database }% at least one, from doc/KEYWORDS
