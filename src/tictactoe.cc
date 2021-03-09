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

  vector<vector<char>> boardArray = FillGameBoard();

  if (abs(num_of_o - num_of_x) <= 1 && num_of_o <= num_of_x) {
    BoardState is_winner = BoardState::NoWinner;

    // check if there is a winner horizontally
    is_winner = CheckHorizontal(boardArray);

    // check if there is a winner vertically
    if (is_winner == BoardState::NoWinner) {
      is_winner = CheckVertical(boardArray);
    }

    // check if there is a winner diagonally left to right
    if (is_winner == BoardState::NoWinner) {
      is_winner = CheckDiagonalLeftToRight(boardArray);
    }

    // check if there is a winner diagonally right to left
    if (is_winner == BoardState::NoWinner) {
      is_winner = CheckDiagonalRightToLeft(boardArray);
    }

    // to overcome edge case where O wins and num_of_x > num_of_o
    if (is_winner == BoardState::Owins && num_of_x > num_of_o) {
      is_winner = BoardState::UnreachableState;
    }
    return is_winner;
  } else {
    return BoardState::UnreachableState;
  }
}

vector<vector<char>> Board::FillGameBoard() const {
  vector<vector<char>> game_board;
  int positionOnString = 0;
  for (int i = 0; i < board_side_length_; i++) {
    vector<char> row;
    for (int j = 0; j < board_side_length_; j++) {
      char letter = specific_board_[positionOnString];
      row.push_back(letter);
      positionOnString++;
    }
    game_board.push_back(row);
  }
  return game_board;
}

BoardState Board::CheckHorizontal(vector<vector<char>> game_board) const {
  int num_of_x_horizontal = 0;
  int num_of_o_horizontal = 0;

  BoardState is_winner = BoardState::NoWinner;

  for (int i = 0; i < board_side_length_; i++) {
    num_of_x_horizontal = 0;
    num_of_o_horizontal = 0;
    for (int j = 0; j < board_side_length_; j++) {
      if (game_board.at(i).at(j) == 'x') {
        num_of_x_horizontal++;
      } else if (game_board.at(i).at(j) == 'o') {
        num_of_o_horizontal++;
      }
      if (num_of_x_horizontal == board_side_length_) {
        if (is_winner == BoardState::Owins ||
            is_winner == BoardState::UnreachableState) {
          is_winner = BoardState::UnreachableState;
        } else {
          is_winner = BoardState::Xwins;
        }
      } else if (num_of_o_horizontal == board_side_length_) {
        if (is_winner == BoardState::Xwins ||
            is_winner == BoardState::UnreachableState) {
          is_winner = BoardState::UnreachableState;
        } else {
          is_winner = BoardState::Owins;
        }
      }
    }
  }
  return is_winner;
}

BoardState Board::CheckVertical(vector<vector<char>> game_board) const {
  int num_of_x_vertical = 0;
  int num_of_o_vertical = 0;

  BoardState is_winner = BoardState::NoWinner;

  for (int i = 0; i < board_side_length_; i++) {
    num_of_x_vertical = 0;
    num_of_o_vertical = 0;
    for (int j = 0; j < board_side_length_; j++) {
      if (game_board.at(j).at(i) == 'x') {
        num_of_x_vertical++;
      } else if (game_board.at(j).at(i) == 'o') {
        num_of_o_vertical++;
      }
      if (num_of_x_vertical == board_side_length_) {
        if (is_winner == BoardState::Owins || is_winner == BoardState::UnreachableState) {
          is_winner = BoardState::UnreachableState;
        } else {
          is_winner = BoardState::Xwins;
        }
      } else if (num_of_o_vertical == board_side_length_) {
        if (is_winner == BoardState::Xwins || is_winner == BoardState::UnreachableState) {
          is_winner = BoardState::UnreachableState;
        } else {
          is_winner = BoardState::Owins;
        }
      }
    }
  }
  return is_winner;
}

BoardState Board::CheckDiagonalLeftToRight(vector<vector<char>> game_board) const {
  int num_of_x_diagonal = 0;
  int num_of_o_diagonal = 0;

  BoardState is_winner = BoardState::NoWinner;

  for (int i = 0, j = 0; i < board_side_length_; i++, j++) {
    if (game_board.at(i).at(j) == 'x') {
      num_of_x_diagonal++;
    } else if (game_board.at(i).at(j) == 'o') {
      num_of_o_diagonal++;
    }
    if (num_of_x_diagonal == board_side_length_) {
      if (is_winner == BoardState::Owins || is_winner == BoardState::UnreachableState) {
        is_winner = BoardState::UnreachableState;
      } else {
        is_winner = BoardState::Xwins;
      }
    } else if (num_of_o_diagonal == board_side_length_) {
      if (is_winner == BoardState::Xwins || is_winner == BoardState::UnreachableState) {
        is_winner = BoardState::UnreachableState;
      } else {
        is_winner = BoardState::Owins;
      }
    }
  }
  return is_winner;
}

BoardState Board::CheckDiagonalRightToLeft(vector<vector<char>> game_board) const {
  int num_of_x_diagonal = 0;
  int num_of_o_diagonal = 0;

  BoardState is_winner = BoardState::NoWinner;

  for (int i = 0, j = board_side_length_ - 1; i < board_side_length_; i++, j--) {
    if (game_board.at(i).at(j) == 'x') {
      num_of_x_diagonal++;
    } else if (game_board.at(i).at(j) == 'o') {
      num_of_o_diagonal++;
    }
    if (num_of_x_diagonal == board_side_length_) {
      if (is_winner == BoardState::Owins || is_winner == BoardState::UnreachableState) {
        is_winner = BoardState::UnreachableState;
      } else {
        is_winner = BoardState::Xwins;
      }
    } else if (num_of_o_diagonal == board_side_length_) {
      if (is_winner == BoardState::Xwins || is_winner == BoardState::UnreachableState) {
        is_winner = BoardState::UnreachableState;
      } else {
        is_winner = BoardState::Owins;
      }
    }
  }
  return is_winner;
}

}  // namespace tictactoe
