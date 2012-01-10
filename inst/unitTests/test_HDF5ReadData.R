.setUp <-
	function()
{
	## write a test HDF5 file
	hfFile <- file.path(tempdir(), "test.h5")
	d <- diag(5)
	d <- rbind(d, d[1:2,]) ##A 7x5 matrix
	HDF5WriteData(hfFile, "/dataTable", d, options=list(forceNewFile=TRUE))
}

.tearDown <-
	function()
{
	hfFile <- file.path(tempdir(), "test.h5")
	if(file.exists())
		file.remove(hfFile)
}

unitTestReadFirstRow <-
	function()
{
	hfFile <- file.path(tempdir(), "test.h5")
	d <- HDF5ReadData(hfFile, "/dataTable", options=list(startindex=0, nrows=1))
	
	checkEquals(nrow(d), 1L)
	checkEquals(ncol(d), 5L)
	checkTrue(all(d[1,] == diag(5)[1,]))
}

unitTestReadLastRow <-
	function()
{
	hfFile <- file.path(tempdir(), "test.h5")
        d <- HDF5ReadData(hfFile, "/dataTable", options=list(startindex=6, nrows=1))
        
        checkEquals(nrow(d), 1L)
        checkEquals(ncol(d), 5L)
        checkTrue(all(d[1,] == diag(5)[2,]))
}

unitTestReadBlockInclLastRow <-
	function()
{
        hfFile <- file.path(tempdir(), "test.h5")
        d <- HDF5ReadData(hfFile, "/dataTable", options=list(startindex=5, nrows=2))

        checkEquals(nrow(d), 2L)
        checkEquals(ncol(d), 5L)
        checkTrue(all(d[1:2,] == diag(5)[1:2,]))
}

unitTestReadBlockInclFirstRow <-
        function()
{
        hfFile <- file.path(tempdir(), "test.h5")
        d <- HDF5ReadData(hfFile, "/dataTable", options=list(startindex=0, nrows=2))

        checkEquals(nrow(d), 2L)
        checkEquals(ncol(d), 5L)
        checkTrue(all(d == diag(5)[1:2,]))
}

unitTestReadRowBlock <-
        function()
{
        hfFile <- file.path(tempdir(), "test.h5")
        d <- HDF5ReadData(hfFile, "/dataTable", options=list(startindex=1, nrows=3))

        checkEquals(nrow(d), 3L)
        checkEquals(ncol(d), 5L)
        checkTrue(all(d == diag(5)[2:4,]))
}

unitTestReadFirstCol <-
	function()
{
	orig <- diag(5)
        orig <- rbind(orig, orig[1:2,]) ##A 7x5 matrix
	
	hfFile <- file.path(tempdir(), "test.h5")
        d <- HDF5ReadData(hfFile, "/dataTable", options=list(startindex=0, ncols=1))

	checkEquals(nrow(d), nrow(orig))
        checkEquals(ncol(d), 1L)
        checkTrue(all(d == orig[,1]))
}

unitTestReadLastCol <-
	function()
{
        orig <- diag(5)
        orig <- rbind(orig, orig[1:2,]) ##A 7x5 matrix

	hfFile <- file.path(tempdir(), "test.h5")
        d <- HDF5ReadData(hfFile, "/dataTable", options=list(startindex=4, ncols=1))

	checkEquals(nrow(d), nrow(orig))
        checkEquals(ncol(d), 1L)
        checkTrue(all(d == orig[,5]))
}

unitTestReadBlockInclFirstCol <-
	function()
{
        orig <- diag(5)
        orig <- rbind(orig, orig[1:2,]) ##A 7x5 matrix

	hfFile <- file.path(tempdir(), "test.h5")
        d <- HDF5ReadData(hfFile, "/dataTable", options=list(startindex=0, ncols=2))

	checkEquals(nrow(d), nrow(orig))
        checkEquals(ncol(d), 2L)
        checkTrue(all(d == orig[,1:2]))
}

unitTestReadBlockInclLastCol <-
        function()
{
        orig <- diag(5)
        orig <- rbind(orig, orig[1:2,]) ##A 7x5 matrix

	hfFile <- file.path(tempdir(), "test.h5")
        d <- HDF5ReadData(hfFile, "/dataTable", options=list(startindex=3, ncols=2))
	
	checkEquals(nrow(d), nrow(orig))
        checkEquals(ncol(d), 2L)
        checkTrue(all(d == orig[,4:5]))
}


unitTestReadColBlock <-
{
        orig <- diag(5)
        orig <- rbind(orig, orig[1:2,]) ##A 7x5 matrix
	
	hfFile <- file.path(tempdir(), "test.h5")
        d <- HDF5ReadData(hfFile, "/dataTable", options=list(startindex=1, ncols=3))

	checkEquals(nrow(d), nrow(orig))
	checkEquals(ncol(d), 3L)
	checkTrue(all(d == orig[,2:4]))
}

