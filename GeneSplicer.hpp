
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"

using namespace std;
namespace pandemic {
  class GeneSplicer: public Player{

    public:
      GeneSplicer(Board board,City city):Player(board,city,"GeneSplicer"){}
      Player& discover_cure(Color color) override;
  };
}
