#include "doctest.h"
#include <iostream>

#include "Player.hpp"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"
#include <sstream>
#include <stdexcept>

using namespace pandemic;
using namespace std;


TEST_CASE ("test board") {
     Board board;
            CHECK(board.is_clean() == true);
    board[Tehran] = 1;
            CHECK(board[Tehran] == 1);
    board[Mumbai] = 2;
            CHECK(board[Mumbai] == 2);
    board[SanFrancisco] = 3;

    //able to change
    board[Tehran] = 5;
            CHECK(board[Tehran] == 5);
    board[Mumbai] = 4;
            CHECK(board[Mumbai] == 4);
            CHECK(board.is_clean() == false);
}



/*Can "build" in any city he is in, without throwing a suitable city card.*/

//OperationsExpert
TEST_CASE("Test OperationsExpert"){
    Board board;
    OperationsExpert player {board, City::Bangkok};
     CHECK_NOTHROW(player.take_card(Cairo)
                                 .take_card(Istanbul)
                                 .take_card(SaoPaulo));
    CHECK_NOTHROW(player.build()); // not throwing any card- can build in any city
// the same check with another city
    CHECK_NOTHROW(player.drive(City::HongKong)); // this city close to Bangkok
    CHECK_NOTHROW(player.build());
    CHECK_THROWS(player.drive(City::Chicago));// He cannot drive to this city
// another check
    CHECK_NOTHROW(player.fly_direct(City::Istanbul));//He has the card for this city- throwing 1 card
    CHECK_THROWS(player.fly_charter(City::Paris)); //He does not have the card of this city

    board[Moscow] = 2; // Black
    CHECK_NOTHROW(player.drive(City::Moscow));
    CHECK_NOTHROW(player.build());
    CHECK_NOTHROW(player.treat(Moscow));
    CHECK_EQ(board[Moscow], 1);

}

/* When he is at a research station, he can perform a "fly_direct" 
operation to any city he wants, without throwing a city card.*/

// //Dispatcher
TEST_CASE("Test Dispatcher"){
    Board board;
     
    Dispatcher player {board, City::Atlanta};
    CHECK_NOTHROW(player.take_card(City::Algiers)
                        .take_card(City::Baghdad)
                        .take_card(City::Cairo)
                        .take_card(City::Delhi)
                        .take_card(City::Chicago)
                        .take_card(City::Bogota)
                        .take_card(City::Karachi));
    
    CHECK_NOTHROW(player.drive(City::Chicago));
    CHECK_NOTHROW(player.build()); // trowing 1 card
    CHECK_NOTHROW(player.fly_direct(City::Miami)); // no throwing any card 
    //There is no research station in the city he is in
    CHECK_THROWS(player.fly_direct(City::NewYork));  // He can not make a fly direct
    CHECK_NOTHROW(player.fly_direct(City::Bogota)); //throw 1 card
    player.take_card(City::Bogota);
    CHECK_NOTHROW(player.build());  // trowing 1 card
    CHECK_NOTHROW(player.fly_direct(City::NewYork)); //no throwing any card 
    CHECK_THROWS(player.drive(City::Paris));

}

/*Can perform a "discover_cure" operation with only n cards */
//Scientist
TEST_CASE("Test Scientist"){
    Board board;
   

    Scientist player {board, City:: Algiers, 4};
    CHECK_NOTHROW(player.take_card(City::Baghdad)
                        .take_card(City::Cairo)
                        .take_card(City::Delhi)
                        .take_card(City::Karachi)
                        .take_card(City::Montreal)
                        .take_card(City::Algiers)
                        .take_card(City::Milan));
      CHECK_NOTHROW(player.build());  // trowing 1 card
      CHECK_NOTHROW(player.discover_cure(Color::Black)); // throw 4 card
      player.take_card(City::NewYork);
      player.take_card(City::London);
      CHECK_NOTHROW(player.drive(City::Madrid)); // throw 1 card
      player.take_card(City::Madrid);
      CHECK_NOTHROW(player.build()); //throw 1 card
      CHECK_NOTHROW(player.discover_cure(Color::Blue)); // throw 4 card
      player.take_card(City::Algiers);
      // fly to shuttle another city that has a research station
      CHECK_NOTHROW(player.fly_shuttle(City::Algiers)); //not throw any card
}

/*Can perform a "discover_cure" operation in any city -
 does not have to be at a research station.*/
//Researcher
TEST_CASE("Test Researcher"){
    Board board;
    board[Algiers] = 3; 
    board[Madrid] = 2;
    board[Paris] = 2;


    Researcher player {board, City:: Algiers};
    CHECK_NOTHROW(player.take_card(City::Baghdad)
                        .take_card(City::Cairo)
                        .take_card(City::Delhi)
                        .take_card(City::Karachi)
                        .take_card(City::Montreal)
                        .take_card(City::Algiers)
                        .take_card(City::Milan));
      
      CHECK_NOTHROW(player.discover_cure(Color::Black)); // throw 5 card Black
     player.take_card(City::NewYork);
     player.take_card(City::London);
     player.take_card(City::Washington);
     player.take_card(City::Madrid);
     CHECK_NOTHROW(player.treat(Algiers)); 
     //In this city there was a discovery cure and therefore all the disease cubes were deleted
     CHECK_EQ(board[Algiers], 0);
     //CHECK_NOTHROW(player.discover_cure(Color::Blue)); // throw 5 card Blue
     player.take_card(City::Paris);
     player.take_card(City::Madrid);
     CHECK_NOTHROW(player.drive(City::Paris)); 
     CHECK_NOTHROW(player.build()); //throw 1 card
     CHECK_NOTHROW(player.treat(Paris)); // throw 1 card
     CHECK_EQ(board[Paris], 1);
}

