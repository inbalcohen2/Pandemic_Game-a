#pragma once

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <list>

using namespace std;

namespace pandemic{
  class Player{
      private:
        list<City> cards;
        City start;
        Board bord;
        string name_player;

      public:
        Player(Board& board,City city,string name):bord(board) ,start(city),name_player(name){}
        virtual Player& take_card(City city);
        virtual Player& discover_cure(Color color);
        string role();
        Player& drive(City city);
        virtual Player& fly_direct(City city);
        virtual Player& treat(City city);
        Player& fly_charter(City city);
        Player& fly_shuttle(City city);
        virtual Player& build();
      };
}
