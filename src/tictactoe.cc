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
  int num_of_x = 0;
  int num_of_o = 0;

  // counts the amount of Xs and Os in the board
  for (int position = 0; position < specific_board_.length(); position++) {
    if (specific_board_.at(position) == 'x') {
      num_of_x++;
    } else if (specific_board_.at(position) =='o') {
      num_of_o++;
    }
  }

  vector<vector<char>> boardArray = FillCharArray();

  if (abs(num_of_o - num_of_x) <= 1 && num_of_o <= num_of_x) {
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

    // to overcome edge case where O wins and num_of_x > num_of_o
    if (isWinner == BoardState::Owins && num_of_x > num_of_o) {
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
  int num_of_x_horizontal = 0;
  int num_of_o_horizontal = 0;

  BoardState isWinner = BoardState::NoWinner;

  for (int i = 0; i < board_side_length_; i++) {
    num_of_x_horizontal = 0;
    num_of_o_horizontal = 0;
    for (int j = 0; j < board_side_length_; j++) {
      if (vector.at(i).at(j) == 'x') {
        num_of_x_horizontal++;
      } else if (vector.at(i).at(j) == 'o') {
        num_of_o_horizontal++;
      }
      if (num_of_x_horizontal == board_side_length_) {
        if (isWinner == BoardState::Owins ||
            isWinner == BoardState::UnreachableState) {
          isWinner = BoardState::UnreachableState;
        } else {
          isWinner = BoardState::Xwins;
        }
      } else if (num_of_o_horizontal == board_side_length_) {
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
  int num_of_x_vertical = 0;
  int num_of_o_vertical = 0;

  BoardState isWinner = BoardState::NoWinner;

  for (int i = 0; i < board_side_length_; i++) {
    num_of_x_vertical = 0;
    num_of_o_vertical = 0;
    for (int j = 0; j < board_side_length_; j++) {
      if (vector.at(j).at(i) == 'x') {
        num_of_x_vertical++;
      } else if (vector.at(j).at(i) == 'o') {
        num_of_o_vertical++;
      }
      if (num_of_x_vertical == board_side_length_) {
        if (isWinner == BoardState::Owins || isWinner == BoardState::UnreachableState) {
          isWinner = BoardState::UnreachableState;
        } else {
          isWinner = BoardState::Xwins;
        }
      } else if (num_of_o_vertical == board_side_length_) {
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
  int num_of_x_diagonal = 0;
  int num_of_o_diagonal = 0;

  BoardState isWinner = BoardState::NoWinner;

  for (int i = 0, j = 0; i < board_side_length_; i++, j++) {
    if (vector.at(i).at(j) == 'x') {
      num_of_x_diagonal++;
    } else if (vector.at(i).at(j) == 'o') {
      num_of_o_diagonal++;
    }
    if (num_of_x_diagonal == board_side_length_) {
      if (isWinner == BoardState::Owins || isWinner == BoardState::UnreachableState) {
        isWinner = BoardState::UnreachableState;
      } else {
        isWinner = BoardState::Xwins;
      }
    } else if (num_of_o_diagonal == board_side_length_) {
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
  int num_of_x_diagonal = 0;
  int num_of_o_diagonal = 0;

  BoardState isWinner = BoardState::NoWinner;

  for (int i = 0, j = board_side_length_ - 1; i < board_side_length_; i++, j--) {
    if (vector.at(i).at(j) == 'x') {
      num_of_x_diagonal++;
    } else if (vector.at(i).at(j) == 'o') {
      num_of_o_diagonal++;
    }
    if (num_of_x_diagonal == board_side_length_) {
      if (isWinner == BoardState::Owins || isWinner == BoardState::UnreachableState) {
        isWinner = BoardState::UnreachableState;
      } else {
        isWinner = BoardState::Xwins;
      }
    } else if (num_of_o_diagonal == board_side_length_) {
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
