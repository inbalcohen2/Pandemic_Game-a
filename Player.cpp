#include "Player.hpp"

using namespace pandemic;

//Taking some city card.
Player& Player::take_card(City city){return *this;}
//Discovering a cure for a disease of a certain color. 
//To do this, you must be in a city that has a research station, and throw 5 colored cards of the disease.
Player& Player::discover_cure(Color color){return *this;}

//A function that returns the role of the player
string Player::role(){return "";}

//Moving from the current city to a nearby city
Player& Player::drive(City city){return *this;}

//Moving from the current city to the city of some card in his hand.
// To do this, throw the appropriate card to the city you are flying to.
Player& Player::fly_direct(City city){return *this;}

//Treatment of the disease - lowering one cube of disease from the city in which they are
//If a cure for the disease has already been discovered in the color of the city,
//removes all the disease cubes from the city that are in it
Player& Player::treat(City city){return *this;}

//Moving from the current city to any city. To do this, throw the appropriate card to the city you are in.
Player& Player::fly_charter(City city){return *this;}

//If there is a research station in the current city,
// you can fly to any other city that has a research station.
Player& Player::fly_shuttle(City city){return *this;}

//build a research station in the city in which they are located.
// To do this, throw the appropriate card to the city you are in.
Player& Player::build(){return *this;}
