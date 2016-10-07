#ifndef LASAGNA_PDF_TRANSPOSITION_HH
#define LASAGNA_PDF_TRANSPOSITION_HH

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
using namespace std;
/*!
  @function int main( int argc, char* argv[] )
  @brief
  @details argument of main function should be : 
   1st   : nup for pdfjam ( ex. 2x2 )
   ith   : name of pdf file
   i+1th : page of the pdf file
   where i>=2
 */
int main( int argc, char* argv[] );

/*!
  @fn void GetRowColumnNum( string nup , int& row, int& column );
  @brief get row num and column num from nup
  @param nup should be "NxM" where N is a number of row and M is a number of column
*/
void GetRowColumnNum( string nup , int& row, int& column );

/*!
  @fn void EraseVector2D( vector < vector < string > >& vec );
  @brief erase vector < string > element from vector < vector < string > >
  @details I just want to erase all element from 2D vector.
  vec.erase( vec.begin(), vec.end() ) erase reserved vector < string >.
  To avoid this, I erase each vector < string > 
*/
void EraseVector2D( vector < vector < string > >& vec );
#endif //LASAGNA_PDF_TRANSPOSITION_HH
