#include <iostream>
#include <cmath>
using namespace std;

class SudokuTable{

private:

  int ** table;
  int totalRows;
  int totalColumns;

  /*
  Given that the table utilizes a double pointer, this helper method sets the nextRow and nextColumn
  pointers to the row and column locations of the next value
  */
  void getnextIndex(int currRow, int currColumn,int * nextRow, int *nextColumn){

    if(currColumn < totalColumns-1){
      currColumn++;
    }
    else {
      currRow++;
      currColumn = 0;
    }
    *nextRow = currRow;
    *nextColumn = currColumn;

  }

public:

  SudokuTable(int numRows, int numColumns) : totalRows(numRows), totalColumns(numColumns){

    //creates the double pointer table
    table = new int * [totalRows];

    //initialized the rows to have columns
    for(int currentRow = 0; currentRow < totalRows; ++ currentRow)
      *(table+currentRow) = new int [totalColumns];

    //initialize each spot to 0
    for(int currRow = 0; currRow < totalRows; ++currRow)
      for(int currColumn = 0; currColumn < totalColumns; ++currColumn)
        *((*(table+currRow))+currColumn) = 0;

  }

  /*
  Provides easier access to sudoku table
  */
  int& operator()(int row, int column) {

   return *((*(table+row))+column);

  }


  /*
  Returns true is the number is in the current row
  */
  bool isInRow(int row, int number){

    for(int i = 0; i < totalColumns;++i)
      if(table[row][i] == number)
        return true;

    return false;

  }

  /*
  Returns true if the number is in the current column
  */
  bool isInColumn(int column, int number){

    for(int i = 0; i < totalRows; ++i)
      if(table[i][column] == number)
        return true;

    return false;

  }

  /*
  Returns true if the number is in the current sub box of table
  */
  bool isInBox(int currentRow, int currentColumn, int number){

    int rowStart = (currentRow/((int)sqrt(totalRows))) * ((int)sqrt(totalRows)) ;
    int columnStart = (currentColumn/((int)sqrt(totalColumns)))*((int)sqrt(totalColumns));

    for(int row = rowStart;row<rowStart+sqrt(totalRows); ++row )
      for(int column = columnStart; column < columnStart+sqrt(totalColumns); ++column)
        if(table[row][column] == number)
          return true;

    return false;

  }

  /*
  Prints the contents of the sudoku table at the given state
  */
  void printTable(){

    for(int i = 0; i < totalRows; ++i){
      for(int j = 0; j < totalColumns; ++j){
        cout << table[i][j] << "    ";
      }
      cout << endl;
      cout << endl;
    }

  }

  /*
  Uses recursion to fill the sudoku table while following the rules of the game
  */
  int fillSpot(int thisRow,int thisColumn,int startIndex){

    //table is full
    if(thisRow == totalRows && thisColumn == 0)
      return 1;

    //if the value was already previously given
    if(table[thisRow][thisColumn]!=0){
      int newRow;
      int newColumn;
      getnextIndex(thisRow,thisColumn,&newRow,&newColumn);
      return fillSpot(newRow,newColumn,1);
    }

    // to recall the index that we left off for the given row and column
    int lastIndex;

    //find next number that follows all three rules
    for(int i = startIndex; i <= totalRows; ++i){
      if(!isInRow(thisRow,i) && !isInColumn(thisColumn,i) && !isInBox(thisRow,thisColumn,i)){
        table[thisRow][thisColumn] = i;
        lastIndex = i;
        break;
      }
    }


    int successfull;

    //if no number can fit into location
    if(table[thisRow][thisColumn]==0){
      return -1;
    }
    else{
      int newRow;
      int newColumn;
      getnextIndex(thisRow,thisColumn,&newRow,&newColumn);
      successfull = fillSpot(newRow,newColumn,1);
    }

    //trying again witht the next number
    if(successfull == -1){
      table[thisRow][thisColumn] = 0;
      return fillSpot(thisRow,thisColumn,lastIndex+1);
    }

return 1;

}

  };


int main(void){

SudokuTable mytable = SudokuTable(9,9);

mytable(0,1) = 9;
mytable(0,3) = 8;
mytable(0,7) = 3;
mytable(1,1) = 8;
mytable(1,4) = 7;
mytable(1,5) = 1;
mytable(1,7) = 5;
mytable(2,1) = 2;
mytable(2,6) = 1;
mytable(2,8) = 9;
mytable(3,0) = 6;
mytable(3,2) = 1;
mytable(3,3) = 2;
mytable(4,5) = 7;
mytable(4,6) = 8;
mytable(4,8) = 3;
mytable(5,2) = 4;
mytable(5,4) = 5;
mytable(5,6) = 9;
mytable(6,0) = 3;
mytable(6,2) = 5;
mytable(6,6) = 6;
mytable(6,7) = 1;
mytable(7,0) = 7;
mytable(7,4) = 4;
mytable(7,5) = 6;
mytable(8,0) = 2;
mytable(8,4) = 3;
mytable(8,6) = 7;
mytable(8,7) = 4;

cout << endl;
cout << endl;
cout << "Before solving it " << endl;
cout << endl;
mytable.printTable();

if(mytable.fillSpot(0,0,1)==1){
  cout << endl;
  cout << endl;
  cout << "After solving it " << endl;
  cout << endl;
  mytable.printTable();
}else{
  cout << "Not solvable" << endl;
}


return 1;
}
