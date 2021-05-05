
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"

using namespace std;
namespace pandemic {
  class Medic: public Player{

    public:
      Medic(Board board,City city):Player(board,city,"Medic"){}
      Player& treat(City city) override;
  };
}
