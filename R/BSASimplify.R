"BSASimplify" <- 
function(bsa.rslt) 
# Convert the result of a call to 'BSAExecute' to a data frame, or set of
# data frames, by flattening its tree structure.  Also, remove redundant 
# 'unit' info when possible.

# VALUE
#  If all fields in 'bsa.rslt' are scalar, a single data frame is returned,
#  with one row per sample and one or two columns per field.  A scalar 
#  field is one with a single value per sample; a time series field is 
#  one with possibly multiple values per sample, and a time associated 
#  with each value.
#
#  If there is at least one time series field, the returned value is a 
#  list with components 'scalar.fields' and 'timeseries.fields'.  The
#  former will be a data frame containing the scalar fields.  The
#  'timeseries.fields' component will be a data frame if all the time
#  series fields have the same number of values per sample, and the
#  same times associated with those values.  The data frame will have 
#  one row per value per sample, and one or two columns per times series 
#  field.  If the time series fields do not have the same number or
#  time points for each sample, the 'timeseries.fields' component will
#  be a list with one component per time series field, each component
#  a data frame with data and time points for that field.
#
#  If all values for a field have the same units, a character string
#  with the units is attached to the field as a 'units' attribute.
#  Otherwise two columns are used to represent the values of the field,
#  one column for the data, and the other for the units.  The name of 
#  the units column is the name of the data column, with "_unit" appended.

# NOTE
#  This implementation makes strong assumptions about the structure of
#  the object returned by 'BSAExecute'.  A field 'sampleids' is assumed
#  to be present and to contain unique sample identifiers.  All other
#  fields are assumed to correspond to samples ordered in the same way
#  as in 'sampleids'.  Scalar fields must be either simple vectors or a 
#  list with two equal-length vector components named "data" and "unit".  
#  Time series fields must be lists with three equal-length vector 
#  components named "data", "unit", and "datetime".  For time series fields 
#  it is also assumed that "data" is missing whenever "datetime" is; i.e., 
#  there are no data  values with unknown times.

