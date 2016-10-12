#include "transposition.hh"

//
// purpose - transpose input strings for lpdf.sh
//
// input image: 
// page 1               page2
// -------------------  ------------------- 
// | a11 a12 ... a1n |  | b11 b12 ... b1n | 
// | a21 a22 ... a2n |  | b21 b22 ... b2n | 
// | ... aij ... ain |  | ... bij ... bin | 
// | am1 am2 ... amn |  | bm1 bm2 ... bmn | 
// -------------------  ------------------- ...
//
// actual input
// => a11 a12 ... aij ... amn b11 ... bij .. ...
//
//
// output image: 
// page 1               page2
// -------------------  ------------------- 
// | a11 a21 ... an1 |  | b11 b21 ... bn1 | 
// | a12 a22 ... an2 |  | b12 b22 ... bn2 | 
// | ... aji ... ani |  | ... bji ... bni | 
// | a1m a2m ... anm |  | b1m b2m ... bnm | 
// -------------------  ------------------- ...
//
// actual output
// => a11 a21 ... an1 a12 ... an2 ... aji ... anm b11 .. bji ...
//
//

using namespace std;
int main( int argc, char* argv[] )
{
  
  // number of argument must be 3 or larger
  if( argc <= 2 )
    return -1;

  // 1st ( except the name of execution file) is nup for pdfjam
  string nup = argv[1];

  // get a number of row and column from nup
  int row, column;
  GetRowColumnNum( nup, row, column );

  // for lpdf.sh
  // extracting row and column num in shell script is trouble,
  // so these are also done in this program
  if( (string)argv[2] == "row" )
    {
      cout << row;
      return 0;
    }
  
  if( (string)argv[2] == "column" )
    {
      cout << column;
      return 0;
    }

  // argument after 1st should be a pair, i.e. ( name of pdf file , page num )
  if( argc%2 != 0 )
    return -1;

  // store arguments after 1st one in vector anyway
  vector < string > vargv;
  for( int i=1; i<argc/2; i++ )
    vargv.push_back( (string)argv[i*2] + " " + argv[i*2+1] + " " );

  // this variable is used to output string to tarminal
  string target = "";

  // store argument pairs in 2D array ( row x column )
  vector < vector < string > > vvtarget_original(row);
  // transposed 2D array ( column x row )
  vector < vector < string > > vvtarget_transposed(column);

  int row_counter = 0, column_counter = 0;
  for( unsigned int i=0; i<vargv.size(); i++ )
    {

      // store i-th argument into (i,j) element
      vvtarget_original[row_counter].push_back( vargv[i] );
      column_counter++;

      // if this column is in next row, change!
      if( column_counter == column )
	{
	  column_counter = 0;
	  row_counter++;
	}

      // if this row is at the end, store results in "string target"
      // and re-initialize variables
      if( row_counter == row )
	{

	  column_counter = 0;
	  row_counter = 0;
	  
	  // store elements with transposition
	  for( unsigned int k=0; k<vvtarget_original[0].size(); k++ )
	    for( unsigned int j=0; j<vvtarget_original.size(); j++ )
	      vvtarget_transposed[k].push_back( vvtarget_original[j][k] );

	  // add all elements into "string target"
	  for( unsigned int j=0; j<vvtarget_transposed.size(); j++ )
	    for( unsigned int k=0; k<vvtarget_transposed[j].size(); k++ )
		target += vvtarget_transposed[j][k];

	  // erase all elements for next matrix
	  EraseVector2D( vvtarget_original );
	  EraseVector2D( vvtarget_transposed );
	}

      // if (#page to be accumulated) % (row*colum) != 0
      // some pages are remained
      // In this case, not transposed at this moment
      if( i == vargv.size()-1 )
	{

	  int remain_num = vargv.size() - row * column;
	  int counter = 0;

	  // loop over remained pages
	  for( unsigned int j=0; j<vvtarget_original.size(); j++ )
	    for( unsigned int k=0; k<vvtarget_original[0].size(); k++ )
	      {
		counter++;
		target += vvtarget_original[j][k];
		if( counter == remain_num )
		  {
		    j = vvtarget_original.size();
		    k = vvtarget_original[0].size();
		  }
	      }
	}
    }
  
  // this is the output of the result
  cout << target << endl;
  return 0;
}

void GetRowColumnNum( string nup , int& row, int& column )
{
  istringstream iss_row( nup.substr( nup.find( "x" )+1, nup.size() - nup.find( "x" ) ) );
  iss_row >> row;

  istringstream iss_column( nup.substr( 0 , nup.find( "x" ) ) );  
  iss_column >> column;
}

void EraseVector2D( vector < vector < string > >& vec )
{
  for( unsigned int i=0; i<vec.size(); i++ )
    vec[i].erase( vec[i].begin(), vec[i].end() );
}
