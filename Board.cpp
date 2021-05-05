#include "Board.hpp"
using namespace pandemic;

// Boolean function without parameters, which returns "true" if and only if the whole board is clean
// - there are no disease cubes.
   bool Board::is_clean(){
     return false;
   }
   // operator [] - accepts as a city ID parameter, 
   //and allows to read and update the level of disease in that city
   int & Board::operator[](City city){
     return map[city];
   }
   // A function that removes from the board all the drugs that have been discovered so far
  void Board::remove_cures(){

  }
  
   ostream& pandemic::operator<<(ostream& out,const Board& board){
     return out;
   }
