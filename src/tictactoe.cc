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

BoardState Board::EvaluateBoard() const {
  int numOfX = 0;
  int numOfO = 0;

  // counts the amount of Xs and Os in the board
  for (int position = 0; position < specificBoard.length(); position++) {
    transform(specificBoard.begin(), specificBoard.end(),
              specificBoard.begin(), ::tolower);
    if (specificBoard.at(position) == 'x') {
      numOfX++;
    } else if (specificBoard.at(position) =='o') {
      numOfO++;
    }
  }

  vector<vector<char>> boardArray = FillCharArray();

  if (abs(numOfO - numOfX) <= 1) {
    BoardState isWinner = BoardState::NoWinner;

    // check if there is a winner horizontally
    isWinner = CheckHorizontal(boardArray);

    // check if there is a winner vertically
    if (isWinner == BoardState::NoWinner) {
      isWinner = CheckVertical(boardArray);
    }

    // check if there is a winner diagonally left to right
    if (isWinner == BoardState::NoWinner) {
      isWinner = CheckDiagonalLeftToRight(boardArray);
    }

    // check if there is a winner diagonally right to left
    if (isWinner == BoardState::NoWinner) {
      isWinner = CheckDiagonalRightToLeft(boardArray);
    }

    return isWinner;
  } else {
    return BoardState::UnreachableState;
  }
}

vector<vector<char>> Board::FillCharArray() const {
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

BoardState Board::CheckHorizontal(vector<vector<char>> vector) const {
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

BoardState Board::CheckVertical(vector<vector<char>> vector) const {
  int numOfXVertical = 0;
  int numOfOVertical = 0;

  BoardState isWinner = BoardState::NoWinner;

  for (int i = 0; i < boardSideLength; i++) {
    numOfXVertical = 0;
    numOfOVertical = 0;
    for (int j = 0; j < boardSideLength; j++) {
      if (vector.at(j).at(i) == 'x') {
        numOfXVertical++;
      } else if (vector.at(j).at(i) == 'o') {
        numOfOVertical++;
      }
      if (numOfXVertical == boardSideLength) {
        if (isWinner == BoardState::Owins || isWinner == BoardState::UnreachableState) {
          isWinner = BoardState::UnreachableState;
        } else {
          isWinner = BoardState::Xwins;
        }
      } else if (numOfOVertical == boardSideLength) {
        if (isWinner == BoardState::Xwins || isWinner == BoardState::UnreachableState) {
          isWinner = BoardState::UnreachableState;
        } else {
          isWinner = BoardState::Owins;
        }
      }
    }
  }
  return isWinner;
}

BoardState Board::CheckDiagonalLeftToRight(vector<vector<char>> vector) const {
  int numOfXDiagonal = 0;
  int numOfODiagonal = 0;

  BoardState isWinner = BoardState::NoWinner;

  for (int i = 0, j = 0; i < boardSideLength; i++, j++) {
    if (vector.at(i).at(j) == 'x') {
      numOfXDiagonal++;
    } else if (vector.at(i).at(j) == 'o') {
      numOfODiagonal++;
    }
    if (numOfXDiagonal == boardSideLength) {
      if (isWinner == BoardState::Owins || isWinner == BoardState::UnreachableState) {
        isWinner = BoardState::UnreachableState;
      } else {
        isWinner = BoardState::Xwins;
      }
    } else if (numOfODiagonal == boardSideLength) {
      if (isWinner == BoardState::Xwins || isWinner == BoardState::UnreachableState) {
        isWinner = BoardState::UnreachableState;
      } else {
        isWinner = BoardState::Owins;
      }
    }
  }
  return isWinner;
}

BoardState Board::CheckDiagonalRightToLeft(vector<vector<char>> vector) const {
  int numOfXDiagonal = 0;
  int numOfODiagonal = 0;

  BoardState isWinner = BoardState::NoWinner;

  for (int i = 0, j = boardSideLength - 1; i < boardSideLength; i++, j--) {
    if (vector.at(i).at(j) == 'x') {
      numOfXDiagonal++;
    } else if (vector.at(i).at(j) == 'o') {
      numOfODiagonal++;
    }
    if (numOfXDiagonal == boardSideLength) {
      if (isWinner == BoardState::Owins || isWinner == BoardState::UnreachableState) {
        isWinner = BoardState::UnreachableState;
      } else {
        isWinner = BoardState::Xwins;
      }
    } else if (numOfODiagonal == boardSideLength) {
      if (isWinner == BoardState::Xwins || isWinner == BoardState::UnreachableState) {
        isWinner = BoardState::UnreachableState;
      } else {
        isWinner = BoardState::Owins;
      }
    }
  }
  return isWinner;
}

}  // namespace tictactoe
