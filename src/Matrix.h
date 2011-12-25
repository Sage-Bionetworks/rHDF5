#ifndef MATRIX_INC
#define MATRIX_INC


#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>

//#include "portable_numeric.h" 
#include "UtilitiesException.h"

namespace seg
{

template<class T>
class Matrix
{
public:
    //
    // ctor's
    //
    Matrix();
    Matrix(size_t noCols);
    Matrix(size_t noRows,size_t noCols);
    Matrix(std::vector<T>& vectorData,size_t noRows,size_t noCols); // shallow
    Matrix(std::vector<T>& vectorData);             // 1-d, shallow
    Matrix(T* cData,size_t noRows,size_t noCols);   // shallow c-data types
    //
    // assignment and copy
    //
    Matrix(const Matrix& inMatrix);                 // deep copy
    Matrix& operator=(const Matrix& rhs);           // deep copy
    //
    // dtor
    //
    virtual ~Matrix();
    // 
    // accessor functions
    //
    T* Data();                                      // get the data
    const T* Data() const;
    void Row(size_t row,std::vector<T>& v) const;   // row as a vector
    T* Row(size_t row);                             // row as a pointer
    const T* Row(size_t row) const;
    const T& operator()(size_t index) const;        // 1-d data element
    T& operator()(size_t index);
    const T& operator[](size_t index) const;        // 1-d data element 
    T& operator[](size_t index);
    const T& operator()(size_t rI,size_t cI) const; // 2-d data element
    T& operator()(size_t rI,size_t cI);
    size_t NumberOfRows() const;                    // number of rows
    size_t NumberOfColumns() const;                 // number of columns
    size_t Size() const;                            // size of data
    //
    // data modification functions
    //
    void Resize(size_t nRows,
                size_t nCols);                      // 2-d resize (data deleted)
    void Resize(size_t size);                       // 1-d resize (data deleted)
    void DeepCopy(size_t size,                      // 1-d deep copy for c-types
                  const T* data);
    void DeepCopy(size_t nRows,                     // 2-d deep copy for c-types
                  size_t nCols,
                  const T* d);
    void LiteCopy(Matrix& inMatrix);                // shallow copy
    void Transpose();                               // in-place
    void SetData(T value);
    //
    // converter
    //
    void ToVector(std::vector<T>& vd) const;        // obvious deep copy

	//
	// debug
	//
	void Print(std::ostream& out);


protected:
    T       *m_data;
    size_t  m_numberOfRows;
    size_t  m_numberOfColumns;
    size_t  m_size;
    bool    m_ownData;

