#include <string>

#include <catch2/catch.hpp>
#include <tictactoe/tictactoe.h>

using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid string provided to constructor") {
  SECTION("String is too short - length 8") {
    REQUIRE_THROWS_AS(Board("xxoooxxo"), std::invalid_argument);
  }
  SECTION("String is too large - length 10") {
    REQUIRE_THROWS_AS(Board("xxoooxxoox"), std::invalid_argument);
  }
  SECTION("Empty String input") {
    REQUIRE_THROWS_AS(Board(""), std::invalid_argument);
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
  SECTION("Full board where O wins horizontally and vertically") {
    REQUIRE(Board("oOooxXoXx").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Full board where O wins horizontally and diagonally") {
    REQUIRE(Board("xXoOoOoxx").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Full board where O wins vertically and diagonally") {
    REQUIRE(Board("oOxxoxXoo").EvaluateBoard() == BoardState::UnreachableState);
  }
}

TEST_CASE("Boards where X wins") {
  SECTION("Full board where X wins vertically") {
    REQUIRE(Board("XooxOxXXo").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("Incomplete board where X wins vertically") {
    REQUIRE(Board("oXOxX-OXO").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("Full board where X wins horizontally") {
    REQUIRE(Board("XXxOXOxoo").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("Incomplete board where X wins horizontally") {
    REQUIRE(Board("o.oXxX.xO").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("Full board where X wins diagonally") {
    REQUIRE(Board("XOxXxoOOX").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("Incomplete board where X wins diagonally") {
    REQUIRE(Board("Oox.X.x.o").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("Full board where X wins horizontally and vertically") {
    REQUIRE(Board("oxoxxxoxo").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("Full board where X wins horizontally and diagonally") {
    REQUIRE(Board("xOOxxxooX").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("Full board where X wins vertically and diagonally") {
    REQUIRE(Board("oXxoXOxxo").EvaluateBoard() == BoardState::Xwins);
  }
}

TEST_CASE("Boards where O wins") {
  SECTION("Full board where O wins vertically") {
    REQUIRE(Board("OxXoxoOoX").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("Incomplete board where O wins vertically") {
    REQUIRE(Board("XoxOo-xox").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("Full board where O wins horizontally") {
    REQUIRE(Board("OoOxOxoxx").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("Incomplete board where O wins horizontally") {
    REQUIRE(Board("x.XooO.oX").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("Full board where O wins diagonally") {
    REQUIRE(Board("oXOooxXxo").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("Incomplete board where O wins diagonally") {
    REQUIRE(Board("xxo.O.O.x").EvaluateBoard() == BoardState::Owins);
  }
}