/*When he performs a "treat" operation, 
he removes all the disease cubes from the city he is in, and not just one.
If a cure for the disease has already been discovered,
it automatically lowers all disease cubes from any city it is in, even without performing a "treat" action.*/
//Medic

TEST_CASE("Test Medic"){
    Board board;
    board[Tokyo] = 3; 
    board[Sydney] = 2;
    board[Miami] = 2;
    board[SanFrancisco] = 5;

    Medic player {board, City:: Tokyo};
    CHECK_NOTHROW(player.take_card(City::Tokyo)
                        .take_card(City::Sydney)
                        .take_card(City::Seoul)
                        .take_card(City::SanFrancisco)
                        .take_card(City::Miami));
     CHECK_NOTHROW(player.build()); //throw 1 card
     CHECK_NOTHROW(player.treat(Tokyo)); 
     CHECK_EQ(board[City::Tokyo], 0); // Healed all disease cubes
     CHECK_NOTHROW(player.drive(City::SanFrancisco)); 
     CHECK_NOTHROW(player.build());
     CHECK_NOTHROW(player.treat(SanFrancisco)); // throw 1 card-SanFrancisco
     CHECK_EQ(board[City::SanFrancisco], 0);//Healed all disease cubes
     CHECK_NOTHROW(player.fly_shuttle(City::Tokyo)); //There are research stations in the cities
}

/*Can do a "treat" operation, not only to be there in it,
 but in every city in the world - by throwing a card of that city.*/
 //Virologist

TEST_CASE("Test Virologist"){
    Board board;
    board[Tokyo] = 3; 
    board[Paris] = 2;
    board[Cairo] = 2;
    board[SanFrancisco] = 5;

    Virologist player {board, City:: SanFrancisco};
    CHECK_NOTHROW(player.take_card(City::Tokyo)
                        .take_card(City::Sydney)
                        .take_card(City::Seoul)
                        .take_card(City::SanFrancisco)
                        .take_card(City::Cairo)
                        .take_card(City::Osaka));
    
     CHECK_NOTHROW(player.build()); //throws 1 card- SanFrancisco
     CHECK_NOTHROW(player.fly_direct(City::Tokyo)); //throws 1 card- Tokyo
     player.take_card(City::SanFrancisco);
     CHECK_NOTHROW(player.treat(SanFrancisco)); 
     CHECK_EQ(board[City::SanFrancisco], 4); // Healed all disease cubes
     player.drive(City::Osaka);
     CHECK_NOTHROW(player.fly_charter(City::Cairo));
     CHECK_NOTHROW(player.build());
     player.take_card(City::Cairo);
     CHECK_NOTHROW(player.treat(Cairo)); // throws 1 card-SanFrancisco
     CHECK_EQ(board[City::Cairo], 1);

}

/*Can perform a "discover_cure" operation with the help of some 5 cards - 
 not necessarily from the color of the disease.*/
 //GeneSplicer
 TEST_CASE("Test GeneSplicer"){
    Board board;
     board[Madrid] = 4; 
    GeneSplicer player{board, City::  Madrid};
    
        //  takes mixed 6 cards
        player.take_card(City::  Paris)
              .take_card(City::  Madrid)
              .take_card(City::  Taipei)
              .take_card(City::  Tokyo)
              .take_card(City::  Bogota)
              .take_card(City::  Tehran)
              .take_card(City::  Jakarta);
        player.build(); // throws 1 card- Madrid
        CHECK_NOTHROW(player.discover_cure(Blue);); // can discover cure with 5 mixed colored cards
        player.drive(City::London);
        CHECK_THROWS(player.discover_cure(Black);); // didnt have 5 card
        player.take_card(City::London); 
        CHECK_NOTHROW(player.fly_charter(City::Madrid));
        CHECK_NOTHROW(player.treat(Madrid));
        CHECK_EQ(board[City::Madrid], 0);

    }

/*Can perform a "treat" operation not only in the city he is in 
 but in any city near the city he is in, without throwing a city card.*/
 //FieldDoctor
    TEST_CASE("Test FieldDoctor"){
    Board board;
    board[SaoPaulo] = 3; 
    board[BuenosAires] = 2;
    board[Madrid] = 2;
    board[MexicoCity] = 5;

    FieldDoctor player {board, City:: BuenosAires};
    CHECK_NOTHROW(player.take_card(City::Madrid)
                        .take_card(City::SaoPaulo)
                        .take_card(City::London)
                        .take_card(City::SanFrancisco)
                        .take_card(City::Paris));
     CHECK_NOTHROW(player.treat(SaoPaulo)); //  FieldDoctor treat a nearby town-without throwing a card
     CHECK_EQ(board[City::SaoPaulo], 2); 
     CHECK_NOTHROW(player.drive(City::Bogota)); 
     CHECK_NOTHROW(player.treat(MexicoCity)); //  FieldDoctor treat a nearby town-without throwing a card
     CHECK_EQ(board[City::MexicoCity], 4);//
     CHECK_NOTHROW(player.drive(City:: BuenosAires));
     CHECK_NOTHROW(player.treat(BuenosAires)); //  FieldDoctor treat in the city he is in-without throwing a card
     CHECK_EQ(board[City::BuenosAires], 1);//
    }