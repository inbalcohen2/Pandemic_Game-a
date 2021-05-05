
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"

using namespace std;
namespace pandemic {
  class Dispatcher: public Player{

    public:
      Dispatcher(Board board,City city):Player(board,city,"Dispatcher"){}
      Player& fly_direct(City city) override;
  };
}
