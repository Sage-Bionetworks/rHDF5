\name{HDF5WriteData}
\alias{HDF5WriteData}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Write HDF5 dataset }
\description{
  Write a dataset to HDF5 file.
}
\usage{
HDF5WriteData(filename,path,data,options)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{filename}{ HDF5 file name in full path }
  \item{path}{ the full path of the dataset within the HDF5 file}
  \item{data}{ data to be written}
  \item{options}\tabular{rll}{ 
         \tab startindex   \tab the starting row index (zero based) of the dataset to be overwritten\cr
         \tab nrows \tab the number of rows of data to be overwritten\cr
         \tab forceNewFile    \tab  logical value to indicate if an existing file will \cr
		\tab				\tab	be erased first before writing \cr
         \tab overwrite    \tab  logical value to indicate if an existing dataset will get\cr
		\tab               \tab	 overwritten \cr
		 \tab compresslevel \tab integer value (0-9) to indicate data compression level. \cr
		 \tab               \tab Higher compression results in longer time. Default(0) \cr	
       }
}
\author{ Wilson Lau }
\note{ None at this time }

\seealso{ HDF5Summary HDF5ReadData HDF5ReadAttribute HDF5WriteAttribute }
\examples{
 
 # write the dataset named "dsInt" in a hdf5 file
 data <- array(1:10,dim=10) 
 HDF5WriteData("./Kidneycortex_Female_W10.h5","/dsInt",data)

 # write the dataset named "dsInt" within a group "dsGrp" 
 HDF5WriteData("./Kidneycortex_Female_W10.h5","/dsGrp/dsInt",data)

 # write only the 2nd and 3rd row of the dataset named "dsInt" within a group "dsGrp" 
 data <- array(1:2,dim=2) 
 HDF5WriteData("./Kidneycortex_Female_W10.h5","/dsGrp/dsInt", data, options=list(startindex=2, nrows=2))
}
\keyword{ database }% at least one, from doc/KEYWORDS
