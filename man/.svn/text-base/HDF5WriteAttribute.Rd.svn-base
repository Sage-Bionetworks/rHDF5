\name{HDF5WriteAttribute}
\alias{HDF5WriteAttribute}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ Write HDF5 attribute }
\description{
  Write an attribute to HDF5 file.
}
\usage{
HDF5WriteAttribute(filename,path,data,options)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{filename}{ HDF5 file name in full path }
  \item{path}{ the full path of the attribute within the HDF5 file}
  \item{data}{ attribute data to be written}
  \item{options}\tabular{rll}{ 
	 \tab overwrite \tab logical value to indicate if an existing attribute will get overwritten \cr	
	 \tab compresslevel \tab integer value (0-9) to indicate data compression level. \cr
	 \tab               \tab Higher compression results in longer time. Default(0) \cr	
	}
}
\author{ Wilson Lau }
\note{ None at this time }

\seealso{ HDF5Summary HDF5ReadData HDF5WriteData HDF5ReadAttribute }
\examples{
 
 # write an attribute named "dsAtt" within a group "dsGrp" 
 data <- array(1:10,dim=10) 
 HDF5WriteAttribute("./Kidneycortex_Female_W10.h5","/dsGrp/dsAtt",data)

 # write an attribute named "attInt" of a dataset "dsInt" within a group "dsGrp"  
 data <- array(1:2,dim=2) 
 HDF5WriteAttribute("./Kidneycortex_Female_W10.h5","/dsGrp/dsInt/dsAtt", data)

 # overwrite the same attribute named "attInt" of a dataset "dsInt" within a group "dsGrp"  
 data <- array(1:12,dim=12) 
 HDF5WriteAttribute("./Kidneycortex_Female_W10.h5","/dsGrp/dsInt/dsAtt", data, options=list(overwrite="true"))
}
\keyword{ database }% at least one, from doc/KEYWORDS
