
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"

using namespace std;
namespace pandemic {
  class Scientist: public Player{
  private:
    int Number;
    public:
      Scientist(Board board,City city,int n):Player(board,city,"Scientist"),Number(n){}
      Player& discover_cure(Color color) override;
  };
}
