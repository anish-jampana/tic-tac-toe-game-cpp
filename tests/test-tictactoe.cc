#include <string>

#include <catch2/catch.hpp>
#include <tictactoe/tictactoe.h>

using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid string provided to constructor") {
  SECTION("String is too short") {
    REQUIRE_THROWS_AS(Board("xxooo"), std::invalid_argument);
  }

  SECTION("placeholder") {

  }
}

TEST_CASE("Boards with no winner") {
  SECTION("Full board with no winner") {
    REQUIRE(Board("xxoooxxxo").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Full board with no winner - ignore case") {
    REQUIRE(Board("oOxXXoOxO").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Incomplete board with no winner") {
    REQUIRE(Board("x.x.o..o.").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Incomplete board with no winner - ignore case") {
    REQUIRE(Board("X.x.O..o.").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Empty board with no winner") {
    REQUIRE(Board("---------").EvaluateBoard() == BoardState::NoWinner);
  }
}