    virtual void DeleteData();                      // delete;set size to 0

private:
    void Reserve(size_t numberRows,size_t numberCols);  // allocate only

};

//=============================================================================
// inline implementations (required for templates at this time of vc6
//=============================================================================
//
//  default ctor
//
template<class T>
inline Matrix<T>::Matrix() :
m_data(0),
m_numberOfRows(0),
m_numberOfColumns(0),
m_size(0),
m_ownData(true)
{
}
//
//  1-d ctor
//
template<class T>
inline Matrix<T>::Matrix(size_t numberCols) :
m_ownData(true)
{
    Reserve(1,numberCols);
}
//
//  2-d ctor
//
template<class T>
inline Matrix<T>::Matrix(size_t numberRows,size_t numberCols) :
m_ownData(true)
{
    Reserve(numberRows,numberCols);
}
//
//  copy ctor
//
template<class T>
inline Matrix<T>::Matrix(const Matrix<T>& inMatrix) :
m_ownData(true),m_data(0)
{
    DeepCopy(inMatrix.m_numberOfRows,
             inMatrix.m_numberOfColumns,
             inMatrix.Data());
}
//
//  ctor via vector (shallow copy)
//
template<class T>
inline Matrix<T>::Matrix(std::vector<T>& vectorData,
                         size_t noRows,
                         size_t noCols) :
m_ownData(false)
{
    
    const std::string rName="Matrix ctor (with vector)/";
    //
    // we just want to use the buffer of the vector and we also don't want
    // to delete it because it isn't ours.  Another issue is the consistency
    // of the size in the vector and the number of rows/cols passed in. 
    //
    m_size=vectorData.size();
    if (m_size != noRows*noCols)
        throw UtilitiesException(rName + "Inconsistent size in vector");
    m_numberOfRows=noRows;
    m_numberOfColumns=noCols;
    m_data=&vectorData[0];
}

template<class T>
inline Matrix<T>::Matrix(std::vector<T>& vectorData) :
m_ownData(false)
{
    
    const std::string rName="Matrix ctor (with vector)/";
    //
    // we just want to use the buffer of the vector and we also don't want
    // to delete it because it isn't ours.  Another issue is the consistency
    // of the size in the vector and the number of rows/cols passed in. 
    //
    m_size=vectorData.size();
    m_numberOfRows=1;
    m_numberOfColumns=m_size;
    //
    // in vs2005, a zero length vector is null; so must handle this case
    //
    if (m_size==0)
        m_data=0;
    else
        m_data=&vectorData[0];
}
//
//  ctor intended for basic c types (e.g., float *)
//
template<class T>
inline Matrix<T>::Matrix(T* cData,size_t noRows,size_t noCols) :
m_data(cData),
m_numberOfRows(noRows),
m_numberOfColumns(noCols),
m_size(noRows*noCols),
m_ownData(false)
{
}
//
// assignment
//
template<class T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
    // check for self assignment
    if(&rhs != this)
    {
        DeepCopy(rhs.m_numberOfRows,rhs.m_numberOfColumns,rhs.Data());
    }
    return (*this);
}
//
// dtor
//
template<class T>
inline Matrix<T>::~Matrix()
{
    DeleteData();
}
//
// Reserve
//
template<class T>
inline void Matrix<T>::Reserve(size_t numberRows,size_t numberCols)
{
    const std::string rName="Matrix::Reserve/";
    m_ownData=true;
    m_size=numberRows*numberCols;
    if (m_size==0)
    {
        m_numberOfRows=0;
        m_numberOfColumns=0;
        m_data=0;
    }
    else
    {
        m_numberOfRows=numberRows;
        m_numberOfColumns=numberCols;
        if (m_size)
            m_data=new T[m_size];
            if (!m_data)
            {
				std::ostringstream ostr;
                ostr << rName << "Allocation failed for " << m_size << " bytes.";
                throw UtilitiesException(ostr.str());
            }
    }
}
//
// DeleteData
//
template<class T>
inline void Matrix<T>::DeleteData()
{
    
    if (m_ownData)
        delete [] m_data;
    m_data=0;
    m_numberOfRows=0;
    m_numberOfColumns=0;
    m_size=0;
}
//
// Data
//
template<class T>
inline T* Matrix<T>::Data()
{
    return m_data;
}
//
// Resize 
//
template<class T>
inline void Matrix<T>::Resize(size_t nRows,size_t nCols)
{
    DeleteData();
    Reserve(nRows,nCols);
}

template<class T>
inline void Matrix<T>::Resize(size_t size)
{
    Resize(1,size);
}
//
// LiteCopy - shallow copy of matrix
//
template<class T>
inline void Matrix<T>::LiteCopy(Matrix<T>& data)
{
    DeleteData();
    m_ownData=false;
    m_data=data.Data();
    m_numberOfRows=data.NumberOfRows();
    m_numberOfColumns=data.NumberOfColumns();
    m_size=m_numberOfRows*m_numberOfColumns;
}
//
// DeepCopy - deep copy of ctypes (1-d and 2-d); matrix
//
template<class T>
inline void Matrix<T>::DeepCopy(size_t size,const T* data)
{
    DeepCopy(1,size,data);
}

template<class T>
inline void Matrix<T>::DeepCopy(size_t nRows,
                                size_t nCols,
                                const T* inData)
{
    size_t size=nRows*nCols;
    Resize(size);
    m_numberOfRows=nRows;
    m_numberOfColumns=nCols;
    for (size_t index=0;index<size;index++)
        m_data[index]=inData[index];
}
//
// ZeroData
//
template<class T>
inline void Matrix<T>::SetData(T value)
{
    for (size_t index=0;index<m_size;index++)
        m_data[index]=value;
}
//
// Data
//
template<class T>
inline const T* Matrix<T>::Data() const
{
    return (const_cast<Matrix<T>* >(this))->Data();
}
//
// Row as a vector
//
template<class T>
inline void Matrix<T>::Row(size_t row,std::vector<T>& v) const
{
    const std::string rName="Matrix::Row(vector)/";   
    size_t dIndex=row*m_numberOfColumns;
    if (dIndex>m_size-m_numberOfColumns)
        throw UtilitiesException(rName+"Row number is too big.");
    for(size_t vIndex=0;vIndex<m_numberOfColumns;vIndex++)
        v[vIndex] = m_data[dIndex+vIndex];
}
//
// Row as a pointer to data
//
template<class T>
inline T* Matrix<T>::Row(size_t row)
{
    const std::string rName="Matrix::Row(pointer)/";   
    if(row>=m_numberOfRows)
        throw UtilitiesException(rName+"Row number is too big.");
    return &(m_data[row*m_numberOfColumns]);
}

