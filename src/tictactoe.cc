#include "tictactoe/tictactoe.h"

#include <stdexcept>
#include <string>

namespace tictactoe {

using std::string;
using std::vector;

Board::Board(const string& board) {
  if (board.length() != 9) {
    throw std::invalid_argument("The string provided is not a valid board.");
  }
  specificBoard = board;
  boardSideLength = (int)sqrt(specificBoard.length());
}

BoardState Board::EvaluateBoard() const { return BoardState::NoWinner; }

vector<vector<char>> Board::FillCharArray() {
  vector<vector<char>> array;
  int positionOnString = 0;
  for (int i = 0; i < boardSideLength; i++) {
    vector<char> row;
    for (int j = 0; j < boardSideLength; j++) {
      transform(specificBoard.begin(), specificBoard.end(),
                specificBoard.begin(), ::tolower);
      char letter = specificBoard[positionOnString];
      row.push_back(letter);
      positionOnString++;
    }
    array.push_back(row);
  }
  return array;
}

BoardState Board::CheckHorizontal(vector<vector<char>> vector) {
  int numOfXHorizontal = 0;
  int numOfOHorizontal = 0;

  BoardState isWinner = BoardState::NoWinner;

  for (int i = 0; i < boardSideLength; i++) {
    numOfXHorizontal = 0;
    numOfOHorizontal = 0;
    for (int j = 0; j < boardSideLength; j++) {
      if (vector.at(i).at(j) == 'x') {
        numOfXHorizontal++;
      } else if (vector.at(i).at(j) == 'o') {
        numOfOHorizontal++;
      }
      if (numOfXHorizontal == boardSideLength) {
        if (isWinner == BoardState::Owins ||
            isWinner == BoardState::UnreachableState) {
          isWinner = BoardState::UnreachableState;
        } else {
          isWinner = BoardState::Xwins;
        }
      } else if (numOfOHorizontal == boardSideLength) {
        if (isWinner == BoardState::Xwins ||
            isWinner == BoardState::UnreachableState) {
          isWinner = BoardState::UnreachableState;
        } else {
          isWinner = BoardState::Owins;
        }
      }
    }
  }
  return isWinner;
}

//BoardState Board::CheckVertical(vector<vector<char>> vector) {
//  int numOfXVertical = 0;
//  int numOfOVertical = 0;
//
//  BoardState isWinner = BoardState::NoWinner;
//
//  for (int i = 0; i < boardSideLength; i++) {
//    numOfXVertical = 0;
//    numOfOVertical = 0;
//    for (int j = 0; j < boardSideLength; j++) {
//      if (vector.at(j).at(i) == 'x') {
//        num
//      }
//    }
//  }
//}

}  // namespace tictactoe
