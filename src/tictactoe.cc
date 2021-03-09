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
  specific_board_ = board;
  transform(specific_board_.begin(), specific_board_.end(),
            specific_board_.begin(), ::tolower);
  board_side_length_ = (int)sqrt(specific_board_.length());
}

BoardState Board::EvaluateBoard() const {
  int numOfX = 0;
  int numOfO = 0;

  // counts the amount of Xs and Os in the board
  for (int position = 0; position < specific_board_.length(); position++) {
    if (specific_board_.at(position) == 'x') {
      numOfX++;
    } else if (specific_board_.at(position) =='o') {
      numOfO++;
    }
  }

  vector<vector<char>> boardArray = FillCharArray();

  if (abs(numOfO - numOfX) <= 1 && numOfO <= numOfX) {
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

    // to overcome edge case where O wins and numOfX > numOfO
    if (isWinner == BoardState::Owins && numOfX > numOfO) {
      isWinner = BoardState::UnreachableState;
    }
    return isWinner;
  } else {
    return BoardState::UnreachableState;
  }
}

vector<vector<char>> Board::FillCharArray() const {
  vector<vector<char>> array;
  int positionOnString = 0;
  for (int i = 0; i < board_side_length_; i++) {
    vector<char> row;
    for (int j = 0; j < board_side_length_; j++) {
      char letter = specific_board_[positionOnString];
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

  for (int i = 0; i < board_side_length_; i++) {
    numOfXHorizontal = 0;
    numOfOHorizontal = 0;
    for (int j = 0; j < board_side_length_; j++) {
      if (vector.at(i).at(j) == 'x') {
        numOfXHorizontal++;
      } else if (vector.at(i).at(j) == 'o') {
        numOfOHorizontal++;
      }
      if (numOfXHorizontal == board_side_length_) {
        if (isWinner == BoardState::Owins ||
            isWinner == BoardState::UnreachableState) {
          isWinner = BoardState::UnreachableState;
        } else {
          isWinner = BoardState::Xwins;
        }
      } else if (numOfOHorizontal == board_side_length_) {
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

  for (int i = 0; i < board_side_length_; i++) {
    numOfXVertical = 0;
    numOfOVertical = 0;
    for (int j = 0; j < board_side_length_; j++) {
      if (vector.at(j).at(i) == 'x') {
        numOfXVertical++;
      } else if (vector.at(j).at(i) == 'o') {
        numOfOVertical++;
      }
      if (numOfXVertical == board_side_length_) {
        if (isWinner == BoardState::Owins || isWinner == BoardState::UnreachableState) {
          isWinner = BoardState::UnreachableState;
        } else {
          isWinner = BoardState::Xwins;
        }
      } else if (numOfOVertical == board_side_length_) {
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

  for (int i = 0, j = 0; i < board_side_length_; i++, j++) {
    if (vector.at(i).at(j) == 'x') {
      numOfXDiagonal++;
    } else if (vector.at(i).at(j) == 'o') {
      numOfODiagonal++;
    }
    if (numOfXDiagonal == board_side_length_) {
      if (isWinner == BoardState::Owins || isWinner == BoardState::UnreachableState) {
        isWinner = BoardState::UnreachableState;
      } else {
        isWinner = BoardState::Xwins;
      }
    } else if (numOfODiagonal == board_side_length_) {
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

  for (int i = 0, j = board_side_length_ - 1; i < board_side_length_; i++, j--) {
    if (vector.at(i).at(j) == 'x') {
      numOfXDiagonal++;
    } else if (vector.at(i).at(j) == 'o') {
      numOfODiagonal++;
    }
    if (numOfXDiagonal == board_side_length_) {
      if (isWinner == BoardState::Owins || isWinner == BoardState::UnreachableState) {
        isWinner = BoardState::UnreachableState;
      } else {
        isWinner = BoardState::Xwins;
      }
    } else if (numOfODiagonal == board_side_length_) {
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