template<class T>
inline const T* Matrix<T>::Row(size_t row) const
{
    return (const_cast<Matrix<T>* >(this))->Row(row);
}
//
// number of rows, number of columns and size
//
template<class T>
inline size_t Matrix<T>::NumberOfRows() const
{
    return m_numberOfRows;
}

template<class T>
inline size_t Matrix<T>::NumberOfColumns() const
{
    return m_numberOfColumns;
}

template<class T>
inline size_t Matrix<T>::Size() const
{
    return m_size;
}
//
// function operators - access 1-d elements
//
template<class T>
inline T& Matrix<T>::operator()(size_t index)
{
    return m_data[index];
}

template<class T>
inline const T& Matrix<T>::operator()(size_t index) const
{
    return m_data[index];
}
template<class T>
inline T& Matrix<T>::operator[](size_t index)
{
    return m_data[index];
}

template<class T>
inline const T& Matrix<T>::operator[](size_t index) const
{
    return m_data[index];
}
//
// function operators - access 2-d elements
//
template<class T>
inline T& Matrix<T>::operator()(size_t rI,size_t cI)
{
    return m_data[rI*m_numberOfColumns+cI];
}

template<class T>
inline const T& Matrix<T>::operator()(size_t rI,size_t cI) const
{
    return m_data[rI*m_numberOfColumns+cI];
}
//
// Transpose
//
template<class T>
inline void Matrix<T>::Transpose()
{
    const std::string rName="Matrix::Transpose/";
    //
    // in-place transposition
    // 
    T savedData;
    size_t savedIndex;
    const int BITS_PER_BYTE=8;
    //
    // transpose within allocation
    //
    size_t statusIndex=0;
    size_t numberTransposed=0;
    size_t numberStatusBits=m_numberOfRows*m_numberOfColumns;
    //
    // allocate an array of status bytes -- each bit corresponds to a transposed
    // index -- if the bit is on, the associated index has been transposed.
    //
    size_t numberStatusBytes=numberStatusBits/BITS_PER_BYTE + 1;
    unsigned char* status = new unsigned char[numberStatusBytes];
    if (!status)
    {
        std::ostringstream ostr;
        ostr << rName << "Allocation failed for " << numberStatusBytes 
             << " bytes.";
        throw UtilitiesException(ostr.str());
    }
    for (size_t index=0;index<numberStatusBytes;index++)
        status[index]=0;
    //
    // iterate until the number of transposed have been done (skip the last
    // one since it doesn't change)
    //
    size_t statusByte;
    size_t statusBit;
    size_t statusMask;
    while(numberTransposed<numberStatusBits-1)
    {
        //
        // find the first index not transposed by checking status
        //
        for (;statusIndex<numberStatusBits;statusIndex++)
        {
            //
            // get the correct status byte and bit position with byte
            //
            statusByte=statusIndex/BITS_PER_BYTE;
            statusBit=statusIndex%BITS_PER_BYTE;
            //
            // create a mask to check if the bit is on or off (on-transposed)
            //
            statusMask=1;
            statusMask=statusMask << statusBit;
            //
            // check status
            //
            if (status[statusByte] & statusMask)
                continue;
            else
                break;
        }
        //
        // given the statusIndex as a transposed index, calculate the
        // input index (see notes at end of module)
        //
        size_t tIndex=statusIndex++;
        size_t iIndex=(tIndex%m_numberOfRows)*m_numberOfColumns +
                      tIndex/m_numberOfRows;    // see note at end of file
        //
        // in all cases we're essentially transposed so set the status
        // and increment number of transpositions
        //
        status[statusByte] |= statusMask;
        numberTransposed++;
        //
        // if the index's are the same (first and last elements), just continue
        //
        if (iIndex==tIndex)
        {
            continue;
        }
        //
        // if not the same then save the data and index and loop to transpose
        // available index
        //
        else
        {
            savedIndex=tIndex;                  // saved index
            savedData=m_data[tIndex];           // saved data
            m_data[tIndex]=m_data[iIndex];      // copy
            tIndex=iIndex;                      // set transposed to input index
            //
            // ok, this is the complicated loop.  when we copy the input data to
            // the new transposed location, the source of the copy can now be used.
            // so, we iteratively do the following:
            //      1. calculate the new input index associated with the transposed
            //         index
            //      2. mark the transposed index as transposed and inc the number
            //         of transpositions
            //      3. if the new input index is the same as the saved index
            //         copy the saved data and break;
            //      4. else copy data from input index to transposed index and
            //         set the transposed index to the input index
            // 
            while (true)
            {
                //
                // we now want the next index from the existing one
                //
                iIndex=(tIndex%m_numberOfRows)*m_numberOfColumns +
                        tIndex/m_numberOfRows;  // see note at end of file
                //
                // Mark the tIndex as transposed by:
                //   1. finding the status bit and byte
                //   2. create a mask
                //   3. setting the status
                //
                statusByte=tIndex/BITS_PER_BYTE;    // find byte
                statusBit=tIndex%BITS_PER_BYTE;     // find bit

                statusMask=1;                       // create mask
                statusMask=statusMask << statusBit; // set bit in mask
                status[statusByte] |= statusMask;   // set status
                //
                // inc number of t's
                //
                numberTransposed++;
                //
                // check if we cycled around
                //
                if (iIndex==savedIndex)
                {
                    m_data[tIndex]=savedData;
                    break;
                }
                else
                {
                    m_data[tIndex]=m_data[iIndex];
                    tIndex=iIndex;
                }
            }
        }
    }
    size_t temp = m_numberOfRows;
    m_numberOfRows = m_numberOfColumns;
    m_numberOfColumns = temp;

    delete [] status;
}   
//
// ToVector
//
template<class T>
inline void Matrix<T>::ToVector(std::vector<T>& vd) const
{
    vd.resize(m_size);
    for (size_t index=0;index<m_size;index++)
        vd[index]=m_data[index];
}

