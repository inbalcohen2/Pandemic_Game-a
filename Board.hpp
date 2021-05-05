#pragma once
#include <iostream>
#include <unordered_map>
#include "City.hpp"
#include "Color.hpp"
using namespace std;

namespace pandemic {
  class Board {
    private:
    unordered_map<City,int> map;
    unordered_map<City, unordered_map<City,Color>> graph;
    public:
    Board(){}
    bool is_clean();
    void remove_cures();
    int & operator[](City city);
    friend ostream& operator<<(ostream& out,const Board& board);
  };
}
