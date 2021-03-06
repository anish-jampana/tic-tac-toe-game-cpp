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

TEST_CASE("Boards that are unreachable") {
  SECTION("Full board with only Xs") {
    REQUIRE(Board("xxxxxxxxx").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Full board with only Xs - ignore case") {
    REQUIRE(Board("xXxXxXxXx").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Full board with only Os") {
    REQUIRE(Board("ooooooooo").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Full board with only Os - ignore case") {
    REQUIRE(Board("oOoOoOoOo").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Full board with two winners horizontal") {
    REQUIRE(Board("xxxOOO...").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Full board with two winners vertical") {
    REQUIRE(Board("xo-xo-xo-").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Full board with difference of x and o is > 1 - unfair turns") {
    REQUIRE(Board("XxXxxXooX").EvaluateBoard() == BoardState::UnreachableState);
  }
}