//
// Print
//
template<class T>
inline void Matrix<T>::Print(std::ostream& out)
{
	size_t i;
	for(  i=0; i<NumberOfRows(); i++)
	{
		for(size_t j=0; j<NumberOfColumns(); j++)
		{
			out << m_data[i*m_numberOfColumns+j] << " ";
		}
		out << "\n";
	}
}



}
//============================== Notes =======================================
//1. Transpose
//
//  Given an input matrix with r rows and c columns, the transposed matrix
//  has r columns and c rows.  The relationship between the input matrix
//  and the transposed matrix is:
//      i(r1,c1) ==> t(c1,r1)
//
//  If we consider the matrix(2-d) as a 1-d vector (or array), we can use
//  our knowledge of row-major c/c++ memory to convert the array index
//  into a row and column id; and vica versa.  Given rowIndex and columnIndex
//  in a matrix, the index into the 1-d array/vector is:
//      index=rowIndex*numberOfColumns+columnIndex;
//  where
//      0 <= rowIndex < numberOfRows
//      0 <= columnIndex < numberOfColums
//
//  So now, given our 1-d array that really maps to a 2-d matrix, we
//  transpose the 2-d matrix by converting indices and copying data.  You
//  basically can either iterate over the input array and for each index
//  convert to a transposed index and copy data; or you can iterate over the
//  transposed data and for each index convert to the input index and copy
//  data.
//
//  If we consider the latter case above, we are given the following:
//      1. numberInputRows
//      2. numberInputColumns
//      3. transposedIndex
//  and we want to calculate:
//      4. inputIndex
//
//  The following equation can be used:
//  (1)    inputIndex=(transposedIndex%numberInputRows)*numberInputColumns+
//                     transposedIndex/numberInputRows;
//


#if _MSC_VER > 1399
#include "Matrix_bool.h"
#endif

#endif