# VERSION
#  17 Jun 2005 / R.F. Raubertas
#  11 Nov 2005 : Add code to handle general pairs of scalar fields with
#                names like 'foo' and 'foo_unit'.
{
  # Convert pairs of scalar fields with names like 'foo' and 'foo_unit'
  # to the list format used for custom fields:  foo=list(data=..., unit=...)
  nms <- names(bsa.rslt)
  if (length(unms <- nms[grep("_unit$", nms)]) > 0) {
    pnms <- nms[nms %in% sub("_unit$", "", unms)]
    for (i in pnms) {
      iu <- paste(i, "_unit", sep="")
      if (is.atomic(bsa.rslt[[i]]) && is.atomic(bsa.rslt[[iu]])) {
        bsa.rslt[[i]] <- list(data=bsa.rslt[[i]], unit=bsa.rslt[[iu]])
        bsa.rslt[[iu]] <- NULL
      }
    }
  }

  sampids <- bsa.rslt$sampleids
  if (is.null(sampids) || !is.atomic(sampids)) stop(
        "Expected 'sampleids' field not found")
  fieldnames <- names(bsa.rslt)
  units <- structure(rep("", length(bsa.rslt)), names=fieldnames)
  periods <- structure(rep("",length(bsa.rslt)),names=fieldnames)
  isseries <- structure(rep(FALSE, length(bsa.rslt)), names=fieldnames)
  for (nm in fieldnames) {
    fld <- bsa.rslt[[nm]]
    if (!is.list(fld)) {
      # Just an ordinary scalar field; leave as is.
    } else {
      if (identical(names(fld), c("data"))) {
        # custom attributes may only have data
        bsa.rslt[[nm]] <- fld$data
      } else if (identical(names(fld), c("data","unit"))) {
        # A custom field: pair of 'data', 'unit' vectors
        bsa.rslt[[nm]] <- fld$data
        # Deal with units:
        un <- unique(fld$unit[!is.na(fld$data)])
        # Treat empty unit ("") as equivalent to any string
        if (length(un) > 1)  un <- setdiff(un, "")
        if (length(un) == 1) {     # Same units for all values
          units[nm] <- un
        } else {      # Different units, so create a separate variable for units
          bsa.rslt[[paste(nm, "_unit", sep="")]] <- fld$unit
          units[nm] <- NA
        }
      } else if (identical(names(fld), c("data","unit","datetime"))) {
        # this is for absolute time points
        # A time series field: each component is a list with one component
        # per sample.  For each sample there is a vector of values across
        # times.
        isseries[nm] <- TRUE
        # Rearrange the list so that 'data', 'unit', and 'datetime' are 
        # each vectors with one row per time point per sample
        ntimes <- sapply(fld$data, length)
        stopifnot(length(bsa.rslt$sampleids)==length(ntimes))
        fld <- list(sampleids=rep(sampids, ntimes),
                    data=unlist(fld$data, use.names=FALSE), 
                    unit=unlist(fld$unit, use.names=FALSE),
                    datetime=unlist(fld$datetime, use.names=FALSE))
        # Convert blank dates to missing, for consistency
        fld$datetime <- with(fld, ifelse(is.na(datetime) | datetime=="", NA, 
                                         datetime))
        un <- unique(fld$unit[!is.na(fld$data)])
        # Treat empty unit ("") as equivalent to any string
        if (length(un) > 1)  un <- setdiff(un, "")
        if (length(un) == 1) {
          # Same unit for all values, so drop the 'unit' component
          units[nm] <- un
          fld$unit <- NULL
        }
        bsa.rslt[[nm]] <- df.from.list(fld)
      } else if (identical(names(fld), c("data","unit","period","interval"))) {
        # this is for relative time points.
        # A time series field: each component is a list with one component
        # per sample.  For each sample there is a vector of values across
        # times.
        isseries[nm] <- TRUE
        # Rearrange the list so that 'data', 'unit', and 'datetime' are
        # each vectors with one row per time point per sample
        ntimes <- sapply(fld$data, length)
        stopifnot(length(bsa.rslt$sampleids)==length(ntimes))
        fld <- list(sampleids=rep(sampids,ntimes),
                    data=unlist(fld$data,use.names=FALSE),
                    unit=unlist(fld$unit,use.names=FALSE),
                    period=unlist(fld$period,use.names=FALSE),
                    interval=unlist(fld$interval,use.names=FALSE))
        un <- unique(fld$unit[!is.na(fld$data)])
        # Treat empty unit ("") as equivalent to any string
        if (length(un) > 1)  un <- setdiff(un, "")
        if (length(un) == 1) {
            # Same unit for all values, so drop the 'unit' component
            units[nm] <- un
            fld$unit <- NULL
        }
        # do the same thing for period
        un <- unique(fld$period[!is.na(fld$data)])
        # Treat empty unit ("") as equivalent to any string
        if (length(un) > 1)  un <- setdiff(un, "")
        if (length(un) == 1) {
            # Same unit for all values, so drop the 'unit' component
            periods[nm] <- un
            fld$period <- NULL
        }
        bsa.rslt[[nm]] <- df.from.list(fld)
      } else  stop(paste("Unrecognized data structure for field", nm))
    }
  }

  if (all(isseries)) {   # All fields are time series (unlikely)
    scalar.fields <- NULL
  } else {
    scalar.fields <- df.from.list(bsa.rslt[!isseries])
    for (nm in names(scalar.fields)) {
      un <- units[nm]
      if (!is.na(un) && un != "")  attr(scalar.fields[[nm]], "units") <- 
                                             as.vector(un)
    }
  }

  if (any(isseries)) {   # At least one time series field
    if (sum(isseries) == 1) {     #  Only one times series field
      nm <- names(bsa.rslt)[isseries]
      dfr <- bsa.rslt[[nm]]
      # Rename 'data' and 'unit' columns using actual field name
      names(dfr)[match("data", names(dfr))] <- nm
      names(dfr)[match("unit", names(dfr), nomatch=0)] <- 
                    paste(nm, "_unit", sep="")
      timeseries.fields <- dfr
    } else {    # More than one time series field
      # Check whether all time series fields use the same times.  If so, 
      # they can be merged into a single data frame.  Complicated because
      # time order may not be the same for all fields, and time is sometimes
      # missing when data values are missing.
      times <- NULL
      ids <- chk.equiv(lapply(bsa.rslt[isseries], function(x) x$sampleids),
                       match.anything=NULL)
      if (!is.null(ids)) {
        # Check whether there are any non-missing data values with missing 
        # times.  If so, don't try to merge.
        temp <- sapply(bsa.rslt[isseries], 
                       function(x) any(is.na(x$datetime) & !is.na(x$data)))
        if (any(temp)) {
          warning(paste("Missing datetime for non-missing data in field(s)",
                        paste(names(temp)[temp], collapse=", ")))
          times <- NULL
        } else {
          idx.by.sample <- split(1:length(ids), ids)[sampids]
          # For each sample, get the union of all times
          times <- lapply(idx.by.sample,
                          function(idx, listofdf) {
                            dts <- vector("list", length(listofdf))
                            for (i in 1:length(listofdf)) {
                              dts[[i]] <- (listofdf[[i]]$datetime)[idx]
                            }
                            udts <- sort(unique(unlist(dts, use.names=FALSE)), 
                                         na.last=TRUE)
                            udts <- setdiff(udts, NA)
                            # Pad list of times with NA's if necessary
                            rslt <- 
                              { if (length(udts) <= length(idx))
                                    c(udts, rep(NA, length(idx)-length(udts)))
                                else NULL }
                            rslt
                          }, listofdf=bsa.rslt[isseries])
          # If the length of the union for each sample is greater than the  
          # number of time points for the sample, we cannot merge.
          if (any(sapply(times, is.null))) {
            times <- NULL
          } else {
            # Rearrange the observations within samples for each field to
            # match the shared time points.  Note that 'NA' in a datetime
            # field is taken to match _any_ value in 'times'.
            for (nm in names(bsa.rslt[isseries])) {
              dfr <- bsa.rslt[[nm]]
              for (i in 1:length(idx.by.sample)) {
                idx <- idx.by.sample[[i]]
                idx2 <- which(!is.na(dfr$datetime[idx]))
                if (length(idx2) > 0) {
                  pos <- numeric(length(idx))
                  pos[idx2] <- match(dfr$datetime[idx][idx2], times[[i]])
                  stopifnot(!is.na(pos))  # should never happen
                  pos[-idx2] <- setdiff(1:length(idx), pos[idx2])
                  dfr[idx[pos],] <- dfr[idx,,drop=FALSE]
                }
              }
              # Rename 'data' and 'unit' columns using actual field name
              idx <- match("data", names(dfr))
              names(dfr)[idx] <- nm
              idx <- match("unit", names(dfr))
              if (!is.na(idx)) names(dfr)[idx] <- paste(nm, "_unit", sep="")
              # Omit 'sampleids' and 'datetime' since they are redundant in
              # merged data
              dfr$sampleids <- NULL
              dfr$datetime <- NULL
              bsa.rslt[[nm]] <- dfr
            }
          }
        }
      }
      if (!is.null(times)) {   #  Do the merge
        stopifnot(identical(names(times), sampids))
        times <- unlist(times, use.names=FALSE)
        temp <- unlist(bsa.rslt[isseries], recursive=FALSE, use.names=FALSE)
        names(temp) <- names(bsa.rslt[isseries])
        timeseries.fields <- 
           df.from.list(c(list(sampleids=ids, datetime=times), temp))
      } else {
        timeseries.fields <- bsa.rslt[isseries]
      }
    }
    for (nm in names(timeseries.fields)) {
      un <- units[nm]
      if (!is.na(un) && un != "")  attr(timeseries.fields[[nm]], "units") <- 
                                             as.vector(un)
    }
    for (nm in names(timeseries.fields)) {
      un <- periods[nm]
      if (!is.na(un) && un != "")  attr(timeseries.fields[[nm]], "periods") <-
                                             as.vector(un)
    }
  } else  timeseries.fields <- NULL

  if (is.null(timeseries.fields))  return(scalar.fields)
  else return(list(scalar.fields=scalar.fields, 
                   timeseries.fields=timeseries.fields))
}


df.from.list <- function(x)
# Utility function to create a data frame from a list of vectors, but 
# without converting character vectors to factors
{
  stopifnot(is.list(x))
  stopifnot(sapply(x, is.atomic))   # all components must be simple vectors
  ischar <- sapply(x, is.character)
  isnull <- sapply(x,is.null)		# No components can be null in data.frame
  x <- replace(x,which(isnull),NA)	# Replacing the null components
  rslt <- data.frame(x)
  for (i in seq(along=rslt)) {
    if (ischar[i])  rslt[,i] <- as.character(rslt[,i])
  }
  rslt
}
  

chk.equiv <- function(v, match.anything=NULL)
# Utility function to determine whether all vectors in the list
# 'v' are equivalent.  Two vectors are equivalent if they have the
# same length and mode, and if all their values agree.  'match.anything' 
# is a vector of values that will be treated as equal to anything.
# If all vectors are equivalent by this criterion, a representative
# vector is returned.  It will have the fewest possible values from
# 'match.anything'.  If the vectors are not all equivalent, NULL is
# returned.
{
  stopifnot(is.list(v))
  if (length(v) == 1)  return(v[[1]])
  chk1 <- sapply(v, length)
  chk2 <- sapply(v, mode)
  chk3 <- sapply(v, is.atomic)
  if (!all(chk3) || any(chk1 != chk1[1]) || any(chk2 != chk2[1]))  return(NULL)
  if (chk1[1] == 0)  return(v[[1]])
  rvec <- v[[1]]
  for (i in 2:length(v)) {
    chg <- (rvec %in% match.anything)
    rvec[chg] <- v[[i]][chg]
    use <- !(rvec %in% match.anything)
    if (any(use)) {
      if (!identical(all.equal(rvec[use], v[[i]][use]), TRUE))  return(NULL)
    }
  }
  rvec
}
